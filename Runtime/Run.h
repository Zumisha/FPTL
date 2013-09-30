#pragma once

#include <vector>

#include <boost/thread.hpp>

#include "WorkStealingQueue.h"

namespace FPTL { namespace Runtime {

struct SExecutionContext;
class FSchemeNode;
class SchemeEvaluator;

// Вычислитель схемы, привязан к конкретному потоку.
class EvaluatorUnit
{
public:

	EvaluatorUnit(SchemeEvaluator * aSchemeEvaluator);

	// Основная процедура, в которой произдводятс вычисления.
	void evaluateScheme();

	// Добавление нового задания в очередь.
	// Вызывается только из потока, к которому привязан или до его создания.
	void addJob(SExecutionContext * aContext);

	// Получение работы для другого потока.
	// Вызывается из любого потока.
	SExecutionContext * stealJob();

	// Поиск и выполнение задания.
	void schedule();

private:

	int mJobsCompleted;
	int mJobsCreated;
	int mJobsStealed;
	WorkStealingQueue<SExecutionContext *> mJobQueue;
	SchemeEvaluator * mEvaluator;
};

// Производит вычисления программы, заданной функциональной схемой.
// Порождает, владеет и управляет всеми потоками.
class SchemeEvaluator
{
public:
	SchemeEvaluator();

	// Запуск вычисления схемы.
	void runScheme(const FSchemeNode * aScheme, const FSchemeNode * aInputGenerator, int aNumEvaluators);

	// Прерывать вычисления.
	void stop();

	// Взять задание у других вычислителей. Возвращает 0, если не получилось.
	SExecutionContext * findJob(const EvaluatorUnit * aUnit);

private:
	std::vector<EvaluatorUnit *> mEvaluatorUnits;
	boost::thread_group mThreadGroup;
};

}} // FPTL::Runtime
