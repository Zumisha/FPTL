#include <string>
#include <cassert>
#include <cmath>
#include <regex>

#include <boost/lexical_cast.hpp>

#include "Tokenizer.h"
#include "Support.h"
#include "Nodes.h"

namespace FPTL { namespace Parser {

//-------------------------------------------------------------------------------------------
Tokenizer::Tokenizer(std::istream & input)
	: yyFlexLexer( input, std::cout ),
	mLine(1),
	mCol(0),
	mTokenBegin(0),
	mLastTokenLen(0),
	mPrevTokenLine(0)
{
}

//-------------------------------------------------------------------------------------------
ConstantNode * Tokenizer::formDecimalConstant()
{
	// Проверяем диапазон.
	try
	{
		boost::lexical_cast<int>(YYText());
	}
	catch (const std::exception &)
	{
		mSupport->semanticError(ErrTypes::InvalidConstant, getErrorIdent());
	}

	return new ConstantNode(ASTNode::IntConstant, mSupport->newConstant(YYText(), mLine, mCol));
}

//-------------------------------------------------------------------------------------------
ConstantNode * Tokenizer::formLongLongConstant()
{
	std::regex rx("(\\d+)[Ll][Ll]");
	std::cmatch match;

	std::regex_search(YYText(), match, rx); 

	// Проверяем диапазон.
	try
	{
		boost::lexical_cast<long long int>(match[1]);
	}
	catch (const std::exception &)
	{
		mSupport->semanticError(ErrTypes::InvalidConstant, getErrorIdent());
	}

	return new ConstantNode(ASTNode::LongLongConstant, mSupport->newConstant(match[1], mLine, mCol));
}

//-------------------------------------------------------------------------------------------
ConstantNode * Tokenizer::formFPConstant( bool aForceFloat )
{
	std::string str = YYText();

	// Проверяем константу.
	try
	{
		boost::lexical_cast<double>(str);
	}
	catch (std::exception &)
	{
		mSupport->semanticError(ErrTypes::InvalidConstant, getErrorIdent());
	}

	if( aForceFloat )
	{
		str = std::string( str.begin(), str.begin() + str.find_first_of("f") );
	}

	return new ConstantNode( ASTNode::FloatConstant, mSupport->newConstant( str, mLine, mCol ) );
}

//-------------------------------------------------------------------------------------------
ConstantNode * Tokenizer::formStringConstant(void)
{
	std::string str = YYText();
	str = std::string( str.begin() + str.find_first_of('\"') + 1, str.begin() + str.find_last_of('\"') );

	// Заменяем escape-символы.

	str = std::regex_replace(str, std::regex("\\\\\\\\"), std::string("\\"));
	str = std::regex_replace(str, std::regex("[\\\\][a]"), std::string("\a"));
	str = std::regex_replace(str, std::regex("[\\\\][b]"), std::string("\b"));
	str = std::regex_replace(str, std::regex("[\\\\][f]"), std::string("\f"));
	str = std::regex_replace(str, std::regex("[\\\\][n]"), std::string("\n"));
	str = std::regex_replace(str, std::regex("[\\\\][r]"), std::string("\r"));
	str = std::regex_replace(str, std::regex("[\\\\][t]"), std::string("\t"));
	str = std::regex_replace(str, std::regex("[\\\\][v]"), std::string("\v"));
	str = std::regex_replace(str, std::regex("[\\\\]\""), std::string("\""));

	return new ConstantNode( ASTNode::StringConstant, mSupport->newConstant( str, mLine, mCol ));
}

//-------------------------------------------------------------------------------------------
int Tokenizer::processCommentBlock(void)
{
	// Обрабатываем многострочные комментарии.
	// Проще так, чем через flex.
	char ch;
	do
	{
		do
		{
			ch = yyinput();
			if( ch == '\n' )
			{
				mCol = 0;
				mLine++;
			}
			else if( ch == EOF )
			{
				mSupport->semanticError( ErrTypes::EOFInComment, getErrorIdent() );
				return 0;
			}
		} while( ch != '*' );

		ch = yyinput();

	} while( ch != '/' );

	return '\n';
}

//-------------------------------------------------------------------------------------------
int Tokenizer::processIdentifier(void)
{
	mVal->scIdent.Col = mCol;
	mVal->scIdent.Line = mLine;

	const char * token = YYText();
	int tokenId;
	if( !(tokenId = mSupport->lookForIdent( token, mVal->scIdent )) )
	{
		if( token[0] == 'c' && token[1] == '_' )
		{
			mSupport->newIdent( token, BisonParser::token::CONSNAME, mVal->scIdent );
			return BisonParser::token::CONSNAME;
		}
		else if( token[0] == '\'' )
		{
			mSupport->newIdent( token, BisonParser::token::TYPEPARAMNAME, mVal->scIdent );
			return BisonParser::token::TYPEPARAMNAME;
		}
		else
		{
			mSupport->newIdent( token, BisonParser::token::NAME, mVal->scIdent );
			return BisonParser::token::NAME;
		}
	}
	else
		return tokenId;
}

//-------------------------------------------------------------------------------------------
// getToken - получение лексемы.
BisonParser::token_type Tokenizer::getToken( BisonParser::semantic_type * aVal, Support * aSupport )
{
	mSupport = aSupport;
	mVal = aVal;
	BisonParser::token_type token;
	mTokenBegin += mLastTokenLen;
	do
	{
		token = (BisonParser::token_type)yylex();
		if( token == '\n' )
		{
			mCol++;
		}
	} while( token == '\n' );

	mLastTokenLen = YYLeng();
	mCol += mLastTokenLen;
	mSupport = 0;
	mVal = 0;
	return token;
}

//-------------------------------------------------------------------------------------------
Ident Tokenizer::getErrorIdent() const
{
	static std::string nullStr;
	Ident ident = { static_cast<short>(mCol), static_cast<short>(mLine), &nullStr };
	return ident;
}


//-------------------------------------------------------------------------------------------
// yylex - интерфейс лексера для yacc.
int yylex( BisonParser::semantic_type * aVal, Support * aSupport, Tokenizer * aTokenizer )
{
	return aTokenizer->getToken( aVal, aSupport );
}

//-------------------------------------------------------------------------------------------
void BisonParser::error(const std::string & msg)
{
	pSupport->semanticError( ErrTypes::GeneralSyntaxError, aTokenizer->getErrorIdent() );
}

}} // FPTL::Parser
