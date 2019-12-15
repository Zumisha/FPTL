#pragma once

#include <vector>
#include <set>
#include <atomic>
#include <memory>

#include "DataTypes/Ops/Ops.h"
#include "InternalForm/ControlValue.h"
#include <sstream>

namespace FPTL {
	namespace Runtime {

		//---------------------------------------------------------------------------------------------
		class EvaluatorUnit;
		class FSchemeNode;
		class CollectedHeap;

		// Контекст выполнения.
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

			static std::string outOfRange(size_t aIndex, size_t argNum)
			{
				std::stringstream error;
				error << "attempt to get the [" << aIndex << "] argument in a tuple of size " << argNum;
				return error.str();
			}

		protected:
			EvaluatorUnit * mEvaluatorUnit;
		};

		//-----------------------------------------------------------------------------

		class IFExecutionContext : public SExecutionContext
		{
			InternalForm * mInternalForm;

		public:
			explicit IFExecutionContext(InternalForm * body);

			void run(EvaluatorUnit * evaluator) override;

			IFExecutionContext * spawn(InternalForm * forkBody);

			void cancel() override;
		};

	}
}
