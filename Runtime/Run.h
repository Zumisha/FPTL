#pragma once

#include <vector>

#include <boost/thread.hpp>

#include "WorkStealingQueue.h"
#include "LockFreeWorkStealingQueue.h"
#include "CollectedHeap.h"
#include "GarbageCollector.h"

namespace FPTL { namespace Runtime {

struct SExecutionContext;
class FSchemeNode;
class SchemeEvaluator;

// Вычислитель схемы, привязан к конкретному потоку.
class EvaluatorUnit
{
public:
	friend struct SExecutionContext;

	EvaluatorUnit(SchemeEvaluator * aSchemeEvaluator);

	// Основная процедура, в которой произдводятс вычисления.
	void evaluateScheme();

	// Запуск независимого процесса выполнения задания.
	void fork(SExecutionContext * task);

	// Ожидание завершения процесса выполнения задания.
	SExecutionContext * join();

	// Ожидание завершения процесса выполнения "правильной" ветки.
	SExecutionContext * joinAnticipation(bool thenBr);

	// Запуск независимого процесса выполнения упреждающего задания.
	void forkAnticipation(SExecutionContext * task);

	// Проверка на необходимость выполнения системного действия (сборка мусора и т.п.).
	void safePoint();

	// Добавление нового задания в очередь.
	// Вызывается только из потока, к которому привязан или до его создания.
	void addJob(SExecutionContext * aContext);

	// Получение работы для другого потока.
	// Вызывается из любого потока.
	SExecutionContext * stealJob();

	// Добавление нового задания в очередь  упреждающих задач.
	// Вызывается только из потока, к которому привязан или до его создания.
	void addAnticipationJob(SExecutionContext * aContext);

	// Получение работы из очереди упреждающих задач для другого потока.
	// Вызывается из любого потока.
	SExecutionContext * stealAnticipationJob();

	// Поиск и выполнение задания.
	void schedule();

	CollectedHeap & heap() const;

	// Трассировка корней стека.
	void markDataRoots(ObjectMarker * marker);

	void pushTask(SExecutionContext * task);
	void popTask();

private:
	std::vector<SExecutionContext *> pendingTasks;
	std::vector<SExecutionContext *> runningTasks;

	int mJobsCompleted;
	int mJobsCompleted_a;
	int mJobsCreated;
	int mJobsCreated_a;
	int mJobsStealed;
	int mJobsStealed_a;
	LockFreeWorkStealingQueue<SExecutionContext *> mJobQueue;
	SchemeEvaluator * mEvaluator;
	mutable CollectedHeap mHeap;
	GarbageCollector * mCollector;
};

// Производит вычисления программы, заданной функциональной схемой.
// Порождает, владеет и управляет всеми потоками.
class SchemeEvaluator : public DataRootExplorer
{
public:
	SchemeEvaluator();

	void setGcConfig(const GcConfig & config){ mGcConfig = config; }

	// Запуск вычисления схемы.
	void runScheme(const FSchemeNode * aScheme, const FSchemeNode * aInputGenerator, int aNumEvaluators);

	void run(SExecutionContext & program, int numEvaluators);

	// Прерывать вычисления.
	void stop();

	// Взять задание у других вычислителей. Возвращает 0, если не получилось.
	SExecutionContext * findJob(const EvaluatorUnit * aUnit);

	// Взять упреждающую задачу у других вычислителей. Возвращает 0, если не получилось.
	SExecutionContext * findAnticipationJob(const EvaluatorUnit * aUnit);

	virtual void markRoots(ObjectMarker * marker);

	GarbageCollector * garbageCollector() const;

private:
	std::vector<EvaluatorUnit *> mEvaluatorUnits;
	boost::thread_group mThreadGroup;
    boost::mutex mStopMutex;
	std::unique_ptr<GarbageCollector> mGarbageCollector;
	GcConfig mGcConfig;
};

}} // FPTL::Runtime
