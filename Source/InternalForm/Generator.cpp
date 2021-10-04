#include <cassert>

#include "Generator.h"

#include <Evaluator/EvalConfig.h>

#include "InternalForm.h"
#include "FScheme/FScheme.h"

namespace FPTL
{
	namespace Runtime
	{

		void Generator::visit(const FParallelNode * node)
		{
			if (node->left()->isLong() && node->right()->isLong())
			{
				const auto join = std::make_shared<ParJoin>(mTail);
				auto left = createSpan(node->left(), join);
				auto right = createSpan(node->right(), std::make_shared<EndOp>());

				mResult = std::make_shared<ParFork>(left, right);
			}
			else
			{
				const auto right = createSpan(node->right(), mTail);
				const auto left = createSpan(node->left(), right);

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
			IfPtr thenBr = nullptr, elseBr = nullptr, thenBrFork = nullptr, elseBrFork = nullptr;

			if (!Config.proactiveEnabled || !node->condition()->isLong())
			{
				thenBr = createSpan(node->trueBranch(), mTail);
				elseBr = createSpan(node->falseBranch(), mTail);
			}
			else
			{
				if (node->trueBranch()->isLong())
					thenBrFork = createSpan(node->trueBranch(), std::make_shared<EndOp>());
				else
					thenBr = createSpan(node->trueBranch(), mTail);

				if (node->falseBranch()->isLong())
					elseBrFork = createSpan(node->falseBranch(), std::make_shared<EndOp>());
				else
					elseBr = createSpan(node->falseBranch(), mTail);
			}

			const auto choose = std::make_shared<CondChoose>(thenBr, elseBr, mTail);

			IfPtr cond = createSpan(node->condition(), choose);

			mResult = std::make_shared<CondStart>(cond, thenBrFork, elseBrFork);
		}

		void Generator::visit(const FScheme * scheme)
		{
			// При первом заходе создаем определения в контексте.
			if (mCtx.declareFun(scheme))
			{
				const auto ret = std::make_shared<Ret>();
				mCtx.defineFun(scheme, createSpan(scheme->firstNode(), ret));
			}

			auto* const rec = new RecFn(mTail, scheme->name());
			mResult = IfPtr(rec);

			mCtx.addRec(scheme, rec);
		}

		void Generator::visit(const FFunctionNode * node)
		{
			if (Config.stackTrace) {
				mResult = std::make_shared<TraceErrBasicFn>(mTail, node->name(), node->pos(), node->fn());
			} else if (Config.unsafeMode) {
				mResult = std::make_shared<UnsafeBasicFn>(mTail, node->name(), node->pos(), node->fn());
			} else {
				mResult = std::make_shared<BasicFn>(mTail, node->name(), node->pos(), node->fn());
			}
		}

		void Generator::visit(const FTakeNode * node)
		{
			if (Config.stackTrace) {
				mResult = std::make_shared<TraceErrGetArg>(mTail, node->from(), node->to(), node->pos());
			}
			else if (Config.unsafeMode) {
				mResult = std::make_shared<UnsafeGetArg>(mTail, node->from(), node->to(), node->pos());
			}
			else {
				mResult = std::make_shared<GetArg>(mTail, node->from(), node->to(), node->pos());
			}
		}

		void Generator::visit(const FConstantNode * node)
		{
			mResult = std::make_shared<Constant>(mTail, node->data());
		}

		void Generator::visit(const FStringConstant * node)
		{
			// Для строк создаем функцию-констурктор,
			// т.к. строка может создаваться только при наличии контекста.
			std::string constant = node->str();
			auto fn = [constant](SExecutionContext & ctx) { Constant::pushString(ctx, constant); };
			if (Config.unsafeMode) {
				mResult = std::make_shared<UnsafeBasicFn>(mTail, "c_string", std::make_pair(0, 0), fn);
			}
			else {
				mResult = std::make_shared<BasicFn>(mTail, "c_string", std::make_pair(0, 0), fn);
			}
		}

		FunctionalProgram * Generator::generate(FSchemeNode * node, const EvalConfig config)
		{
			Generator generator;
			generator.Config = config;
			const auto main = generator.createSpan(node, std::make_shared<EndOp>());

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
	}
}
