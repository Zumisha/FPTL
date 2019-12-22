#pragma once

#include <map>
#include <stack>

#include "Parser/NodeVisitor.h"
#include "FScheme.h"
#include "DataTypes/Ops/ADTOps.h"

namespace FPTL
{
	namespace Runtime
	{

		class ConstructorGenerator;

		//
		// Генератор функциональных схем по АСД. На вход должно предоставляться только семантически корректное дерево.
		//
		class FSchemeGenerator : public Parser::NodeVisitor
		{
		public:

			explicit FSchemeGenerator(Parser::ASTNode * astRoot);
			~FSchemeGenerator();
			FSchemeGenerator(const FSchemeGenerator &generator) = delete;
			FSchemeGenerator& operator= (const FSchemeGenerator &generator) = delete;

			void visit(Parser::FunctionalProgram * aFuncProgram) override;
			void visit(Parser::FunctionNode * aFunctionNode) override;
			void visit(Parser::NameRefNode * aNameRefNode) override;
			void visit(Parser::DefinitionNode * aDefinitionNode) override;
			void visit(Parser::ExpressionNode * aExpressionNode) override;
			void visit(Parser::ConditionNode * aExpressionNode) override;
			void visit(Parser::ConstantNode * aNode) override;

			// Получение результата.
			FSchemeNode * getProgram() const;

		private:

			void processBuildInFunction(Parser::NameRefNode * aFunctionNameNode);
			void processFunctionalTerm(Parser::NameRefNode * aFuncTermName);

			Parser::ASTNode * mTree;

			typedef std::map<std::string, FScheme*> TLexicalContext;

			std::stack<FSchemeNode *> mNodeStack;

			TLexicalContext mDefinitions;

			std::stack<TLexicalContext> mDefinitionsStack;

			std::map<std::string, Constructor *> mConstructors;

			FSchemeNode * mScheme;
			FSchemeNode * mSchemeInput;
			FSchemeNode * mProgram;

			ConstructorGenerator * mConstructorGenerator;
			FunctionLibrary * mLibrary;
		};
	}
}
