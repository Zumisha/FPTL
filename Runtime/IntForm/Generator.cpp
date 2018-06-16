#include "Generator.h"
#include "InternalForm.h"

#include "../FScheme.h"

#include <cassert>

namespace FPTL {
namespace Runtime {

Generator::Generator()
{
}

void Generator::visit(const FParallelNode * node)
{
	if (node->left()->isLong() && node->right()->isLong())
	{
		auto join = std::make_shared<ParJoin>(mTail);
		auto left = createSpan(node->left(), join);
		auto right = createSpan(node->right(), std::make_shared<EndOp>());

		mResult = std::make_shared<ParFork>(left, right);
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
	// Если подряд следует несколько выражений A . B . C, 
	// то генерируем внутреннее представления для всей цепочки.

	std::vector<FSchemeNode *> chain;

	const FSequentialNode * current = node;
	while (current)
	{
		node = current;
		chain.push_back(current->second());
		current = dynamic_cast<FSequentialNode *>(node->first());
	}

	IfPtr last = std::make_shared<SeqEnd>(mTail);
	for (auto elem : chain)
	{
		last = createSpan(elem, last);
		last = std::make_shared<SeqAdvance>(last);
	}

	auto first = createSpan(node->first(), last);
	auto begin = std::make_shared<SeqBegin>(first);
	mResult = begin;
}

void Generator::visit(const FConditionNode * node)
{
	IfPtr thenBr, elseBr, cond;
	if (node->condition()->isLong() && (node->trueBranch()->isLong() && node->falseBranch()->isLong()))
	{
		auto join = std::make_shared<CondJoin>(mTail);
		cond = createSpan(node->condition(), join);

		if (node->trueBranch()->isLong())
			thenBr = createSpan(node->trueBranch(), std::make_shared<EndOp>());

		if (node->falseBranch()->isLong())
			elseBr = createSpan(node->falseBranch(), std::make_shared<EndOp>());

		mResult = std::make_shared<CondFork>(cond, thenBr, elseBr);
	}
	else
	{
		thenBr = createSpan(node->trueBranch(), mTail);
		elseBr = createSpan(node->falseBranch(), mTail);

		auto chooser = std::make_shared<CondChoose>(thenBr, elseBr);

		cond = createSpan(node->condition(), chooser);

		mResult = std::make_shared<CondStart>(cond);
	}
}

void Generator::visit(const FScheme * scheme)
{
	// При первом заходе создаем определения в контексте.
	if (mCtx.declareFun(scheme))
	{
		auto ret = std::make_shared<Ret>();
		mCtx.defineFun(scheme, createSpan(scheme->firstNode(), ret));
	}
	
	auto rec = new RecFn(mTail, scheme->name());
	mResult = IfPtr(rec);

	mCtx.addRec(scheme, rec);
}

void Generator::visit(const FFunctionNode * node)
{
	mResult = std::make_shared<BasicFn>(mTail, node->name(), node->pos(), node->fn());
}

void Generator::visit(const FTakeNode * node)
{
	mResult = std::make_shared<GetArg>(mTail, node->index());
}

void Generator::visit(const FConstantNode * node)
{
	auto str = dynamic_cast<const FStringConstant *>(node);
	if (str)
	{
		// Для строк создаем функцию-констурктор,
		// т.к. строка может создаваться только при наличии контекста.

		std::string constant = str->str();
		mResult = std::make_shared<BasicFn>(
			mTail,
			"c_string",
			std::make_pair(0,0),
			[constant](SExecutionContext & ctx) { Constant::pushString(ctx, constant); }
		);
	}
	else
	{
		mResult = std::make_shared<Constant>(mTail, node->data());
	}
}

FunctionalProgram * Generator::generate(FSchemeNode * node)
{
	Generator generator;
	auto main = generator.createSpan(node, std::make_shared<EndOp>());

	generator.mCtx.resolveRec();

	auto result = new FunctionalProgram(main);
	generator.mCtx.getFunctions(result->mDefinitions);
	return result;
}

IfPtr Generator::createSpan(FSchemeNode * node, const IfPtr & tail)
{
	auto tmp = tail;
	std::swap(mTail, tmp);
	node->accept(this);
	std::swap(mTail, tmp);
	return mResult;
}

}}
