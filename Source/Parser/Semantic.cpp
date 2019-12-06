#include "SemanticCheck.h"

namespace FPTL {
	namespace Parser {
		NamesChecker::NamesChecker(Support * aSupport, ASTNode * root) : mSupport(aSupport)
		{
			process(root);
		}

		//---------------------------------------------------------------------------
		void NamesChecker::visit(DataNode * aDataNode)
		{
			if (!mContext.insertName(aDataNode->getDataName(), aDataNode))
			{
				mSupport->semanticError(ErrTypes::DuplicateDefinition, aDataNode->getDataName());
			}

			pushContext();

			NodeVisitor::visit(aDataNode);

			checkNames();
			popContext();
		}

		//---------------------------------------------------------------------------
		void NamesChecker::visit(FunctionNode * aFunctionNode)
		{
			mContext.insertName(aFunctionNode->getFuncName(), aFunctionNode);

			pushContext(aFunctionNode);

			// Добавляем вложенные fun-конструкции в лексический контекст
			for (auto functionNode : aFunctionNode->getFunctionNodes()) {
				if (!mContext.insertName(functionNode->getFuncName(), functionNode)) {
					mSupport->semanticError(ErrTypes::DuplicateDefinition, functionNode->getFuncName());
				}
			}

			NodeVisitor::visit(aFunctionNode);

			// Проверяем наличие главного уравнения.
			if (!aFunctionNode->getDefinition(aFunctionNode->getFuncName()))
			{
				mSupport->semanticError(ErrTypes::MissingMainDefinition, aFunctionNode->getFuncName());
			}

			// Выполняем проверку имен.
			checkNames();
			popContext();
		}


		//---------------------------------------------------------------------------
		void NamesChecker::visit(DefinitionNode * aDefinitionNode)
		{
			switch (aDefinitionNode->getType())
			{
			case ASTNode::FunctionParameterDefinition:
			case ASTNode::Definition:
			case ASTNode::TypeParameterDefinition:
			case ASTNode::InputVarDefinition:
				if (!mContext.insertName(aDefinitionNode->getDefinitionName(), aDefinitionNode))
				{
					// Повторное определение.
					mSupport->semanticError(ErrTypes::DuplicateDefinition, aDefinitionNode->getDefinitionName());
				}
				break;

			case ASTNode::TypeConstructorDefinition:
				if (!mContextStack[0].insertName(aDefinitionNode->getDefinitionName(), aDefinitionNode))
				{
					mSupport->semanticError(ErrTypes::DuplicateDefinition, aDefinitionNode->getDefinitionName());
				}
				break;
			}

			NodeVisitor::visit(aDefinitionNode);
		}

		//---------------------------------------------------------------------------
		void NamesChecker::visit(NameRefNode * aNameNode)
		{
			STermDescriptor termDesc;
			termDesc.TermName = aNameNode->getName();
			termDesc.Node = aNameNode;

			switch (aNameNode->getType())
			{
			case ASTNode::InputVarName:
			case ASTNode::FuncObjectName:
			case ASTNode::TypeParamName:
			case ASTNode::ConstructorName:
			case ASTNode::FuncObjectWithParameters:
			case ASTNode::FuncParameterName:
			case ASTNode::RunningSchemeName:
				mContext.TermsList.push_back(termDesc);
				break;

			case ASTNode::Type:
			case ASTNode::Template:
				mContextStack[0].TermsList.push_back(termDesc);
				break;
			}

			NodeVisitor::visit(aNameNode);
		}

		//---------------------------------------------------------------------------
		void NamesChecker::visit(ApplicationBlock * aApplicationBlock)
		{
			NodeVisitor::visit(aApplicationBlock);

			checkNames();
		}

		//---------------------------------------------------------------------------
		void NamesChecker::pushContext()
		{
			mContextStack.push_back(mContext);
			mContext.clear();
		}

		void NamesChecker::pushContext(FunctionNode * function)
		{
			mContextStack.push_back(mContext);
			mContext.clear();
			mContext.currentFunction = function;
		}

		//---------------------------------------------------------------------------
		void NamesChecker::popContext()
		{
			mContext = mContextStack.back();
			mContextStack.pop_back();
		}

		//---------------------------------------------------------------------------
		void NamesChecker::checkName(STermDescriptor & aTermDesc)
		{
			ASTNode * target = nullptr;

			std::vector<STermDescriptor> undefinedTerms;

			// Сначала ищем в локальном пространстве имен.
			auto pos = mContext.DefinitionsList.find(aTermDesc.TermName);

			if (pos != mContext.DefinitionsList.end())
			{
				target = pos->second;
			}
			else
			{
				// Затем ищем в глобальном пространстве имен.
				if (!mContextStack.empty())
				{
					// Ищем среди определений блоков fun из родительского контекста
					SLexicalContext & parent = mContextStack.back();

					pos = parent.DefinitionsList.find(aTermDesc.TermName);
					if (pos != parent.DefinitionsList.end())
					{
						target = pos->second;
					}
					else
					{
						// Ищем в глобальном контексте (типы данных, конструкторы, ...)
						pos = mContextStack[0].DefinitionsList.find(aTermDesc.TermName);

						if (pos != mContextStack[0].DefinitionsList.end())
						{
							target = pos->second;
						}
						else
						{
							mSupport->semanticError(ErrTypes::UndefinedIdentifier, aTermDesc.TermName);
							return;
						}
					}
				}
				else
				{
					mSupport->semanticError(ErrTypes::UndefinedIdentifier, aTermDesc.TermName);
					return;
				}
			}

			if (aTermDesc.Node->getType() == ASTNode::RunningSchemeName && target->getType() && target->getType() != ASTNode::FunctionBlock)
			{
				mSupport->semanticError(ErrTypes::UndefinedSchemeName, aTermDesc.TermName);
			}

			if (aTermDesc.Node->numParameters() == target->numParameters())
			{
				aTermDesc.Node->setTarget(target);
			}
			else
			{
				// TODO: выводить число требуемых и фактических параметров.
				mSupport->semanticError(ErrTypes::InvalidNumberOfParameters, aTermDesc.TermName);
			}
		}

		//---------------------------------------------------------------------------
		void NamesChecker::checkNames()
		{
			for (auto &termsList : mContext.TermsList)
			{
				checkName(termsList);
			}
		}
	}
}