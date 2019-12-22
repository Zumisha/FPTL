#include "NodeVisitor.h"
#include "Nodes.h"

namespace FPTL
{
	namespace Parser
	{
		void NodeVisitor::visit(NameRefNode * aNameRefNode)
		{
			process(aNameRefNode->getParameters());
		}

		void NodeVisitor::visit(FunctionNode * aFunctionNode)
		{
			process(aFunctionNode->getDefinitions());
			process(aFunctionNode->getFormalParameters());
		}

		void NodeVisitor::visit(DefinitionNode * aDefinitionNode)
		{
			process(aDefinitionNode->getDefinition());
		}

		void NodeVisitor::visit(ConstructorNode * aConstructorNode)
		{
			process(aConstructorNode->getCtorParameters());
		}

		void NodeVisitor::visit(DataNode * aDataNode)
		{
			process(aDataNode->getConstructors());
			process(aDataNode->getTypeParams());
			process(aDataNode->getTypeDefs());
		}

		void NodeVisitor::visit(FunctionalProgram * aFuncProgram)
		{
			process(aFuncProgram->getDataDefinitions());
			process(aFuncProgram->getScheme());
			process(aFuncProgram->getApplication());
		}

		void NodeVisitor::visit(ApplicationBlock * aApplicationBlock)
		{
			process(aApplicationBlock->getRunningSchemeName());
			process(aApplicationBlock->getSchemeParameters());
			process(aApplicationBlock->getDataVarDefinitions());
		}

		void NodeVisitor::visit(ExpressionNode * aExpressionNode)
		{
			process(aExpressionNode->getLeft());
			process(aExpressionNode->getRight());
		}

		void NodeVisitor::visit(ConditionNode * aExpressionNode)
		{
			process(aExpressionNode->getThen());
			process(aExpressionNode->getCond());
			process(aExpressionNode->getElse());
		}

		void NodeVisitor::visit(ConstantNode * aConstantNode)
		{
		}

		void NodeVisitor::visit(ListNode * aNode)
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
				aNode->accept(this);
			}
		}
	}
}
