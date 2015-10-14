#pragma once

#include <vector>
#include <stack>

#include <boost/atomic.hpp>

#include "Data.h"

namespace FPTL {
namespace Runtime {

//---------------------------------------------------------------------------------------------
class EvaluatorUnit;
class FSchemeNode;

// Контекст выполняения.
struct SExecutionContext
{
	// Указатель на схему.
	FSchemeNode * Scheme;

	// Указатель на дочерний контекст.
	SExecutionContext * Parent;

	// Флаг готовности задания.
	boost::atomic<size_t> Ready;

	// Стек для работы с кортежами.
	std::vector<DataValue> stack;

	// Положение кортежа аргументов.
	int argPos;

	// Теущая арность операции.
	int arity;

	// Количество аргументов во входном кортеже.
	int argNum;

	// Список выделенной памяти.
	std::list<void *> allocatedMemory;

	// Объем памяти, выделенной до сборки мусора.
	size_t numAllocated;
	size_t prevAllocated;

	SExecutionContext();

	// Методы работы с данными.
	const DataValue & getArg(int index) const;
	void push(const DataValue & aData);
	void advance();
	void unwind(int aArgPosOld, int aArity, int aPos);

	// Управление памятью в куче.
	void * alloc(size_t aSize);
	int collect();
	void tryCollect();

	// Запуск выполнения.
	void run(EvaluatorUnit * aEvaluatorUnit);

	// Порождение нового задания. После выполнения задания результат будет записан по адресу aResult.
	SExecutionContext * spawn(FSchemeNode * aFirstNode);

	EvaluatorUnit * evaluator() const;
	 
private:
	EvaluatorUnit * mEvaluatorUnit;
};

// Интерфейс объектов с автоматическим управлением памятью.
class Collectable
{
public:
	virtual void mark(std::stack<Collectable *> & aMarkStack) = 0;
	virtual size_t size() const = 0;
};

} // Runtime
} // FPTL