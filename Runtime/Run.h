#pragma once

#include <vector>

#include <boost/thread.hpp>
#include <boost/lockfree/stack.hpp>

#include "LockFreeWorkStealingQueue.h"
#include "CollectedHeap.h"
#include "GarbageCollector.h"
#include "Utils/FormatedOutput.h"

namespace FPTL {
namespace Runtime {

struct SExecutionContext;
class FSchemeNode;
class SchemeEvaluator;

//----------------------------------------------------------------------------
class EvalConfig
{
public:
	EvalConfig() :
		mOutput(new Utils::FormatedOutput()),
		mProactive(false),
		mNumCores(1)
	{}

	void SetOutput(Utils::FormatedOutput & fo)
	{ mOutput = fo; }

	void SetProactive(bool state)
	{ mProactive = state; }

	void SetNumCores(int numCores)
	{ mNumCores = numCores; }

	Utils::FormatedOutput Output()
	{ return mOutput; }

	bool Proactive()
	{ return mProactive; }

	int NumCores()
	{ return mNumCores; }

private:
	Utils::FormatedOutput mOutput;
	bool mProactive;
	int mNumCores;
};

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
	void moveToMainOrder(SExecutionContext * movingTask);

	// Ожидание завершения процесса выполнения последнего в очереди задания.
	SExecutionContext * join();

	//Отмена задания, стоящего в списке ожидающих выполнения на позиции pos с конца.
	void cancelFromPendingEnd(int pos = 1);

	//Отмена задания и всех его дочерних заданий.
	void cancel(SExecutionContext *cancelTask);

	// Проверка на необходимость выполнения системного действия (сборка мусора и т.п.).
	void safePoint() const;

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

	CollectedHeap & heap() const;

	// Трассировка корней стека.
	void markDataRoots(ObjectMarker * marker);

	void pushTask(SExecutionContext * task);
	void popTask();

private:
	std::vector<SExecutionContext *> pendingTasks;
	std::vector<SExecutionContext *> runningTasks;

	int mJobsCompleted;
	int mProactiveJobsCompleted;
	int mJobsCreated;
	int mProactiveJobsCreated;
	int mJobsStealed;
	int mProactiveJobsStealed;
	int mProactiveJobsMoved;
	int mProactiveJobsCanceled;
	LockFreeWorkStealingQueue<SExecutionContext *> mJobQueue;
	boost::lockfree::stack<SExecutionContext *> mProactiveJobQueue;
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

	void setEvalConfig(const EvalConfig & config) { mEvalConfig = config; }

	EvalConfig getEvalConfig() { return mEvalConfig; }

	void run(SExecutionContext & program);

	// Прервать вычисления.
	void stop();

	// Взять задание у других вычислителей. Возвращает нулевой указатель, если не получилось.
	SExecutionContext * findJob(const EvaluatorUnit * aUnit);

	// Взять упреждающую задачу у других вычислителей. Возвращает 0, если не получилось.
	SExecutionContext * findProactiveJob(const EvaluatorUnit * aUnit);

	void markRoots(ObjectMarker * marker) override;

	GarbageCollector * garbageCollector() const;

private:
	std::vector<EvaluatorUnit *> mEvaluatorUnits;
	boost::thread_group mThreadGroup;
    boost::mutex mStopMutex;
	std::unique_ptr<GarbageCollector> mGarbageCollector;
	GcConfig mGcConfig;
	EvalConfig mEvalConfig;
};

}} // FPTL::Runtime
