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

	ctx.evaluator()->addForkJob(fork);

	mLeft->exec(ctx);
}

void ParFork::zeroing(SExecutionContext & ctx)
{
	ctx.exchangedNodes.push_back(mLeft);
	mLeft = ctx.endIfPtr;
	ctx.exchangedNodes.back()->zeroing(ctx);
}

void ParJoin::exec(SExecutionContext & ctx) const
{
	ctx.join();
	mNext->exec(ctx);
}

void ParJoin::zeroing(SExecutionContext & ctx)
{
	ctx.exchangedNodes.push_back(mNext);
	mNext = ctx.endIfPtr;
	ctx.exchangedNodes.back()->zeroing(ctx);
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
	ctx.exchangedNodes.push_back(mNext);
	mNext = ctx.endIfPtr;
	ctx.exchangedNodes.back()->zeroing(ctx);
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
	ctx.exchangedNodes.push_back(mNext);
	mNext = ctx.endIfPtr;
	ctx.exchangedNodes.back()->zeroing(ctx);
}

void SeqAdvance::exec(SExecutionContext & ctx) const
{
	ctx.advance();

	mNext->exec(ctx);
}

void SeqAdvance::zeroing(SExecutionContext & ctx) 
{
	ctx.exchangedNodes.push_back(mNext);
	mNext = ctx.endIfPtr;
	ctx.exchangedNodes.back()->zeroing(ctx);
}

void CondStart::exec(SExecutionContext & ctx) const
{
	ctx.controlStack.push_back(ctx.arity);

	if (mThen)
	{
		IFExecutionContext *fork = static_cast<IFExecutionContext &>(ctx).spawn(mThen.get());
		fork->NewAnticipationLevel = 1;
		fork->Anticipation = 1;
		ctx.evaluator()->addForkJob(fork);
	}

	if (mElse)
	{
		IFExecutionContext *fork = static_cast<IFExecutionContext &>(ctx).spawn(mElse.get());
		fork->NewAnticipationLevel = 1;
		fork->Anticipation = 1;
		ctx.evaluator()->addForkJob(fork);
	}
	
	mCond->exec(ctx);
}

void CondStart::zeroing(SExecutionContext & ctx)
{
	ctx.exchangedNodes.push_back(mCond);
	mCond = ctx.endIfPtr;
	ctx.exchangedNodes.back()->zeroing(ctx);
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
	// TODO: переписать, чтобы работала оптимизация хвостовой рекурсии.
	if (mThen)
	{
		ctx.exchangedNodes.push_back(mThen);
		mThen = ctx.endIfPtr;
		ctx.exchangedNodes.back()->zeroing(ctx);
	}
	if (mElse)
	{
		ctx.exchangedNodes.push_back(mElse);
		mElse = ctx.endIfPtr;
		ctx.exchangedNodes.back()->zeroing(ctx);
	}
	ctx.exchangedNodes.push_back(mNext);
	mNext = ctx.endIfPtr;
	ctx.exchangedNodes.back()->zeroing(ctx);
}

void RecFn::exec(SExecutionContext & ctx) const
{
	ctx.controlStack.push_back(mNext.get());

	mFn->exec(ctx);
}

void RecFn::zeroing(SExecutionContext & ctx)
{
	InternalForm *temp = mFn;
	mFn = ctx.endPtr;
	temp->zeroing(ctx);
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

void BasicFn::zeroing(SExecutionContext & ctx)
{
	ctx.exchangedNodes.push_back(mNext);
	mNext = ctx.endIfPtr;
	ctx.exchangedNodes.back()->zeroing(ctx);
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

void GetArg::zeroing(SExecutionContext & ctx)
{
	//mArgNum = 0;
	ctx.exchangedNodes.push_back(mNext);
	mNext = ctx.endIfPtr;
	ctx.exchangedNodes.back()->zeroing(ctx);
}

void Constant::exec(SExecutionContext & ctx) const
{
	ctx.push(mData);
	
	mNext->exec(ctx);
}

void Constant::zeroing(SExecutionContext & ctx)
{
	ctx.exchangedNodes.push_back(mNext);
	mNext = ctx.endIfPtr;
	ctx.exchangedNodes.back()->zeroing(ctx);
}

void Constant::pushString(SExecutionContext & ctx, const std::string & str)
{
	ctx.push(StringBuilder::create(ctx, str));
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
	endPtr = &EndOp();
	mInternalForm->zeroing(*this);
}

IFExecutionContext * IFExecutionContext::spawn(InternalForm * forkBody)
{
	IFExecutionContext * fork = new IFExecutionContext(forkBody);
	fork->Parent = this;
	fork->Anticipation = this->Anticipation.load(std::memory_order_acquire);
	this->Childs.insert(fork);
	//fork->id = this->id + 1;

	// Копируем стек.
	for (int i = argPos; i < (argPos + argNum); i++)
	{
		fork->stack.push_back(stack.at(i));
	}
	
	fork->argNum = argNum;
	return fork;
}

}}