#pragma once

#include <map>
#include <stack>

#include "Parser/AST.h"
#include "Parser/NodeHandler.h"
#include "Parser/Nodes.h"
#include "FScheme.h"
#include "ConstructorGenerator.h"

namespace FPTL
{
	namespace Runtime
	{
		class NewFSchemeGenerator : public Parser::NodeHandler
		{
		public:

			explicit NewFSchemeGenerator(Parser::ASTNode* astRoot);
			~NewFSchemeGenerator();
			NewFSchemeGenerator(const NewFSchemeGenerator &generator) = delete;
			NewFSchemeGenerator& operator= (const NewFSchemeGenerator &generator) = delete;

			Parser::ASTNode* getChild(Parser::ExpressionNode* aExpressionNode, size_t childNum) override;
			Parser::ASTNode* getChild(Parser::ConditionNode* aConditionNode, size_t childNum) override;
			Parser::ASTNode* getChild(Parser::ConstantNode* aConstantNode, size_t childNum) override;
			Parser::ASTNode* getChild(Parser::TakeNode* aTakeNode, size_t childNum) override;
			Parser::ASTNode* getChild(Parser::ListNode* aListNode, size_t childNum) override;
			Parser::ASTNode* getChild(Parser::DefinitionNode* aDefinitionNode, size_t childNum) override;
			Parser::ASTNode* getChild(Parser::NameRefNode* aNameRefNode, size_t childNum) override;
			Parser::ASTNode* getChild(Parser::ConstructorNode* aConstructorNode, size_t childNum) override;
			Parser::ASTNode* getChild(Parser::DataNode* aDataNode, size_t childNum) override;
			Parser::ASTNode* getChild(Parser::FunctionNode* aFunctionNode, size_t childNum) override;
			Parser::ASTNode* getChild(Parser::ApplicationBlock* aApplicationBlock, size_t childNum) override;
			Parser::ASTNode* getChild(Parser::FunctionalProgram* aFuncProgram, size_t childNum) override;

			size_t getChildIndex(Parser::ExpressionNode* aExpressionNode, Parser::ASTNode* child) override;
			size_t getChildIndex(Parser::ConditionNode* aConditionNode, Parser::ASTNode* child) override;
			size_t getChildIndex(Parser::ConstantNode* aConstantNode, Parser::ASTNode* child) override;
			size_t getChildIndex(Parser::TakeNode* aTakeNode, Parser::ASTNode* child) override;
			size_t getChildIndex(Parser::ListNode* aListNode, Parser::ASTNode* child) override;
			size_t getChildIndex(Parser::DefinitionNode* aDefinitionNode, Parser::ASTNode* child) override;
			size_t getChildIndex(Parser::NameRefNode* aNameRefNode, Parser::ASTNode* child) override;
			size_t getChildIndex(Parser::ConstructorNode* aConstructorNode, Parser::ASTNode* child) override;
			size_t getChildIndex(Parser::DataNode* aDataNode, Parser::ASTNode* child) override;
			size_t getChildIndex(Parser::FunctionNode* aFunctionNode, Parser::ASTNode* child) override;
			size_t getChildIndex(Parser::ApplicationBlock* aApplicationBlock, Parser::ASTNode* child) override;
			size_t getChildIndex(Parser::FunctionalProgram* aFuncProgram, Parser::ASTNode* child) override;

			void intermediateProcessing(Parser::ExpressionNode* aExpressionNode, size_t childNum) override;
			void intermediateProcessing(Parser::ConditionNode* aConditionNode, size_t childNum) override;
			void intermediateProcessing(Parser::ConstantNode* aConstantNode, size_t childNum) override;
			void intermediateProcessing(Parser::TakeNode* aTakeNode, size_t childNum) override;
			void intermediateProcessing(Parser::ListNode* aListNode, size_t childNum) override;
			void intermediateProcessing(Parser::DefinitionNode* aDefinitionNode, size_t childNum) override;
			void intermediateProcessing(Parser::NameRefNode* aNameRefNode, size_t childNum) override;
			void intermediateProcessing(Parser::ConstructorNode* aConstructorNode, size_t childNum) override;
			void intermediateProcessing(Parser::DataNode* aDataNode, size_t childNum) override;
			void intermediateProcessing(Parser::FunctionNode* aFunctionNode, size_t childNum) override;
			void intermediateProcessing(Parser::ApplicationBlock* aApplicationBlock, size_t childNum) override;
			void intermediateProcessing(Parser::FunctionalProgram* aFuncProgram, size_t childNum) override;

			void ChildHandled(Parser::ExpressionNode* aExpressionNode, size_t childNum) override;
			void ChildHandled(Parser::ConditionNode* aConditionNode, size_t childNum) override;
			void ChildHandled(Parser::ConstantNode* aConstantNode, size_t childNum) override;
			void ChildHandled(Parser::TakeNode* aTakeNode, size_t childNum) override;
			void ChildHandled(Parser::ListNode* aListNode, size_t childNum) override;
			void ChildHandled(Parser::DefinitionNode* aDefinitionNode, size_t childNum) override;
			void ChildHandled(Parser::NameRefNode* aNameRefNode, size_t childNum) override;
			void ChildHandled(Parser::ConstructorNode* aConstructorNode, size_t childNum) override;
			void ChildHandled(Parser::DataNode* aDataNode, size_t childNum) override;
			void ChildHandled(Parser::FunctionNode* aFunctionNode, size_t childNum) override;
			void ChildHandled(Parser::ApplicationBlock* aApplicationBlock, size_t childNum) override;
			void ChildHandled(Parser::FunctionalProgram* aFuncProgram, size_t childNum) override;

			// Получение результата.
			FSchemeNode* getProgram() const;

		private:
			typedef std::map<std::string, FScheme*> TLexicalContext;

			std::stack<FSchemeNode*> mNodeStack;

			TLexicalContext mDefinitions;

			std::stack<TLexicalContext> mDefinitionsStack;

			FSchemeNode* mScheme;
			FSchemeNode* mSchemeInput;
			FSchemeNode* mProgram;

			ConstructorGenerator mConstructorGenerator;
		};
	}
}
