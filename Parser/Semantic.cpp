#include "SemanticCheck.h"
#include "boost/bind.hpp"

// Semantic.cpp - реализация класса для семантической проверки структуры программы.

namespace FPTL { namespace Parser {

//---------------------------------------------------------------------------
NamesChecker::NamesChecker( Support * aSupport ) : mSupport(aSupport)
{}

//---------------------------------------------------------------------------
void NamesChecker::visit( DataNode * aDataNode )
{
	if( mContext.insertName( aDataNode->getDataName(), aDataNode ) == false )
	{
		mSupport->semanticError( ErrTypes::DuplicateDefinition, aDataNode->getDataName() );
	}

	pushContext();

	NodeVisitor::visit(aDataNode);

	checkNames();
	popContext();
}

//---------------------------------------------------------------------------
void NamesChecker::visit( FunctionNode * aFunctionNode )
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
void NamesChecker::visit( DefinitionNode * aDefinitionNode )
{
	switch (aDefinitionNode->getType())
	{
		case ASTNode::FunctionParameterDefinition:
		case ASTNode::Definition:
			if (aDefinitionNode->numArguments())
			{
				// проверка на повторение аргументов
				if (!aDefinitionNode->hasDuplicates())
				{
					// создание фейковых уравнений
					//ListNode * FEList = aDefinitionNode->getFakeEquations(); //FIXME хранение и удаление
					//FEList = new ListNode(ConstantNode::TupleElemNumber);
					int i = 0;
					ListNode * pList = aDefinitionNode->getArguments();
					for (ListNode::iterator it = pList->begin(); it != pList->end(); ++it)
					{
						NameRefNode * arg = static_cast<NameRefNode*>(*it);
						Ident ident = arg->getName();

						Ident newId;
						mSupport->newIdent(std::to_string(++i), 0, newId);
						newId.Col = ident.Col;
						newId.Line = ident.Line;
						ConstantNode * node = new ConstantNode(ASTNode::TupleElemNumber, newId);
								
						//FEList->addElement(node);   //  FIXME
						mContext.insertArg(ident, node);
					}
				}
				else
				{
					// FIXME вместо getDefinitionName() должен быть Ident повторяемого аргумента
					// переделать метод hasDuplicates()
					mSupport->semanticError(ErrTypes::DuplicateDefinition, aDefinitionNode->getDefinitionName());
					return;
				}
			}
			if (mContext.insertName(aDefinitionNode->getDefinitionName(), aDefinitionNode) == false)
			{
				// Повторное определение.
				mSupport->semanticError(ErrTypes::DuplicateDefinition, aDefinitionNode->getDefinitionName());
			}
			break;
		case ASTNode::TypeParameterDefinition:
		case ASTNode::InputVarDefinition:
			if (mContext.insertName(aDefinitionNode->getDefinitionName(), aDefinitionNode) == false)
			{
				// Повторное определение.
				mSupport->semanticError(ErrTypes::DuplicateDefinition, aDefinitionNode->getDefinitionName());
			}
			break;

		case ASTNode::TypeConstructorDefinition:
			if (mContextStack[0].insertName( aDefinitionNode->getDefinitionName(), aDefinitionNode ) == false)
			{
				mSupport->semanticError( ErrTypes::DuplicateDefinition, aDefinitionNode->getDefinitionName() );
			}
			break;
	}

	NodeVisitor::visit(aDefinitionNode);

	if (aDefinitionNode->numArguments())
	{
		// Удаляем добавлененные раннее фейковые уравнения
		ListNode * pList = aDefinitionNode->getArguments();
		for (auto it = pList->begin(); it != pList->end(); ++it)
		{
			NameRefNode * arg = static_cast<NameRefNode*>(*it);
			mContext.eraseArg(arg->getName());
		}
	}
}

void NamesChecker::visit(ExpressionNode * aNode)
{
	ASTNode * lNode = aNode->getLeft();
	ASTNode * rNode = aNode->getRight();
	if (lNode != nullptr && rNode != nullptr)
		if (aNode->getType() != ASTNode::CompositionTerm &&
			lNode->getType() == ASTNode::FuncNamedArg && 
			rNode->getType() == ASTNode::FuncNamedArg)
		{
			mSupport->semanticError(ErrTypes::UndefinedIdentifier, (static_cast<NameRefNode *>(rNode))->getName());
			return;
		}
	NodeVisitor::visit(aNode);
}

//---------------------------------------------------------------------------
void NamesChecker::visit( NameRefNode * aNameNode )
{
	STermDescriptor termDesc;
	termDesc.TermName = aNameNode->getName();
	termDesc.Node = aNameNode;
	 
	switch( aNameNode->getType() )
	{
		case ASTNode::InputVarName:
		case ASTNode::FuncObjectName:
		case ASTNode::TypeParamName:
		case ASTNode::ConstructorName:
		case ASTNode::FuncObjectWithParameters:
		case ASTNode::FuncParameterName:
		case ASTNode::RunningSchemeName:
			mContext.TermsList.push_back( termDesc );
			break;

		case ASTNode::FuncNamedArg:
			{
				std::map<Ident, ASTNode*>::iterator pos = mContext.ArgumentsList.find(aNameNode->getName());
				if (pos != mContext.ArgumentsList.end())
				{
					ConstantNode * node = static_cast<ConstantNode *> (pos->second);
					aNameNode->setTarget(node);
				}
				else
				{
					mSupport->semanticError(ErrTypes::UndefinedIdentifier, aNameNode->getName());
					return;
				}
			}
			break;

		case ASTNode::Type:
		case ASTNode::Template:
			mContextStack[0].TermsList.push_back( termDesc );
			break;
	}

	NodeVisitor::visit(aNameNode);
}

//---------------------------------------------------------------------------
void NamesChecker::visit( ApplicationBlock * aApplicationBlock )
{
	NodeVisitor::visit(aApplicationBlock);

	checkNames();
}

//---------------------------------------------------------------------------
void NamesChecker::pushContext()
{
	mContextStack.push_back( mContext );
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
void NamesChecker::checkName( STermDescriptor & aTermDesc )
{
	ASTNode * target = 0;

	std::vector<STermDescriptor> undefinedTerms;

	// Сначала ищем в локальном пространстве имен.
	std::map<Ident,ASTNode*>::iterator pos = mContext.DefinitionsList.find( aTermDesc.TermName );

	if( pos != mContext.DefinitionsList.end() )
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
			mSupport->semanticError( ErrTypes::UndefinedIdentifier, aTermDesc.TermName);
			return;
		}
	}

	if (aTermDesc.Node->getType() == ASTNode::RunningSchemeName && target->getType() && target->getType() != ASTNode::FunctionBlock)
	{
		mSupport->semanticError(ErrTypes::UndefinedSchemeName, aTermDesc.TermName);
	}

	if( aTermDesc.Node->numParameters() == target->numParameters() )
	{
		aTermDesc.Node->setTarget( target );
	}
	else
	{
		// TODO: выводить число требуемых и фактических параметров.
		mSupport->semanticError( ErrTypes::InvalidNumberOfParameters, aTermDesc.TermName );
	}
}

//---------------------------------------------------------------------------
void NamesChecker::checkNames()
{
	std::for_each( mContext.TermsList.begin(), mContext.TermsList.end(), boost::bind( &NamesChecker::checkName, this, _1 ) );
}

}} // FPTL::Parser