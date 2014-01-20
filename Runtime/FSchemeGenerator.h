/// Создание функциональных схем по AST-дереву.

#ifndef FSCHEME_GENERATOR_H
#define FSCHEME_GENERATOR_H

#include <map>
#include <functional>
#include <stack>

#include "../Parser/NodeVisitor.h"
#include "Functions.h"
#include "FScheme.h"

namespace FPTL {
namespace Runtime {

class ConstructorGenerator;

//
// Генератор функциональных схем по АСТ-дереву. На вход должно предоставляться только семантически корректное дерево.
//
class FSchemeGenerator : public Parser::NodeVisitor
{
public:

	FSchemeGenerator();
	~FSchemeGenerator();

	virtual void visit(Parser::FunctionalProgram * aFuncProgram);
	virtual void visit(Parser::FunctionNode * aFunctionNode);
	virtual void visit(Parser::NameRefNode * aNameRefNode);
	virtual void visit(Parser::DefinitionNode * aDefinitionNode);
	virtual void visit(Parser::ExpressionNode * aExpressionNode);
	virtual void visit(Parser::ConstantNode * aConstantNode);

	// Запуск генерации функциональной схемы.
	void generateFScheme();

	// Получение результата.
	FSchemeNode * getFScheme();
	FSchemeNode * getSchemeInput();

	ConstructorGenerator * getConstructorGenerator() const;

private:

	void processBuildInFunction(Parser::NameRefNode * aFunctionName);
	void processFunctionalTerm(Parser::NameRefNode * aFuncTermName);

	template <typename F> static FFunctionNode * newFunctionNode(const F &aFunction);
	template <typename F> static FFunctionNode * newFunctionNode(const F &aFunction, const Parser::Ident & aIdent);

private:

	Parser::ASTNode * mTree;

	typedef std::map<std::string, FScheme *> TLexicalContext;

	std::stack<FSchemeNode *> mNodeStack;
	std::stack<bool> mIsParallel;

	TLexicalContext mDefinitions;

	std::stack<TLexicalContext> mDefinitionsStack;

	std::map<std::string, Constructor *> mConstructors;
	
	FSchemeNode * mScheme;
	FSchemeNode * mSchemeInput;

	ConstructorGenerator * mConstructorGenerator;
	FunctionLibrary * mLibrary;
};

} // Runtime
} // FPTL

#endif