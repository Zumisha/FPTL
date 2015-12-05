#include "Generator.h"
#include "InternalForm.h"

#include "../FScheme.h"

#include <cassert>

namespace FPTL {
namespace Runtime {

Generator::Generator() :
	mTail(nullptr),
	mResult(nullptr)
{
}

void Generator::visit(const FParallelNode * node)
{
	if (node->left()->isLong() && node->right()->isLong())
	{
		auto join = new ParJoin(mTail);
		auto left = createSpan(node->left(), join);
		auto right = createSpan(node->right(), join);

		mResult = new ParFork(left, right);
	}
	else
	{
		auto right = createSpan(node->right(), mTail);
		auto left = createSpan(node->left(), right);

		mResult = left;
	}
}

void Generator::visit(const FSequentialNode * node)
{
	auto end = new SeqEnd(mTail);
	auto second = createSpan(node->second(), end);
	auto unwind = new SeqAdvance(second);
	auto first = createSpan(node->first(), unwind);
	auto begin = new SeqBegin(first);

	mResult = begin;
}

void Generator::visit(const FConditionNode * node)
{
	auto thenBr = createSpan(node->trueBranch(), mTail);	
	auto elseBr = createSpan(node->falseBranch(), mTail);
	
	auto chooser = new CondChoose(thenBr, elseBr);

	auto cond = createSpan(node->condition(), chooser);

	auto start = new CondStart(cond);

	mResult = start;
}

void Generator::visit(const FScheme * scheme)
{
	// ѕри первом заходе создаем определени€ в контексте.
	if (mCtx.declareFun(scheme))
	{
		auto ret = new Ret();
		mCtx.defineFun(scheme, createSpan(scheme->firstNode(), ret));
	}
	
	mResult = new RecFn(mCtx.getFun(scheme), mTail, scheme->name());
}

void Generator::visit(const FFunctionNode * node)
{
	mResult = new BasicFn(mTail, node->name());
}

void Generator::visit(const FTakeNode * node)
{
	mResult = new BasicFn(mTail, "[]");
}

void Generator::visit(const FConstantNode * node)
{
	mResult = new BasicFn(mTail, "C");
}

InternalForm * Generator::generate(FSchemeNode * node)
{
	Generator generator;
	return generator.createSpan(node, new EndOp());
}

InternalForm * Generator::createSpan(FSchemeNode * node, InternalForm * tail)
{
	InternalForm * tmp = tail;
	std::swap(mTail, tmp);
	node->accept(this);
	std::swap(mTail, tmp);
	return mResult;
}

}}
