#include <iterator>

#include "../Parser/Nodes.h"
#include "ConstructorGenerator.h"
#include "Functions.h"

namespace FPTL { namespace Runtime {

//-------------------------------------------------------------------------------------------
ConstructorGenerator::ConstructorGenerator()
{
}

//-------------------------------------------------------------------------------------------
void ConstructorGenerator::visit(Parser::DataNode * aData)
{
	mCurrentData = aData;

	NodeVisitor::visit(aData);

	mTypeParameters.clear();
}

//-------------------------------------------------------------------------------------------
void ConstructorGenerator::visit(Parser::NameRefNode * aNameReference)
{
	if (aNameReference->getType() == Parser::ASTNode::Template)
	{
		mStack.push(mTypeTuple);
		mTypeTuple.clear();
	}

	NodeVisitor::visit(aNameReference);

	switch (aNameReference->getType())
	{
		case Parser::ASTNode::TypeParamName:
		case Parser::ASTNode::BaseType:
		case Parser::ASTNode::Type:
		{
			mTypeTuple.push_back(TypeInfo(aNameReference->getName().getStr()));
			break;
		}

		// Пользовательский тип с параметрами.
		case Parser::ASTNode::Template:
		{
			TypeInfo newType(aNameReference->getName().getStr());
			
			// Добавляем параметры.
			int i = 0;

			Parser::DataNode * data = static_cast<Parser::DataNode *>(aNameReference->getTarget());

			for (auto element : *data->getTypeParams())
			{
				Parser::NameRefNode * paramName = static_cast<Parser::NameRefNode *>(element);
				newType.Parameters[paramName->getName().getStr()] = mTypeTuple[i];
				i++;
			}

			mTypeTuple = mStack.top();
			mStack.pop();
			mTypeTuple.push_back(newType);
			break;
		}
	}
}

//-------------------------------------------------------------------------------------------
void ConstructorGenerator::visit(Parser::DefinitionNode * aDefinition)
{
	NodeVisitor::visit(aDefinition);

	if (aDefinition->getType() == Parser::ASTNode::TypeConstructorDefinition)
	{
		std::string dataName = mCurrentData->getDataName().getStr();
		std::string constructorName = aDefinition->getDefinitionName().getStr();

		Constructor * constructor = !mTypeTuple.empty() ? new Constructor(constructorName, dataName, mTypeTuple, mTypeParameters)
			: new EmptyConstructor(constructorName, dataName);

		// Добавляем новый конструктор в список.
		mConstructors.insert(std::make_pair(constructorName, std::shared_ptr<Constructor>(constructor)));

		mTypeTuple.clear();
	}
	else if (aDefinition->getType() == Parser::ASTNode::TypeParameterDefinition)
	{
		mTypeParameters.push_back(aDefinition->getDefinitionName().getStr());
	}
}

//-------------------------------------------------------------------------------------------
Constructor * ConstructorGenerator::getConstructor(const std::string & aConstructorName) const
{
	return mConstructors.at(aConstructorName).get();
}

//-------------------------------------------------------------------------------------------
std::vector<std::string> ConstructorGenerator::constructors() const
{
	std::vector<std::string> result;

	for (auto &arg : mConstructors)
	{
		result.push_back(arg.first);
	}
	return result;
}

}} // FPTL::Runtime