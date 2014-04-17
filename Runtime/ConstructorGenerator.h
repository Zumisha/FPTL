#ifndef CONSTRUCTOR_GENERATOR_H
#define CONSTRUCTOR_GENERATOR_H

#include <string>
#include <map>
#include <stack>

#include "../Parser/NodeVisitor.h"
#include "Types.h"

namespace FPTL { namespace Runtime {

class Constructor;

class ConstructorGenerator : public Parser::NodeVisitor
{
public:

	ConstructorGenerator();

	virtual void visit(Parser::DataNode * aData);
	virtual void visit(Parser::NameRefNode * aNameReference);
	virtual void visit(Parser::DefinitionNode * aDefinition);

	Constructor * getConstructor(const std::string & aConstructorName) const;
	std::vector<std::string> constructors() const;

private:

	Parser::DataNode * mCurrentData;

	// Сгенерированные эталонные типы для конструкторов.
	std::map<std::string, std::shared_ptr<Constructor>> mConstructors;

	TTypeList mTypeTuple;
	std::stack<TTypeList> mStack;

	// Типовые параметры для типа, определяемого конструкторами.
	std::vector<std::string> mTypeParameters;
};

}} // FPTL::Runtime

#endif