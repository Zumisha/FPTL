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

namespace FPTL { namespace Runtime {

//-----------------------------------------------------------------------------
SExecutionContext::SExecutionContext()
		: Scheme(nullptr),
		  Parent(nullptr),
		  Ready(0),
		  Working(0),
		  Anticipation(0),
		  NewAnticipationLevel(0),
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
	if (!joined->Canceled)
		// Копируем результат.
		for (int i = 0; i < joined->arity; ++i)
		{
			push(joined->stack.at(joined->stack.size() - joined->arity + i));
		}

	delete joined;
}

//-----------------------------------------------------------------------------
EvaluatorUnit::EvaluatorUnit(SchemeEvaluator * aSchemeEvaluator, const bool disableAnt)
	: mJobsCompleted(0),
	  mAnticipationJobsCompleted(0),
	  mJobsCreated(0),
	  mAnticipationJobsCreated(0),
	  mJobsStealed(0),
	  mAnticipationJobsStealed(0),
	  mAnticipationJobsMoved(0),
	  mAnticipationJobsCanceled(0),
	  mEvaluator(aSchemeEvaluator),
	  mHeap(aSchemeEvaluator->garbageCollector()),
	  mCollector(aSchemeEvaluator->garbageCollector()),
	  disableAnticipatory(disableAnt)
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

SExecutionContext * EvaluatorUnit::stealAnticipationJob()
{
	SExecutionContext * elem = nullptr;
	mAnticipationJobQueue.pop(elem);
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
	ss << "\n\033[4;37mThread ID\033[0m = " << boost::this_thread::get_id() << ". Jobs \033[1;36mcreated:\033[0m " << mJobsCreated << ", \033[1;32mcompleated:\033[0m " << mJobsCompleted << ", \033[1;35mstealed:\033[0m " << mJobsStealed << ".";
	if (!disableAnticipatory)
		ss << "\nAnticipation jobs \033[1;36mcreated:\033[0m " << mAnticipationJobsCreated << ", \033[1;32mcompleated:\033[0m " << mAnticipationJobsCompleted << ", \033[1;35mstealed:\033[0m " << mAnticipationJobsStealed << ", \033[1;33mmoved:\033[0m " << mAnticipationJobsMoved << ", \033[1;31mcanceled:\033[0m " << mAnticipationJobsCanceled << ".\033[0m";
	std::cout << ss.str();
}

void EvaluatorUnit::addForkJob(SExecutionContext * task)
{
	pendingTasks.push_back(task);
	if (task->Anticipation.load(std::memory_order_acquire))
	{
		mAnticipationJobQueue.push(task);
		mAnticipationJobsCreated++;
	}
	else
	{
		addJob(task);
	}
}

SExecutionContext *EvaluatorUnit::join()
{
	// Перед возможным выполнением новой задачи проверяем, не запланированна ли сборка мусора.
	// Иначе может получаться ситуация, когда 1 поток пораждает задания и сразу же их берёт на выполнение,
	// а все остальные ожидают сборки мусора.
	safePoint();

	SExecutionContext * joinTask = pendingTasks.back();

	if (joinTask->Anticipation.load(std::memory_order_acquire) && !joinTask->Parent->Anticipation.load(std::memory_order_acquire))
		moveToMainOrder(joinTask);
	
	while (!joinTask->Ready.load(std::memory_order_acquire))
	{
		schedule();
	}

	joinTask->Parent->Childs.erase(joinTask);
	pendingTasks.pop_back();
	return joinTask;
}

void EvaluatorUnit::moveToMainOrder(SExecutionContext * movingTask)
{
	if (movingTask->Parent->Anticipation.load(std::memory_order_acquire))
	{
		movingTask->Anticipation.store(0, std::memory_order_release);
		if (!movingTask->Ready && !movingTask->Working)
		{
			mJobQueue.push(movingTask);
			mAnticipationJobsMoved++;
		}
		for (SExecutionContext * child : movingTask->Childs)
		{
			if (!child->NewAnticipationLevel)
				moveToMainOrder(child);
		}
	}
	movingTask->NewAnticipationLevel.store(0, std::memory_order_release);
}

void EvaluatorUnit::cancelFromPendingEnd(const int backPos)
{
	static std::mutex outputMutex;
	SExecutionContext * cancelTask = pendingTasks.at(pendingTasks.size() - backPos);
	cancelTask->Parent->Childs.erase(cancelTask);
	outputMutex.lock();
	cancel(cancelTask);
	outputMutex.unlock();
	//Убираем из очереди ожидающих выполнения задач.
	pendingTasks.erase(pendingTasks.end() - backPos);
}

void EvaluatorUnit::cancel(SExecutionContext * cancelingTask)
{
	cancelingTask->Parent->Childs.erase(cancelingTask);
	cancelingTask->Canceled = 1;
	if (!cancelingTask->Ready)
	{	// Если задание ещё не выполнено, выставляем флаг готовности, чтобы никто не начал выполнение.
		cancelingTask->Ready = 1;
		// Если уже выполняется - запускаем процесс остановки.
		if (cancelingTask->Working.load(std::memory_order_acquire))
		{
			cancelingTask->cancel();
		}
		mAnticipationJobsCanceled++;
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

	if (!disableAnticipatory)
	{
		// Если не нашли, берём задание из своей упреждающей очереди и выполняем, если оно не отменено.
		if (mAnticipationJobQueue.pop(context) && !context->Ready.load(std::memory_order_acquire) && context->Anticipation.load(std::memory_order_acquire))
		{
			context->Working.store(1, std::memory_order_release);
			context->run(this);
			mAnticipationJobsCompleted++;
			// Выполнили задание - проверяем не запланированна ли сборка мусора.
			safePoint();
			return;
		}

		// Если не удалось, ищем упреждающую задачу у кого-нибудь другого и выполняем, если оно не отменено.
		context = mEvaluator->findAnticipationJob(this);
		if (context && !context->Ready.load(std::memory_order_acquire) && context->Anticipation.load(std::memory_order_acquire))
		{
			context->Working.store(1, std::memory_order_release);
			context->run(this);
			mAnticipationJobsStealed++;
			mAnticipationJobsCompleted++;
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

SExecutionContext * SchemeEvaluator::findAnticipationJob(const EvaluatorUnit * aUnit)
{
	for (size_t i = 0; i < mEvaluatorUnits.size(); i++)
	{
		if (mEvaluatorUnits[i] != aUnit)
		{
			SExecutionContext * job = mEvaluatorUnits[i]->stealAnticipationJob();
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

void SchemeEvaluator::run(SExecutionContext & program, const int numEvaluators, const bool disableAnt)
{
	GarbageCollector * collector = GarbageCollector::getCollector(numEvaluators, this, mGcConfig);
	mGarbageCollector.reset(collector);

	// Создаем юниты выполнения.
	for (size_t i = 0; i < numEvaluators; i++)
	{
		mEvaluatorUnits.push_back(new EvaluatorUnit(this, disableAnt));
	}

	std::cout.precision(15);
	ControlContext controlContext(&program, this);

	// Добавляем задание в очередь к первому потоку.
	mEvaluatorUnits[0]->addJob(&controlContext);

	// Защита от случая, когда поток завершит вычисления раньше, чем другие будут созданы.
	mStopMutex.lock();

	// Создаем потоки.
	for (size_t i = 0; i < numEvaluators; ++i)
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