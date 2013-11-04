#include <cassert>

#include <boost/lexical_cast.hpp>

#include "FSchemeGenerator.h"
#include "ConstructorGenerator.h"
#include "../Parser/BuildInFunctionNames.h"
#include "StandartLibrary.h"
#include "String.h"

namespace FPTL {
namespace Runtime {

namespace BFNames = Parser::BuildInFunctions;

//-----------------------------------------------------------------------------
// TODO: эти 2 функции больше не нужны.
template <typename F>
FFunctionNode * FSchemeGenerator::newFunctionNode(const F &aFunction)
{
	return new FFunctionNode(aFunction);
}

template <typename F>
FFunctionNode * FSchemeGenerator::newFunctionNode(const F &aFunction, const Parser::Ident & aIdent)
{
	return new FFunctionNode(aFunction, aIdent.getStr(), aIdent.Line, aIdent.Col);
}

//-----------------------------------------------------------------------------
FSchemeGenerator::FSchemeGenerator()
	: mScheme(0),
	  mSchemeInput(0),
	  mLibrary(new StandartLibrary),
	  mConstructorGenerator(new ConstructorGenerator)
{
}

//-----------------------------------------------------------------------------
FSchemeGenerator::~FSchemeGenerator()
{
	delete mLibrary;
	delete mConstructorGenerator;
}

//-----------------------------------------------------------------------------
FSchemeNode * FSchemeGenerator::getFScheme()
{
	return mScheme;
}

//-----------------------------------------------------------------------------
FSchemeNode * FSchemeGenerator::getSchemeInput()
{
	return mSchemeInput;
}

//-----------------------------------------------------------------------------
void FSchemeGenerator::visit(Parser::ConstantNode * aNode)
{
	FSchemeNode * node = 0;

	Parser::Ident name = aNode->getConstant();

	switch (aNode->getType())
	{
		// Целочисленная константа.
		case Parser::ASTNode::IntConstant:
		{
			long constant = std::atoi(aNode->getConstant().getStr().c_str());
			node = new FConstantNode(TypeInfo("integer"), DataBuilders::createInt(constant), name.Line, name.Col);
			break;
		}

		// Динное целое. НАТИВНО НЕ ПОДДЕРЖИВАЕТСЯ.
		case Parser::ASTNode::LongLongConstant:
		{
			auto value = boost::lexical_cast<double>(aNode->getConstant().getStr());
			node = new FConstantNode(TypeInfo("double"), DataBuilders::createDouble(value), name.Line, name.Col);
			break;
		}

		// Вещественная константа.
		case Parser::ASTNode::FloatConstant:
		case Parser::ASTNode::DoubleConstant:
		{
			double constant = std::atof(aNode->getConstant().getStr().c_str());
			node = new FConstantNode(TypeInfo("double"), DataBuilders::createDouble(constant), name.Line, name.Col);
			break;
		}

		// Строковая константа.
		case Parser::ASTNode::StringConstant:
		{
			std::string str = aNode->getConstant().getStr();
			node = new FStringConstant(str, name.Line, name.Col);
			break;
		}

		// Выбор элемента из кортежа.
		case Parser::ASTNode::TupleElemNumber:
		{			
			int elemNumber = std::atoi(aNode->getConstant().getStr().c_str()) - 1;
			assert(elemNumber >= 0);

			node = new FTakeNode(elemNumber, name.Line, name.Col);
			break;
		}

		// Булевские константы.

		case Parser::ASTNode::TrueValue:
		case Parser::ASTNode::FalseValue:
			node = new FConstantNode(TypeInfo("boolean"), DataBuilders::createBoolean(aNode->getType() == Parser::ASTNode::TrueValue), name.Line, name.Col);
			break;

		default:
			assert(false);
	}

	mNodeStack.push(node);
}

//-----------------------------------------------------------------------------
void FSchemeGenerator::visit(Parser::NameRefNode * aNameRefNode)
{
	NodeVisitor::visit(aNameRefNode);

	switch (aNameRefNode->getType())
	{
		case Parser::ASTNode::BuildInFunction:
		{
			processBuildInFunction(aNameRefNode);
			break;
		}

		case Parser::ASTNode::FuncParameterName:
		case Parser::ASTNode::FuncObjectWithParameters:
		case Parser::ASTNode::FuncObjectName:
		{
			processFunctionalTerm(aNameRefNode);
			break;
		}

		case Parser::ASTNode::ConstructorName:
		{
			Constructor * ctor = mConstructorGenerator->getConstructor(aNameRefNode->getName().getStr());
			FSchemeNode * node = newFunctionNode(boost::bind(&Constructor::execConstructor, ctor, _1), aNameRefNode->getName());
			mNodeStack.push(node);
			break;
		}

		case Parser::ASTNode::DestructorName:
		{
			Constructor * ctor = mConstructorGenerator->getConstructor(aNameRefNode->getName().getStr());
			FSchemeNode * node = newFunctionNode(boost::bind(&Constructor::execDestructor, ctor, _1));
			mNodeStack.push(node);
			break;
		}

		case Parser::ASTNode::InputVarName:
		{
			Parser::DefinitionNode * inputVarDef = static_cast<Parser::DefinitionNode *>(aNameRefNode->getTarget());
			process(inputVarDef->getDefinition());
			break;
		}

		default:
			assert(false);
	}
}

//-----------------------------------------------------------------------------
void FSchemeGenerator::visit(Parser::DefinitionNode * aDefinitionNode)
{
	NodeVisitor::visit(aDefinitionNode);

	if (aDefinitionNode->getType() == Parser::ASTNode::Definition)
	{
		FScheme * scheme = mDefinitions[aDefinitionNode->getDefinitionName().getStr()];

		FSchemeNode * contents = mNodeStack.top();
		mNodeStack.pop();
		scheme->setFirstNode(contents);
	}
}

//-----------------------------------------------------------------------------
void FSchemeGenerator::visit(Parser::ExpressionNode * aExpressionNode)
{
	NodeVisitor::visit(aExpressionNode);

	switch (aExpressionNode->getType())
	{
		case Parser::ASTNode::ConditionTerm:
		{
			FSchemeNode * thenBranch = mNodeStack.top();
			mNodeStack.pop();

			Parser::ASTNode * middle = aExpressionNode->getMiddle();
			FSchemeNode * elseBranch = 0;
			if (middle)
			{
				elseBranch = mNodeStack.top();
				mNodeStack.pop();
			}

			FSchemeNode * condition = mNodeStack.top();
			mNodeStack.pop();

			mNodeStack.push(new FConditionNode(condition, thenBranch, elseBranch));

			break;
		}

		case Parser::ASTNode::SequentialTerm:
		case Parser::ASTNode::ValueConstructor:
		{
			FSchemeNode * second = mNodeStack.top();
			mNodeStack.pop();

			FSchemeNode * first = mNodeStack.top();
			mNodeStack.pop();

			// Трансформируем дерево, чтобы оно ветвилось только в левую сторону, 
			// чтобы при выполнении за каждым advance шел unwind.
			auto seqNode = dynamic_cast<FSequentialNode *>(second);

			if (seqNode)
			{
				mNodeStack.push(new FSequentialNode(new FSequentialNode(first, seqNode->first()), seqNode->second()));	
			}
			else
			{
				mNodeStack.push(new FSequentialNode(first, second));
			}

			break;
		}

		case Parser::ASTNode::CompositionTerm:
		case Parser::ASTNode::ValueComposition:
		case Parser::ASTNode::InputVarList:
		{
			FSchemeNode * right = mNodeStack.top();
			mNodeStack.pop();

			FSchemeNode * left = mNodeStack.top();
			mNodeStack.pop();

			mNodeStack.push(new FParallelNode(left, right));

			break;
		}
	}
}

//-----------------------------------------------------------------------------
void FSchemeGenerator::processFunctionalTerm(Parser::NameRefNode * aFuncTermName)
{
	// Проверяем, на кого ссылается имя терма.
	Parser::ASTNode * target = aFuncTermName->getTarget();

	if (target->getType() == Parser::ASTNode::Definition)
	{
		// Делаем подстановку нерекурсивного уравнения.
		if (!target->isRecursive())
		{
			target = static_cast<Parser::DefinitionNode *>(target)->getDefinition();
			process(target);

			return;
		}
	}

	if (aFuncTermName->getType() == Parser::ASTNode::FuncObjectWithParameters)
	{
		// Создаем новую функциональную схему с параметрами.
		mDefinitionsStack.push(mDefinitions);

		// Добавляем в текущий лексический контекст функциональные параметры.
		Parser::ListNode * parameters = static_cast<Parser::FunctionNode *>(target)->getFormalParameters();

		for (auto formalParam = parameters->rbegin(); formalParam != parameters->rend(); ++formalParam)
		{
			FSchemeNode * node = mNodeStack.top();
			mNodeStack.pop();

			FScheme * delegateScheme = new FScheme(node);

			Parser::NameRefNode * formalParamName = static_cast<Parser::NameRefNode *>(*formalParam);

			// Здесь нельзя делать insert(), т.к. значения параметров должны переопределяться каждый раз при заходе во вложенную функцию.
			mDefinitions[formalParamName->getName().getStr()] = delegateScheme;
		}

		// Генерируем схему для функции.
		// TODO: target может быть функцией для встроенной библиотеки.
		// в этом случае необходимо передать ей все функциональные параметры в виде функций Fi: aCtx -> void
		process(target);

		// Подставляем сгенерированную схему.
		mNodeStack.push(mDefinitions[aFuncTermName->getName().getStr()]);

		mDefinitions = mDefinitionsStack.top();
		mDefinitionsStack.pop();

		return;
	}

	mNodeStack.push(mDefinitions[aFuncTermName->getName().getStr()]);
}

//-----------------------------------------------------------------------------
void FSchemeGenerator::processBuildInFunction(Parser::NameRefNode * aFunctionNameNode)
{
	Parser::Ident name = aFunctionNameNode->getName();
	
	// Ищем функцию в библиотеке.
	auto function = newFunctionNode(mLibrary->getFunction(name.getStr()), name);

	mNodeStack.push(function);
}

//-----------------------------------------------------------------------------
void FSchemeGenerator::visit(Parser::FunctionNode * aFunctionNode)
{
	Parser::ListNode * definitions = aFunctionNode->getDefinitions();

	std::vector<Parser::ASTNode *> toProcess;

	// Создаем узлы схемы для каждого рекурсивного функционального уравнения и функции без параметров.
	for (Parser::ListNode::iterator it = definitions->begin(); it != definitions->end(); ++it)
	{
		Parser::ASTNode * aDef = *it;

		if (aDef->getType() == Parser::ASTNode::FunctionBlock)
		{
			Parser::FunctionNode * function = static_cast<Parser::FunctionNode *>(aDef);

			if (!function->getFormalParameters())
			{
				// Генерируем схемы для внутренних функций.
				mDefinitionsStack.push(mDefinitions);
				mDefinitions.clear();

				process(aDef);

				FScheme * scheme = mDefinitions[function->getFuncName().getStr()];
				mDefinitions = mDefinitionsStack.top();
				mDefinitionsStack.pop();
				mDefinitions.insert(std::make_pair(function->getFuncName().getStr(), scheme));
			}
		}
		else if (aDef->getType() == Parser::ASTNode::Definition)
		{
			Parser::DefinitionNode * definition = static_cast<Parser::DefinitionNode *>(aDef);

			if (definition->isRecursive() || definition->getDefinitionName() == aFunctionNode->getFuncName())
			{
				mDefinitions.insert(std::make_pair(definition->getDefinitionName().getStr(), new FScheme(0)));
				toProcess.push_back(aDef);
			}
		}
	}

	std::for_each(toProcess.begin(), toProcess.end(), [this](Parser::ASTNode * aDef)
	{
		process(aDef);
	});
}

//-----------------------------------------------------------------------------
void FSchemeGenerator::visit(Parser::FunctionalProgram * aFuncProgram)
{
	// Обрабатываем блоки данных.
	if (aFuncProgram->getDataDefinitions())
	{
		mConstructorGenerator->process(aFuncProgram->getDataDefinitions());
	}

	// Обрабатываем только схему.
	process(aFuncProgram->getScheme());

	mScheme = mDefinitions[aFuncProgram->getScheme()->getFuncName().getStr()];

	// Обрабатываем входные данные секции Application.
	if (aFuncProgram->getApplication()->getSchemeParameters())
	{
		process(aFuncProgram->getApplication()->getSchemeParameters());

		mSchemeInput = mNodeStack.top();
		mNodeStack.pop();
	}
}

//-----------------------------------------------------------------------------

}} // FPTL::Runtime