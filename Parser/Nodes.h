// Nodes.h - узлы абстрактного синтаксического дерева.
#ifndef NODES_H
#define NODES_H

#include "AST.h"
#include "Ident.h"
#include <list>

namespace FPTL {
namespace Parser {

class Support;


//-------------------------------------------------------------------------------------
// Выражение.

class ExpressionNode : public ASTNode
{
public:

	ExpressionNode( ASTNodeType aType, ASTNode * aLeft, ASTNode * aRight );
	ExpressionNode( ASTNodeType aType, ASTNode * aLeft, ASTNode * aRight, ASTNode * aMiddle );
	~ExpressionNode();

	ASTNode * getLeft() const { return mLeft; }
	ASTNode * getRight() const { return mRight; }
	ASTNode * getMiddle() const { return mMiddle; }

	void accept( NodeVisitor * aVisitor );

	ASTNode * copy() const;

private:

	ASTNode * mLeft;
	ASTNode * mRight;
	ASTNode * mMiddle;
};

//-------------------------------------------------------------------------------------
// Описание константы.

class ConstantNode : public ASTNode
{
public:

	ConstantNode( ASTNodeType aType, Ident aConstant ) : ASTNode(aType), mIdent(aConstant)
	{}

	Ident getConstant() const { return mIdent; }

	bool isNatural() const;
	void accept( NodeVisitor * aVisitor );
	ASTNode * copy() const;

private:
	Ident          mIdent;
};

//-------------------------------------------------------------------------------------
// Списковая синтаксическая структура.

class ListNode : public ASTNode, public std::list<ASTNode*>
{
public:

	ListNode( ASTNodeType aType ) : ASTNode(aType) {}
	~ListNode();

	ListNode *    addElement( ASTNode * aElem ) { if( aElem ) push_front( aElem ); return this; }
	size_t        getNumElements() const { return size(); }

	void accept( NodeVisitor * aVisitor );

	ListNode * copy() const;
};

//-------------------------------------------------------------------------------------
// Определение (типового уравнения, функциональной переменной, типового или функционального параметра, переменной).

class DefinitionNode : public ASTNode
{
public:
	DefinitionNode( ASTNodeType aType, Ident aName, ASTNode * aDefinition );
	~DefinitionNode();

	Ident         getDefinitionName() const { return mDefinitionName; }
	ASTNode *     getDefinition() const     { return mDefinition; }

	void accept( NodeVisitor * aVisitor );

	ASTNode * copy() const;

private:
	Ident mDefinitionName;
	ASTNode * mDefinition;
};

//-------------------------------------------------------------------------------------
// Ссылка на именованый объект (тип, конструктор, имя функци или функциональной переменной, имя встроенной функции).

class NameRefNode : public ASTNode
{
public:

	NameRefNode( Ident aTypeName, ASTNodeType aNodeType );
	NameRefNode( Ident aTypeName, ASTNodeType aNodeType, ListNode * aParams );
	~NameRefNode();

	void setTarget( ASTNode * aTarget ) { if (mTarget) delete mTarget; mTarget = aTarget; }
	void accept( NodeVisitor * aVisitor );

	Ident                    getName() const       { return mTypeName; }
	ListNode *               getParameters() const { return mParameters; }

	// Возвращает узел, на который ссылается данное имя.
	ASTNode *                getTarget() const { return mTarget; }
	ASTNode *                copy() const;
	int                      numParameters() const { return mParameters ? mParameters->size() : 0; }

private:

	Ident mTypeName;
	ListNode * mParameters;
	ASTNode *  mTarget;
};

//-------------------------------------------------------------------------------------
// Конструктор. FIXME: этот класс не нужен в новой нотации описания конструкторов.

class ConstructorNode : public ASTNode
{
public:

	ConstructorNode( Ident aName, ListNode * aCtorParameters, Ident aCtorResultTypeName );
	virtual ~ConstructorNode();

	void accept( NodeVisitor * aVisitor );

	Ident                 getCtorName() const { return mName; }
	Ident                 getCtorResultTypeName() const { return mCtorResultTypeName; }
	ListNode *            getCtorParameters() const { return mCtorParameters; }

	ASTNode *             copy() const;

private:

	Ident mName;
	ListNode * mCtorParameters;
	Ident mCtorResultTypeName;
};

//-------------------------------------------------------------------------------------
// Блок описания данных.

class DataNode : public ASTNode
{
public:

	DataNode( Ident aTypeName, ListNode * aTypeDefs, ListNode * aTypeParams, ListNode * aConstructors );
	~DataNode();

	void accept( NodeVisitor * aVisitor );

	ListNode *      getConstructors() const { return mConstructors; }
	Ident           getDataName() const     { return mTypeName; }
	ListNode *      getTypeDefs() const     { return mTypeDefinitions; }
	ListNode *      getTypeParams() const   { return mTypeParameters; }

	ASTNode *       copy() const;
	int             numParameters() const   { return mTypeParameters ? mTypeParameters->size() : 0; }

private:

	Ident mTypeName;
	ListNode * mConstructors;
	ListNode * mTypeDefinitions;
	ListNode * mTypeParameters;
};

//-------------------------------------------------------------------------------------
// Описание функции или схемы.

class FunctionNode : public ASTNode
{
public:

	FunctionNode( Ident aFuncName, ListNode * aDefinitions, ListNode * aFormalParams );
	~FunctionNode();

	void accept( NodeVisitor * aVisitor );

	Ident             getFuncName() const         { return mFuncName; }
	ListNode *        getFormalParameters() const { return mFormalParameters; }
	ListNode *        getDefinitions() const      { return mDefinitions; }

	DefinitionNode *  getDefinition(Ident aName) const;

	FunctionNode *    copy() const;
	int               numParameters() const { return mFormalParameters ? mFormalParameters->size() : 0; }

private:

	Ident mFuncName;
	ListNode * mDefinitions;
	ListNode * mFormalParameters;
};

//-------------------------------------------------------------------------------------
// Описание входных данных схемы.

class ApplicationBlock : public ASTNode
{
public:

	ApplicationBlock(NameRefNode * aRunSchemeName, ASTNode * aSchemeParameters, ListNode * aDataVarDefs);
	~ApplicationBlock();

	void accept( NodeVisitor * aVisitor );

	ASTNode *     getSchemeParameters() const    { return mSchemeParameters; }
	ListNode *    getDataVarDefinitions() const { return mDataVarDefinitions; }
	NameRefNode * getRunningSchemeName() const  { return mRunSchemeName; }

	ApplicationBlock *  copy() const;

private:
	NameRefNode * mRunSchemeName;
	ASTNode * mSchemeParameters;
	ListNode * mDataVarDefinitions;
};

//-------------------------------------------------------------------------------------
// Описание функциональной программы.

class FunctionalProgram : public ASTNode
{
public:
	FunctionalProgram( ListNode * aDataDefinitions, FunctionNode * aScheme, ApplicationBlock * aApplication );
	~FunctionalProgram();

	void accept( NodeVisitor * aVisitor );

	ListNode *             getDataDefinitions() const { return mDataDefinitions; }
	FunctionNode *         getScheme() const          { return mScheme; }
	ApplicationBlock *     getApplication() const     { return mApplication; }

	ASTNode * copy() const;

private:

	ListNode *         mDataDefinitions;
	FunctionNode *     mScheme;
	ApplicationBlock * mApplication;	
};

}// Parser
}// FPTL

#endif