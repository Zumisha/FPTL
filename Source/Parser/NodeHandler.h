#pragma once
#include "Nodes.h"

namespace FPTL
{
	namespace Parser
	{
		class NodeHandler
		{
		public:
			virtual ~NodeHandler() = default;

			virtual void handle(ExpressionNode* aExpressionNode) = 0;
			virtual void handle(ConditionNode* aExpressionNode) = 0;
			virtual void handle(ConstantNode* aConstantNode) = 0;
			virtual void handle(ListNode* aNode) = 0;
			virtual void handle(DefinitionNode* aDefinitionNode) = 0;
			virtual void handle(NameRefNode* aNameRefNode) = 0;
			virtual void handle(ConstructorNode* aFunctionNode) = 0;
			virtual void handle(DataNode* aDataNode) = 0;
			virtual void handle(FunctionNode* aFunctionNode) = 0;
			virtual void handle(ApplicationBlock* aApplicationBlock) = 0;
			virtual void handle(FunctionalProgram* aFuncProgram) = 0;
		};
	}
}
