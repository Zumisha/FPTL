#pragma once

#include <unordered_set>

#include "FSchemeVisitor.h"

namespace FPTL
{
	namespace Runtime
	{

		class NodeDeleter : public FSchemeVisitor
		{
		public:
			void visit(const FFunctionNode * node) override;
			void visit(const FParallelNode * node) override;
			void visit(const FSequentialNode * node) override;
			void visit(const FConditionNode * node) override;
			void visit(const FScheme * scheme) override;
			void visit(const FTakeNode * node) override;
			void visit(const FConstantNode * node) override;

			void releaseGraph(const FSchemeNode * node);

		private:
			void process(const FSchemeNode * node);

			std::unordered_set<const FSchemeNode*> visited;
		};
	}
}
