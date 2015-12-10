#include "InternalForm.h"

namespace FPTL {
namespace Runtime {

void ParFork::exec(SExecutionContext & ctx) const
{
	mLeft->exec(ctx);
	mRight->exec(ctx);
}

void ParJoin::exec(SExecutionContext & ctx) const
{
	mNext->exec(ctx);
}

void SeqBegin::exec(SExecutionContext & ctx) const
{
	// Запоминаем предыдущие параметры.
	ctx.controlStack.emplace_back(ctx.argPos, ctx.stack.size(), ctx.argNum, ctx.arity);
	ctx.arity = 0;

	mNext->exec(ctx);
}

void SeqEnd::exec(SExecutionContext & ctx) const
{
	ControlValue & cv = ctx.controlStack.back();
	ctx.controlStack.pop_back();

	// Сворачиваем стек.
	ctx.unwind(cv.ArgPos, cv.OutArity, cv.Size);
	ctx.argNum = cv.InArity;

	mNext->exec(ctx);
}

void SeqAdvance::exec(SExecutionContext & ctx) const
{
	ctx.advance();

	mNext->exec(ctx);
}

void CondStart::exec(SExecutionContext & ctx) const
{
	ctx.controlStack.push_back(ctx.arity);

	mCond->exec(ctx);
}

const DataValue CondChoose::falseConst = DataBuilders::createBoolean(false);
const DataValue CondChoose::undefined = DataBuilders::createUndefinedValue();

void CondChoose::exec(SExecutionContext & ctx) const
{
	auto arity = ctx.controlStack.back().OutArity;
	ctx.controlStack.pop_back();

	// Запоминаем на верху стека 1 аргумент - результат вычисления предиката.
	DataValue cond = ctx.stack.back();
	bool isUndefined = false;

	int numArgs = ctx.arity - arity;
	for (int i = 0; i < numArgs; ++i)
	{
		DataValue & arg = ctx.stack.back();

		// Проверяем, содержится ли в кортеже неопределенное значение w для реализации семантики w*a = a*w = w.
		if (arg.getOps() == undefined.getOps())
		{
			isUndefined = true;
		}

		ctx.stack.pop_back();
	}

	ctx.arity = arity;

	// Проверка условия.
	if (numArgs > 0 && (isUndefined || (cond.getOps() == falseConst.getOps() && !cond.mIntVal)))
	{
		mElse->exec(ctx);
	}
	else
	{
		mThen->exec(ctx);
	}
}

void RecFn::exec(SExecutionContext & ctx) const
{
	ctx.controlStack.push_back(mNext.get());

	mFn->exec(ctx);
}

void Ret::exec(SExecutionContext & ctx) const
{
	auto next = ctx.controlStack.back().Ptr;
	ctx.controlStack.pop_back();

	next->exec(ctx);
}

void BasicFn::exec(SExecutionContext & ctx) const
{
	mFn(ctx);

	mNext->exec(ctx);
}

void GetArg::exec(SExecutionContext & ctx) const
{
	ctx.push(ctx.getArg(mArgNum));

	mNext->exec(ctx);
}

void Constant::exec(SExecutionContext & ctx) const
{
	ctx.push(mData);
	
	mNext->exec(ctx);
}

void EndOp::exec(SExecutionContext & ctx) const
{
}

}}