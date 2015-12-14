#include "FScheme.h"
#include "FSchemeVisitor.h"
#include "Run.h"
#include "String.h"

#include <iostream>
#include <cassert>

namespace FPTL { namespace Runtime {

//-----------------------------------------------------------------------------------
FSchemeNode::FSchemeNode(bool aIsLong) : mIsLong(aIsLong)
{
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
	size_t argPos = aCtx.argPos;
	size_t size = aCtx.stack.size();
	int argNum = aCtx.argNum;

	aCtx.arity = 0;

	mFirst->execute(aCtx);

	// Продвигаемся к новому фрейму на стеке.
	aCtx.advance();

	mSecond->execute(aCtx);

	// Сворачиваем стек.
	aCtx.unwind(argPos, arity, size);
	aCtx.argNum = argNum;
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

	// Выполняем системные действия.
	aCtx.evaluator()->safePoint();

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
		SExecutionContext * fork = aCtx.spawn(mRight);

		auto evaluator = aCtx.evaluator();
		evaluator->fork(fork);

		mLeft->execute(aCtx);

		evaluator->join();

		// Копируем результат.
		for (int i = 0; i < fork->arity; ++i)
		{
			aCtx.push(fork->stack.at(fork->stack.size() - fork->arity + i));
		}

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
	: FSchemeNode(aFirstNode->isLong()), mFirstNode(aFirstNode)
{
}

FScheme::FScheme(FSchemeNode * aFirstNode, const std::string & aName)
	: FSchemeNode(true), mFirstNode(aFirstNode), mName(aName)
{
}

void FScheme::setFirstNode(FSchemeNode * aFirstNode)
{ 
	mFirstNode = aFirstNode;
	mIsLong = aFirstNode->isLong();

	//optimizeTailCall();
}

void FScheme::setDefinitions(const std::map<std::string, FSchemeNode *> & aDefinitions)
{
	mDefinitions = aDefinitions;
}

std::vector<std::string> FScheme::definitions() const
{
	std::vector<std::string> defs;

	std::for_each(mDefinitions.begin(), mDefinitions.end(), [&defs](const std::pair<std::string, FSchemeNode *> & elem)
		{
			defs.push_back(elem.first);
		}
	);

	return defs;
}

FSchemeNode * FScheme::definition(const std::string & aName) const
{
	return mDefinitions.at(aName);
}

void FScheme::execute(SExecutionContext & aCtx) const
{
	mFirstNode->execute(aCtx);
}

void FScheme::accept(FSchemeVisitor * aVisitor) const
{
	aVisitor->visit(this);
}

void FScheme::optimizeTailCall()
{
	// Пытаемся произвести оптимизацию хвостового вызова.
	auto cond = dynamic_cast<FConditionNode *>(mFirstNode);
	if (cond)
	{
		auto falseBr = cond->falseBranch();
		auto seq = dynamic_cast<FSequentialNode *>(falseBr);
		if (seq)
		{
			if (seq->second() == this)
			{
				auto cont = seq->first();
				auto exit = cond->trueBranch();

				auto trueBranch = new FConstantNode(TypeInfo("boolean"), DataBuilders::createBoolean(true), -1, -1);
				auto falseBranch = new FConstantNode(TypeInfo("boolean"), DataBuilders::createBoolean(false), -1, -1);
				auto optimizedCond = new FConditionNode(cond->condition(), trueBranch, falseBranch);

				// Производим оптимизацию.
				mFirstNode = new FFunctionNode([=](SExecutionContext & aCtx)
				{
					// Копируем входные данные.
					auto pos = aCtx.stack.size();

					for (int i = 0; i < aCtx.argNum; ++i)
					{
						aCtx.push(aCtx.getArg(i));
					}

					for ( ; ; )
					{
						// Вычисляем условие.
						optimizedCond->execute(aCtx);

						// Проверяем условие.
						DataValue & condRes = aCtx.stack.back();
						aCtx.stack.pop_back();
						aCtx.arity--;

						if (condRes.mIntVal)
						{
							exit->execute(aCtx);
							break;
						}

						cont->execute(aCtx);

						// Не даем стеку разрастаться.
						aCtx.unwind(pos, -aCtx.arity, pos); 
					}
				});
			}
		}
	}
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

//-----------------------------------------------------------------------------------
void FTakeNode::execute(SExecutionContext & aCtx) const
{
	aCtx.push(aCtx.getArg(mIndex));
}

void FTakeNode::accept(FSchemeVisitor * aVisitor) const
{
	aVisitor->visit(this);
}

//-----------------------------------------------------------------------------------
void FConstantNode::execute(SExecutionContext & aCtx) const
{
	aCtx.push(mData);
}

void FConstantNode::accept(FSchemeVisitor * aVisitor) const
{
	aVisitor->visit(this);
}

FStringConstant::FStringConstant(const std::string & aStr, short aLine, short aCol)
	: FConstantNode(TypeInfo("string"), DataValue(), aLine, aCol),
	mStr(aStr)
{
}

void FStringConstant::execute(SExecutionContext & aCtx) const
{
	aCtx.push(StringBuilder::create(aCtx, mStr));
}

}} // FPTL::Runtime