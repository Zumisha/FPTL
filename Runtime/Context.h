#pragma once

#include <vector>
#include <set>
#include <atomic>

#include "DataTypes/Data.h"
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
	std::atomic<bool> Ready;

	// Флаг выполнения задания.
	std::atomic<bool> Working;

	// Флаг упреждения.
	std::atomic<bool> Proactive;

	// Флаг нового уровня упреждения.
	std::atomic<bool> NewProactiveLevel;

	std::atomic<bool> Canceled;

	// Экземпляр завершающего узла, чтобы не создавать множественные при отмене.
	std::shared_ptr<InternalForm> endIfPtr;

	//Вектор для сохранения указателей на заменённые при остановке узлы, чтобы они не удалились преждевременно.
	std::vector<std::shared_ptr<InternalForm>> exchangedNodes;

	// Стек для работы с кортежами.
	std::vector<DataValue> stack;

	// Положение кортежа аргументов.
	size_t argPos;

	// Теущая арность операции.
	size_t arity;

	// Количество аргументов во входном кортеже.
	size_t argNum;

	std::vector<ControlValue> controlStack;

	SExecutionContext();

	bool isReady() const;

	// Методы работы с данными.
	const DataValue & getArg(size_t aIndex) const;
	void push(const DataValue & aData);
	void advance();
	void unwind(size_t aArgPosOld, size_t aArity, size_t aPos);
	void join();
	void print(std::ostream & aStream) const;
	void printTypes(std::ostream & aStream) const;

	// Запуск выполнения.
	virtual void run(EvaluatorUnit * aEvaluatorUnit) = 0;

	virtual void cancel() {}

	EvaluatorUnit * evaluator() const;
	CollectedHeap & heap() const;
	 
protected:
	EvaluatorUnit * mEvaluatorUnit;
};

//-----------------------------------------------------------------------------

class IFExecutionContext : public SExecutionContext
{
	InternalForm * mInternalForm;

public:
	IFExecutionContext(InternalForm * body);

	void run(EvaluatorUnit * evaluator) override;

	IFExecutionContext * spawn(InternalForm * fork);

	void cancel() override;
};

} // Runtime
} // FPTL