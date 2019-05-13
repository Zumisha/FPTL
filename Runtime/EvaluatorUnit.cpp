#include <iostream>

#include "Run.h"

namespace FPTL {
namespace Runtime {

EvaluatorUnit::EvaluatorUnit(SchemeEvaluator * aSchemeEvaluator)
	: mJobsCompleted(0),
	mProactiveJobsCompleted(0),
	mJobsCreated(0),
	mProactiveJobsCreated(0),
	mJobsStealed(0),
	mProactiveJobsStealed(0),
	mProactiveJobsMoved(0),
	mProactiveJobsCanceled(0),
	mProactiveJobQueue(32),
	mEvaluator(aSchemeEvaluator),
	mHeap(aSchemeEvaluator->garbageCollector()),
	mCollector(aSchemeEvaluator->garbageCollector())
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
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	static boost::mutex outputMutex;
	boost::lock_guard<boost::mutex> guard(outputMutex);

	// Выводим статистику.
	std::stringstream ss;
	Utils::FormatedOutput fo = mEvaluator->getEvalConfig().Output();

	ss << "\n" << fo.Underlined("Thread ID") << " = " << boost::this_thread::get_id() << ". Jobs " << fo.Bold(fo.Cyan("created: ")) << mJobsCreated << ", " << fo.Bold(fo.Green("completed: ")) << mJobsCompleted << ", " << fo.Bold(fo.Magenta("stolen: ")) << mJobsStealed << ".";

	if (mEvaluator->getEvalConfig().Proactive())
		ss << "\nProactive jobs " << fo.Bold(fo.Cyan("created: ")) << mProactiveJobsCreated << ", " << fo.Bold(fo.Green("completed: ")) << mProactiveJobsCompleted << ", " << fo.Bold(fo.Magenta("stolen: ")) << mProactiveJobsStealed << ", " << fo.Bold(fo.Yellow("moved: ")) << mProactiveJobsMoved << ", " << fo.Bold(fo.Red("canceled: ")) << mProactiveJobsCanceled << ".";

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
	if (!cancelTask->Canceled.load(std::memory_order_acquire)) cancel(cancelTask);

	while (!cancelTask->Ready.load(std::memory_order_acquire))
	{
		schedule();
	}

	//Убираем из очереди ожидающих выполнения задач.
	pendingTasks.erase(pendingTasks.end() - backPos);
}

void EvaluatorUnit::cancel(SExecutionContext * cancelingTask)
{
	cancelingTask->Canceled.store(1, std::memory_order_release); // Чтобы никто не начал выполнение.
	if (!cancelingTask->Ready.load(std::memory_order_acquire))
	{
		//cancelingTask->arity = 0;
		// Если уже выполняется - запускаем процесс остановки.
		if (cancelingTask->Working.load(std::memory_order_acquire))
		{
			cancelingTask->cancel();
		}
		mProactiveJobsCanceled++;
		cancelingTask->Ready.store(1, std::memory_order_release);
	}
	for (SExecutionContext * child : cancelingTask->Childs)
	{
		if (!child->Canceled.load(std::memory_order_acquire)) cancel(child);
	}
}

void EvaluatorUnit::safePoint() const
{
	mCollector->safePoint();
}

void EvaluatorUnit::schedule()
{
	// Перед выполнением задачи проверяем, не запланированна ли сборка мусора.
	safePoint();

	SExecutionContext * context = nullptr;

	// Берем задание из своей очереди.
	if (mJobQueue.pop(context))
	{
		context->run(this);
		mJobsCompleted++;
		return;
	}

	// Если это не удалось, ищем у кого-нибудь другого.
	context = mEvaluator->findJob(this);
	if (context)
	{
		context->run(this);
		mJobsStealed++;
		mJobsCompleted++;
		return;
	}

	if (mEvaluator->getEvalConfig().Proactive())
	{
		// Если не нашли, берём задание из своей упреждающей очереди и выполняем, если оно не отменено.
		if (mProactiveJobQueue.pop(context) && !context->Canceled.load(std::memory_order_acquire) && context->Proactive.load(std::memory_order_acquire))
		{
			context->Working.store(1, std::memory_order_release);
			context->run(this);
			mProactiveJobsCompleted++;
			return;
		}

		// Если не удалось, ищем упреждающую задачу у кого-нибудь другого и выполняем, если оно не отменено.
		context = mEvaluator->findProactiveJob(this);
		if (context && !context->Canceled.load(std::memory_order_acquire) && context->Proactive.load(std::memory_order_acquire))
		{
			context->Working.store(1, std::memory_order_release);
			context->run(this);
			mProactiveJobsStealed++;
			mProactiveJobsCompleted++;
			return;
		}
	}

	// Если заданий нет - приостанавливаем поток.
	boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
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

}}
