#ifndef FLEXTOKENIZER_H
#define FLEXTOKENIZER_H

#include <string>
#include <sstream>
#include "Generated/Parser.tab.hh"

namespace FPTL {
namespace Parser {

	class Support;
	class ConstantNode;

	/*
	 * Tokenizer - обертка над flex.
	 * Выделяет лексему из входной строки.
	 */
	class Tokenizer : private yyFlexLexer
	{
	public:
		Tokenizer( const std::string& aInputString );

		BisonParser::token_type  getToken( BisonParser::semantic_type * aVal, Support * aSupport );
		Ident                    getErrorIdent() const;

	private:

		int yylex( void );

		// Вспомогательные методы, вызываемые из yylex.

		ConstantNode * formDecimalConstant();
		ConstantNode * formLongLongConstant();
		ConstantNode * formFPConstant( bool aForceFloat );
		ConstantNode * formStringConstant();

		int	processCommentBlock();
		int	processIdentifier();

	private:

		std::stringstream mInputStream;
		Support * mSupport;
		BisonParser::semantic_type * mVal;

		// Переменные позиционирования внутри исходного файла.
		size_t mLine;
		size_t mCol;
		size_t mPrevTokenLine;
		size_t mTokenBegin;
		size_t mLastTokenLen;
	};

	int yylex( BisonParser::semantic_type * aVal, Support * aSupport, Tokenizer * aTokenizer );

}
}

#endif
