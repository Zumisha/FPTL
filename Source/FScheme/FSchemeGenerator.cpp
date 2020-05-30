#include <cassert>

#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include "FSchemeGenerator.h"
#include "ConstructorGenerator.h"
#include "NodeDeleter.h"
#include "Parser/Nodes.h"
#include "DataTypes/Ops/DoubleOps.h"
#include "DataTypes/Ops/ADTValue.h"

namespace FPTL
{
	namespace Runtime
	{
		FSchemeGenerator::FSchemeGenerator(Parser::ASTNode * astRoot):
			mScheme(nullptr),
			mSchemeInput(nullptr),
			mProgram(nullptr)
		{
			process(astRoot);
		}

		FSchemeGenerator::~FSchemeGenerator()
		{
			NodeDeleter deleter;
			deleter.releaseGraph(mProgram);
		}

		FSchemeNode * FSchemeGenerator::getProgram() const
		{
			return mProgram;
		}

		//-----------------------------------------------------------------------------
		void FSchemeGenerator::handle(Parser::ConstantNode * aNode)
		{
			FSchemeNode * node = nullptr;

			const auto name = aNode->getConstant();

			switch (aNode->getType())
			{
				// Целочисленная константа.
			case Parser::ASTNode::IntConstant:
			{
				const auto constant = boost::lexical_cast<int64_t>(aNode->getConstant().getStr().c_str());
				node = new FConstantNode(TypeInfo("integer"), DataBuilders::createInt(constant), name.Line, name.Col);
				break;
			}

			// Вещественная константа, длинное целое.
			case Parser::ASTNode::LongLongConstant:
			case Parser::ASTNode::FloatConstant:
			case Parser::ASTNode::DoubleConstant:
			{
				const auto constant = boost::lexical_cast<double>(aNode->getConstant().getStr().c_str());
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

			// Булевы константы.
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
		void FSchemeGenerator::handle(Parser::TakeNode * aTakeNode)
		{
			const auto fromIdent = aTakeNode->getFrom();
			const auto toIdent = aTakeNode->getTo();
			
			int64_t from;
			if (fromIdent.Ptr != nullptr) {
				from = boost::lexical_cast<int64_t>(fromIdent.getStr().c_str());
			}
			else from = 1;
			
			int64_t to;
			if (toIdent.Ptr != nullptr) {
				to = boost::lexical_cast<int64_t>(toIdent.getStr().c_str());
			}
			else to = -1;

			FSchemeNode* node = new FTakeNode(from, to, fromIdent.Line, fromIdent.Col);

			mNodeStack.push(node);
		}

		//-----------------------------------------------------------------------------
		void FSchemeGenerator::handle(Parser::NameRefNode * aNameRefNode)
		{
			NodeVisitor::handle(aNameRefNode);

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
				auto* const ctor = mConstructorGenerator.getConstructor(aNameRefNode->getName().getStr());
				auto name = aNameRefNode->getName();
				FSchemeNode * node = new FFunctionNode(boost::bind(&Constructor::execConstructor, ctor, _1), name.getStr(), name.Line, name.Col);
				mNodeStack.push(node);
				break;
			}

			case Parser::ASTNode::DestructorName:
			{
				const auto ctor = mConstructorGenerator.getConstructor(aNameRefNode->getName().getStr());
				auto name = aNameRefNode->getName();
				FSchemeNode * node = new FFunctionNode(boost::bind(&Constructor::execDestructor, ctor, _1), "~" + name.getStr(), name.Line, name.Col);
				mNodeStack.push(node);
				break;
			}

			case Parser::ASTNode::InputVarName:
			{
				auto* inputVarDef = dynamic_cast<Parser::DefinitionNode *>(aNameRefNode->mTarget);
				process(inputVarDef->getDefinition());
				break;
			}

			default:
				assert(false);
			}
		}

		//-----------------------------------------------------------------------------
		void FSchemeGenerator::handle(Parser::DefinitionNode * aDefinitionNode)
		{
			if (aDefinitionNode->getType() == Parser::ASTNode::Definition)
			{
				auto name = aDefinitionNode->getDefinitionName().getStr();

				auto* me = new FScheme(nullptr, name);
				mDefinitions.insert(std::make_pair(name, me));

				NodeVisitor::handle(aDefinitionNode);

				const auto contents = mNodeStack.top();
				mNodeStack.pop();
				me->setFirstNode(contents);
			}
			else
			{
				NodeVisitor::handle(aDefinitionNode);
			}
		}

		//-----------------------------------------------------------------------------
		void FSchemeGenerator::handle(Parser::ExpressionNode * aExpressionNode)
		{
			NodeVisitor::handle(aExpressionNode);

			switch (aExpressionNode->getType())
			{
			case Parser::ASTNode::SequentialTerm:
			case Parser::ASTNode::ValueConstructor:
			{
				const auto second = mNodeStack.top();
				mNodeStack.pop();

				const auto first = mNodeStack.top();
				mNodeStack.pop();

				// Трансформируем дерево, чтобы оно ветвилось только в левую сторону, 
				// чтобы при выполнении за каждым advance шел unwind.
				const auto seqNode = dynamic_cast<FSequentialNode*>(second);

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
		void FSchemeGenerator::handle(Parser::ConditionNode * aExpressionNode)
		{
			NodeVisitor::handle(aExpressionNode);
			const auto thenBranch = mNodeStack.top();
			mNodeStack.pop();

			const auto middle = aExpressionNode->getCond();
			FSchemeNode * elseBranch = nullptr;
			if (middle)
			{
				elseBranch = mNodeStack.top();
				mNodeStack.pop();
			}

			const auto condition = mNodeStack.top();
			mNodeStack.pop();

			mNodeStack.push(new FConditionNode(condition, thenBranch, elseBranch));
		}

		//-----------------------------------------------------------------------------
		void FSchemeGenerator::processFunctionalTerm(Parser::NameRefNode * aFuncTermName)
		{
			// Проверяем, на кого ссылается имя терма.
			auto target = aFuncTermName->mTarget;

			if (aFuncTermName->getType() == Parser::ASTNode::FuncObjectWithParameters)
			{
				// Создаем новую функциональную схему с параметрами.
				mDefinitionsStack.push(mDefinitions);
				mDefinitions.clear();

				// Добавляем в текущий лексический контекст функциональные параметры.
				// ToDo: сломано наследование - переделать (до этого не использовать dynamic_cast).
				Parser::ListNode * parameters = static_cast<Parser::FunctionNode *>(target)->getFormalParameters();

				for (auto& child : parameters->mChilds)
				{
					FSchemeNode * node = mNodeStack.top();
					mNodeStack.pop();

					// ToDo: сломано наследование - переделать (до этого не использовать dynamic_cast).
					Parser::DefinitionNode * formalParamName = static_cast<Parser::DefinitionNode *>(child);
					//Parser::DefinitionNode * formalParamName = static_cast<Parser::DefinitionNode *>(parameters->mChilds[i]);

					FScheme *delegateScheme = dynamic_cast<FScheme *>(node);
					if (!delegateScheme)
					{
						delegateScheme = new FScheme(node);
					}

					// Здесь нельзя делать insert(), т.к. значения параметров должны переопределяться каждый раз при заходе во вложенную функцию.
					mDefinitions[formalParamName->getDefinitionName().getStr()] = delegateScheme;
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
			const auto function = new FFunctionNode(FunctionLibrary::getFunction(name.getStr()), name.getStr(), name.Line, name.Col);

			mNodeStack.push(function);
		}

		//-----------------------------------------------------------------------------
		void FSchemeGenerator::handle(Parser::FunctionNode * aFunctionNode)
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
		void FSchemeGenerator::handle(Parser::FunctionalProgram * aFuncProgram)
		{
			// Обрабатываем блоки данных.	
			mConstructorGenerator.work(aFuncProgram);

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
	}
}