#include "InternalForm.h"
#include "Context.h"

#include "../Run.h"
#include "../String.h"

namespace FPTL {
namespace Runtime {

//-----------------------------------------------------------------------------

void ParFork::exec(SExecutionContext & ctx) const
{
	auto fork = static_cast<IFExecutionContext &>(ctx).spawn(mRight.get());

	ctx.evaluator()->fork(fork);

	mLeft->exec(ctx);
}

void ParJoin::exec(SExecutionContext & ctx) const
{
	auto joined = ctx.evaluator()->join();

	// Копируем результат.
	for (int i = 0; i < joined->arity; ++i)
	{
		ctx.push(joined->stack.at(joined->stack.size() - joined->arity + i));
	}

	delete joined;

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
	// Выполняем системные действия.
	ctx.evaluator()->safePoint();

	ctx.controlStack.push_back(ctx.arity);

	mCond->exec(ctx);
}

void CondFork::exec(SExecutionContext & ctx) const
{
	IFExecutionContext *fork;

	// Выполняем системные действия.
	ctx.evaluator()->safePoint();

	ctx.controlStack.push_back(ctx.arity);

	if (mThen)
	{
		fork = static_cast<IFExecutionContext &>(ctx).spawn(mThen.get());
		ctx.evaluator()->forkAnticipation(fork);
	}
	else
	{

	}

	if (mElse)
	{
		fork = static_cast<IFExecutionContext &>(ctx).spawn(mElse.get());
		ctx.evaluator()->forkAnticipation(fork);
	}
	else
	{

	}
	
	mCond->exec(ctx);
}

const DataValue falseConst = DataBuilders::createBoolean(false);
const DataValue undefined = DataBuilders::createUndefinedValue();

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

void CondJoin::exec(SExecutionContext & ctx) const
{
	auto arity = ctx.controlStack.back().OutArity;
	ctx.controlStack.pop_back();

	// Берём сверху стека 1 аргумент - результат вычисления предиката.
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

	SExecutionContext *branch;

	// Проверка условия.
	if (numArgs > 0 && (isUndefined || (cond.getOps() == falseConst.getOps() && !cond.mIntVal)))
	{
		branch = ctx.evaluator()->joinAnticipation(false);
	}
	else
	{
		branch = ctx.evaluator()->joinAnticipation(true);
	}


	// Копируем результат.
	for (int i = 0; i < branch->arity; ++i)
	{
		ctx.push(branch->stack.at(branch->stack.size() - branch->arity + i));
	}

	delete branch;

	mNext->exec(ctx);
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
	// Поскольку при вызове базисной функции необходимо обработать исключение, проивзодим вызов
	// через метод-трамплин, чтобы не повлиять на оптимизацию компилятором хвостовой рекурсии.
	callFn(ctx);

	mNext->exec(ctx);
}

void BasicFn::callFn(SExecutionContext & ctx) const
{
	try
	{
		mFn(ctx);
	}
	catch (std::exception & thrown)
	{
		std::stringstream error;
		error << "Runtime error in function '" << mName << "' line: " << mPos.second << " column: " << mPos.first << ": " << thrown.what() << std::endl;
		std::cerr << error.str();
		throw;
	}
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

void Constant::pushString(SExecutionContext & ctx, const std::string & str)
{
	ctx.push(StringBuilder::create(ctx, str));
}

void EndOp::exec(SExecutionContext & ctx) const
{
}

//-----------------------------------------------------------------------------
IFExecutionContext::IFExecutionContext(const InternalForm * body)
	: mInternalForm(body)
{
}


void IFExecutionContext::run(EvaluatorUnit * evaluator)
{
	mEvaluatorUnit = evaluator;
	mEvaluatorUnit->pushTask(this);

	mInternalForm->exec(*this);

	mEvaluatorUnit->popTask();

	// Сообщаем о готовности задания.
	Ready.store(1, std::memory_order_release);
}

IFExecutionContext * IFExecutionContext::spawn(const InternalForm * forkBody)
{
	IFExecutionContext * fork = new IFExecutionContext(forkBody);
	fork->Parent = this;

	// Копируем стек.
	for (int i = argPos; i < (argPos + argNum); i++)
	{
		fork->stack.push_back(stack.at(i));
	}

	fork->argNum = argNum;
	return fork;
}

}}