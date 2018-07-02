#include <cassert>

#include <boost/lexical_cast.hpp>

#include "FSchemeGenerator.h"
#include "ConstructorGenerator.h"
#include "../Parser/BuildInFunctionNames.h"
#include "StandartLibrary.h"
#include "String.h"
#include "NodeDeleter.h"

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
		: mTree(nullptr), 
		  mScheme(nullptr),
		  mSchemeInput(nullptr), 
		  mProgram(nullptr),
		  mConstructorGenerator(new ConstructorGenerator),
		  mLibrary(new StandartLibrary)
	{
	}

//-----------------------------------------------------------------------------
FSchemeGenerator::~FSchemeGenerator()
{
	NodeDeleter deleter;

	deleter.releaseGraph(mProgram);

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

FSchemeNode * FSchemeGenerator::getProgram()
{
	return mProgram;
}

//-----------------------------------------------------------------------------
ConstructorGenerator * FSchemeGenerator::getConstructorGenerator() const
{
	return mConstructorGenerator;
}

//-----------------------------------------------------------------------------
void FSchemeGenerator::visit(Parser::ConstantNode * aNode)
{
	FSchemeNode * node = nullptr;

	const Parser::Ident name = aNode->getConstant();

	switch (aNode->getType())
	{
		// Целочисленная константа.
		case Parser::ASTNode::IntConstant:
		{
			const long constant = std::atoi(aNode->getConstant().getStr().c_str());
			node = new FConstantNode(TypeInfo("integer"), DataBuilders::createInt(constant), name.Line, name.Col);
			break;
		}

		// Динное целое. НАТИВНО НЕ ПОДДЕРЖИВАЕТСЯ.
		case Parser::ASTNode::LongLongConstant:
		{
			const auto value = boost::lexical_cast<double>(aNode->getConstant().getStr());
			node = new FConstantNode(TypeInfo("double"), DataBuilders::createDouble(value), name.Line, name.Col);
			break;
		}

		// Вещественная константа.
		case Parser::ASTNode::FloatConstant:
		case Parser::ASTNode::DoubleConstant:
		{
			const double constant = std::atof(aNode->getConstant().getStr().c_str());
			node = new FConstantNode(TypeInfo("double"), DataBuilders::createDouble(constant), name.Line, name.Col);
			break;
		}

		// Строковая константа.
		case Parser::ASTNode::StringConstant:
		{
			const std::string str = aNode->getConstant().getStr();
			node = new FStringConstant(str, name.Line, name.Col);
			break;
		}

		// Выбор элемента из кортежа.
		case Parser::ASTNode::TupleElemNumber:
		{
			const int elemNumber = std::atoi(aNode->getConstant().getStr().c_str()) - 1;
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
	if (aDefinitionNode->getType() == Parser::ASTNode::Definition)
	{
		auto name = aDefinitionNode->getDefinitionName().getStr();

		FScheme * me = new FScheme(nullptr, name);
		mDefinitions.insert(std::make_pair(name, me));

		NodeVisitor::visit(aDefinitionNode);

		FSchemeNode * contents = mNodeStack.top();
		mNodeStack.pop();
		me->setFirstNode(contents);
	}
	else
	{
		NodeVisitor::visit(aDefinitionNode);
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
			const auto seqNode = dynamic_cast<FSequentialNode *>(second);

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

	if (aFuncTermName->getType() == Parser::ASTNode::FuncObjectWithParameters)
	{
		// Создаем новую функциональную схему с параметрами.
		mDefinitionsStack.push(mDefinitions);
		mDefinitions.clear();

		// Добавляем в текущий лексический контекст функциональные параметры.
		Parser::ListNode * parameters = static_cast<Parser::FunctionNode *>(target)->getFormalParameters();

		for (auto formalParam = parameters->rbegin(); formalParam != parameters->rend(); ++formalParam)
		{
			FSchemeNode * node = mNodeStack.top();
			mNodeStack.pop();

			Parser::NameRefNode * formalParamName = static_cast<Parser::NameRefNode *>(*formalParam);			

			FScheme * delegateScheme = dynamic_cast<FScheme *>(node);
			if (!delegateScheme)
			{
				delegateScheme = new FScheme(node);
			}

			// Здесь нельзя делать insert(), т.к. значения параметров должны переопределяться каждый раз при заходе во вложенную функцию.
			mDefinitions[formalParamName->getName().getStr()] = delegateScheme;
		}

		// Генерируем схему для функции.
		process(target);

		// Подставляем сгенерированную схему.
		mNodeStack.push(mDefinitions.at(aFuncTermName->getName().getStr()));

		mDefinitions = mDefinitionsStack.top();
		mDefinitionsStack.pop();

		return;
	} 
	else
	{
		const auto name = aFuncTermName->getName().getStr();
		if (target->getType() == Parser::ASTNode::Definition || target->getType() == Parser::ASTNode::FunctionBlock)
		{
			// Делаем подстановку нерекурсивного уравнения.
			if (!target->isRecursive() && target->getType() == Parser::ASTNode::Definition)
			{
				target = static_cast<Parser::DefinitionNode *>(target)->getDefinition();
				process(target);
				return;
			}
			else
			{
				if (mDefinitions.find(name) == mDefinitions.end())
				{
					// Инстанциируем рекурсивную функцию, как только встречаем ее первый раз
					process(target);
				}

				mNodeStack.push(mDefinitions.at(name));
				return;
			}
		}
		else
		{
			// Базисная функция, переданная, как функциональный параметр
			mNodeStack.push(mDefinitions.at(name));
			return;
		}
	}
}

//-----------------------------------------------------------------------------
void FSchemeGenerator::processBuildInFunction(Parser::NameRefNode * aFunctionNameNode)
{
	Parser::Ident name = aFunctionNameNode->getName();
	
	// Ищем функцию в библиотеке.
	const auto function = newFunctionNode(mLibrary->getFunction(name.getStr()), name);

	mNodeStack.push(function);
}

//-----------------------------------------------------------------------------
void FSchemeGenerator::visit(Parser::FunctionNode * aFunctionNode)
{
	auto name = aFunctionNode->getFuncName();
	auto mainDef = aFunctionNode->getDefinition(name);

	bool hasParameters = (aFunctionNode->getFormalParameters() != nullptr);

	// Сохраняем контекст. Если есть функциональные параметры, контекст сохраняется раньше
	if (!hasParameters) {
		mDefinitionsStack.push(mDefinitions);
		mDefinitions.clear();
	}

	process(mainDef);

	// Сохраняеи список определений.
	std::map<std::string, FSchemeNode *> definitionMap;
	std::for_each(mDefinitions.begin(), mDefinitions.end(), [&](const std::pair<std::string, FScheme *> & elem) -> void
		{
			// FIXME: нужно добавлять только те функции, которые есть в aFunctionNode, а не в контексте!
			definitionMap.insert(std::make_pair(elem.first, elem.second));
		}
	);

	FScheme * me = mDefinitions.at(name.getStr());
	me->setDefinitions(definitionMap);

	// Восстанавливаем контекст
	if (!hasParameters) {
		mDefinitions = mDefinitionsStack.top();
		mDefinitionsStack.pop();

		// fun-блок должен быть виден во внешнем контексте
		mDefinitions.insert(std::make_pair(name.getStr(), me));
	}
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

		mProgram = new FSequentialNode(mSchemeInput, mScheme);
	}
	else
	{
		mProgram = mScheme;
	}
}

//-----------------------------------------------------------------------------

}} // FPTL::Runtime