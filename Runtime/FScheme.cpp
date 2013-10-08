#include "FScheme.h"
#include "FSchemeVisitor.h"

#include <iostream>
#include <cassert>

namespace FPTL { namespace Runtime {

// execute-методы в узлах схемы были нужны для старой версии реализации вычислений.
// В новой версии для каждого узла генерируется код во время компиляции.
// Сгенерированный код полностью дублирует соответсвующий код методов execute.

//-----------------------------------------------------------------------------------
FSchemeNode::FSchemeNode(bool aIsLong) : mIsLong(aIsLong)
{
	//mCompiledProc = createJITStub();
}

//-----------------------------------------------------------------------------------
FSequentialNode::FSequentialNode(FSchemeNode * aFirst, FSchemeNode * aSecond)
	: FSchemeNode(aFirst->isLong() || aSecond->isLong()),
	mFirst(aFirst),
	mSecond(aSecond)
{
}

void FSequentialNode::execute(SExecutionContext & aCtx) const
{
	// Запоминаем предыдущие параметры.
	int arity = aCtx.arity;
	int argPos = aCtx.argPos;
	int size = aCtx.stack.size();
	aCtx.arity = 0;

	mFirst->execute(aCtx);

	// Продвигаемся к новому фрейму на стеке.
	aCtx.advance();

	mSecond->execute(aCtx);

	// Сворачиваем стек.
	aCtx.unwind(argPos, arity, size);
}

void FSequentialNode::accept(FSchemeVisitor * aVisitor) const
{
	aVisitor->visit(this);
}

//-----------------------------------------------------------------------------------
FConditionNode::FConditionNode(FSchemeNode * aCondition, FSchemeNode * aTrueBranch, FSchemeNode * aFalseBranch)
	: FSchemeNode(aCondition->isLong() || aTrueBranch->isLong() || (aFalseBranch && aFalseBranch->isLong())), 
	mCondition(aCondition),
	mTrueBranch(aTrueBranch),
	mFalseBranch(aFalseBranch)
{
	if (!mFalseBranch)
	{
		// Если в условной конструкции отсутсвует явно ветка else, считаем что она возвращает UndefinedValue.
		mFalseBranch = new FFunctionNode([](SExecutionContext & aCtx) { 
			aCtx.push(DataBuilders::createUndefinedValue());
		});
	}
}

void FConditionNode::execute(SExecutionContext & aCtx) const
{
	static DataValue falseConst = DataBuilders::createBoolean(false);
	static DataValue undefined = DataBuilders::createUndefinedValue();

	int arity = aCtx.arity;

	// Вычисление условия.
	mCondition->execute(aCtx);

	// Запоминаем на верху стека 1 аргумент - результат вычисления предиката.
	DataValue cond = aCtx.stack.back();
	bool isUndefined = false;

	int numArgs = aCtx.arity - arity;
	for (int i = 0; i < numArgs; ++i)
	{
		DataValue & arg = aCtx.stack.back();
		
		// Проверяем, содержится ли в кортеже неопределенное значение w для реализации семантики w*a = a*w = w.
		if (arg.getOps() == undefined.getOps())
		{
			isUndefined = true;
		}

		aCtx.stack.pop_back();
	}

	aCtx.arity = arity;

	// Проверка условия.
	if (numArgs > 0 && (isUndefined || (cond.getOps() == falseConst.getOps() && !cond.mIntVal)))
	{
		mFalseBranch->execute(aCtx);
	}
	else
	{
		mTrueBranch->execute(aCtx);
	}
}

void FConditionNode::accept(FSchemeVisitor * aVisitor) const
{
	aVisitor->visit(this);
}

//-----------------------------------------------------------------------------------
FParallelNode::FParallelNode(FSchemeNode * aLeft, FSchemeNode * aRight)
	: FSchemeNode(aLeft->isLong() || aRight->isLong()), mLeft(aLeft), mRight(aRight)
{
}

void FParallelNode::execute(SExecutionContext & aCtx) const
{
	if (mLeft->isLong() && mRight->isLong())
	{
		// Параллельное выполнение.
		SExecutionContext * fork = aCtx.fork(mRight);

		mLeft->execute(aCtx);

		while (!fork->Ready.load(boost::memory_order_acquire))
		{
			aCtx.yield();
		}

		// Копируем результат.
		for (int i = 0; i < fork->arity; ++i)
		{
			aCtx.push(fork->stack.at(fork->stack.size() - fork->arity + i));
		}

		// Обновляем список выделенной памяти.
		aCtx.allocatedMemory.splice(aCtx.allocatedMemory.end(), fork->allocatedMemory);

		// TEST
		//aCtx.tryCollect();

		delete fork;
	}
	else
	{
		// Последовательное выполнение.
		mLeft->execute(aCtx);

		mRight->execute(aCtx);
	}
}

void FParallelNode::accept(FSchemeVisitor * aVisitor) const
{
	aVisitor->visit(this);
}

//-----------------------------------------------------------------------------------
FScheme::FScheme(FSchemeNode * aFirstNode)
	: FSchemeNode(true), mFirstNode(aFirstNode)
{
}

void FScheme::execute(SExecutionContext & aCtx) const
{
	mFirstNode->execute(aCtx);
}

void FScheme::accept(FSchemeVisitor * aVisitor) const
{
	aVisitor->visit(this);
}

//-----------------------------------------------------------------------------------
void FFunctionNode::execute(SExecutionContext & aCtx) const
{
	call(this, &aCtx);
}

void FFunctionNode::accept(FSchemeVisitor * aVisitor) const
{
	aVisitor->visit(this);
}

void FFunctionNode::call(const FFunctionNode * aNode, SExecutionContext * aCtx)
{
	try
	{
		aNode->mFunction(*aCtx);
	}
	catch (const std::exception & e)
	{
		std::stringstream error;
		error << "Runtime error in function '" << aNode->mName << "' line: " << aNode->mLine << " column: " <<aNode->mColumn << ": " << e.what() << std::endl;
		
		// TODO: выводить дамп последнего кортежа, к которому применялась операция (printType).

		std::cerr << error.str();

		// Добавить на стек неорпделенность.
		aCtx->push(DataBuilders::createUndefinedValue());
	}
}

}} // FPTL::Runtime