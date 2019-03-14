#pragma once

#include <vector>
#include <stack>
#include <set>

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
	virtual ~SExecutionContext() = default;
	// Указатель на схему.
	FSchemeNode * Scheme;

	// Указатель на родительский контекст.
	SExecutionContext * Parent;

	// Указатели на порождённые задачи.
	std::set<SExecutionContext *> Childs;

	// Флаг готовности задания.
	std::atomic<int> Ready;

	// Флаг выполнения задания.
	std::atomic<int> Working;

	// Флаг упреждения.
	std::atomic<int> Proactive;

	// Флаг нового уровня упреждения.
	std::atomic<int> NewProactiveLevel;

	std::atomic<int> Canceled;

	// Экземпляр завершающего узла, чтобы не создавать множественные при отмене.
	std::shared_ptr<InternalForm> endIfPtr;
	InternalForm *endPtr;

	//Вектор для сохранения указателей на заменённые при остановке узлы, чтобы они не удалились преждевременно.
	std::vector<std::shared_ptr<InternalForm>> exchangedNodes;

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
	void join();

	// Запуск выполнения.
	virtual void run(EvaluatorUnit * aEvaluatorUnit) = 0;

	virtual void cancel() {}

	EvaluatorUnit * evaluator() const;
	CollectedHeap & heap() const;
	 
protected:
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