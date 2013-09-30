// NodeVisitor.cpp - выполняет передачу вызова от конкретного узла к абстрактному.
#include <algorithm>
#include <functional>

#include "NodeVisitor.h"
#include "Nodes.h"

namespace FPTL {
namespace Parser {

void NodeVisitor::visit( NameRefNode * aNameRefNode )
{
	process(aNameRefNode->getParameters());
}

void NodeVisitor::visit( FunctionNode * aFunctionNode )
{ 
	process(aFunctionNode->getDefinitions());
	process(aFunctionNode->getFormalParameters());
}

void NodeVisitor::visit( DefinitionNode * aDefinitionNode )   
{
	process(aDefinitionNode->getDefinition());
}

void NodeVisitor::visit( ConstructorNode * aConstructorNode ) 
{
	process(aConstructorNode->getCtorParameters());
}

void NodeVisitor::visit( DataNode * aDataNode )               
{ 
	process(aDataNode->getConstructors());
	process(aDataNode->getTypeParams());
	process(aDataNode->getTypeDefs());
}

void NodeVisitor::visit( FunctionalProgram * aFuncProgram )
{ 
	process(aFuncProgram->getDataDefinitions());
	process(aFuncProgram->getScheme());
	process(aFuncProgram->getApplication());
}

void NodeVisitor::visit( ApplicationBlock * aApplicationBlock )
{
	process(aApplicationBlock->getRunningSchemeName());
	process(aApplicationBlock->getSchemeParameters());
	process(aApplicationBlock->getDataVarDefinitions());
}

void NodeVisitor::visit( ExpressionNode * aExpressionNode )
{
	process(aExpressionNode->getLeft());
	process(aExpressionNode->getMiddle());
	process(aExpressionNode->getRight());
}

void NodeVisitor::visit( ConstantNode * aConstantNode )
{
}

void NodeVisitor::visit( ListNode * aNode )                    
{
	using namespace std::placeholders;

	std::for_each(aNode->begin(), aNode->end(), std::bind(&NodeVisitor::process, this, _1));
}

void NodeVisitor::process( ASTNode * aNode )
{
	if (aNode)
	{
		aNode->accept( this );
	}
}

} // Parser
} // FPTL