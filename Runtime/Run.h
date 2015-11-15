#pragma once

#include <vector>

#include <boost/thread.hpp>

#include "WorkStealingQueue.h"
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
	void join(SExecutionContext * task, SExecutionContext * joinTask);

	// Проверка на необходимость выполнения системного действия (сборка мусора и т.п.).
	void safePoint();

	// Добавление нового задания в очередь.
	// Вызывается только из потока, к которому привязан или до его создания.
	void addJob(SExecutionContext * aContext);

	// Получение работы для другого потока.
	// Вызывается из любого потока.
	SExecutionContext * stealJob();

	// Поиск и выполнение задания.
	void schedule();

	CollectedHeap & heap() const;

	// Трассировка корней стека.
	void markDataRoots(ObjectMarker * marker);

private:
	void traceRoots();

private:
	std::vector<SExecutionContext *> pendingTasks;
	std::vector<SExecutionContext *> runningTasks;

	int mJobsCompleted;
	int mJobsCreated;
	int mJobsStealed;
	WorkStealingQueue<SExecutionContext *> mJobQueue;
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

	// Запуск вычисления схемы.
	void runScheme(const FSchemeNode * aScheme, const FSchemeNode * aInputGenerator, int aNumEvaluators);

	// Прерывать вычисления.
	void stop();

	// Взять задание у других вычислителей. Возвращает 0, если не получилось.
	SExecutionContext * findJob(const EvaluatorUnit * aUnit);

	virtual void markRoots(ObjectMarker * marker);

	GarbageCollector * garbageCollector() const;

private:
	std::vector<EvaluatorUnit *> mEvaluatorUnits;
	boost::thread_group mThreadGroup;
    boost::mutex mStopMutex;
	std::unique_ptr<GarbageCollector> mGarbageCollector;
};

}} // FPTL::Runtime
