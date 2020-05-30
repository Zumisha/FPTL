#include "NodeVisitor.h"
#include "Nodes.h"

namespace FPTL
{
	namespace Parser
	{
		void NodeVisitor::handle(NameRefNode * aNameRefNode)
		{
			process(aNameRefNode->getParameters());
		}

		void NodeVisitor::handle(FunctionNode * aFunctionNode)
		{
			process(aFunctionNode->getDefinitions());
			process(aFunctionNode->getFormalParameters());
		}

		void NodeVisitor::handle(DefinitionNode * aDefinitionNode)
		{
			process(aDefinitionNode->getDefinition());
		}

		void NodeVisitor::handle(ConstructorNode * aConstructorNode)
		{
			process(aConstructorNode->getCtorParameters());
		}

		void NodeVisitor::handle(DataNode * aDataNode)
		{
			process(aDataNode->getConstructors());
			process(aDataNode->getTypeParams());
			process(aDataNode->getTypeDefs());
		}

		void NodeVisitor::handle(FunctionalProgram * aFuncProgram)
		{
			process(aFuncProgram->getDataDefinitions());
			process(aFuncProgram->getScheme());
			process(aFuncProgram->getApplication());
		}

		void NodeVisitor::handle(ApplicationBlock * aApplicationBlock)
		{
			process(aApplicationBlock->getRunningSchemeName());
			process(aApplicationBlock->getSchemeParameters());
			process(aApplicationBlock->getDataVarDefinitions());
		}

		void NodeVisitor::handle(ExpressionNode * aExpressionNode)
		{
			process(aExpressionNode->getLeft());
			process(aExpressionNode->getRight());
		}

		void NodeVisitor::handle(ConditionNode * aExpressionNode)
		{
			process(aExpressionNode->getThen());
			process(aExpressionNode->getCond());
			process(aExpressionNode->getElse());
		}

		void NodeVisitor::handle(ConstantNode * aConstantNode)
		{
		}

		void NodeVisitor::handle(TakeNode * aTupleElemNode)
		{
		}

		void NodeVisitor::handle(ListNode * aNode)
		{
			//for (auto& node : aNode->mChilds)
			for (size_t i = aNode->mChilds.size(); i--;)
			{
				//process(node);
				process(aNode->mChilds[i]);
			}
		}

		void NodeVisitor::process(ASTNode * aNode)
		{
			if (aNode)
			{
				aNode->handle(this);
			}
		}
	}
}
