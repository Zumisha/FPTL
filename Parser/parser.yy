%defines
%define api.namespace {FPTL::Parser}
%define parser_class_name {BisonParser}

%code requires
{
#include "../Ident.h"

	namespace FPTL {
	namespace Parser {

		class ASTNode;
			class ListNode;
			class DefinitionNode;
			class DataNode;
			class FunctionNode;
			class ApplicationBlock;
			class NameRefNode;
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
#include "../Tokenizer.h"
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
%type <scName>  NamedArgument
%type <scList>  NamedArgumentsList

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
			
			// Возвращаем 0, иначе все дерево будет "срублено" деструктором парсера.
			$$ = 0;
		}
	| Scheme Application
		{
			mASTRoot = new FunctionalProgram( 0, $1, $2 );
			$$ = 0;
		}
	;
		
/* Синтаксис описания блоков данных */

DataTypeDefinitionsBlocks
	: DataTypeDefinitionsBlock
		{
			$$ = new ListNode(  ASTNode::DataTypeDefinitionsBlocks );
			$$->addElement( $1 );
		}
	| DataTypeDefinitionsBlock DataTypeDefinitionsBlocks
		{
			$$ = $2->addElement( $1 );
		}
	;

DataTypeDefinitionsBlock
	: T_DATA TypeName '{' TypesDefinitionList '}'
		{
			$$ = new DataNode(  $2, $4, 0, 0 );
		}
	| T_DATA TypeName '[' TypeParametersList ']' '{' TypesDefinitionList '}'
		{
			$$ = new DataNode(  $2, $7, $4, 0 );
		}
	| T_DATA TypeName '{' T_CONSTRUCTORS '{' ConstructorsDefinitionList '}' TypesDefinitionList '}'
		{
			$$ = new DataNode(  $2, $8, 0, $6 );
		}
	| T_DATA TypeName '[' TypeParametersList ']' '{' T_CONSTRUCTORS '{' ConstructorsDefinitionList '}' TypesDefinitionList '}'
		{
			$$ = new DataNode(  $2, $11, $4, $9 );
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
		}
	| TypeParameterDef ',' TypeParametersList
		{		
			$$ = $3->addElement( $1 );
		}
	;
	
TypeParameterDef
	: TypeParameter
		{
			$$ = new DefinitionNode( ASTNode::TypeParameterDefinition, $1, 0, 0 );
		}
	;

ConstructorsDefinitionList
	: ConstructorDef
		{
			$$ = new ListNode( ASTNode::ConstructorsDefinitionList );
			$$->addElement( $1 );
		}
	| ConstructorDef ConstructorsDefinitionList
		{
			$$ = $2->addElement( $1 );
		}
	;

ConstructorDef
	: T_TARROW TypeName ':' CONSNAME ';'
		{
			$$ = new ConstructorNode( $4, 0, $2 );
		}
	| ConstructorParametersList T_TARROW TypeName ':' CONSNAME ';'
		{
			$$ = new ConstructorNode( $5, $1, $3 );
		}
	
ConstructorParametersList
	: AtomType
		{
			$$ = new ListNode( ASTNode::ConstructorParametersList );
			$$->addElement( $1 );
		}
	| AtomType '*' ConstructorParametersList
		{
			$$ = $3->addElement( $1 );
		}
	;
	
	
TypesDefinitionList
	: TypesDefinitionList2
		{
			if( $1->size() > 1 )
			{
				for( ListNode::iterator it = $1->begin(); it != $1->end(); ++it )
					pSupport->semanticError( ErrTypes::MultipleTypeExpression, static_cast<DefinitionNode*>( *it )->getDefinitionName() );
			}

			$$ = $1;
		}
	;

TypesDefinitionList2
	: TypeDefinition
		{
			$$ = new ListNode( ASTNode::TypesDefinitionList );
			$$->addElement( $1 );
		}
	| TypeDefinition TypesDefinitionList2
		{
			$$ = $2->addElement( $1 );
		}
	;

TypeDefinition
	: TypeName '=' TypeExpression ';'
		{
			$$ = new DefinitionNode( ASTNode::TypeDefinition, $1, $3, 0 );
		}
	| DataTypeDefinitionsBlock
		{
			pSupport->semanticError( ErrTypes::NestedDataDefinition, static_cast<DataNode*>($1)->getDataName() );
			delete $1;
			$$ = 0;
		}
	;
	
TypeDefConstructor
	: ConstructorParametersList '.' ConstructorName
		{
			$$ = new DefinitionNode( ASTNode::TypeConstructorDefinition, $3, $1, 0 );
		}
	| ConstructorName
		{
			$$ = new DefinitionNode( ASTNode::TypeConstructorDefinition, $1, 0, 0 );
		}
	;
	
TypeExpression
	: TypeDefConstructor
	| TypeDefConstructor T_UNION TypeExpression
		{
			$$ = new ExpressionNode( ASTNode::TypeExpression, $1, $3 );
		}
	;
		
		
AtomType
	: BaseType
		{	
			$$ = new NameRefNode( $1, NameRefNode::BaseType );
		}
	| TypeName
		{
			$$ = new NameRefNode( $1, NameRefNode::Type );
		}
	| TypeName '[' TypeExpressionsList ']'
		{
			$$ = new NameRefNode( $1, NameRefNode::Template, $3 );
		}
	| TypeParameter
		{
			$$ = new NameRefNode( $1, NameRefNode::TypeParamName );
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
		}
	| AtomType ',' TypeExpressionsList
		{
			$$ = $3->addElement( $1 );
		}
	;

TypeParameter : TYPEPARAMNAME;

ConstructorName : CONSNAME;
	
/* Правила описания схемы. */

Scheme
	: SchemeBegin '{' DefinitionsList '}'
		{
			$$ = new FunctionNode( $1, $3, 0 );
			pSupport->popIdent();
		}
	| SchemeBegin '[' FormalParametersList ']' '{' DefinitionsList '}'
		{
			$$ = new FunctionNode( $1, $6, $3 );
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
		}
	| FormalParameter ',' FormalParametersList
		{
			$$ = $3->addElement( $1 );
		}
	;
	
FormalParameter
	: NAME
		{
			$$ = new DefinitionNode( ASTNode::FunctionParameterDefinition, $1, 0, 0 );
		}
	;
	
DefinitionsList
	: Definition
		{
			$$ = new ListNode( ASTNode::DefinitionsList );
			$$->addElement( $1 );
		}
	| Definition DefinitionsList
		{
			$$ = $2->addElement( $1 );
		}
	;

Definition
	: '@' '=' Term ';'
		{
			$$ = new DefinitionNode( ASTNode::Definition, pSupport->getTopIdent(), $3, 0 );
		}
	| '@' '(' NamedArgumentsList ')' '=' Term ';'
		{
			$$ = new DefinitionNode( ASTNode::Definition, pSupport->getTopIdent(), $6, $3 );
		}
	| FuncVarName '=' Term ';'
		{
			$$ = new DefinitionNode( ASTNode::Definition, $1, $3, 0 );
		}
	| FuncVarName '(' NamedArgumentsList ')' '=' Term ';'
		{
			$$ = new DefinitionNode( ASTNode::Definition, $1, $6, $3 );
		}
	| ConstructionFun
		{ $$ = $1; }
	;

NamedArgument 
	: NAME
		{
			$$ = new NameRefNode( $1, NameRefNode::NamedArgument);
		}
	;

NamedArgumentsList
	: NamedArgument
		{
			$$ = new ListNode( ASTNode::NamedArgumentsList );
			$$ -> addElement( $1 );
		}
	| NamedArgument ',' NamedArgumentsList
		{
		   $$ = $3 -> addElement( $1 );
		}
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
			$$ = new NameRefNode( pSupport->getTopIdent(), ASTNode::FuncObjectName );
		}
	;

FuncObjectWithParameters
	: NAME '(' FuncArgumentList ')'
		{
			$$ = new NameRefNode( $1, NameRefNode::FuncObjectWithParameters, $3 );
		}
	
FuncArgumentList
	: FuncParameterName
		{
			$$ = new ListNode( ASTNode::FuncArgumentsList );
			$$->addElement( $1 );
		}
	| FuncParameterName ',' FuncArgumentList
		{
			$$ = $3->addElement( $1 );
		}
	;

FuncParameterName
	: NAME
		{
			$$ = new NameRefNode( $1, NameRefNode::FuncParameterName );
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
		}
	;
	
CompositionTerm
	: SequentialTerm
	| CompositionTerm '*' SequentialTerm
		{
			$$ = new ExpressionNode( ASTNode::CompositionTerm, $1, $3 );
		}
	;
	
ConditionTerm
	: CompositionTerm
	| CompositionTerm T_FARROW CompositionTerm ',' ConditionTerm
		{
			$$ = new ExpressionNode( ASTNode::ConditionTerm, $1, $3, $5 );
		}
	| CompositionTerm T_FARROW CompositionTerm
		{
			$$ = new ExpressionNode( ASTNode::ConditionTerm, $1, $3 );
		}
	;
	
VariantTerm
	: ConditionTerm
	| VariantTerm '+' ConditionTerm
		{
			$$ = new ExpressionNode( ASTNode::VariantTerm, $1, $3 );
		}
	;
	
FuncObjectName
	: NAME
		{
			$$ = new NameRefNode( $1, NameRefNode::FuncObjectName );
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
		}
	| T_FUN ConstructionFunName
		{
			pSupport->pushIdent( $2 );
		}
		'[' FormalParametersList ']' '{' DefinitionsList '}'
		{
			$$ = new FunctionNode( $2, $8, $5 );
			pSupport->popIdent();
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
			$$ = new NameRefNode( $1, NameRefNode::ConstructorName );
		}
	;
	
Destructor
	: '~' ConstructorName
		{	
			$$ = new NameRefNode( $2, NameRefNode::DestructorName );
		}
	;
	
BuiltInFunction
	: BuiltInFunctionName
		{ $$ = $1; }
	| TupleElement
	| FuncObjectName
	| Constant
	;
	
TupleElement
	: '[' NUMBER ']'
	{
		ConstantNode * number = static_cast<ConstantNode*>( $2 );
		if (number->isNatural())
		{
			$$ = new ConstantNode( ASTNode::TupleElemNumber, number->getConstant() );
			delete number;
		}
		else
		{
			pSupport->semanticError(ErrTypes::InvalidTupleIndex, number->getConstant());
			$$ = 0;
		}
	}
	;
	
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
			$$ = new NameRefNode( $1, NameRefNode::BuildInFunction );
		}
	;
		
Application
	: T_APPLICATION InterpFunProgramName
		{
			$$ = new ApplicationBlock( $2, 0, 0 );
		}
	| T_APPLICATION InterpFunProgramName '(' Data ')'
		{
			$$ = new ApplicationBlock( $2, $4, 0 );
		}
	| T_APPLICATION DataInit InterpFunProgramName
		{
			$$ = new ApplicationBlock( $3, 0, $2 ); 
		}
	| T_APPLICATION DataInit InterpFunProgramName '(' Data ')'
		{
			$$ = new ApplicationBlock( $3, $5, $2 );
		}
	;
	
DataInit
	: OneDataInit
		{
			$$ = new ListNode( ASTNode::InputVarDefinitionList );
			$$->addElement( $1 );
		}
	| OneDataInit DataInit
		{
			$$ = $2->addElement( $1 );
		}
	;
	
OneDataInit
	: DataName '=' Value ';'
		{
			$$ = new DefinitionNode( ASTNode::InputVarDefinition, $1, $3, 0 );
		}
	;
	
DataName : NAME;

InterpFunProgramName
	 : '%' NAME
		{ 
			$$ = new NameRefNode($2, ASTNode::RunningSchemeName);
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
		}
	;
	
OneData
	: DataName
		{
			$$ = new NameRefNode( $1, ASTNode::InputVarName );
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
		}
	;
	
ValueComposition
	: ValueConstructor
	| ValueConstructor '*' ValueComposition
		{
			$$ = new ExpressionNode( ASTNode::ValueComposition, $1, $3 );
		}
	;
	
Value : ValueComposition;

