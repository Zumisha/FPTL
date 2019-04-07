#include <assert.h>

#include <iostream>
#include <unordered_set>
#include <stack>
#include <mutex>
#include <string>
#include <boost/timer/timer.hpp>
#include <boost/chrono.hpp>

#include "Run.h"
#include "FScheme.h"
#include "WorkStealingQueue.h"

#undef max

namespace FPTL { 
namespace Runtime {

//-----------------------------------------------------------------------------
SExecutionContext::SExecutionContext()
		: Scheme(nullptr),
		  Parent(nullptr),
		  Ready(0),
		  Working(0),
		  Proactive(0),
		  NewProactiveLevel(0),
		  Canceled(0),
	      endPtr(nullptr),
		  argPos(0),
		  arity(0),
		  argNum(0),
		  mEvaluatorUnit(nullptr)
	{
		stack.reserve(10);
		controlStack.reserve(10);
	}

bool SExecutionContext::isReady() const
{
	return Ready.load(std::memory_order_acquire) == 1;
}

EvaluatorUnit * SExecutionContext::evaluator() const
{
	return mEvaluatorUnit;
}

CollectedHeap & SExecutionContext::heap() const
{
	return mEvaluatorUnit->heap();
}

const DataValue & SExecutionContext::getArg(int aIndex) const
{
	return stack.at(argPos + aIndex);
}

void SExecutionContext::push(const DataValue & aData)
{
	stack.push_back(aData);
	++arity;
}

void SExecutionContext::advance()
{
	argPos = stack.size() - arity;
	argNum = arity;
	arity = 0;
}

void SExecutionContext::unwind(size_t aArgPosOld, int aArity, size_t aPos)
{;
	for (int i = 0; i < arity; ++i)
	{
		stack[aPos + i] = stack[stack.size() - arity + i];
	}

	argPos = aArgPosOld;
	stack.resize(aPos + arity);
	arity += aArity;
}

void SExecutionContext::join()
{
	auto joined = mEvaluatorUnit->join();
	if (!joined->Canceled.load(std::memory_order_acquire))
		// Копируем результат.
		for (int i = 0; i < joined->arity; ++i)
		{
			push(joined->stack.at(joined->stack.size() - joined->arity + i));
		}

	delete joined;
}

//-----------------------------------------------------------------------------
EvaluatorUnit::EvaluatorUnit(SchemeEvaluator * aSchemeEvaluator)
	: mJobsCompleted(0),
	  mProactiveJobsCompleted(0),
	  mJobsCreated(0),
	  mProactiveJobsCreated(0),
	  mJobsStealed(0),
	  mProactiveJobsStealed(0),
	  mProactiveJobsMoved(0),
	  mProactiveJobsCanceled(0),
	  mEvaluator(aSchemeEvaluator),
	  mHeap(aSchemeEvaluator->garbageCollector()),
	  mCollector(aSchemeEvaluator->garbageCollector()),
	  mProactiveJobQueue(32)
{
}

void EvaluatorUnit::addJob(SExecutionContext * aContext)
{
	mJobsCreated++;
	mJobQueue.push(aContext);
}

SExecutionContext * EvaluatorUnit::stealJob()
{
	SExecutionContext * elem = nullptr;
	mJobQueue.steal(elem);
	return elem;
}

SExecutionContext * EvaluatorUnit::stealProactiveJob()
{
	SExecutionContext * elem = nullptr;
	mProactiveJobQueue.pop(elem);
	return elem;
}

void EvaluatorUnit::evaluateScheme()
{
	while (true)
	{
        try
        {
            boost::this_thread::interruption_point();
            schedule();
        }
        catch (boost::thread_interrupted)
        {
            break;
        }
	}
    
    static boost::mutex outputMutex;
    boost::lock_guard<boost::mutex> guard(outputMutex);

	// Выводим статистику.
	std::stringstream ss;
	Utils::FormatedOutput fo =  mEvaluator->getEvalConfig().Output();

	ss << "\n" << fo.Underlined("Thread ID") << " = " << boost::this_thread::get_id() << ". Jobs " << fo.Bold(fo.Cyan("created: ")) << mJobsCreated << ", " << fo.Bold(fo.Green("completed: ")) << mJobsCompleted << ", " << fo.Bold(fo.Magenta("stealed: ")) << mJobsStealed << ".";
	
	if (mEvaluator->getEvalConfig().Proactive())
		ss << "\nProactive jobs " << fo.Bold(fo.Cyan("created: ")) << mProactiveJobsCreated << ", " << fo.Bold(fo.Green("completed: ")) << mProactiveJobsCompleted << ", " << fo.Bold(fo.Magenta("stealed: ")) << mProactiveJobsStealed << ", " << fo.Bold(fo.Yellow("moved: ")) << mProactiveJobsMoved << ", " << fo.Bold(fo.Red("canceled: ")) << mProactiveJobsCanceled << ".";
	
	std::cout << ss.str();
}

void EvaluatorUnit::addForkJob(SExecutionContext * task)
{
	pendingTasks.push_back(task);
	if (task->Proactive.load(std::memory_order_acquire))
	{
		mProactiveJobQueue.push(task);
		mProactiveJobsCreated++;
	}
	else
	{
		addJob(task);
	}
}

SExecutionContext *EvaluatorUnit::join()
{
	// Перед возможным выполнением новой задачи проверяем, не запланирована ли сборка мусора.
	// Иначе может получаться ситуация, когда 1 поток порождает задания и сразу же их берёт на выполнение,
	// а все остальные ожидают сборки мусора.
	safePoint();

	SExecutionContext * joinTask = pendingTasks.back();

	if (joinTask->Proactive.load(std::memory_order_acquire))
	{
		joinTask->NewProactiveLevel.store(0, std::memory_order_release);
		if (!joinTask->Parent->Proactive.load(std::memory_order_acquire)) moveToMainOrder(joinTask);
	}
	
	while (!joinTask->Ready.load(std::memory_order_acquire))
	{
		schedule();
	}

	//joinTask->Parent->Childs.erase(joinTask);
	pendingTasks.pop_back();
	return joinTask;
}

void EvaluatorUnit::moveToMainOrder(SExecutionContext * movingTask)
{
	if (movingTask->Parent->Proactive.load(std::memory_order_acquire))
	{
		movingTask->Proactive.store(0, std::memory_order_release);
		if (!movingTask->Ready.load(std::memory_order_acquire) && !movingTask->Working.load(std::memory_order_acquire))
		{
			mJobQueue.push(movingTask);
			mProactiveJobsMoved++;
		}
		for (SExecutionContext * child : movingTask->Childs)
		{
			if (!child->NewProactiveLevel.load(std::memory_order_acquire))
				moveToMainOrder(child);
		}
	}
	movingTask->NewProactiveLevel.store(0, std::memory_order_release);
}

void EvaluatorUnit::cancelFromPendingEnd(const int backPos)
{
	SExecutionContext * cancelTask = pendingTasks.at(pendingTasks.size() - backPos);
	cancel(cancelTask);
	//Убираем из очереди ожидающих выполнения задач.
	pendingTasks.erase(pendingTasks.end() - backPos);
}

void EvaluatorUnit::cancel(SExecutionContext * cancelingTask)
{
	//cancelingTask->Parent->Childs.erase(cancelingTask);
	cancelingTask->Canceled.store(1, std::memory_order_release);
	if (!cancelingTask->Ready.load(std::memory_order_acquire))
	{	// Если задание ещё не выполнено, выставляем флаг готовности, чтобы никто не начал выполнение.
		cancelingTask->Ready.store(1, std::memory_order_release);
		// Если уже выполняется - запускаем процесс остановки.
		if (cancelingTask->Working.load(std::memory_order_acquire))
		{
			cancelingTask->cancel();
		}
		mProactiveJobsCanceled++;
	}
	for (SExecutionContext * child : cancelingTask->Childs)
	{
		cancel(child);
	}
}

void EvaluatorUnit::safePoint() const
{
	mCollector->safePoint();
}

void EvaluatorUnit::schedule()
{
	SExecutionContext * context = nullptr;

	// Берем задание из своей очереди.
	if (mJobQueue.pop(context))
	{
		context->run(this);
		mJobsCompleted++;
		// Выполнили задание - проверяем не запланированна ли сборка мусора.
		safePoint();
		return;
	}

	// Если это не удалось, ищем у кого-нибудь другого.
	context = mEvaluator->findJob(this);	
	if (context)
	{
		context->run(this);
		mJobsStealed++;
		mJobsCompleted++;
		// Выполнили задание - проверяем не запланированна ли сборка мусора.
		safePoint();
		return;
	}

	if (mEvaluator->getEvalConfig().Proactive())
	{
		// Если не нашли, берём задание из своей упреждающей очереди и выполняем, если оно не отменено.
		if (mProactiveJobQueue.pop(context) && !context->Ready.load(std::memory_order_acquire) && context->Proactive.load(std::memory_order_acquire))
		{
			context->Working.store(1, std::memory_order_release);
			context->run(this);
			mProactiveJobsCompleted++;
			// Выполнили задание - проверяем не запланированна ли сборка мусора.
			safePoint();
			return;
		}

		// Если не удалось, ищем упреждающую задачу у кого-нибудь другого и выполняем, если оно не отменено.
		context = mEvaluator->findProactiveJob(this);
		if (context && !context->Ready.load(std::memory_order_acquire) && context->Proactive.load(std::memory_order_acquire))
		{
			context->Working.store(1, std::memory_order_release);
			context->run(this);
			mProactiveJobsStealed++;
			mProactiveJobsCompleted++;
			// Выполнили задание - проверяем не запланированна ли сборка мусора.
			safePoint();
			return;
		}
	}

	// Если заданий нет - приостанавливаем поток.
	boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
	safePoint();
}

CollectedHeap & EvaluatorUnit::heap() const
{
	return mHeap;
}

void EvaluatorUnit::markDataRoots(ObjectMarker * marker)
{
	// Помечаем корни у всех заданий, взятых на выполнение текщим юнитом.
	for (SExecutionContext * ctx : runningTasks)
	{
		for (auto & data : ctx->stack)
		{
			data.getOps()->mark(data, marker);
		}
	}

	// Помечаем корни у всех форкнутых заданий, которые были выполнены.
	for (SExecutionContext * ctx : pendingTasks)
	{
		if (ctx->isReady())
		{
			for (auto & data : ctx->stack)
			{
				data.getOps()->mark(data, marker);
			}
		}
	}
}

void EvaluatorUnit::pushTask(SExecutionContext * task)
{
	runningTasks.push_back(task);
}

void EvaluatorUnit::popTask()
{
	runningTasks.pop_back();
}

//-----------------------------------------------------------------------------
SchemeEvaluator::SchemeEvaluator()
{
}

void SchemeEvaluator::stop()
{
    boost::lock_guard<boost::mutex> guard(mStopMutex);
    
	mThreadGroup.interrupt_all();
}

SExecutionContext * SchemeEvaluator::findJob(const EvaluatorUnit * aUnit)
{
	for (size_t i = 0; i < mEvaluatorUnits.size(); i++)
	{
		if (mEvaluatorUnits[i] != aUnit)
		{
			SExecutionContext * job = mEvaluatorUnits[i]->stealJob();
			if (job)
			{
				return job;
			}
		}
	}
	return nullptr;
}

SExecutionContext * SchemeEvaluator::findProactiveJob(const EvaluatorUnit * aUnit)
{
	for (size_t i = 0; i < mEvaluatorUnits.size(); i++)
	{
		if (mEvaluatorUnits[i] != aUnit)
		{
			SExecutionContext * job = mEvaluatorUnits[i]->stealProactiveJob();
			if (job)
			{
				return job;
			}
		}
	}
	return nullptr;
}

void SchemeEvaluator::markRoots(ObjectMarker * marker)
{
	for (EvaluatorUnit * unit : mEvaluatorUnits)
	{
		unit->markDataRoots(marker);
	}
}

GarbageCollector * SchemeEvaluator::garbageCollector() const
{
	return mGarbageCollector.get();
}

struct ControlContext : SExecutionContext
{
	ControlContext(SExecutionContext * target, SchemeEvaluator * evaluator)
		: mTarget(target),
		mEvaluator(evaluator)
	{}

	void run(EvaluatorUnit * evaluatorUnit) override
	{
		boost::timer::cpu_timer timer;

		mTarget->run(evaluatorUnit);
		mEvaluator->stop();

		elapsed_times = timer.elapsed();
	}

	boost::timer::cpu_times getWorkTime() const
	{
		return elapsed_times;
	}

private:
	SExecutionContext * mTarget;
	SchemeEvaluator * mEvaluator;
	boost::timer::cpu_times elapsed_times;
};

void SchemeEvaluator::run(SExecutionContext & program)
{
	GarbageCollector * collector = GarbageCollector::getCollector(mEvalConfig.NumCores(), this, mGcConfig);
	mGarbageCollector.reset(collector);

	// Создаем юниты выполнения.
	for (size_t i = 0; i < mEvalConfig.NumCores(); i++)
	{
		mEvaluatorUnits.push_back(new EvaluatorUnit(this));
	}

	std::cout.precision(15);
	ControlContext controlContext(&program, this);

	// Добавляем задание в очередь к первому потоку.
	mEvaluatorUnits[0]->addJob(&controlContext);

	// Защита от случая, когда поток завершит вычисления раньше, чем другие будут созданы.
	mStopMutex.lock();

	// Создаем потоки.
	for (size_t i = 0; i < mEvalConfig.NumCores(); ++i)
	{
		mThreadGroup.create_thread(boost::bind(&EvaluatorUnit::evaluateScheme, mEvaluatorUnits[i]));
	}
	mStopMutex.unlock();

	mThreadGroup.join_all();

	std::for_each(mEvaluatorUnits.begin(), mEvaluatorUnits.end(), [](auto unit) { delete unit; });
	mEvaluatorUnits.clear();

	std::cout << "\n\nTime: " << boost::timer::format(controlContext.getWorkTime(), 3, "%ws\n");
}

//-----------------------------------------------------------------------------

}} // FPTL::Runtime