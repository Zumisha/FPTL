#pragma once
#include "Nodes.h"

namespace FPTL
{
	namespace Parser
	{
		class NodeVisitor
		{
		public:

			virtual ~NodeVisitor() = default;

			//
			// Группа методов, вызываемых при входе в конкртеный узел, до обхода его дочерних узлов.
			// Решение об обходе дочерних узлов принимается на основе возвращаемого значения (если true, то обход производится).
			//
			virtual void handle(ListNode * aNode);
			virtual void handle(NameRefNode * aNameRefNode);
			virtual void handle(FunctionNode * aFunctionNode);
			virtual void handle(DefinitionNode * aDefinitionNode);
			virtual void handle(ConstructorNode * aConstructorNode);
			virtual void handle(DataNode * aDataNode);
			virtual void handle(FunctionalProgram * aFuncProgram);
			virtual void handle(ApplicationBlock * aApplicationBlock);
			virtual void handle(ExpressionNode * aExpressionNode);
			virtual void handle(ConditionNode * aExpressionNode);
			virtual void handle(ConstantNode * aConstantNode);

			//XXX made public to be callable from TypeBuilder::handle
			  // Начинает обход дерева.
			void process(ASTNode * aNode);

		protected:

		};
	}
}
