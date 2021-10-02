#include <iostream>
#include <boost/format/format_fwd.hpp>

#include "Run.h"
#include "Macros.h"
#include "InternalForm/InternalForm.h"
#include "DataTypes/Ops/Ops.h"

namespace FPTL
{
	namespace Runtime
	{

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
			mWorkTimer.stop();
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
					mEvaluator->StopRunTime();
					break;
				}
#if !disableExceptionHandling
				catch (std::exception& e)
				{
					std::cerr << e.what() << std::endl
						<< "Execution aborted." << std::endl;
					mEvaluator->abort();
				}
				catch (...)
				{
					std::cerr << "Congratulations, you found the entrance to Narnia!" << std::endl
						<< "(Not std::exception error.)" << std::endl
						<< "Execution aborted." << std::endl;
					mEvaluator->abort();
				}
#endif
			}

			// Выводим статистику.
			auto evalConf = mEvaluator->getEvalConfig();
			if (evalConf.Info())
			{
				std::stringstream ss;
				ss << std::fixed << std::setprecision(3);
				const auto fo = evalConf.Output();
				ss << "\n" << fo.Underlined("Thread ID") << " = " << boost::this_thread::get_id() << ". Jobs " << fo.Bold(fo.Cyan("created: ")) << mJobsCreated << ", " << fo.Bold(fo.Green("completed: ")) << mJobsCompleted << ", " << fo.Bold(fo.Magenta("stolen: ")) << mJobsStealed << ".";

				if (evalConf.Proactive())
				{
					ss << "\nProactive jobs " << fo.Bold(fo.Cyan("created: ")) << mProactiveJobsCreated << ", " << fo.Bold(fo.Green("completed: ")) << mProactiveJobsCompleted << ", " << fo.Bold(fo.Magenta("stolen: ")) << mProactiveJobsStealed << ", " << fo.Bold(fo.Yellow("moved: ")) << mProactiveJobsMoved << ", " << fo.Bold(fo.Red("canceled: ")) << mProactiveJobsCanceled << ".";
				}

				const auto workTime = static_cast<double>(GetWorkTime().wall) / 1000000000;
				const auto runTime = static_cast<double>(mEvaluator->GetRunTime().wall) / 1000000000;
				const auto idleTime  = runTime - workTime;
				ss << fo.Bold(fo.Green("\nUseful work time: ")) << workTime << "s. " <<
					fo.Bold(fo.Red("Idle time: ")) << idleTime << "s. " <<
					fo.Bold(fo.Cyan(" Utilization: ")) << workTime / runTime * 100 << "%\n";
				
				static boost::mutex outputMutex;
				boost::lock_guard<boost::mutex> guard(outputMutex);
				std::cout << ss.str();
			}
		}

		void EvaluatorUnit::addForkJob(SExecutionContext * task)
		{
			if (task->Parent != nullptr && !task->Parent->Canceled.load(std::memory_order_acquire))
			{
				task->Parent->Childs.insert(task);
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
		}

		SExecutionContext *EvaluatorUnit::join()
		{
			// Отменена
			if (pendingTasks.empty())
				return new IFExecutionContext(new EndOp());

			auto joinTask = pendingTasks.back();

			if (joinTask->Proactive.load(std::memory_order_acquire))
			{
				joinTask->NewProactiveLevel.store(false, std::memory_order_release);
				if (!joinTask->Parent->Proactive.load(std::memory_order_acquire)) moveToMainOrder(joinTask);
			}

			while (!joinTask->Ready.load(std::memory_order_acquire))
			{
				schedule();
			}
			mWorkTimer.resume();

			//joinTask->Parent->Childs.erase(joinTask);
			pendingTasks.pop_back();
			return joinTask;
		}

		void EvaluatorUnit::moveToMainOrder(SExecutionContext * movingTask)
		{
			if (movingTask->Parent->Proactive.load(std::memory_order_acquire))
			{
				movingTask->Proactive.store(false, std::memory_order_release);
				if (!movingTask->Ready.load(std::memory_order_acquire) && !movingTask->Working.load(std::memory_order_acquire))
				{
					mJobQueue.push(movingTask);
					mProactiveJobsMoved++;
				}
				for (auto child : movingTask->Childs)
				{
					if (!child->NewProactiveLevel.load(std::memory_order_acquire))
						moveToMainOrder(child);
				}
			}
			movingTask->NewProactiveLevel.store(false, std::memory_order_release);
		}

		void EvaluatorUnit::cancelFromPendingEnd(const size_t pos)
		{
			if (!pendingTasks.empty() && pendingTasks.size() >= pos)
			{
				const auto cancelTask = pendingTasks.at(pendingTasks.size() - pos);
				if (!cancelTask->Canceled.load(std::memory_order_acquire)) cancel(cancelTask);

				while (!cancelTask->Ready.load(std::memory_order_acquire))
				{
					schedule();
				}
				mWorkTimer.resume();

				//Убираем из очереди ожидающих выполнения задач.
				pendingTasks.erase(pendingTasks.end() - pos);
			}
		}

		void EvaluatorUnit::cancel(SExecutionContext * cancelingTask)
		{
			// Чтобы никто не начал выполнение.
			cancelingTask->Canceled.store(true, std::memory_order_release);

			if (!cancelingTask->Ready.load(std::memory_order_acquire))
			{
				//cancelingTask->arity = 0;
				// Если уже выполняется - запускаем процесс остановки.
				if (cancelingTask->Working.load(std::memory_order_acquire))
				{
					cancelingTask->cancel();
				}
				mProactiveJobsCanceled++;
				cancelingTask->Ready.store(true, std::memory_order_release);
			}
			for (auto child : cancelingTask->Childs)
			{
				if (!child->Canceled.load(std::memory_order_acquire)) cancel(child);
			}
		}

		void EvaluatorUnit::safePoint()
		{
			if (mCollector->needGC())
			{
				mWorkTimer.stop();
				mCollector->safePoint();
			}
		}

		void EvaluatorUnit::schedule()
		{
			// Перед выполнением задачи проверяем, не запланирована ли сборка мусора.
			safePoint();

			SExecutionContext * context = nullptr;

			// Берем задание из своей очереди.
			if (mJobQueue.pop(context))
			{
				mWorkTimer.resume();
				context->run(this);
				mJobsCompleted++;
				return;
			}

			// Если это не удалось, ищем у кого-нибудь другого.
			context = mEvaluator->findJob(this);
			if (context)
			{
				mWorkTimer.resume();
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
					mWorkTimer.resume();
					context->Working.store(true, std::memory_order_release);
					context->run(this);
					mProactiveJobsCompleted++;
					return;
				}

				// Если не удалось, ищем упреждающую задачу у кого-нибудь другого и выполняем, если оно не отменено.
				context = mEvaluator->findProactiveJob(this);
				if (context && !context->Canceled.load(std::memory_order_acquire) && context->Proactive.load(std::memory_order_acquire))
				{
					mWorkTimer.resume();
					context->Working.store(true, std::memory_order_release);
					context->run(this);
					mProactiveJobsStealed++;
					mProactiveJobsCompleted++;
					return;
				}
			}

			// Если заданий нет - приостанавливаем поток.
			mWorkTimer.stop();
			boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
		}

		CollectedHeap & EvaluatorUnit::heap() const
		{
			return mHeap;
		}

		void EvaluatorUnit::markDataRoots(ObjectMarker * marker)
		{
			// Помечаем корни у всех заданий, взятых на выполнение текущим юнитом.
			for (auto ctx : runningTasks)
			{
				for (auto & data : ctx->stack)
				{
					data.getOps()->mark(data, marker);
				}
			}

			// Помечаем корни у всех созданных заданий, которые были выполнены.
			for (auto ctx : pendingTasks)
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
	}
}
