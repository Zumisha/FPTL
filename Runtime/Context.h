#pragma once

#include <vector>
#include <stack>

#include <atomic>
#include <boost/intrusive/list.hpp>

#include "Data.h"

namespace FPTL {
namespace Runtime {

//---------------------------------------------------------------------------------------------
class EvaluatorUnit;
class FSchemeNode;
class CollectedHeap;

// Контекст выполняения.
struct SExecutionContext
{
	// Указатель на схему.
	FSchemeNode * Scheme;

	// Указатель на дочерний контекст.
	SExecutionContext * Parent;

	// Флаг готовности задания.
	std::atomic<int> Ready;

	// Стек для работы с кортежами.
	std::vector<DataValue> stack;

	// Положение кортежа аргументов.
	int argPos;

	// Теущая арность операции.
	int arity;

	// Количество аргументов во входном кортеже.
	int argNum;

	// Объем памяти, выделенной до сборки мусора.
	size_t numAllocated;
	size_t prevAllocated;

	SExecutionContext();

	bool isReady() const;

	// Методы работы с данными.
	const DataValue & getArg(int index) const;
	void push(const DataValue & aData);
	void advance();
	void unwind(int aArgPosOld, int aArity, int aPos);

	// Запуск выполнения.
	void run(EvaluatorUnit * aEvaluatorUnit);

	// Порождение нового задания. После выполнения задания результат будет записан по адресу aResult.
	SExecutionContext * spawn(FSchemeNode * aFirstNode);

	EvaluatorUnit * evaluator() const;
	CollectedHeap & heap() const;
	 
private:
	EvaluatorUnit * mEvaluatorUnit;
};

// Интерфейс объектов с автоматическим управлением памятью.
class Collectable :
	public boost::intrusive::list_base_hook<>
{
	friend class CollectedHeap;

	CollectedHeap * myHeap;
};

} // Runtime
} // FPTL