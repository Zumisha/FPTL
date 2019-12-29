#pragma once

namespace FPTL {
	namespace Runtime {

		class FSchemeNode;
		class FFunctionNode;
		class FParallelNode;
		class FSequentialNode;
		class FConditionNode;
		class FScheme;
		class FTakeNode;
		class FConstantNode;
		class FStringConstant;

		class FSchemeVisitor
		{
		public:
			virtual void visit(const FFunctionNode * aNode) = 0;
			virtual void visit(const FParallelNode * aNode) = 0;
			virtual void visit(const FSequentialNode * aNode) = 0;
			virtual void visit(const FConditionNode * aNode) = 0;
			virtual void visit(const FScheme * aScheme) = 0;
			virtual void visit(const FTakeNode * aNode) = 0;
			virtual void visit(const FConstantNode * aNode) = 0;
			virtual void visit(const FStringConstant* node) = 0;

			virtual ~FSchemeVisitor() = default;;
		};
	}
}
