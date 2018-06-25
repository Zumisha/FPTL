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
	void addForkJob(SExecutionContext * task);

	// Переместить задачу и все подзадачи в основную очередь.
	void StartMoving(SExecutionContext * movingTask);

	// Переместить задачу и все подзадачи в основную очередь.
	void MoveJob(SExecutionContext * movingTask);

	// Ожидание завершения процесса выполнения последнего в очереди задания.
	SExecutionContext * join();

	//Отмена задания, стоящего в списке ожидающих выполнения на позиции pos с конца.
	void cancelFromPendingEnd(int pos = 1);

	//Отмена задания и всех его дочерних заданий.
	void cancel(SExecutionContext *cancelTask);

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
	SExecutionContext * stealAnticipationJob();

	// Получение работы из очереди упреждающих задач следующего уровня вложенности для другого потока.
	// Вызывается из любого потока.
	SExecutionContext * stealNextLevelAnticipationJob();

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
	int mAnticipationJobsCompleted;
	int mJobsCreated;
	int mAnticipationJobsCreated;
	int mJobsStealed;
	int mAnticipationJobsStealed;
	int mAnticipationJobsMoved;
	int mAnticipationJobsCanceled;
	LockFreeWorkStealingQueue<SExecutionContext *> mJobQueue;
	LockFreeWorkStealingQueue<SExecutionContext *> mAnticipationJobQueue;
	LockFreeWorkStealingQueue<SExecutionContext *> mNextLevelAnticipationJobQueue;
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

	// Взять упреждающую задачу более высокого уровня вложенности упреждения у других вычислителей. Возвращает 0, если не получилось.
	SExecutionContext * findNextLevelAnticipationJob(const EvaluatorUnit * aUnit);

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
