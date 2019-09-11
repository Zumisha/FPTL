/* Описание сканнера для генерации с использованием flex. */

%option c++
%option outfile="FlexScanner.cpp"
%option yyclass="FPTL::Parser::Tokenizer"
%option noyywrap
%option nounistd

%top{
#include <cstdint>
}

%{
#include "../../FlexTokenizer.h"
#include "../../Support.h"
#include "../../Nodes.h"

%}

White 			[ \t]
NewLine 		[\n\r]

ShortComment 	"//"(.)*\n

DecNumber		(\-)?[0-9]+
Frac      		(\-)?[0-9]*"."[0-9]+
Exp       		[eE][\+\-]?[0-9]+
RealNumber 		(({Frac}{Exp}?)|({DecNumber}{Exp}))

StringConstant	L?\"([^\"\\\n]|(\\['\"?\\abfnrtv])|(\\([0123456]{1,3}))|(\\x[[:xdigit:]]+)|(\\u([[:xdigit:]]{4}))|(\\U([[:xdigit:]]{8})))*\"

Ident			[a-zA-Z][a-zA-Z0-9_]*

%%

"/*"							{ return processCommentBlock(); }

{White}							{ return '\n'; }
{NewLine}|{ShortComment}		{
									mCol = 0;
									mLine++;
									return '\n';
								}

{Ident}							{ return processIdentifier(); }
								
\'{Ident}						{ return processIdentifier(); }
								
{DecNumber}						{
									mVal->scNode = formDecimalConstant();
									return BisonParser::token::NUMBER;
								}

{DecNumber}[Ll][Ll]             {
                                    mVal->scNode = formLongLongConstant();
									return BisonParser::token::NUMBER;
                                }
								
{RealNumber} 					{
									mVal->scNode = formFPConstant( false );
									return BisonParser::token::REALNUMBER;
								}
								
{RealNumber}[fF]				{
									mVal->scNode = formFPConstant( true );
									return BisonParser::token::REALNUMBER;
								}
								
{StringConstant}				{
									mVal->scNode = formStringConstant();
									return BisonParser::token::STRING;
								}
								
								
"++"							{ return BisonParser::token::T_UNION; }
"->"							{ return BisonParser::token::T_FARROW; }
"=>"							{ return BisonParser::token::T_TARROW; }

[\(\)\.\,\:\;\[\]\{\}\<\>\~\$\#\*\=\+\~\@\%]	{ return *YYText(); }

.								{
									Ident errSymb = { static_cast<size_t>(mCol), static_cast<size_t>(mLine), 0 };
									mSupport->newIdent( YYText(), 0, errSymb );
									mSupport->semanticError( ErrTypes::IllegalCharacter, errSymb );
								}
