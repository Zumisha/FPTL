#pragma once

#include <vector>
#include <stack>

#include <atomic>
#include <boost/intrusive/slist.hpp>

#include "Data.h"
#include "IntForm/ControlValue.h"

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
	size_t argPos;

	// Теущая арность операции.
	int arity;

	// Количество аргументов во входном кортеже.
	int argNum;

	std::vector<ControlValue> controlStack;

	SExecutionContext();

	bool isReady() const;

	// Методы работы с данными.
	const DataValue & getArg(int index) const;
	void push(const DataValue & aData);
	void advance();
	void unwind(size_t aArgPosOld, int aArity, size_t aPos);

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
// Все наследника этого класса обязаны иметь тривиальный деструктор.
class Collectable :
	public boost::intrusive::slist_base_hook<>
{
	friend class CollectedHeap;
	friend class ObjectMarker;

public:
	enum Age
	{
		YOUNG = 0,
		OLD   = 1
	};

private:
	struct MetaInfo
	{
		Age age : 30;
		unsigned int marked : 2;
	};

	MetaInfo meta;

public:
	Collectable()
		: meta({YOUNG, 0})
	{}

	bool isMarked() const
	{ return meta.marked == 1; }
};

} // Runtime
} // FPTL