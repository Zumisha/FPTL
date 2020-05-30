#include <iostream>
#include <mutex>
#include "Run.h"
#include "FScheme/FScheme.h"

#undef max

namespace FPTL {
	namespace Runtime {

		SchemeEvaluator::SchemeEvaluator()
		{
			mRunTimer.stop();
		}

		void SchemeEvaluator::abort()
		{
			StopRunTime();
			boost::lock_guard<boost::mutex> guard(mStopMutex);
			mWasErrors = true;
			mThreadGroup.interrupt_all();
		}

		void SchemeEvaluator::stop()
		{
			boost::lock_guard<boost::mutex> guard(mStopMutex);

			mThreadGroup.interrupt_all();
		}

		SExecutionContext * SchemeEvaluator::findJob(const EvaluatorUnit * aUnit)
		{
			for (auto& mEvaluatorUnit : mEvaluatorUnits)
			{
				if (mEvaluatorUnit != aUnit)
				{
					SExecutionContext * job = mEvaluatorUnit->stealJob();
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
			for (auto& mEvaluatorUnit : mEvaluatorUnits)
			{
				if (mEvaluatorUnit != aUnit)
				{
					SExecutionContext * job = mEvaluatorUnit->stealProactiveJob();
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
				mTarget->run(evaluatorUnit);
				mEvaluator->stop();
			}

		private:
			SExecutionContext * mTarget;
			SchemeEvaluator * mEvaluator;
		};

		void SchemeEvaluator::run(SExecutionContext & program)
		{
			GarbageCollector * collector = GarbageCollector::getCollector(mEvalConfig.NumCores(), this, mGcConfig);
			mGarbageCollector.reset(collector);

			// Создаем единицы выполнения.
			for (size_t i = 0; i < mEvalConfig.NumCores(); i++)
			{
				mEvaluatorUnits.push_back(new EvaluatorUnit(this));
			}

			ControlContext controlContext(&program, this);

			// Добавляем задание в очередь к первому потоку.
			mEvaluatorUnits[0]->addJob(&controlContext);

			mRunTimer.start();
			// Защита от случая, когда поток завершит вычисления раньше, чем другие будут созданы.
			mStopMutex.lock();
			// Создаем потоки.
			for (size_t i = 0; i < mEvalConfig.NumCores(); ++i)
			{
				mThreadGroup.create_thread(boost::bind(&EvaluatorUnit::evaluateScheme, mEvaluatorUnits[i]));
			}
			mStopMutex.unlock();

			mThreadGroup.join_all();

			if (mEvalConfig.Time()) {
				const auto& fo = mEvalConfig.Output();
				std::stringstream ss;
				ss << std::fixed << std::setprecision(3);

				const auto runTime = static_cast<double>(GetRunTime().wall) / 1000000000;
				const auto totalWallTime = runTime * mEvaluatorUnits.size();
				double totalWorkTime = 0;
				for (auto unit : mEvaluatorUnits)
				{
					totalWorkTime += unit->GetWorkTime().wall;
				}
				totalWorkTime /= 1000000000;
				ss << fo.Bold(fo.Yellow("\n\nTotal runtime: ")) << totalWallTime << "s. " <<
					fo.Bold(fo.Green("Total useful: ")) << totalWorkTime << "s. " <<
					fo.Bold(fo.Red("Total idle: ")) << totalWallTime - totalWorkTime << "s. " <<
					fo.Bold(fo.Green("\nRuntime: ")) << runTime << "s. " <<
					fo.Bold(fo.Cyan("Parallelization efficiency: ")) << (totalWorkTime - runTime) / (totalWallTime - runTime) * 100 << "%";

				static boost::mutex outputMutex;
				boost::lock_guard<boost::mutex> guard(outputMutex);
				std::cout << ss.str();				
			}
				
			for (auto unit : mEvaluatorUnits) { delete unit; }
			mEvaluatorUnits.clear();
		}
	}
}
