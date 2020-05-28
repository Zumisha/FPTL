#pragma once

#include <map>
#include <stack>


#include "ConstructorGenerator.h"
#include "Parser/NodeVisitor.h"
#include "FScheme.h"

namespace FPTL
{
	namespace Runtime
	{

		class ConstructorGenerator;

		//
		// Генератор функциональных схем по АСД. На вход должно предоставляться только семантически корректное дерево.
		//
		class FSchemeGenerator: public Parser::NodeVisitor
		{
		public:

			explicit FSchemeGenerator(Parser::ASTNode * astRoot);
			~FSchemeGenerator();
			FSchemeGenerator(const FSchemeGenerator &generator) = delete;
			FSchemeGenerator& operator= (const FSchemeGenerator &generator) = delete;

			void handle(Parser::FunctionalProgram * aFuncProgram) override;
			void handle(Parser::FunctionNode * aFunctionNode) override;
			void handle(Parser::NameRefNode * aNameRefNode) override;
			void handle(Parser::DefinitionNode * aDefinitionNode) override;
			void handle(Parser::ExpressionNode * aExpressionNode) override;
			void handle(Parser::ConditionNode * aExpressionNode) override;
			void handle(Parser::ConstantNode * aNode) override;

			// Получение результата.
			FSchemeNode * getProgram() const;

		private:

			void processBuildInFunction(Parser::NameRefNode * aFunctionNameNode);
			void processFunctionalTerm(Parser::NameRefNode * aFuncTermName);

			typedef std::map<std::string, FScheme*> TLexicalContext;

			std::stack<FSchemeNode *> mNodeStack;

			TLexicalContext mDefinitions;
			std::stack<TLexicalContext> mDefinitionsStack;

			FSchemeNode * mScheme;
			FSchemeNode * mSchemeInput;
			FSchemeNode * mProgram;

			ConstructorGenerator mConstructorGenerator;
		};
	}
}
