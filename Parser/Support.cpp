#include "Support.h"
#include "Generated/Parser.tab.hh"
#include "SemanticCheck.h"
#include "Nodes.h"
#include "Runtime/StandartLibrary.h"
#include <memory>
#include <string>
#include "../Parser/Tokenizer.h"
#include "Runtime/Run.h"

namespace FPTL { namespace Parser {

//-------------------------------------------------------------------------------------------
ErrorMessage::ErrorMessage(const ErrTypes::ErrType aErr, const Ident aIdent )
	: mErr(aErr), mIdent(aIdent)
{}

//-------------------------------------------------------------------------------------------
Support::Support() : mWasError(false)
{
}

//-------------------------------------------------------------------------------------------
Support::~Support()
{
}

//-------------------------------------------------------------------------------------------
void Support::semanticError(const ErrTypes::ErrType aErr, const Ident aIdent )
{
	mErrorList.push_back( ErrorMessage( aErr, aIdent ) );
	mWasError = true;
}

//
// InitializeIdentTable - регистрируем основные лексемы: ключевые слова, имена типов и т.п.
//
void Support::initializeKeywordTable( void )
{
	// Типы данных.
	registerKeyword("int", BisonParser::token::T_TINT);
	registerKeyword("uint", BisonParser::token::T_TUINT);
	registerKeyword("float", BisonParser::token::T_TDOUBLE); // float не реализован.
	registerKeyword("double", BisonParser::token::T_TDOUBLE);
	registerKeyword("string", BisonParser::token::T_TSTRING);
	registerKeyword("boolean", BisonParser::token::T_TBOOL);

	// Ключевые слова.
	registerKeyword("Functional program", BisonParser::token::T_FUNCTIONAL_PROGRAM);
	registerKeyword("Functional Program", BisonParser::token::T_FUNCTIONAL_PROGRAM);
	registerKeyword("Data", BisonParser::token::T_DATA);
	registerKeyword("Constructors", BisonParser::token::T_CONSTRUCTORS);
	registerKeyword("Scheme", BisonParser::token::T_SCHEME);
	registerKeyword("Fun", BisonParser::token::T_FUN);
	registerKeyword("Application", BisonParser::token::T_APPLICATION);
	registerKeyword("@", 0);
	registerKeyword("true", BisonParser::token::T_TRUE);
	registerKeyword("false", BisonParser::token::T_FALSE);

	for (auto fName : Runtime::StandartLibrary::mFunctions)
	{
		registerKeyword(fName.first, BisonParser::token::BFNAME);
	}
}

//-------------------------------------------------------------------------------------------
void Support::registerKeyword( const std::string & aName, const int aId )
{
	mNameTable[aName] = aId;
}

//
// lookForIdent - поиск идентификатора в таблице имен.
//
int Support::lookForIdent( const std::string & aName, Ident & aIdent )
{
	std::unordered_map<std::string,int>::iterator pos = mNameTable.find( aName );
	if( pos != mNameTable.end() )
	{
		aIdent.Ptr = &pos->first;
		return mNameTable[aName];
	}
	return 0;
}

//
// newIdent - добавление идентификатора в таблицу имен.
//
void Support::newIdent( const std::string & aName, const int aId, Ident & aIdent )
{
	mNameTable[aName] = aId;
	aIdent.Ptr = &mNameTable.find( aName )->first;
}

//-------------------------------------------------------------------------------------------
Ident Support::newConstant( const std::string & aConstant, const int aLine, const int aCol )
{
	Ident ident;
	ident.Col = aCol;
	ident.Line = aLine;
	ident.Ptr = &*mConstantTable.insert( aConstant ).first;
	return ident;
}

//-------------------------------------------------------------------------------------------
const char * Support::getErrorString(const ErrTypes::ErrType aErr )
{
	const char * msg = nullptr;
	switch( aErr )
	{
	case ErrTypes::GeneralSyntaxError:                  msg = "general syntax error"; break;
	case ErrTypes::EOFInComment:                        msg = "end of file was reached in comment block"; break;
	case ErrTypes::IntConstOverflow:                    msg = "integer constant overflow"; break;
	case ErrTypes::IllegalCharacter:                    msg = "illegal character"; break;
	case ErrTypes::MissingMainTypeDef:                  msg = "missing main type definition"; break;
	case ErrTypes::DuplicateDefinition:                 msg = "identifier was defined before"; break;
	case ErrTypes::UndefinedIdentifier:                 msg = "undefined identifier"; break;
	case ErrTypes::InvalidNumberOfParameters:           msg = "invalid number of parameters"; break;
	case ErrTypes::UndefinedSchemeName:                 msg = "undefined scheme name"; break;
	case ErrTypes::IncorrectIdentifierUsage:            msg = "incorrect use of identifier"; break;
	case ErrTypes::NotATemplateType:                    msg = "not a template type"; break;
	case ErrTypes::InvalidTemplateArgumentsNumber:      msg = "invalid type parameters number"; break;
	case ErrTypes::InvalidConstructorUsage:             msg = "invalid constructor usage"; break;
	case ErrTypes::NestedDataDefinition:                msg = "nested data definitions are not allowed"; break;
	case ErrTypes::MultipleTypeExpression:              msg = "only one type expression is allowed"; break;
	case ErrTypes::InvalidFuncallParameters:            msg = "function parameters cannot be used as another function parameters"; break;
	case ErrTypes::InvalidConstant:                     msg = "constant is invalid or out of range"; break;
	case ErrTypes::MissingMainDefinition:               msg = "missing main definition in function"; break;
	case ErrTypes::InvalidTupleIndex:                   msg = "invalid tuple element index"; break;
	default:                                            msg = "unknown error";
	}
	return msg;
}

//-------------------------------------------------------------------------------------------
void Support::getErrorList( std::ostream & aOutStream )
{
	std::vector<ErrorMessage> processed;
	for(auto errMsg = mErrorList.begin(); errMsg != mErrorList.end(); ++errMsg )
	{
		if (std::find(processed.begin(), processed.end(), *errMsg) == processed.end()) {
			aOutStream << "Error : " << getErrorString(errMsg->mErr) << " : "
				<< "\'" << *errMsg->mIdent.Ptr << "\'"
				<< " line " << errMsg->mIdent.Line
				<< " ch " << errMsg->mIdent.Col << "\n";
			processed.push_back(*errMsg);
		}
	}
}

//-------------------------------------------------------------------------------------------
void Support::pushIdent( const Ident & aIdent )
{
	mIdentStack.push_back( aIdent );
}

//-------------------------------------------------------------------------------------------
void Support::popIdent()
{
	mIdentStack.pop_back();
}

//-------------------------------------------------------------------------------------------
Ident Support::getTopIdent() const
{
	return mIdentStack.back();
}

//-------------------------------------------------------------------------------------------
ASTNode * Support::getInternalForm(const std::string inputStr)
{
	std::stringstream input(inputStr);
	Tokenizer tokenizer(input);

	// Сбрасываем состояние.
	mIdentStack.clear();
	mNameTable.clear();
	mConstantTable.clear();

	initializeKeywordTable();

	ASTNode * root = nullptr;

	BisonParser parser( this, &tokenizer, root );

	//parser.set_debug_stream(std::cerr);
	//parser.set_debug_level(1);

	const int result = parser.parse();

	std::auto_ptr<ASTNode> rootPtr(root);

	if (result)
	{
		return nullptr;
	}

	NamesChecker checkNames( this );
	checkNames.process( root );

	if (mWasError)
	{
		return nullptr;
	}

	RecursionFinder recursionFinder;
	recursionFinder.process( root );

	if (mWasError)
	{
		return nullptr;
	}

	return rootPtr.release();
}

} // Parser
} // FPTL