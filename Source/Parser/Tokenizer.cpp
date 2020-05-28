#include <string>
#include <regex>

#include <boost/lexical_cast.hpp>

#include "Tokenizer.h"
#include "Support.h"
#include "Nodes.h"

namespace FPTL {
	namespace Parser {

		//-------------------------------------------------------------------------------------------
		Tokenizer::Tokenizer(std::istream & input)
			: yyFlexLexer(input, std::cout),
			mSupport(nullptr),
			mVal(nullptr),
			mLine(1),
			mCol(0),
			mPrevTokenLine(0),
			mTokenBegin(0),
			mLastTokenLen(0)
		{
		}

		//-------------------------------------------------------------------------------------------
		ConstantNode * Tokenizer::formDecimalConstant() const
		{
			// Проверяем диапазон.
			try
			{
				boost::lexical_cast<long long>(YYText());
			}
			catch (const std::exception &)
			{
				return formLongLongConstant();
			}

			return new ConstantNode(ASTNode::IntConstant, mSupport->newConstant(YYText(), mLine, mCol));
		}

		//-------------------------------------------------------------------------------------------
		ConstantNode * Tokenizer::formLongLongConstant() const
		{
			const std::regex rx("(\\d+)[Ll][Ll]");
			std::cmatch match;

			std::regex_search(YYText(), match, rx);

			// Проверяем диапазон.
			try
			{
				boost::lexical_cast<double>(match[1]);
			}
			catch (const std::exception &)
			{
				mSupport->semanticError(ParserErrTypes::InvalidConstant, getErrorIdent(""));
			}

			return new ConstantNode(ASTNode::LongLongConstant, mSupport->newConstant(match[1], mLine, mCol));
		}

		//-------------------------------------------------------------------------------------------
		ConstantNode * Tokenizer::formFPConstant(const bool aForceFloat) const
		{
			std::string str = YYText();

			// Проверяем константу.
			try
			{
				boost::lexical_cast<double>(str);
			}
			catch (std::exception &)
			{
				mSupport->semanticError(ParserErrTypes::InvalidConstant, getErrorIdent(""));
			}

			if (aForceFloat)
			{
				str = std::string(str.begin(), str.begin() + str.find_first_of('f'));
			}

			return new ConstantNode(ASTNode::FloatConstant, mSupport->newConstant(str, mLine, mCol));
		}

		//-------------------------------------------------------------------------------------------
		ConstantNode * Tokenizer::formStringConstant(void) const
		{
			std::string str = YYText();
			std::stringstream ss;
			size_t backSlashCount = 0;
			
			// Заменяем escape-символы.
			// Первый и последний всегда кавычки - часть синтаксиса языка.
			for (size_t i = 1; i < str.length() - 1; ++i)
			{
				if (str[i] == '\\')
				{
					backSlashCount++;
				}
				else if (backSlashCount != 0)
				{
					for (size_t j = 0; j < backSlashCount / 2; ++j)
						ss << "\\";
					if (backSlashCount % 2 == 0)
					{
						ss << str[i];
					}
					else
					{
						switch (str[i])
						{
						case '\"':
							{
							ss << '\"';
								break;
							}
						case 'a':
						{
							ss << '\a';
							break;
						}
						case 'b':
						{
							ss << '\b';
							break;
						}
						case 'f':
						{
							ss << '\f';
							break;
						}
						case 'n':
						{
							ss << '\n';
							break;
						}
						case 'r':
						{
							ss << '\r';
							break;
						}
						case 't':
						{
							ss << '\t';
							break;
						}
						case 'v':
						{
							ss << '\v';
							break;
						}
						default:
						{
							ss << '\\' << str[i];
							break;
						}
						}					
					}
					backSlashCount = 0;
				}
				else
				{
					ss << str[i];
				}
			}

			return new ConstantNode(ASTNode::StringConstant, mSupport->newConstant(ss.str(), mLine, mCol));
		}

		//-------------------------------------------------------------------------------------------
		int Tokenizer::processCommentBlock(void)
		{
			// Обрабатываем многострочные комментарии.
			// Проще так, чем через flex.
			int ch = yyinput();
			mCol +=2;
			do
			{
				while (ch != '*')
				{
					if (ch == '\n')
					{
						mCol = 0;
						mLine++;
					}
					else if (ch == EOF || ch == 0)
					{
						mSupport->semanticError(ParserErrTypes::EOFInComment, getErrorIdent(""));
						return 0;
					}
					ch = yyinput();
					mCol++;
				} 

				ch = yyinput();
				mCol++;

			} while (ch != '/');

			return '\n';
		}

		//-------------------------------------------------------------------------------------------
		int Tokenizer::processIdentifier() const
		{
			mVal->scIdent.Col = mCol;
			mVal->scIdent.Line = mLine;

			const char * token = YYText();
			const int tokenId = mSupport->lookForIdent(token, mVal->scIdent);
			if (!tokenId)
			{
				if (token[0] == 'c' && token[1] == '_')
				{
					mSupport->newIdent(token, BisonParser::token::CONSNAME, mVal->scIdent);
					return BisonParser::token::CONSNAME;
				}
				else if (token[0] == '\'')
				{
					mSupport->newIdent(token, BisonParser::token::TYPEPARAMNAME, mVal->scIdent);
					return BisonParser::token::TYPEPARAMNAME;
				}
				else
				{
					mSupport->newIdent(token, BisonParser::token::NAME, mVal->scIdent);
					return BisonParser::token::NAME;
				}
			}
			else
				return tokenId;
		}

		//-------------------------------------------------------------------------------------------
		// getToken - получение лексемы.
		BisonParser::token_type Tokenizer::getToken(BisonParser::semantic_type * aVal, Support * aSupport)
		{
			mSupport = aSupport;
			mVal = aVal;
			BisonParser::token_type token;
			mTokenBegin += mLastTokenLen;
			do
			{
				token = static_cast<BisonParser::token_type>(yylex());
				if (token == '\n')
				{
					mCol++;
				}
			} while (token == '\n');

			mLastTokenLen = YYLeng();
			mCol += mLastTokenLen;
			return token;
		}

		//-------------------------------------------------------------------------------------------
		Ident Tokenizer::getErrorIdent(const std::string& msg) const
		{
			return mSupport->newConstant(msg, mLine, mCol - mLastTokenLen);
		}


		//-------------------------------------------------------------------------------------------
		// yylex - интерфейс лексера для yacc.
		int yylex(BisonParser::semantic_type * aVal, Support * aSupport, Tokenizer * aTokenizer)
		{
			return aTokenizer->getToken(aVal, aSupport);
		}

		//-------------------------------------------------------------------------------------------
		void BisonParser::error(const std::string& msg)
		{
			pSupport->semanticError(ParserErrTypes::GeneralSyntaxError, aTokenizer->getErrorIdent(msg));
		}
	}
}
