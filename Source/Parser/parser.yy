%defines
%define api.namespace {FPTL::Parser}
%define api.parser.class {BisonParser}
%define parse.error verbose

%code requires
{
#include "../Ident.h"

	namespace FPTL {
	namespace Parser {
	
		class ASTNode;
			class NameRefNode;
			class FunctionNode;
			class DefinitionNode;
			class ConstructorNode;
			class DataNode;
			class FunctionalProgram;
			class ApplicationBlock;
			class ExpressionNode;
			class ConditionNode;
			class ConstantNode;
			class ListNode;
		class Tokenizer;
		class Support;

	} // Parser
	} // FPTL
}

/* Параметр парсера - вспомогательный класс для хранения полученной информации. */
%parse-param { Support * pSupport }
%parse-param { Tokenizer * aTokenizer }
%parse-param { ASTNode* & mASTRoot }
%lex-param { Support * pSupport }
%lex-param { Tokenizer * aTokenizer }


/* Варианты типов узлов АСТ. */

%union
{
	Ident			   scToken;
	Ident			   scIdent;
	ASTNode *		   scNode;
	ListNode *         scList;
	ApplicationBlock * scApp;
	FunctionNode *     scFun;
	DefinitionNode *   scDef;
	NameRefNode *      scName;
}

%code
{
#include "../Support.h"
#include "../FlexTokenizer.h"
#include "../Nodes.h"
}

%destructor
{
	ASTNode * node = $$;
	delete node;

} <scNode> <scList> <scApp> <scFun> <scDef> <scName>

/* Идентификаторы. */

%token <scIdent> NAME
%token <scIdent> FUNNAME
%token <scIdent> CONSNAME
%token <scIdent> DESTNAME
%token <scIdent> TYPEPARAMNAME
%token <scIdent> IPNAME
%token <scIdent> FUNCVARNAME
%token <scIdent> BFNAME
%token <scIdent> IFUNC
%token <scNode> NUMBER
%token <scNode> REALNUMBER
%token <scNode> STRING


/* Ключевые слова. */

%token <scToken> T_FUNCTIONAL_PROGRAM
%token <scToken> T_IMPORT
%token <scToken> T_LIBRARIES
%token <scToken> T_SCHEME
%token <scToken> T_INTERPRETATION
%token <scToken> T_APPLICATION
%token <scToken> T_DATA
%token <scToken> T_CONSTRUCTORS
%token <scToken> T_FUN
%token <scToken> T_FUNCTIONS
%token <scToken> T_TSTRING
%token <scToken> T_TINT
%token <scToken> T_TUINT
%token <scToken> T_TSIZE
%token <scToken> T_TFLOAT
%token <scToken> T_TDOUBLE
%token <scToken> T_TBOOL
%token <scToken> T_TRUE
%token <scToken> T_FALSE
%token <scToken> T_ARGET
%token <scToken> T_ID

/* Cимволы. */

%token <scToken> T_UNION
%token <scToken> T_FARROW
%token <scToken> T_TARROW
%token <scToken> T_COLON
%token <scToken> T_SEMICOLON

/* Типы порождаемых конструкций для правил. */

%type <scNode> FunctionalProgram

%type <scList> DataTypeDefinitionsBlocks
%type <scNode> DataTypeDefinitionsBlock

%type <scIdent> TypeName

%type <scList>  TypeParametersList
%type <scList>  ConstructorsDefinitionList
%type <scNode>  ConstructorDef
%type <scList>  ConstructorParametersList
%type <scList>  TypesDefinitionList
%type <scList>  TypesDefinitionList2
%type <scDef>   TypeDefinition
%type <scNode>  TypeExpression
%type <scName>  AtomType
%type <scList>  TypeExpressionsList
%type <scDef>   TypeParameterDef
%type <scToken> BaseType
%type <scIdent> ConstructorName
%type <scIdent> TypeParameter
%type <scNode>  TypeDefConstructor

%type <scFun>   Scheme
%type <scList>  FormalParametersList
%type <scDef>   FormalParameter
%type <scList>  DefinitionsList
%type <scNode>  Definition
%type <scNode>  Term
%type <scNode>  SequentialTerm
%type <scNode>  CompositionTerm
%type <scNode>  ConditionTerm
%type <scNode>  VariantTerm
%type <scNode>  AtomTerm
%type <scFun>   ConstructionFun
%type <scNode>  Constant
%type <scNode>  BuiltInFunction
%type <scName>  BuiltInFunctionName
%type <scName>  Constructor
%type <scName>  Destructor
%type <scNode>  ElementaryFunctionName
%type <scNode>  FuncParameterName

%type <scNode>  TupleElement
%type <scName>  FuncObjectName
%type <scName>  FuncObjectWithParameters
%type <scList>  FuncArgumentList

%type <scIdent> SchemeBegin
%type <scIdent> ConstructionFunName
%type <scIdent> FuncVarName

%type <scApp>   Application
%type <scList>  DataInit
%type <scDef>   OneDataInit
%type <scIdent> DataName
%type <scName>  InterpFunProgramName
%type <scNode>  OneData
%type <scNode>  Data
%type <scNode>  ValueAtom
%type <scNode>  ValueComposition
%type <scNode>  Value
%type <scNode>  ValueConstructor

/* Правила. */

%%
FunctionalProgram
	: DataTypeDefinitionsBlocks Scheme Application
		{
			mASTRoot = new FunctionalProgram( $1, $2, $3 );
			$1->mParent = mASTRoot;
			$2->mParent = mASTRoot;
			$3->mParent = mASTRoot;
			
			// Возвращаем 0, иначе все дерево будет "срублено" деструктором парсера.
			$$ = 0;
		}
	| Scheme Application
		{
			mASTRoot = new FunctionalProgram( 0, $1, $2 );
			$1->mParent = mASTRoot;
			$2->mParent = mASTRoot;
			$$ = 0;
		}
	;
		
/* Синтаксис описания блоков данных */

DataTypeDefinitionsBlocks
	: DataTypeDefinitionsBlock
		{
			$$ = new ListNode(  ASTNode::DataTypeDefinitionsBlocks );
			$$->addElement( $1 );
			$1->mParent = $$;
		}
	| DataTypeDefinitionsBlock DataTypeDefinitionsBlocks
		{
			$$ = $2->addElement( $1 );
			$1->mParent = $2;
		}
	;

DataTypeDefinitionsBlock
	: T_DATA TypeName '{' TypesDefinitionList '}'
		{
			$$ = new DataNode(  $2, $4, 0, 0 );
			$4->mParent = $$;
		}
	| T_DATA TypeName '<' TypeParametersList '>' '{' TypesDefinitionList '}'
		{
			$$ = new DataNode(  $2, $7, $4, 0 );
			$7->mParent = $$;
			$4->mParent = $$;
		}
	| T_DATA TypeName '{' T_CONSTRUCTORS '{' ConstructorsDefinitionList '}' TypesDefinitionList '}'
		{
			$$ = new DataNode(  $2, $8, 0, $6 );
			$8->mParent = $$;
			$6->mParent = $$;
		}
	| T_DATA TypeName '<' TypeParametersList '>' '{' T_CONSTRUCTORS '{' ConstructorsDefinitionList '}' TypesDefinitionList '}'
		{
			$$ = new DataNode(  $2, $11, $4, $9 );
			$11->mParent = $$;
			$4->mParent = $$;
			$9->mParent = $$;
		}	
	;

TypeName
	: NAME
	;

TypeParametersList
	: TypeParameterDef
		{
			$$ = new ListNode( ASTNode::TypeParametersList );
			$$->addElement( $1 );
			$1->mParent = $$;
		}
	| TypeParameterDef ',' TypeParametersList
		{		
			$$ = $3->addElement( $1 );
			$1->mParent = $3;
		}
	;
	
TypeParameterDef
	: TypeParameter
		{
			$$ = new DefinitionNode( ASTNode::TypeParameterDefinition, $1, 0 );
		}
	;

ConstructorsDefinitionList
	: ConstructorDef
		{
			$$ = new ListNode( ASTNode::ConstructorsDefinitionList );
			$$->addElement( $1 );
			$1->mParent = $$;
		}
	| ConstructorDef ConstructorsDefinitionList
		{
			$$ = $2->addElement( $1 );
			$1->mParent = $2;
		}
	;

ConstructorDef
    : T_TARROW TypeName T_COLON CONSNAME T_SEMICOLON
		{
			$$ = new ConstructorNode( $4, 0, $2 );
		}
    | ConstructorParametersList T_TARROW TypeName T_COLON CONSNAME T_SEMICOLON
		{
			$$ = new ConstructorNode( $5, $1, $3 );
			$1->mParent = $$;
		}
	
ConstructorParametersList
	: AtomType
		{
			$$ = new ListNode( ASTNode::ConstructorParametersList );
			$$->addElement( $1 );
			$1->mParent = $$;
		}
	| AtomType '*' ConstructorParametersList
		{
			$$ = $3->addElement( $1 );
			$1->mParent = $3;
		}
	;
	
	
TypesDefinitionList
	: TypesDefinitionList2
		{
			if( $1->mChilds.size() > 1 )
			{
				for(ASTNode* child : $1->mChilds)
					pSupport->semanticError( ParserErrTypes::MultipleTypeExpression, static_cast<DefinitionNode*>(child)->getDefinitionName() );
			}

			$$ = $1;
		}
	;

TypesDefinitionList2
	: TypeDefinition
		{
			$$ = new ListNode( ASTNode::TypesDefinitionList );
			$$->addElement( $1 );
			$1->mParent = $$;
		}
	| TypeDefinition TypesDefinitionList2
		{
			$$ = $2->addElement( $1 );
			$1->mParent = $2;
		}
	;

TypeDefinition
    : TypeName '=' TypeExpression T_SEMICOLON
		{
			$$ = new DefinitionNode( ASTNode::TypeDefinition, $1, $3 );
			$3->mParent = $$;
		}
	| DataTypeDefinitionsBlock
		{
			pSupport->semanticError( ParserErrTypes::NestedDataDefinition, static_cast<DataNode*>($1)->getDataName() );
			delete $1;
			$$ = 0;
		}
	;
	
TypeDefConstructor
	: ConstructorParametersList '.' ConstructorName
		{
			$$ = new DefinitionNode( ASTNode::TypeConstructorDefinition, $3, $1 );
			$1->mParent = $$;
		}
	| ConstructorName
		{
			$$ = new DefinitionNode( ASTNode::TypeConstructorDefinition, $1, 0 );
		}
	;
	
TypeExpression
	: TypeDefConstructor
	| TypeDefConstructor T_UNION TypeExpression
		{
			$$ = new ExpressionNode( ASTNode::TypeExpression, $1, $3 );
			$1->mParent = $$;
			$3->mParent = $$;
		}
	;
		
		
AtomType
	: BaseType
		{	
			$$ = new NameRefNode( $1, NameRefNode::BaseType, nullptr );
		}
	| TypeName
		{
			$$ = new NameRefNode( $1, NameRefNode::Type, nullptr );
		}
	| TypeName '<' TypeExpressionsList '>'
		{
			$$ = new NameRefNode( $1, NameRefNode::Template, $3 );
			$3->mParent = $$;
		}
	| TypeParameter
		{
			$$ = new NameRefNode( $1, NameRefNode::TypeParamName, nullptr );
		}
	;

BaseType
	: T_TSTRING
	| T_TINT
	| T_TUINT
	| T_TSIZE
	| T_TFLOAT
	| T_TDOUBLE
	| T_TBOOL
	;
	
TypeExpressionsList
	: AtomType
		{
			$$ = new ListNode( ASTNode::TypeExpressionsList );
			$$->addElement( $1 );
			$1->mParent = $$;
		}
	| AtomType ',' TypeExpressionsList
		{
			$$ = $3->addElement( $1 );
			$1->mParent = $3;
		}
	;

TypeParameter : TYPEPARAMNAME;

ConstructorName : CONSNAME;
	
/* Правила описания схемы. */

Scheme
	: SchemeBegin '{' DefinitionsList '}'
		{
			$$ = new FunctionNode( $1, $3, 0 );
			$3->mParent = $$;
			pSupport->popIdent();
		}
	| SchemeBegin '<' FormalParametersList '>' '{' DefinitionsList '}'
		{
			$$ = new FunctionNode( $1, $6, $3 );
			$6->mParent = $$;
			$3->mParent = $$;
			pSupport->popIdent();
		}
	;
	
SchemeBegin
	: T_SCHEME NAME
		{
			pSupport->pushIdent( $2 );
			$$ = $2;
		}
	;
	
FormalParametersList
	: FormalParameter
		{
			$$ = new ListNode( ASTNode::FormalParametersList );
			$$->addElement( $1 );
			$1->mParent = $$;
		}
	| FormalParameter ',' FormalParametersList
		{
			$$ = $3->addElement( $1 );
			$1->mParent = $3;
		}
	;
	
FormalParameter
	: NAME
		{
			$$ = new DefinitionNode( ASTNode::FunctionParameterDefinition, $1, 0 );
		}
	;
	
DefinitionsList
	: Definition
		{
			$$ = new ListNode( ASTNode::DefinitionsList );
			$$->addElement( $1 );
			$1->mParent = $$;
		}
	| Definition DefinitionsList
		{
			$$ = $2->addElement( $1 );
			$1->mParent = $2;
		}
	;

Definition
    : '@' '=' Term T_SEMICOLON
		{
			$$ = new DefinitionNode( ASTNode::Definition, pSupport->getTopIdent(), $3 );
			$3->mParent = $$;
		}
    | FuncVarName '=' Term T_SEMICOLON
		{
			$$ = new DefinitionNode( ASTNode::Definition, $1, $3 );
			$3->mParent = $$;
		}
	| ConstructionFun
		{ $$ = $1; }
	;
	
Term
	: VariantTerm
	;
	
AtomTerm
	: '(' Term ')'
		{	$$ = $2; }
	| ElementaryFunctionName
	| FuncObjectName
		{ $$ = $1; }
	| '@'
		{
			$$ = new NameRefNode( pSupport->getTopIdent(), ASTNode::FuncObjectName, nullptr );
		}
	;

FuncObjectWithParameters
	: NAME '<' FuncArgumentList '>'
		{
			$$ = new NameRefNode( $1, NameRefNode::FuncObjectWithParameters, $3 );
			$3->mParent = $$;
		}
	
FuncArgumentList
	: FuncParameterName
		{
			$$ = new ListNode( ASTNode::FuncArgumentsList );
			$$->addElement( $1 );
			$1->mParent = $$;
		}
	| FuncParameterName ',' FuncArgumentList
		{
			$$ = $3->addElement( $1 );
			$1->mParent = $3;
		}
	;

FuncParameterName
	: NAME
		{
			$$ = new NameRefNode( $1, NameRefNode::FuncParameterName, nullptr );
		}
	| ElementaryFunctionName
	| FuncObjectWithParameters
		{ $$ = $1; }
	;
	
SequentialTerm
	: AtomTerm
	| SequentialTerm '.' AtomTerm
		{
			$$ = new ExpressionNode( ASTNode::SequentialTerm, $1, $3 );
			$1->mParent = $$;
			$3->mParent = $$;
		}
	;
	
CompositionTerm
	: SequentialTerm
	| CompositionTerm '*' SequentialTerm
		{
			$$ = new ExpressionNode( ASTNode::CompositionTerm, $1, $3 );
			$1->mParent = $$;
			$3->mParent = $$;
		}
	;
	
ConditionTerm
	: CompositionTerm
	| CompositionTerm T_FARROW CompositionTerm ',' ConditionTerm
		{
			$$ = new ConditionNode( ASTNode::ConditionTerm, $1, $3, $5 );
			$1->mParent = $$;
			$3->mParent = $$;
			$5->mParent = $$;
		}
	| CompositionTerm T_FARROW CompositionTerm
		{
			$$ = new ConditionNode( ASTNode::ConditionTerm, $1, $3, nullptr );
			$1->mParent = $$;
			$3->mParent = $$;
		}
	;
	
VariantTerm
	: ConditionTerm
	| VariantTerm '+' ConditionTerm
		{
			$$ = new ExpressionNode( ASTNode::VariantTerm, $1, $3 );
			$1->mParent = $$;
			$3->mParent = $$;
		}
	;
	
FuncObjectName
	: NAME
		{
			$$ = new NameRefNode( $1, NameRefNode::FuncObjectName, nullptr );
		}
	| FuncObjectWithParameters
	;
	
ConstructionFun
	: T_FUN ConstructionFunName 
		{
			pSupport->pushIdent( $2 );
		}
		'{' DefinitionsList '}'
		{
			$$ = new FunctionNode( $2, $5, 0 );
			pSupport->popIdent();
			$5->mParent = $$;
		}
	| T_FUN ConstructionFunName
		{
			pSupport->pushIdent( $2 );
		}
		'<' FormalParametersList '>' '{' DefinitionsList '}'
		{
			$$ = new FunctionNode( $2, $8, $5 );
			pSupport->popIdent();
			$8->mParent = $$;
			$5->mParent = $$;
		}
	;
	
ConstructionFunName
	: NAME
	;
	
FuncVarName
	: NAME
	;

ElementaryFunctionName
	: BuiltInFunction
	| Constructor
		{ $$ = $1; }
	| Destructor
		{ $$ = $1; }
	;
	
Constructor
	: ConstructorName
		{
			$$ = new NameRefNode( $1, NameRefNode::ConstructorName, nullptr );
		}
	;
	
Destructor
	: '~' ConstructorName
		{	
			$$ = new NameRefNode( $2, NameRefNode::DestructorName, nullptr );
		}
	;
	
BuiltInFunction
	: BuiltInFunctionName
		{ $$ = $1; }
	| TupleElement
	| Constant
	;
	
TupleElement
	: '[' NUMBER ']'
		{
			ConstantNode * number = static_cast<ConstantNode*>( $2 );
			$$ = new TakeNode( number->getConstant(), number->getConstant() );
			delete number;
		}
    | '[' T_SEMICOLON ']'
		{
			Ident from = { $2.Col, $2.Line, nullptr };
			Ident to = { $2.Col, $2.Line, nullptr };
			$$ = new TakeNode( from, to);
		}
	| '[' NUMBER T_SEMICOLON ']'
		{
			ConstantNode * from = static_cast<ConstantNode*>( $2 );
			Ident to = { $3.Col, $3.Line, nullptr };
			$$ = new TakeNode( from->getConstant(), to);
			delete from;
		}
	| '[' T_SEMICOLON NUMBER ']'
		{
			Ident from = { $2.Col, $2.Line, nullptr };
			ConstantNode * to = static_cast<ConstantNode*>( $3 );
			$$ = new TakeNode( from, to->getConstant() );
			delete to;
		}
	| '[' NUMBER T_SEMICOLON NUMBER ']'
		{
			ConstantNode * from = static_cast<ConstantNode*>( $2 );
			ConstantNode * to = static_cast<ConstantNode*>( $4 );
			$$ = new TakeNode( from->getConstant(), to->getConstant() );
			delete from;
			delete to;
		}
	
Constant
	: NUMBER
	| REALNUMBER
	| STRING
	| T_TRUE
		{
			$$ = new ConstantNode( ASTNode::TrueValue, $1 );
		}
	| T_FALSE
		{
			$$ = new ConstantNode( ASTNode::FalseValue, $1 );
		}
	;

	
BuiltInFunctionName
	: BFNAME
		{
			$$ = new NameRefNode( $1, NameRefNode::BuildInFunction, nullptr );
		}
	;
		
Application
	: T_APPLICATION InterpFunProgramName
		{
			$$ = new ApplicationBlock( $2, 0, 0 );
			$2->mParent = $$;
		}
	| T_APPLICATION InterpFunProgramName '(' Data ')'
		{
			$$ = new ApplicationBlock( $2, $4, 0 );
			$2->mParent = $$;
			$4->mParent = $$;
		}
	| T_APPLICATION DataInit InterpFunProgramName
		{
			$$ = new ApplicationBlock( $3, 0, $2 ); 
			$3->mParent = $$;
			$2->mParent = $$;
		}
	| T_APPLICATION DataInit InterpFunProgramName '(' Data ')'
		{
			$$ = new ApplicationBlock( $3, $5, $2 );
			$3->mParent = $$;
			$5->mParent = $$;
			$2->mParent = $$;
		}
	;
	
DataInit
	: OneDataInit
		{
			$$ = new ListNode( ASTNode::InputVarDefinitionList );
			$$->addElement( $1 );
			$1->mParent = $$;
		}
	| OneDataInit DataInit
		{
			$$ = $2->addElement( $1 );
			$1->mParent = $2;
		}
	;
	
OneDataInit
    : DataName '=' Value T_SEMICOLON
		{
			$$ = new DefinitionNode( ASTNode::InputVarDefinition, $1, $3 );
			$3->mParent = $$;
		}
	;
	
DataName : NAME;

InterpFunProgramName
	 : '%' NAME
		{ 
			$$ = new NameRefNode($2, ASTNode::RunningSchemeName, nullptr );
		}
	 ;

Data
	: OneData
		{
			$$ = $1;
		}
	| OneData ',' Data
		{
			$$ = new ExpressionNode(ASTNode::InputVarList, $1, $3);
			$1->mParent = $$;
			$3->mParent = $$;
		}
	;
	
OneData
	: DataName
		{
			$$ = new NameRefNode( $1, ASTNode::InputVarName, nullptr );
		}
	| Value
	;
	
	
ValueAtom
	: Constant
	| Constructor
		{ $$ = $1; }
	| '(' Value ')'
		{
			$$ = $2;
		}
	;
	
ValueConstructor
	: ValueAtom
	| ValueAtom '.' Constructor
		{
			$$ = new ExpressionNode( ASTNode::ValueConstructor, $1, $3 );
			$1->mParent = $$;
			$3->mParent = $$;
		}
	;
	
ValueComposition
	: ValueConstructor
	| ValueConstructor '*' ValueComposition
		{
			$$ = new ExpressionNode( ASTNode::ValueComposition, $1, $3 );
			$1->mParent = $$;
			$3->mParent = $$;
		}
	;
	
Value : ValueComposition;

