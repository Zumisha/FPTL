#include "Context.h"
#include "Run.h"

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
		if (argNum == 0) return;
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
}}
