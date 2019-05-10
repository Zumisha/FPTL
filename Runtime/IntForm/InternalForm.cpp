#include <iostream>

#include "InternalForm.h"
#include "Context.h"
#include "../Run.h"
#include "../DataTypes/String.h"
#include "Runtime/StandartLibrary.h"
#include "Runtime/FScheme.h"

namespace FPTL {
namespace Runtime {

//-----------------------------------------------------------------------------
void ParFork::exec(SExecutionContext & ctx) const
{
	auto fork = static_cast<IFExecutionContext &>(ctx).spawn(mRight.get());

	ctx.evaluator()->addForkJob(fork);

	mLeft->exec(ctx);
}

void ParFork::zeroing(SExecutionContext & ctx)
{
	cancel(ctx, mLeft);
}

void ParJoin::exec(SExecutionContext & ctx) const
{
	ctx.join();
	mNext->exec(ctx);
}

void ParJoin::zeroing(SExecutionContext & ctx)
{
	cancel(ctx, mNext);
}

void SeqBegin::exec(SExecutionContext & ctx) const
{
	// Запоминаем предыдущие параметры.
	ctx.controlStack.emplace_back(ctx.argPos, ctx.stack.size(), ctx.argNum, ctx.arity);
	ctx.arity = 0;

	mNext->exec(ctx);
}

void SeqBegin::zeroing(SExecutionContext & ctx)
{
	cancel(ctx, mNext);
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

void SeqEnd::zeroing(SExecutionContext & ctx)
{
	cancel(ctx, mNext);
}

void SeqAdvance::exec(SExecutionContext & ctx) const
{
	ctx.advance();

	mNext->exec(ctx);
}

void SeqAdvance::zeroing(SExecutionContext & ctx) 
{
	cancel(ctx, mNext);
}

void CondStart::exec(SExecutionContext & ctx) const
{
	ctx.controlStack.push_back(ctx.arity);

	if (mThen)
	{
		IFExecutionContext *fork = static_cast<IFExecutionContext &>(ctx).spawn(mThen.get());
		fork->NewProactiveLevel = 1;
		fork->Proactive = 1;
		ctx.evaluator()->addForkJob(fork);
	}

	if (mElse)
	{
		IFExecutionContext *fork = static_cast<IFExecutionContext &>(ctx).spawn(mElse.get());
		fork->NewProactiveLevel = 1;
		fork->Proactive = 1;
		ctx.evaluator()->addForkJob(fork);
	}
	
	mCond->exec(ctx);
}

void CondStart::zeroing(SExecutionContext & ctx)
{
	cancel(ctx, mCond);
}

const DataValue falseConst = DataBuilders::createBoolean(false);
const DataValue undefined = DataBuilders::createUndefinedValue();

void CondChoose::exec(SExecutionContext & ctx) const
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

	// Проверка условия.
	if (numArgs > 0 && (isUndefined || (cond.getOps() == falseConst.getOps() && !cond.mIntVal)))
	{
		if (!mThen) // Если ненужная ветвь длинная - отменяем её вычисление.
			ctx.evaluator()->cancelFromPendingEnd(1 + !mElse);
		if (mElse) // Если верная ветвь короткая - начинаем её вычислять.
			mElse->exec(ctx);
		else
		{
			ctx.join();			
			mNext->exec(ctx);
		}
	}
	else
	{
		if (!mElse) // Если ненужная ветвь длинная - отменяем её вычисление.
			ctx.evaluator()->cancelFromPendingEnd();
		if (mThen) // Если верная ветвь короткая - начинаем её вычислять.
			mThen->exec(ctx);
		else
		{
			ctx.join();
			mNext->exec(ctx);
		}
	}
}

void CondChoose::zeroing(SExecutionContext & ctx)
{
	if (mThen)
	{
		cancel(ctx, mThen);
	}
	if (mElse)
	{
		cancel(ctx, mElse);
	}
	cancel(ctx, mNext);
}

void RecFn::exec(SExecutionContext & ctx) const
{
	ctx.controlStack.push_back(mNext.get());

	mFn->exec(ctx);
}

void RecFn::zeroing(SExecutionContext & ctx)
{
}

void Ret::exec(SExecutionContext & ctx) const
{
	auto next = ctx.controlStack.back().Ptr;
	ctx.controlStack.pop_back();

	next->exec(ctx);
}

void Ret::zeroing(SExecutionContext & ctx)
{
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
		error << "Runtime error. " << thrown.what() << std::endl;
		error << "In function \'" << mName << "\'. " << "Line: " << mPos.second << ". Column: " << mPos.first << std::endl;
		error << "Input tuple types: ";
		ctx.printTypes(error);
		error << std::endl;
		std::cerr << error.str();
		throw new std::runtime_error(error.str());
	}
}

void BasicFn::zeroing(SExecutionContext & ctx)
{
	cancel(ctx, mNext);
}

void GetArg::exec(SExecutionContext & ctx) const
{
	int argNum;
	if (mArgNum < 0) argNum = ctx.argNum + mArgNum;
	else argNum = mArgNum - 1;
	validateArgNum(ctx, argNum);
	ctx.push(ctx.getArg(argNum));

	mNext->exec(ctx);
}

void GetArg::validateArgNum(SExecutionContext& ctx, int argNum) const
{
	//ToDo Перенести в статический анализатор, когда он будет.
	if (argNum >= ctx.argNum || argNum < 0)
	{
		std::stringstream error;
		error << "Line: " << mPos.second << ". Column: " << mPos.first << ". Attempt to get the [" << mArgNum << "] argument in a tuple of size " << ctx.argNum << ".\n";
		std::cerr << error.str();
		throw new std::runtime_error(error.str());
	}
}


void GetArg::zeroing(SExecutionContext & ctx)
{
	//mArgNum = 0;
	//cancel(ctx, mNext);
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

void Constant::zeroing(SExecutionContext & ctx)
{
	cancel(ctx, mNext);
}

void EndOp::exec(SExecutionContext & ctx) const
{
}

void EndOp::zeroing(SExecutionContext & ctx)
{
}

//-----------------------------------------------------------------------------
IFExecutionContext::IFExecutionContext(InternalForm * body)
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
		for (int i = argPos; i < (argPos + argNum); i++)
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
