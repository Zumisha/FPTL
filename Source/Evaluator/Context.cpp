#include <boost/timer/timer.hpp>

#include "Macros.h"
#include "Context.h"
#include "Run.h"
#include "InternalForm/InternalForm.h"

namespace FPTL 
{
	namespace Runtime 
	{
		SExecutionContext::SExecutionContext()
			: Scheme(nullptr),
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

		bool SExecutionContext::isReady() const
		{
			return Ready.load(std::memory_order_acquire) == 1;
		}

		EvaluatorUnit * SExecutionContext::evaluator() const
		{
			return mEvaluatorUnit;
		}

		CollectedHeap & SExecutionContext::heap() const
		{
			return mEvaluatorUnit->heap();
		}

		const DataValue & SExecutionContext::getArg(const size_t aIndex) const
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

		void SExecutionContext::push(const DataValue & aData)
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
			;
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

		void SExecutionContext::print(std::ostream & aStream) const
		{
			if (argNum == 0) return;
			auto arg = getArg(0);
			arg.getOps()->print(arg, aStream);
			for (size_t i = 1; i < argNum; ++i)
			{
				aStream << " * ";
				arg = getArg(i);
				arg.getOps()->print(arg, aStream);
			}
		}

		void SExecutionContext::printTypes(std::ostream& aStream) const
		{
			aStream << "(";
			if (argNum != 0)
			{
				auto arg = getArg(0);
				auto argType = arg.getOps()->getType(arg);
				aStream << argType;
				for (size_t i = 1; i < argNum; ++i)
				{
					aStream << " * ";
					arg = getArg(i);
					argType = arg.getOps()->getType(arg);
					aStream << argType;
				}
			}
			aStream << ")";
		}

		//-----------------------------------------------------------------------------

		IFExecutionContext::IFExecutionContext(InternalForm * body)
			: mInternalForm(body)
		{
		}


		void IFExecutionContext::run(EvaluatorUnit * evaluator)
		{
			//try
			{
				mEvaluatorUnit = evaluator;
				mEvaluatorUnit->pushTask(this);

				mInternalForm->exec(*this);

				mEvaluatorUnit->popTask();

				// Сообщаем о готовности задания.
				Ready.store(true, std::memory_order_release);
			}
			/*catch (std::exception & e)
			{
				evaluator->mEvaluator->stop();
			}*/
		}

		void IFExecutionContext::cancel()
		{
			endIfPtr = std::make_shared<EndOp>();
			mInternalForm->zeroing(*this);
		}

		IFExecutionContext * IFExecutionContext::spawn(InternalForm * forkBody)
		{
			IFExecutionContext * fork;
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
	}
}
