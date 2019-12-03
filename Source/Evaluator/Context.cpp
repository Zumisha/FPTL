
#include "Macros.h"
#include "Evaluator/Context.h"
#include "Evaluator/Run.h"
#include "InternalForm/InternalForm.h"

namespace FPTL {
	namespace Runtime {

		SExecutionContext::~SExecutionContext() = default;

		SExecutionContext::SExecutionContext() : Scheme(nullptr),
			Parent(nullptr),
			Ready(false),
			Working(false),
			Proactive(false),
			NewProactiveLevel(false),
			Canceled(false),
			argPos(0),
			arity(0),
			argNum(0),
			mEvaluatorUnit(nullptr)
		{
			stack.reserve(10);
			controlStack.reserve(10);
		}

		inline bool SExecutionContext::isReady() const
		{
			return Ready.load(std::memory_order_acquire) == 1;
		}

		inline const Value& SExecutionContext::getArg(const size_t aIndex) const
		{
#if fptlDebugBuild
			// ToDo: производить статический анализ.
			if (aIndex >= argNum)
			{
				std::stringstream error;
				error << "attempt to get the [" << aIndex + 1 << "] argument in a tuple of size " << argNum << ".";
				throw std::runtime_error(error.str());
			}
#endif
			return stack.at(argPos + aIndex);
		}

		inline void SExecutionContext::push(const Value& aData)
		{
			stack.push_back(aData);
			++arity;
		}

		void SExecutionContext::advance()
		{
			argPos = stack.size() - arity;
			argNum = arity;
			arity = 0;
		}

		void SExecutionContext::unwind(const size_t aArgPosOld, const size_t aArity, const size_t aPos)
		{
			for (size_t i = 0; i < arity; ++i)
			{
				stack[aPos + i] = stack[stack.size() - arity + i];
			}

			argPos = aArgPosOld;
			stack.resize(aPos + arity);
			arity += aArity;
		}

		void SExecutionContext::join()
		{
			auto joined = mEvaluatorUnit->join();
			if (!joined->Canceled.load(std::memory_order_acquire))
			{
				// Копируем результат.
				for (size_t i = 0; i < joined->arity; ++i)
				{
					push(joined->stack.at(joined->stack.size() - joined->arity + i));
				}

				delete joined;
			}
		}

		void SExecutionContext::print(std::ostream& aStream) const
		{
			if (argNum == 0) return;
			const auto& arg0 = getArg(0);
			arg0.Print(aStream);
			for (size_t i = 1; i < argNum; ++i)
			{
				aStream << " * ";
				const auto& arg = getArg(i);
				arg.Print(aStream);
			}
		}

		void SExecutionContext::printTypes(std::ostream& aStream) const
		{
			aStream << "(";
			if (argNum != 0)
			{
				const auto& arg0 = getArg(0);
				auto argType = arg0.Type();
				aStream << argType;
				for (size_t i = 1; i < argNum; ++i)
				{
					aStream << " * ";
					const auto& arg = getArg(i);
					argType = arg.Type();
					aStream << argType;
				}
			}
			aStream << ")";
		}

		void SExecutionContext::cancel()
		{
		}

		EvaluatorUnit* SExecutionContext::evaluator() const
		{
			return mEvaluatorUnit;
		}

		IFExecutionContext::IFExecutionContext(InternalForm* body): mInternalForm(body)
		{
		}

		void IFExecutionContext::run(EvaluatorUnit* evaluator)
		{
			{
				mEvaluatorUnit = evaluator;
				mEvaluatorUnit->pushTask(this);

				mInternalForm->exec(*this);

				mEvaluatorUnit->popTask();

				// Сообщаем о готовности задания.
				Ready.store(true, std::memory_order_release);
			}
		}

		IFExecutionContext* IFExecutionContext::spawn(InternalForm* forkBody)
		{
			IFExecutionContext* fork;
			if (!this->Canceled.load(std::memory_order_acquire))
			{
				fork = new IFExecutionContext(forkBody);
				fork->Parent = this;
				fork->Proactive.store(this->Proactive.load(std::memory_order_acquire), std::memory_order_release);


				// Копируем стек.
				for (size_t i = argPos; i < (argPos + argNum); i++)
				{
					fork->stack.push_back(stack.at(i));
				}

				fork->argNum = argNum;
			}
			else
			{
				fork = new IFExecutionContext(new EndOp());
			}
			return fork;
		}

		void IFExecutionContext::cancel()
		{
			endIfPtr = std::make_shared<EndOp>();
			mInternalForm->zeroing(*this);
		}
	}
}
