#include <iostream>
#include <mutex>
#include "Run.h"
#include "FScheme/FScheme.h"

#undef max

namespace FPTL {
	namespace Runtime {

		SchemeEvaluator::SchemeEvaluator() = default;

		void SchemeEvaluator::abort()
		{
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

			// Защита от случая, когда поток завершит вычисления раньше, чем другие будут созданы.
			mStopMutex.lock();
			// Создаем потоки.
			for (size_t i = 0; i < mEvalConfig.NumCores(); ++i)
			{
				mThreadGroup.create_thread(boost::bind(&EvaluatorUnit::evaluateScheme, mEvaluatorUnits[i]));
			}
			mStopMutex.unlock();

			mThreadGroup.join_all();

			for (auto unit : mEvaluatorUnits) { delete unit; }
			mEvaluatorUnits.clear();
		}
	}
}
