﻿#include <cassert>

#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include "FSchemeGenerator.h"
#include "ConstructorGenerator.h"
#include "Libraries/StandardLibrary.h"
#include "NodeDeleter.h"
#include "Parser/Nodes.h"
#include "DataTypes/Ops/DoubleOps.h"
#include "DataTypes/Ops/IntegerOps.h"
#include "DataTypes/Ops/BooleanOps.h"
#include "DataTypes/Ops/StringOps.h"

namespace FPTL {
	namespace Runtime {
		//-----------------------------------------------------------------------------
		FSchemeGenerator::FSchemeGenerator(Parser::ASTNode * astRoot)
			: mTree(nullptr),
			mScheme(nullptr),
			mSchemeInput(nullptr),
			mProgram(nullptr),
			mConstructorGenerator(new ConstructorGenerator),
			mLibrary(new StandardLibrary)
		{
			process(astRoot);
		}

		FSchemeGenerator::FSchemeGenerator(const FSchemeGenerator& generator)
		{
			mTree = generator.mTree;
			mScheme = generator.mScheme;
			mSchemeInput = generator.mSchemeInput;
			mProgram = generator.mProgram;
			mConstructorGenerator = new ConstructorGenerator(*generator.mConstructorGenerator);
			mLibrary = new FunctionLibrary(*generator.mLibrary);
		}

		//-----------------------------------------------------------------------------
		FSchemeGenerator::~FSchemeGenerator()
		{
			NodeDeleter deleter;
			deleter.releaseGraph(mProgram);
			delete mLibrary;
			delete mConstructorGenerator;
		}

		FSchemeGenerator & FSchemeGenerator::operator=(const FSchemeGenerator & generator)
		{
			if (this != &generator)
			{
				delete mLibrary;
				delete mConstructorGenerator;

				mTree = generator.mTree;
				mScheme = generator.mScheme;
				mSchemeInput = generator.mSchemeInput;
				mProgram = generator.mProgram;
				mConstructorGenerator = new ConstructorGenerator(*generator.mConstructorGenerator);
				mLibrary = new FunctionLibrary(*generator.mLibrary);
			}

			return *this;
		}

		FSchemeNode * FSchemeGenerator::getProgram() const
		{
			return mProgram;
		}

		//-----------------------------------------------------------------------------
		void FSchemeGenerator::visit(Parser::ConstantNode * aNode)
		{
			FSchemeNode * node = nullptr;

			const auto name = aNode->getConstant();

			switch (aNode->getType())
			{
				// Целочисленная константа.
			case Parser::ASTNode::IntConstant:
			{
				const auto constant = boost::lexical_cast<long long>(aNode->getConstant().getStr().c_str());
				node = new FConstantNode(IntegerOps::staticTypeInfo, IntegerOps::Create(constant), name.Line, name.Col);
				break;
			}

			// Вещественная константа, длинное целое.
			case Parser::ASTNode::LongLongConstant:
			case Parser::ASTNode::FloatConstant:
			case Parser::ASTNode::DoubleConstant:
			{
				const auto constant = boost::lexical_cast<double>(aNode->getConstant().getStr().c_str());
				node = new FConstantNode(DoubleOps::staticTypeInfo, DoubleOps::Create(constant), name.Line, name.Col);
				break;
			}

			// Строковая константа.
			case Parser::ASTNode::StringConstant:
			{
				const std::string str = aNode->getConstant().getStr();				
				node = new FConstantNode(StringOps::staticTypeInfo, StringOps::Create(str), name.Line, name.Col);
				break;
			}

			// Выбор элемента из кортежа.
			case Parser::ASTNode::TupleElemNumber:
			{
				const auto elemNumber = boost::lexical_cast<long long>(aNode->getConstant().getStr().c_str());
				node = new FTakeNode(elemNumber, name.Line, name.Col);
				break;
			}

			// Булевы константы.
			case Parser::ASTNode::TrueValue:
			case Parser::ASTNode::FalseValue:
				node = new FConstantNode(BooleanOps::staticTypeInfo, BooleanOps::Create(aNode->getType() == Parser::ASTNode::TrueValue), name.Line, name.Col);
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
				const auto ctor = mConstructorGenerator->getConstructor(aNameRefNode->getName().getStr());
				auto name = aNameRefNode->getName();
				FSchemeNode * node = new FFunctionNode(boost::bind(&Constructor::execConstructor, ctor, _1), name.getStr(), name.Line, name.Col);
				mNodeStack.push(node);
				break;
			}

			case Parser::ASTNode::DestructorName:
			{
				const auto ctor = mConstructorGenerator->getConstructor(aNameRefNode->getName().getStr());
				auto name = aNameRefNode->getName();
				FSchemeNode * node = new FFunctionNode(boost::bind(&Constructor::execDestructor, ctor, _1), "~" + name.getStr(), name.Line, name.Col);
				mNodeStack.push(node);
				break;
			}

			case Parser::ASTNode::InputVarName:
			{
				auto* inputVarDef = dynamic_cast<Parser::DefinitionNode *>(aNameRefNode->getTarget());
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

				auto* me = new FScheme(nullptr, name);
				mDefinitions.insert(std::make_pair(name, me));

				NodeVisitor::visit(aDefinitionNode);

				const auto contents = mNodeStack.top();
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
				const auto thenBranch = mNodeStack.top();
				mNodeStack.pop();

				const auto middle = aExpressionNode->getMiddle();
				FSchemeNode * elseBranch = nullptr;
				if (middle)
				{
					elseBranch = mNodeStack.top();
					mNodeStack.pop();
				}

				const auto condition = mNodeStack.top();
				mNodeStack.pop();

				mNodeStack.push(new FConditionNode(condition, thenBranch, elseBranch));

				break;
			}

			case Parser::ASTNode::SequentialTerm:
			case Parser::ASTNode::ValueConstructor:
			{
				const auto second = mNodeStack.top();
				mNodeStack.pop();

				const auto first = mNodeStack.top();
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
				const auto right = mNodeStack.top();
				mNodeStack.pop();

				const auto left = mNodeStack.top();
				mNodeStack.pop();

				mNodeStack.push(new FParallelNode(left, right));

				break;
			}
			default:
				throw std::logic_error("unknown node type");
			}
		}

		//-----------------------------------------------------------------------------
		void FSchemeGenerator::processFunctionalTerm(Parser::NameRefNode * aFuncTermName)
		{
			// Проверяем, на кого ссылается имя терма.
			auto target = aFuncTermName->getTarget();

			if (aFuncTermName->getType() == Parser::ASTNode::FuncObjectWithParameters)
			{
				// Создаем новую функциональную схему с параметрами.
				mDefinitionsStack.push(mDefinitions);
				mDefinitions.clear();

				// Добавляем в текущий лексический контекст функциональные параметры.
				// ToDo: сломано наследование - переделать (до этого не использовать dynamic_cast).
				Parser::ListNode * parameters = static_cast<Parser::FunctionNode *>(target)->getFormalParameters();

				for (auto formalParam = parameters->rbegin(); formalParam != parameters->rend(); ++formalParam)
				{
					FSchemeNode * node = mNodeStack.top();
					mNodeStack.pop();

					// ToDo: сломано наследование - переделать (до этого не использовать dynamic_cast).
					Parser::NameRefNode * formalParamName = static_cast<Parser::NameRefNode *>(*formalParam);

					FScheme *delegateScheme = dynamic_cast<FScheme *>(node);
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
						target = dynamic_cast<Parser::DefinitionNode *>(target)->getDefinition();
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
			const auto function = new FFunctionNode(mLibrary->getFunction(name.getStr()), name.getStr(), name.Line, name.Col);

			mNodeStack.push(function);
		}

		//-----------------------------------------------------------------------------
		void FSchemeGenerator::visit(Parser::FunctionNode * aFunctionNode)
		{
			auto name = aFunctionNode->getFuncName();
			const auto mainDef = aFunctionNode->getDefinition(name);

			const bool hasParameters = (aFunctionNode->getFormalParameters() != nullptr);

			// Сохраняем контекст. Если есть функциональные параметры, контекст сохраняется раньше
			if (!hasParameters) {
				mDefinitionsStack.push(mDefinitions);
				mDefinitions.clear();
			}

			process(mainDef);

			// Сохраняем список определений.
			std::map<std::string, FSchemeNode *> definitionMap;
			for (auto elem : mDefinitions)
			{
				definitionMap.insert(std::make_pair(elem.first, elem.second));
			}

			auto me = mDefinitions.at(name.getStr());
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
			mConstructorGenerator->work(aFuncProgram);

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

	}
}
