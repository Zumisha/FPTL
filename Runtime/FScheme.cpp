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

void FConditionNode::accept(FSchemeVisitor * aVisitor) const
{
	aVisitor->visit(this);
}

//-----------------------------------------------------------------------------------
FParallelNode::FParallelNode(FSchemeNode * aLeft, FSchemeNode * aRight)
	: FSchemeNode(aLeft->isLong() || aRight->isLong()), mLeft(aLeft), mRight(aRight)
{
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
}

void FScheme::setDefinitions(const std::map<std::string, FSchemeNode *> & aDefinitions)
{
	mDefinitions = aDefinitions;
}

std::vector<std::string> FScheme::definitions() const
{
	std::vector<std::string> defs;

	for (auto &elem : mDefinitions)
	{
		defs.push_back(elem.first);
	}
	return defs;
}

FSchemeNode * FScheme::definition(const std::string & aName) const
{
	return mDefinitions.at(aName);
}

void FScheme::accept(FSchemeVisitor * aVisitor) const
{
	aVisitor->visit(this);
}

//-----------------------------------------------------------------------------------

void FFunctionNode::accept(FSchemeVisitor * aVisitor) const
{
	aVisitor->visit(this);
}

//-----------------------------------------------------------------------------------
void FTakeNode::accept(FSchemeVisitor * aVisitor) const
{
	aVisitor->visit(this);
}
//-----------------------------------------------------------------------------------
void FConstantNode::accept(FSchemeVisitor * aVisitor) const
{
	aVisitor->visit(this);
}

FStringConstant::FStringConstant(const std::string & aStr, short aLine, short aCol)
	: FConstantNode(TypeInfo("string"), DataValue(), aLine, aCol),
	mStr(aStr)
{
}
}} // FPTL::Runtime