#pragma once

#include <thread>
#include <vector>

#include "LockFreeWorkStealingQueue.h"
#include "GC/CollectedHeap.h"
#include "GC/GarbageCollector.h"
#include "EvalConfig.h"
#include "Utils/Stopwatch.hpp"

namespace FPTL::Runtime {
	struct SExecutionContext;
	class FSchemeNode;
	class SchemeEvaluator;
	class CollectedHeap;

	class thread_interrupted : public std::exception {
	public:
		const char* what() const noexcept override { return "Thread interrupted"; }
	};

	// Вычислитель схемы, привязан к конкретному потоку.
	class EvaluatorUnit
	{
	public:
		friend struct SExecutionContext;

		explicit EvaluatorUnit(SchemeEvaluator * aSchemeEvaluator);

		// Основная процедура, в которой производятся вычисления.
		void evaluateScheme();

		// Запуск независимого процесса выполнения задания.
		void addForkJob(SExecutionContext * task);

		// Переместить задачу и все подзадачи в основную очередь.
		void moveToMainOrder(SExecutionContext * movingTask);

		// Ожидание завершения процесса выполнения последнего в очереди задания.
		SExecutionContext* join();

		//Отмена задания, стоящего в списке ожидающих выполнения на позиции pos с конца.
		void cancelFromPendingEnd(size_t pos = 1);

		//Отмена задания и всех его дочерних заданий.
		void cancel(SExecutionContext *cancelingTask);

		// Проверка на необходимость выполнения системного действия (сборка мусора и т.п.).
		void safePoint();

		// Добавление нового задания в очередь.
		// Вызывается только из потока, к которому привязан или до его создания.
		void addJob(SExecutionContext * aContext);

		// Получение работы для другого потока.
		// Вызывается из любого потока.
		SExecutionContext * stealJob();

		// Получение работы из очереди упреждающих задач для другого потока.
		// Вызывается из любого потока.
		SExecutionContext * stealProactiveJob();

		// Поиск и выполнение задания.
		void schedule();

		CollectedHeap& heap() const;

		// Трассировка корней стека.
		void markDataRoots(ObjectMarker * marker);

		void pushTask(SExecutionContext * task);
		void popTask();

		int64_t GetWorkTimeNano() const
		{
			return mWorkTimer.elapsed_nano();
		}

		size_t GetCompletedJobsCount() const
		{
			return mJobsCompleted;
		}

		size_t GetCompletedProactiveJobsCount() const
		{
			return mProactiveJobsCompleted;
		}

		size_t GetCreatedJobsCount() const
		{
			return mJobsCreated;
		}

		size_t GetCreatedProactiveJobsCount() const
		{
			return mProactiveJobsCreated;
		}

		size_t GetStealedJobsCount() const
		{
			return mJobsStealed;
		}

		size_t GetStealedProactiveJobsCount() const
		{
			return mJobsCompleted;
		}

		size_t GetMovedProactiveJobsCount() const
		{
			return mProactiveJobsMoved;
		}

		size_t GetCanceledProactiveJobsCount() const
		{
			return mProactiveJobsCanceled;
		}

		std::thread::id GetThreadId() const
		{
			return mThreadId;
		}

		void interrupt() {
			mIsInterrupted.store(true, std::memory_order_relaxed);
		}

		void interruption_point() {
			if (mIsInterrupted.load(std::memory_order_relaxed)) {
				// Сбрасываем флаг (если поток может быть перезапущен) и бросаем исключение
				mIsInterrupted.store(false, std::memory_order_relaxed);
				throw thread_interrupted();
			}
		}

	private:
		std::atomic<bool> mIsInterrupted{false};
		// Задачи, данные из которых ожидаются.
		// Они могут как всё ещё находиться в очереди, так и быть на выполнении
		std::vector<SExecutionContext *> pendingTasks;
		// Выполняемые задачи, в том числе ожидающие данных.
		std::vector<SExecutionContext *> runningTasks;

		std::thread::id mThreadId;
		size_t mJobsCompleted;
		size_t mProactiveJobsCompleted;
		size_t mJobsCreated;
		size_t mProactiveJobsCreated;
		size_t mJobsStealed;
		size_t mProactiveJobsStealed;
		size_t mProactiveJobsMoved;
		size_t mProactiveJobsCanceled;
		Stopwatch mWorkTimer;
		LockFreeWorkStealingQueue<SExecutionContext *> mJobQueue;
		LockFreeWorkStealingQueue<SExecutionContext *> mProactiveJobQueue;
		SchemeEvaluator * mEvaluator;
		mutable CollectedHeap mHeap;
		GarbageCollector * mCollector;
	};

	//----------------------------------------------------------------------------------

	// Производит вычисления программы, заданной функциональной схемой.
	// Порождает, владеет и управляет всеми потоками.
	class SchemeEvaluator : public DataRootExplorer
	{
	public:
		SchemeEvaluator();

		void setGcConfig(const GcConfig & config) { mGcConfig = config; }

		void setEvalConfig(const EvalConfig & config) { mEvalConfig = config; }

		EvalConfig getEvalConfig() const { return mEvalConfig; }

		void run(SExecutionContext & program);

		// Прервать вычисления.
		void abort();

		// Вычисления окончены.
		void stop();

		void interruptAll() const;

		// Взять задание у других вычислителей. Возвращает нулевой указатель, если не получилось.
		SExecutionContext * findJob(const EvaluatorUnit * aUnit) const;

		// Взять упреждающую задачу у других вычислителей. Возвращает 0, если не получилось.
		SExecutionContext * findProactiveJob(const EvaluatorUnit * aUnit) const;

		void markRoots(ObjectMarker * marker) override;

		GarbageCollector * garbageCollector() const;

		bool WasErrors() const
		{
			return mWasErrors;
		}

		int64_t GetWorkTimeNano() const
		{
			return mRunTimer.elapsed_nano();
		}

	private:

		void PrintStatistic() const;

		std::vector<EvaluatorUnit *> mEvaluatorUnits;
		std::vector<std::thread> mThreadGroup;
		std::mutex mStopMutex;
		std::unique_ptr<GarbageCollector> mGarbageCollector;
		GcConfig mGcConfig;
		EvalConfig mEvalConfig;
		Stopwatch mRunTimer;
		bool mWasErrors = false;
	};

}
