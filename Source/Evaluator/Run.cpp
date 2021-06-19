#include <iostream>
#include <mutex>
#include "Run.h"

#include "Macros.h"
#include "FScheme/FScheme.h"

namespace FPTL::Runtime
{

	SchemeEvaluator::SchemeEvaluator()
	{
		mRunTimer.stop();
	}

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
		mRunTimer.stop();

		PrintStatistic();

		for (auto* unit : mEvaluatorUnits) { delete unit; }
		mEvaluatorUnits.clear();
	}

	void SchemeEvaluator::PrintStatistic() const
	{
		if (!mWasErrors)
		{
			// Выводим статистику.
			std::stringstream ss;
			ss << std::fixed << std::setprecision(3);
			const auto fo = mEvalConfig.Output();
			const auto runTime = fromNano(mRunTimer.elapsed().wall);

			for (auto* unit : mEvaluatorUnits)
			{
				if (mEvalConfig.Info())
				{
					ss << std::endl << fo.Underlined("Thread ID") << " = " << unit->GetThreadId()
						<< ". Jobs " << fo.Bold(fo.Cyan("created: ")) << unit->GetCreatedJobsCount() << ", "
						<< fo.Bold(fo.Green("completed: ")) << unit->GetCompletedJobsCount() << ", "
						<< fo.Bold(fo.Magenta("stolen: ")) << unit->GetStealedJobsCount() << "." << std::endl;

					if (mEvalConfig.Proactive())
					{
						ss << "Proactive jobs " << fo.Bold(fo.Cyan("created: ")) << unit->GetCreatedProactiveJobsCount() << ", "
							<< fo.Bold(fo.Green("completed: ")) << unit->GetCompletedProactiveJobsCount() << ", "
							<< fo.Bold(fo.Magenta("stolen: ")) << unit->GetStealedProactiveJobsCount() << ", "
							<< fo.Bold(fo.Yellow("moved: ")) << unit->GetMovedProactiveJobsCount() << ", "
							<< fo.Bold(fo.Red("canceled: ")) << unit->GetCanceledProactiveJobsCount() << "." << std::endl;
					}
				}

				if (mEvalConfig.Time())
				{
					const auto workTime = fromNano(unit->GetWorkTime().wall);
					const auto idleTime = runTime - workTime;
					ss << fo.Bold(fo.Green("Useful work time: ")) << workTime << "s. " <<
						fo.Bold(fo.Red("Idle time: ")) << idleTime << "s. " <<
						fo.Bold(fo.Cyan(" Utilization: ")) << workTime / runTime * 100 << "%" << std::endl;
				}
			}

			if (mEvalConfig.Info())
			{
				size_t totalCreated = 0;
				size_t totalStolen = 0;
				for (auto* unit : mEvaluatorUnits)
				{
					totalCreated += unit->GetCreatedJobsCount();
					totalStolen += unit->GetStealedJobsCount();
				}

				ss << std::endl << "Total jobs " << fo.Bold(fo.Cyan("created: ")) << totalCreated
					<< fo.Bold(fo.Magenta(", stolen: ")) << totalStolen;

				if (mEvalConfig.Proactive())
				{
					size_t totalProactiveCreated = 0;
					size_t totalProactiveStolen = 0;
					size_t totalProactiveMoved = 0;
					size_t totalProactiveCanceled = 0;
					for (auto* unit : mEvaluatorUnits)
					{
						totalProactiveCreated += unit->GetCreatedProactiveJobsCount();
						totalProactiveStolen += unit->GetStealedProactiveJobsCount();
						totalProactiveMoved += unit->GetMovedProactiveJobsCount();
						totalProactiveCanceled += unit->GetCanceledProactiveJobsCount();
					}
					
					ss << std::endl << "Total proactive jobs " << fo.Bold(fo.Cyan("created: ")) << totalProactiveCreated
						<< fo.Bold(fo.Magenta(", stolen: ")) << totalProactiveStolen
						<< fo.Bold(fo.Yellow(", moved: ")) << totalProactiveMoved
						<< fo.Bold(fo.Red(", canceled: ")) << totalProactiveCanceled;
				}
			}

			if (mEvalConfig.Time())
			{
				const auto totalWallTime = runTime * mEvaluatorUnits.size();
				double totalWorkTime = 0;
				for (auto* unit : mEvaluatorUnits)
				{
					totalWorkTime += unit->GetWorkTime().wall;
				}
				totalWorkTime = fromNano(totalWorkTime);

				ss << std::endl << fo.Bold(fo.Yellow("Total work time: ")) << totalWallTime << "s. "
					<< fo.Bold(fo.Green("Total useful: ")) << totalWorkTime << "s. "
					<< fo.Bold(fo.Red("Total idle: ")) << totalWallTime - totalWorkTime << "s. " << std::endl
					<< fo.Bold(fo.Green("Runtime: ")) << runTime << "s. "
					<< fo.Bold(fo.Cyan("Parallelization efficiency: "))
					<< (totalWorkTime - runTime) / (totalWallTime - runTime) * 100 << "%";
			}

			ss << std::endl;
			std::cout << ss.str();
		}
	}
}
