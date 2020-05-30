#pragma once
#include "AST.h"
#include "Nodes.h"

namespace FPTL
{
	namespace Parser
	{
		class NodeHandler
		{
		public:
			void Handle(ASTNode* astRoot);
			virtual ~NodeHandler() = default;

			virtual ASTNode* getChild(ExpressionNode* aExpressionNode, size_t childIndex) = 0;
			virtual ASTNode* getChild(ConditionNode* aConditionNode, size_t childIndex) = 0;
			virtual ASTNode* getChild(ConstantNode* aConstantNode, size_t childIndex) = 0;
			virtual ASTNode* getChild(TakeNode* aTakeNode, size_t childIndex) = 0;
			virtual ASTNode* getChild(ListNode* aListNode, size_t childIndex) = 0;
			virtual ASTNode* getChild(DefinitionNode* aDefinitionNode, size_t childIndex) = 0;
			virtual ASTNode* getChild(NameRefNode* aNameRefNode, size_t childIndex) = 0;
			virtual ASTNode* getChild(ConstructorNode* aConstructorNode, size_t childIndex) = 0;
			virtual ASTNode* getChild(DataNode* aDataNode, size_t childIndex) = 0;
			virtual ASTNode* getChild(FunctionNode* aFunctionNode, size_t childIndex) = 0;
			virtual ASTNode* getChild(ApplicationBlock* aApplicationBlock, size_t childIndex) = 0;
			virtual ASTNode* getChild(FunctionalProgram* aFuncProgram, size_t childIndex) = 0;

			virtual size_t getChildIndex(ExpressionNode* aExpressionNode, ASTNode* child) = 0;
			virtual size_t getChildIndex(ConditionNode* aConditionNode, ASTNode* child) = 0;
			virtual size_t getChildIndex(ConstantNode* aConstantNode, ASTNode* child) = 0;
			virtual size_t getChildIndex(TakeNode* aTakeNode, ASTNode* child) = 0;
			virtual size_t getChildIndex(ListNode* aListNode, ASTNode* child) = 0;
			virtual size_t getChildIndex(DefinitionNode* aDefinitionNode, ASTNode* child) = 0;
			virtual size_t getChildIndex(NameRefNode* aNameRefNode, ASTNode* child) = 0;
			virtual size_t getChildIndex(ConstructorNode* aConstructorNode, ASTNode* child) = 0;
			virtual size_t getChildIndex(DataNode* aDataNode, ASTNode* child) = 0;
			virtual size_t getChildIndex(FunctionNode* aFunctionNode, ASTNode* child) = 0;
			virtual size_t getChildIndex(ApplicationBlock* aApplicationBlock, ASTNode* child) = 0;
			virtual size_t getChildIndex(FunctionalProgram* aFuncProgram, ASTNode* child) = 0;

			virtual void intermediateProcessing(ExpressionNode* aExpressionNode, size_t childNum) = 0;
			virtual void intermediateProcessing(ConditionNode* aConditionNode, size_t childNum) = 0;
			virtual void intermediateProcessing(ConstantNode* aConstantNode, size_t childNum) = 0;
			virtual void intermediateProcessing(TakeNode* aTakeNode, size_t childNum) = 0;
			virtual void intermediateProcessing(ListNode* aListNode, size_t childNum) = 0;
			virtual void intermediateProcessing(DefinitionNode* aDefinitionNode, size_t childNum) = 0;
			virtual void intermediateProcessing(NameRefNode* aNameRefNode, size_t childNum) = 0;
			virtual void intermediateProcessing(ConstructorNode* aConstructorNode, size_t childNum) = 0;
			virtual void intermediateProcessing(DataNode* aDataNode, size_t childNum) = 0;
			virtual void intermediateProcessing(FunctionNode* aFunctionNode, size_t childNum) = 0;
			virtual void intermediateProcessing(ApplicationBlock* aApplicationBlock, size_t childNum) = 0;
			virtual void intermediateProcessing(FunctionalProgram* aFuncProgram, size_t childNum) = 0;

			virtual void ChildHandled(ExpressionNode* aExpressionNode, size_t childNum) = 0;
			virtual void ChildHandled(ConditionNode* aConditionNode, size_t childNum) = 0;
			virtual void ChildHandled(ConstantNode* aConstantNode, size_t childNum) = 0;
			virtual void ChildHandled(TakeNode* aTakeNode, size_t childNum) = 0;
			virtual void ChildHandled(ListNode* aListNode, size_t childNum) = 0;
			virtual void ChildHandled(DefinitionNode* aDefinitionNode, size_t childNum) = 0;
			virtual void ChildHandled(NameRefNode* aNameRefNode, size_t childNum) = 0;
			virtual void ChildHandled(ConstructorNode* aConstructorNode, size_t childNum) = 0;
			virtual void ChildHandled(DataNode* aDataNode, size_t childNum) = 0;
			virtual void ChildHandled(FunctionNode* aFunctionNode, size_t childNum) = 0;
			virtual void ChildHandled(ApplicationBlock* aApplicationBlock, size_t childNum) = 0;
			virtual void ChildHandled(FunctionalProgram* aFuncProgram, size_t childNum) = 0;

		private:
			ASTNode* getParent(ASTNode* child);

			std::vector<std::pair<ASTNode*, ASTNode*>> ChildToParent;
		};
	}
}
