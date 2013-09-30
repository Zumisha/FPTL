#ifndef NODEVISITOR_H
#define NODEVISITOR_H

namespace FPTL { namespace Parser {

class ASTNode;
	class NameRefNode;
	class FunctionNode;
	class DefinitionNode;
	class ConstructorNode;
	class DataNode;
	class FunctionalProgram;
	class ApplicationBlock;
	class ExpressionNode;
	class ConstantNode;
	class ListNode;

class NodeVisitor
{
public:

	virtual ~NodeVisitor() {}

	//
	// Группа методов, вызываемых при входе в конкртеный узел, до обхода его дочерних узлов.
	// Решение об обходе дочерних узлов принимается на основе возвращаемого значения (если true, то обход производится).
	//
	virtual void visit(ListNode * aNode);
	virtual void visit(NameRefNode * aNameRefNode);
	virtual void visit(FunctionNode * aFunctionNode);
	virtual void visit(DefinitionNode * aDefinitionNode);
	virtual void visit(ConstructorNode * aConstructorNode);
	virtual void visit(DataNode * aDataNode);
	virtual void visit(FunctionalProgram * aFuncProgram);
	virtual void visit(ApplicationBlock * aApplicationBlock);
	virtual void visit(ExpressionNode * aExpressionNode);
	virtual void visit(ConstantNode * aConstantNode);

	// Начинает обход дерева.
	void process(ASTNode * aNode );
};

}} // namespace FPTL::Parser

#endif