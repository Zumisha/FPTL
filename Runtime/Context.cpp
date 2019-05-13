#include <boost/timer/timer.hpp>

#include "Context.h"
#include "Run.h"
#include "IntForm/InternalForm.h"

namespace FPTL {
namespace Runtime {

SExecutionContext::SExecutionContext()
		: Scheme(nullptr),
		  Parent(nullptr),
		  Ready(0),
		  Working(0),
		  Proactive(0),
		  NewProactiveLevel(0),
		  Canceled(0),
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

const DataValue & SExecutionContext::getArg(int aIndex) const
{
	// ToDo: производить статический анализ.
	if (aIndex >= argNum || aIndex < 0)
	{
		std::stringstream error;
		error << "attempt to get the [" << aIndex + 1 << "] argument in a tuple of size " << argNum << ".";
		throw std::runtime_error(error.str());
	}
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

void SExecutionContext::unwind(size_t aArgPosOld, int aArity, size_t aPos)
{;
	for (int i = 0; i < arity; ++i)
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
		// Копируем результат.
		for (int i = 0; i < joined->arity; ++i)
		{
			push(joined->stack.at(joined->stack.size() - joined->arity + i));
		}

	delete joined;
}

	void SExecutionContext::print(std::ostream & aStream) const
	{
		if (argNum == 0) return;
		auto & arg = getArg(0);
		arg.getOps()->print(arg, aStream);
		for (int i = 1; i < argNum; ++i)
		{
			aStream << " * ";
			auto & arg = getArg(i);
			arg.getOps()->print(arg, aStream);
		}
	}

	void SExecutionContext::printTypes(std::ostream& aStream) const
	{
		aStream << "(";
		if (argNum != 0)
		{
			DataValue arg = getArg(0);
			TypeInfo argType = arg.getOps()->getType(arg);
			aStream << argType;
			for (int i = 1; i < argNum; ++i)
			{
				aStream << " * ";
				DataValue arg = getArg(i);
				TypeInfo argType = arg.getOps()->getType(arg);
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
			Ready.store(1, std::memory_order_release);
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
			this->Childs.insert(fork);

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
}}
