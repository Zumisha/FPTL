#include "NewFSchemeGenerator.h"

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "NodeDeleter.h"
#include "DataTypes/Ops/Ops.h"
#include "DataTypes/Ops/ADTValue.h"

namespace FPTL
{
	namespace Runtime
	{
		NewFSchemeGenerator::NewFSchemeGenerator(Parser::ASTNode* astRoot):
			mScheme(nullptr),
			mSchemeInput(nullptr),
			mProgram(nullptr)
		{
			Handle(astRoot);
		}

		NewFSchemeGenerator::~NewFSchemeGenerator()
		{
			NodeDeleter deleter;
			deleter.releaseGraph(mProgram);
		}

		FSchemeNode * NewFSchemeGenerator::getProgram() const
		{
			return mProgram;
		}

		// -------------------------------------------------------------------------------------------------------------

		Parser::ASTNode* NewFSchemeGenerator::getChild(Parser::ExpressionNode * aExpressionNode, size_t childNum)
		{
			switch (childNum)
			{
			case Parser::ExpressionNode::mLeft:
			{
				return aExpressionNode->getLeft();
			}
			case Parser::ExpressionNode::mRight:
			{
				return aExpressionNode->getRight();
			}
			default:
			{
				return nullptr;
			}
			}
		}

		size_t NewFSchemeGenerator::getChildIndex(Parser::ExpressionNode* aExpressionNode, Parser::ASTNode* child)
		{
			if (child == aExpressionNode->getLeft())
			{
				return Parser::ExpressionNode::mLeft;
			}
			else if (child == aExpressionNode->getRight())
			{
				return Parser::ExpressionNode::mRight;
			}
			else
			{
				return -1;
			}
		}

		void NewFSchemeGenerator::intermediateProcessing(Parser::ExpressionNode* aExpressionNode, size_t childNum)
		{
			switch (childNum)
			{
			case Parser::ExpressionNode::mLeft:
			case Parser::ExpressionNode::mRight:
				{
					break;
				}
				// post processing
			default:
			{
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
			}
		}

		void NewFSchemeGenerator::ChildHandled(Parser::ExpressionNode*, size_t)
		{
		}

// -------------------------------------------------------------------------------------------------------------

		Parser::ASTNode* NewFSchemeGenerator::getChild(Parser::ConditionNode * aConditionNode, size_t childNum)
		{
			switch (childNum)
			{
			case Parser::ConditionNode::mThen:
			{
				return aConditionNode->getThen();
			}
			case Parser::ConditionNode::mCond:
			{
				return aConditionNode->getCond();
			}
			case Parser::ConditionNode::mElse:
			{
				return aConditionNode->getElse();
			}
			default:
			{
				return nullptr;
			}
			}
		}

		size_t NewFSchemeGenerator::getChildIndex(Parser::ConditionNode * aConditionNode, Parser::ASTNode* child)
		{
			if (child == aConditionNode->getThen())
			{
				return Parser::ConditionNode::mThen;
			}
			else if (child == aConditionNode->getCond())
			{
				return Parser::ConditionNode::mCond;
			}
			else if (child == aConditionNode->getElse())
			{
				return Parser::ConditionNode::mElse;
			}
			else
			{
				return -1;
			}
		}

		void NewFSchemeGenerator::intermediateProcessing(Parser::ConditionNode* aConditionNode, size_t childNum)
		{
			switch (childNum)
			{
			case Parser::ConditionNode::mThen:
			case Parser::ConditionNode::mCond:
			case Parser::ConditionNode::mElse:
				{
					break;
				}
			// post processing
			default:
			{
				const auto thenBranch = mNodeStack.top();
				mNodeStack.pop();

				const auto middle = aConditionNode->getCond();
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
			}
		}

		void NewFSchemeGenerator::ChildHandled(Parser::ConditionNode*, size_t)
		{
		}

// -------------------------------------------------------------------------------------------------------------

		Parser::ASTNode* NewFSchemeGenerator::getChild(Parser::ConstantNode*, size_t)
		{
			return nullptr;
		}

		size_t NewFSchemeGenerator::getChildIndex(Parser::ConstantNode*, Parser::ASTNode*)
		{
			return -1;
		}

		void NewFSchemeGenerator::intermediateProcessing(Parser::ConstantNode* aConstantNode, size_t)
		{
			FSchemeNode * node = nullptr;

			const auto name = aConstantNode->getConstant();

			switch (aConstantNode->getType())
			{
				// Целочисленная константа.
			case Parser::ASTNode::IntConstant:
			{
				const auto constant = boost::lexical_cast<int64_t>(aConstantNode->getConstant().getStr().c_str());
				node = new FConstantNode(TypeInfo("integer"), DataBuilders::createInt(constant), name.Line, name.Col);
				break;
			}

			// Вещественная константа, длинное целое.
			case Parser::ASTNode::LongLongConstant:
			case Parser::ASTNode::FloatConstant:
			case Parser::ASTNode::DoubleConstant:
			{
				const auto constant = boost::lexical_cast<double>(aConstantNode->getConstant().getStr().c_str());
				node = new FConstantNode(TypeInfo("double"), DataBuilders::createDouble(constant), name.Line, name.Col);
				break;
			}

			// Строковая константа.
			case Parser::ASTNode::StringConstant:
			{
				const std::string str = aConstantNode->getConstant().getStr();
				node = new FStringConstant(str, name.Line, name.Col);
				break;
			}

			// Булевы константы.
			case Parser::ASTNode::TrueValue:
			case Parser::ASTNode::FalseValue:
			{
				node = new FConstantNode(TypeInfo("boolean"), DataBuilders::createBoolean(aConstantNode->getType() == Parser::ASTNode::TrueValue), name.Line, name.Col);
				break;
			}

			default:
			{
				assert(false);
				break;
			}
			}

			mNodeStack.push(node);
		}

		void NewFSchemeGenerator::ChildHandled(Parser::ConstantNode*, size_t)
		{
		}

		// -------------------------------------------------------------------------------------------------------------

		Parser::ASTNode* NewFSchemeGenerator::getChild(Parser::TakeNode*, size_t)
		{
			return nullptr;
		}

		size_t NewFSchemeGenerator::getChildIndex(Parser::TakeNode*, Parser::ASTNode*)
		{
			return -1;
		}

		void NewFSchemeGenerator::intermediateProcessing(Parser::TakeNode* aTakeNode, size_t)
		{
			const auto fromIdent = aTakeNode->getFrom();
			const auto from = boost::lexical_cast<int64_t>(fromIdent.getStr().c_str());
			const auto to = boost::lexical_cast<int64_t>(aTakeNode->getTo().getStr().c_str());			

			FSchemeNode* node = new FTakeNode(from, to, fromIdent.Line, fromIdent.Col);

			mNodeStack.push(node);
		}

		void NewFSchemeGenerator::ChildHandled(Parser::TakeNode*, size_t)
		{
		}

// -------------------------------------------------------------------------------------------------------------

		Parser::ASTNode* NewFSchemeGenerator::getChild(Parser::ListNode * aListNode, size_t childNum)
		{
			if (childNum >= aListNode->mChilds.size()) return nullptr;
			return aListNode->mChilds[aListNode->mChilds.size() - 1 - childNum];
		}

		size_t NewFSchemeGenerator::getChildIndex(Parser::ListNode * aListNode, Parser::ASTNode* child)
		{
			for (auto pair = aListNode->mChilds.rbegin(); pair != aListNode->mChilds.rend(); ++pair)
			{
				if (child == *pair)
				{
					return std::next(pair).base() - aListNode->mChilds.begin();
				}				
			}
			
			return -1;
		}

		void NewFSchemeGenerator::intermediateProcessing(Parser::ListNode * aListNode, size_t childNum)
		{
		}

		void NewFSchemeGenerator::ChildHandled(Parser::ListNode*, size_t)
		{
		}

// -------------------------------------------------------------------------------------------------------------

		Parser::ASTNode* NewFSchemeGenerator::getChild(Parser::DefinitionNode * aDefinitionNode, size_t childNum)
		{
			if (childNum == Parser::DefinitionNode::mDefinition)
			{
				return aDefinitionNode->getDefinition();
			}
			return nullptr;
		}

		size_t NewFSchemeGenerator::getChildIndex(Parser::DefinitionNode * aDefinitionNode, Parser::ASTNode* child)
		{
			if (child == aDefinitionNode->getDefinition())
			{
				return Parser::DefinitionNode::mDefinition;
			}
			else
			{
				return -1;
			}
		}

		void NewFSchemeGenerator::intermediateProcessing(Parser::DefinitionNode * aDefinitionNode, size_t childNum)
		{
			if (childNum == Parser::DefinitionNode::mDefinition &&
				aDefinitionNode->getType() == Parser::ASTNode::Definition)
			{
				auto name = aDefinitionNode->getDefinitionName().getStr();

				auto* me = new FScheme(nullptr, name);
				mDefinitions.insert(std::make_pair(name, me));
			}
		}

		void NewFSchemeGenerator::ChildHandled(Parser::DefinitionNode* aDefinitionNode, size_t childNum)
		{
			if (childNum == Parser::DefinitionNode::mDefinition &&
				aDefinitionNode->getType() == Parser::ASTNode::Definition)
			{
				auto* me = new FScheme(nullptr, aDefinitionNode->getDefinitionName().getStr());
				const auto contents = mNodeStack.top();
				mNodeStack.pop();
				me->setFirstNode(contents);
			}
		}

// -------------------------------------------------------------------------------------------------------------

		// ToDo: разбить Parser::NameRefNode на несколько типов узлов
		Parser::ASTNode* NewFSchemeGenerator::getChild(Parser::NameRefNode * aNameRefNode, size_t childNum)
		{
			switch (childNum)
			{
			case Parser::NameRefNode::mParameters:
			{
				return aNameRefNode->getParameters();
			}
			case Parser::NameRefNode::mParameters + 1:
			{
				switch (aNameRefNode->getType())
				{
				case Parser::ASTNode::BuildInFunction:
				{
					return nullptr;
				}

				case Parser::ASTNode::FuncObjectWithParameters:
				{
					return aNameRefNode->mTarget;
				}
				case Parser::ASTNode::FuncParameterName:
				case Parser::ASTNode::FuncObjectName:
				{
					// Проверяем, на кого ссылается имя терма.
					auto target = aNameRefNode->mTarget;
					const auto name = aNameRefNode->getName().getStr();

					if (target->getType() == Parser::ASTNode::FunctionBlock &&
						mDefinitions.find(name) == mDefinitions.end())
					{
						// Инстанциируем рекурсивную функцию, как только встречаем ее первый раз
						return target;
					}

					if (target->getType() == Parser::ASTNode::Definition)
					{
						// Делаем подстановку нерекурсивного уравнения.
						if (!target->isRecursive())
						{
							return dynamic_cast<Parser::DefinitionNode *>(target)->getDefinition();
						}

						if (mDefinitions.find(name) == mDefinitions.end())
						{
							// Инстанциируем рекурсивную функцию, как только встречаем ее первый раз
							return target;
						}
					}

					return nullptr;
				}

				case Parser::ASTNode::ConstructorName:
				case Parser::ASTNode::DestructorName:
				{
					return nullptr;
				}

				case Parser::ASTNode::InputVarName:
				{
					auto* inputVarDef = dynamic_cast<Parser::DefinitionNode *>(aNameRefNode->mTarget);
					return inputVarDef->getDefinition();
				}

				default:
					assert(false);
					return nullptr;
				}
			}
			default:
			{
				return nullptr;
			}
			}
		}

		size_t NewFSchemeGenerator::getChildIndex(Parser::NameRefNode * aNameRefNode, Parser::ASTNode* child)
		{
			const auto target = aNameRefNode->mTarget;
			if (child == aNameRefNode->getParameters())
			{
				return Parser::NameRefNode::mParameters;
			}
			else if ((child == target &&
						(	aNameRefNode->getType() == Parser::ASTNode::FuncObjectWithParameters ||
							(	aNameRefNode->getType() == Parser::ASTNode::FuncParameterName ||
								aNameRefNode->getType() == Parser::ASTNode::FuncObjectName
							) && (
								target->getType() == Parser::ASTNode::FunctionBlock ||
								(target->getType() == Parser::ASTNode::Definition &&
									target->isRecursive()
								)
							)
						)
					) || (child == dynamic_cast<Parser::DefinitionNode *>(target)->getDefinition() &&
							(	aNameRefNode->getType() == Parser::ASTNode::InputVarName || 
								(	(	aNameRefNode->getType() == Parser::ASTNode::FuncParameterName ||
										aNameRefNode->getType() == Parser::ASTNode::FuncObjectName
									) && target->getType() == Parser::ASTNode::Definition && !target->isRecursive()
								)
							)
						)
				)
			{
				return Parser::NameRefNode::mParameters+1;
			}
			else
			{
				return -1;
			}
		}

		void NewFSchemeGenerator::intermediateProcessing(Parser::NameRefNode * aNameRefNode, size_t childNum)
		{
			switch (childNum)
			{
			case Parser::NameRefNode::mParameters:
			{
					break;
			}
				// либо постобработка, либо есть доп. дочерние
			case Parser::NameRefNode::mParameters + 1:
			{
				switch (aNameRefNode->getType())
				{
				case Parser::ASTNode::BuildInFunction:
				{
					const auto name = aNameRefNode->getName();
					const auto func = FunctionLibrary::getFunction(name.getStr());
					// Ищем функцию в библиотеке.
					const auto function = new FFunctionNode(func.first, func.second, name.getStr(), name.Line, name.Col);
					mNodeStack.push(function);
					break;
				}

				case Parser::ASTNode::FuncObjectWithParameters:
				{
					// Проверяем, на кого ссылается имя терма.
					auto* const target = aNameRefNode->mTarget;
					// Создаем новую функциональную схему с параметрами.
					mDefinitionsStack.push(mDefinitions);
					mDefinitions.clear();

					// Добавляем в текущий лексический контекст функциональные параметры.
					// ToDo: сломано наследование - переделать (до этого не использовать dynamic_cast).
					Parser::ListNode * parameters = static_cast<Parser::FunctionNode *>(target)->getFormalParameters();

					for (auto& child : parameters->mChilds)
					{
						FSchemeNode* node = mNodeStack.top();
						mNodeStack.pop();

						// ToDo: сломано наследование - переделать (до этого не использовать dynamic_cast).
						Parser::DefinitionNode * formalParamName = static_cast<Parser::DefinitionNode *>(child);

						FScheme *delegateScheme = dynamic_cast<FScheme *>(node);
						if (!delegateScheme)
						{
							delegateScheme = new FScheme(node);
						}

						// Здесь нельзя делать insert(), т.к. значения параметров должны переопределяться каждый раз при заходе во вложенную функцию.
						mDefinitions[formalParamName->getDefinitionName().getStr()] = delegateScheme;
					}

					// Генерируем схему для функции.
					break;
				}
				case Parser::ASTNode::FuncParameterName:
				case Parser::ASTNode::FuncObjectName:
				{
					const auto name = aNameRefNode->getName().getStr();
					auto target = aNameRefNode->mTarget;
					if (target->getType() == Parser::ASTNode::Definition || target->getType() == Parser::ASTNode::FunctionBlock)
					{
						if (target->getType() != Parser::ASTNode::Definition || target->isRecursive())
						{
							if (mDefinitions.find(name) != mDefinitions.end())
								mNodeStack.push(mDefinitions.at(name));							
						}				
					}
					else
					{
						mNodeStack.push(mDefinitions.at(name));
					}
					break;
				}

				case Parser::ASTNode::ConstructorName:
				{
					const auto ctor = mConstructorGenerator.getConstructor(aNameRefNode->getName().getStr());
					const auto name = aNameRefNode->getName();
					FSchemeNode * node = new FFunctionNode(boost::bind(&Constructor::execConstructor, ctor, _1), false, name.getStr(), name.Line, name.Col);
					mNodeStack.push(node);
					break;
				}

				case Parser::ASTNode::DestructorName:
				{
					const auto ctor = mConstructorGenerator.getConstructor(aNameRefNode->getName().getStr());
					const auto name = aNameRefNode->getName();
					FSchemeNode * node = new FFunctionNode(boost::bind(&Constructor::execDestructor, ctor, _1), false, "~" + name.getStr(), name.Line, name.Col);
					mNodeStack.push(node);
					break;
				}

				case Parser::ASTNode::InputVarName:
				{
					break;
				}

				default:
					assert(false);
					break;
				}

				break;
			}
			default:
			{
				break;
			}
			}
		}

		void NewFSchemeGenerator::ChildHandled(Parser::NameRefNode* aNameRefNode, size_t childNum)
		{
			switch (childNum)
			{
			case Parser::NameRefNode::mParameters + 1:
			{
				switch (aNameRefNode->getType())
				{
				case Parser::ASTNode::FuncObjectWithParameters:
				{
					// Подставляем сгенерированную схему.
					mNodeStack.push(mDefinitions.at(aNameRefNode->getName().getStr()));

					mDefinitions = mDefinitionsStack.top();
					mDefinitionsStack.pop();
					break;
				}
				case Parser::ASTNode::FuncParameterName:
				case Parser::ASTNode::FuncObjectName:
				{
					// Проверяем, на кого ссылается имя терма.
					auto* const target = aNameRefNode->mTarget;
					const auto name = aNameRefNode->getName().getStr();
					if (target->getType() == Parser::ASTNode::Definition || target->getType() == Parser::ASTNode::FunctionBlock)
					{
						if (target->isRecursive() || target->getType() != Parser::ASTNode::Definition)
						{
							if (mDefinitions.find(name) == mDefinitions.end())
								mNodeStack.push(mDefinitions.at(name));
						}
					}
					break;
				}
				default:
				{
					break;
				}
				}
				break;
			}
			default:
			{
				break;
			}
			}
		}

// -------------------------------------------------------------------------------------------------------------

		Parser::ASTNode* NewFSchemeGenerator::getChild(Parser::ConstructorNode* aConstructorNode, size_t childNum)
		{
			if (childNum == Parser::DataNode::mConstructors)
			{
				return aConstructorNode->getCtorParameters();
			}
			return nullptr;
		}

		size_t NewFSchemeGenerator::getChildIndex(Parser::ConstructorNode * aConstructorNode, Parser::ASTNode* child)
		{
			if (child == aConstructorNode->getCtorParameters())
			{
				return Parser::DataNode::mConstructors;
			}
			else
			{
				return -1;
			}
		}

		void NewFSchemeGenerator::intermediateProcessing(Parser::ConstructorNode* aConstructorNode, size_t childNum)
		{
		}

		void NewFSchemeGenerator::ChildHandled(Parser::ConstructorNode*, size_t)
		{
		}

// -------------------------------------------------------------------------------------------------------------

		Parser::ASTNode* NewFSchemeGenerator::getChild(Parser::DataNode* aDataNode, size_t childNum)
		{
			switch (childNum)
			{
			case Parser::DataNode::mConstructors:
			{
				return aDataNode->getConstructors();
			}
			case Parser::DataNode::mTypeParameters:
			{
				return aDataNode->getTypeParams();
			}
			case Parser::DataNode::mTypeDefinitions:
			{
				return aDataNode->getTypeDefs();
			}
			default:
			{
				return nullptr;
			}
			}
		}

		size_t NewFSchemeGenerator::getChildIndex(Parser::DataNode * aDataNode, Parser::ASTNode* child)
		{
			if (child == aDataNode->getConstructors())
			{
				return Parser::DataNode::mConstructors;
			}
			else if (child == aDataNode->getTypeParams())
			{
				return Parser::DataNode::mTypeParameters;
			}
			else if (child == aDataNode->getTypeDefs())
			{
				return Parser::DataNode::mTypeDefinitions;
			}
			else
			{
				return -1;
			}
		}

		void NewFSchemeGenerator::intermediateProcessing(Parser::DataNode* aDataNode, size_t childNum)
		{
		}

		void NewFSchemeGenerator::ChildHandled(Parser::DataNode*, size_t)
		{
		}

// -------------------------------------------------------------------------------------------------------------

		Parser::ASTNode* NewFSchemeGenerator::getChild(Parser::FunctionNode * aFunctionNode, size_t childNum)
		{
			if (childNum == Parser::FunctionNode::mDefinitions)
			{
				return aFunctionNode->getDefinition(aFunctionNode->getFuncName());
			}
			
			return nullptr;
		}

		size_t NewFSchemeGenerator::getChildIndex(Parser::FunctionNode * aFunctionNode, Parser::ASTNode* child)
		{
			if (child == aFunctionNode->getDefinition(aFunctionNode->getFuncName()))
			{
				return Parser::FunctionNode::mDefinitions;
			}
			else
			{
				return -1;
			}
		}

		void NewFSchemeGenerator::intermediateProcessing(Parser::FunctionNode * aFunctionNode, size_t childNum)
		{
			if (childNum == Parser::FunctionNode::mDefinitions)
			{
				// Сохраняем контекст. Если есть функциональные параметры, контекст сохраняется раньше.
				if (aFunctionNode->getFormalParameters() != nullptr) 
				{
					mDefinitionsStack.push(mDefinitions);
					mDefinitions.clear();
				}
			}
		}

		void NewFSchemeGenerator::ChildHandled(Parser::FunctionNode* aFunctionNode, size_t childNum)
		{
			if (childNum == Parser::FunctionNode::mDefinitions)
			{
				// Сохраняем список определений.
				std::map<std::string, FSchemeNode *> definitionMap;
				for (const auto& elem : mDefinitions)
				{
					definitionMap.insert(std::make_pair(elem.first, elem.second));
				}

				const auto name = aFunctionNode->getFuncName();

				auto* me = mDefinitions.at(name.getStr());
				me->setDefinitions(definitionMap);

				// Восстанавливаем контекст. Если есть функциональные параметры, контекст восстанавливается раньше.
				if (aFunctionNode->getFormalParameters() != nullptr) {
					mDefinitions = mDefinitionsStack.top();
					mDefinitionsStack.pop();

					// fun-блок должен быть виден во внешнем контексте
					mDefinitions.insert(std::make_pair(name.getStr(), me));
				}
			}
		}

// -------------------------------------------------------------------------------------------------------------

		Parser::ASTNode* NewFSchemeGenerator::getChild(Parser::ApplicationBlock * aApplicationBlock, size_t childNum)
		{
			if (childNum == Parser::ApplicationBlock::mSchemeParameters)
			{
				return aApplicationBlock->getSchemeParameters();
			}
			
			return nullptr;
		}

		size_t NewFSchemeGenerator::getChildIndex(Parser::ApplicationBlock * aApplicationBlock, Parser::ASTNode* child)
		{
			if (child == aApplicationBlock->getSchemeParameters())
			{
				return Parser::ApplicationBlock::mSchemeParameters;
			}
			else
			{
				return -1;
			}
		}

		void NewFSchemeGenerator::intermediateProcessing(Parser::ApplicationBlock * aApplicationBlock, size_t childNum)
		{
		}

		void NewFSchemeGenerator::ChildHandled(Parser::ApplicationBlock * aApplicationBlock, size_t childNum)
		{
			if (childNum == Parser::ApplicationBlock::mSchemeParameters)
			{
				mSchemeInput = mNodeStack.top();
				mNodeStack.pop();
				mProgram = new FSequentialNode(mSchemeInput, mScheme);
			}
		}

// -------------------------------------------------------------------------------------------------------------

		Parser::ASTNode* NewFSchemeGenerator::getChild(Parser::FunctionalProgram * aFuncProgram, size_t childNum)
		{
			switch (childNum)
			{
			case Parser::FunctionalProgram::mDataDefinitions:
			{
				return nullptr;
				//return aFuncProgram->getDataDefinitions();
			}
			case Parser::FunctionalProgram::mScheme:
			{
				return aFuncProgram->getScheme();
			}
			case Parser::FunctionalProgram::mApplication:
			{
				return aFuncProgram->getApplication()->getSchemeParameters();
			}
			default:
			{
				return nullptr;
			}
			}
		}

		size_t NewFSchemeGenerator::getChildIndex(Parser::FunctionalProgram * aFuncProgram, Parser::ASTNode* child)
		{
			if (child == aFuncProgram->getScheme())
			{
				return Parser::FunctionalProgram::mScheme;
			}
			else if (child == aFuncProgram->getApplication()->getSchemeParameters())
			{
				return Parser::FunctionalProgram::mApplication;
			}
			else
			{
				return -1;
			}
		}

		void NewFSchemeGenerator::intermediateProcessing(Parser::FunctionalProgram * aFuncProgram, size_t childNum)
		{
			if (childNum == Parser::FunctionalProgram::mDataDefinitions)
			{
				mConstructorGenerator.work(aFuncProgram);
				//return aFuncProgram->getDataDefinitions();
			}
		}

		void NewFSchemeGenerator::ChildHandled(Parser::FunctionalProgram * aFuncProgram, size_t childNum)
		{
			switch (childNum)
			{
			case Parser::FunctionalProgram::mScheme:
			{
				mScheme = mDefinitions[aFuncProgram->getScheme()->getFuncName().getStr()];
				mProgram = mScheme;
					break;
			}
			case Parser::FunctionalProgram::mApplication:
			{
				mSchemeInput = mNodeStack.top();
				mNodeStack.pop();

				mProgram = new FSequentialNode(mSchemeInput, mScheme);
				break;
			}
			}
		}
	}
}
