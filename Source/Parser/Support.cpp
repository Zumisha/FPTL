#include <memory>
#include <string>
#include <sstream>

#include "Generated/parser.tab.hh"

#include "Support.h"
#include "SemanticCheck.h"
#include "Nodes.h"
#include "Tokenizer.h"
#include "Evaluator/Run.h"
#include "Libraries/ArithmeticLib.h"
#include "Libraries/ArrayLib.h"
#include "Libraries/FileLib.h"
#include "Libraries/LogicLib.h"
#include "Libraries/StandardLib.h"
#include "Libraries/StringLib.h"
#include "Libraries/TimeLib.h"

namespace FPTL {
	namespace Parser {

		//-------------------------------------------------------------------------------------------
		ErrorMessage::ErrorMessage(const ParserErrTypes::ErrType aErr, const Ident aIdent)
			: mErr(aErr), mIdent(aIdent)
		{}

		//-------------------------------------------------------------------------------------------
		Support::Support() : mWasError(false)
		{
		}

		//-------------------------------------------------------------------------------------------
		Support::~Support() = default;

		//-------------------------------------------------------------------------------------------
		void Support::semanticError(const ParserErrTypes::ErrType aErr, const Ident aIdent)
		{
			mErrorList.emplace_back(aErr, aIdent);
			mWasError = true;
		}

		//
		// InitializeIdentTable - регистрируем основные лексемы: ключевые слова, имена типов и т.п.
		//
		void Support::initializeKeywordTable(void)
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

			// ToDo: сделать нормальный импорт
			Runtime::ArithmeticLib::Register();
			Runtime::LogicLib::Register();
			Runtime::StandardLib::Register();
			Runtime::StringLib::Register();
			Runtime::ArrayLib::Register();
			Runtime::FileLib::Register();
			Runtime::TimeLib::Register();
			for (auto fName : Runtime::FunctionLibrary::getFunctionNames())
			{
				registerKeyword(fName, BisonParser::token::BFNAME);
			}
		}

		//-------------------------------------------------------------------------------------------
		void Support::registerKeyword(const std::string & aName, const int aId)
		{
			mNameTable[aName] = aId;
		}

		//
		// lookForIdent - поиск идентификатора в таблице имен.
		//
		int Support::lookForIdent(const std::string & aName, Ident & aIdent)
		{
			const auto pos = mNameTable.find(aName);
			if (pos != mNameTable.end())
			{
				aIdent.Ptr = &pos->first;
				return mNameTable[aName];
			}
			return 0;
		}

		//
		// newIdent - добавление идентификатора в таблицу имен.
		//
		void Support::newIdent(const std::string & aName, const int aId, Ident & aIdent)
		{
			mNameTable[aName] = aId;
			aIdent.Ptr = &mNameTable.find(aName)->first;
		}

		//-------------------------------------------------------------------------------------------
		Ident Support::newConstant(const std::string& aConstant, const size_t aLine, const size_t aCol)
		{
			Ident ident{};
			ident.Col = aCol;
			ident.Line = aLine;
			ident.Ptr = &*mConstantTable.insert(aConstant).first;
			return ident;
		}

		//-------------------------------------------------------------------------------------------
		const char* Support::getErrorString(const ParserErrTypes::ErrType aErr)
		{
			const char * msg = nullptr;
			switch (aErr)
			{
			case ParserErrTypes::GeneralSyntaxError:             
				msg = ""; 
				break;
			case ParserErrTypes::EOFInComment:                   
				msg = "end of file was reached in comment block. ";
				break;
			case ParserErrTypes::IntConstOverflow:               
				msg = "integer constant overflow. ";
				break;
			case ParserErrTypes::IllegalCharacter:               
				msg = "illegal character. ";
				break;
			case ParserErrTypes::MissingMainTypeDef:             
				msg = "missing main type definition. ";
				break;
			case ParserErrTypes::DuplicateDefinition:            
				msg = "identifier was defined before. ";
				break;
			case ParserErrTypes::UndefinedIdentifier:            
				msg = "undefined identifier. ";
				break;
			case ParserErrTypes::InvalidNumberOfParameters:      
				msg = "invalid number of parameters. "; 
				break;
			case ParserErrTypes::UndefinedSchemeName:            
				msg = "undefined scheme name. ";
				break;
			case ParserErrTypes::IncorrectIdentifierUsage:       
				msg = "incorrect use of identifier. ";
				break;
			case ParserErrTypes::NotATemplateType:               
				msg = "not a template type. ";
				break;
			case ParserErrTypes::InvalidTemplateArgumentsNumber: 
				msg = "invalid type parameters number. ";
				break;
			case ParserErrTypes::InvalidConstructorUsage:        
				msg = "invalid constructor usage. ";
				break;
			case ParserErrTypes::NestedDataDefinition:           
				msg = "nested data definitions are not allowed. ";
				break;
			case ParserErrTypes::MultipleTypeExpression:         
				msg = "only one type expression is allowed. ";
				break;
			case ParserErrTypes::InvalidFunCallParameters: 
				msg = "function parameters cannot be used as another function parameters. "; 
				break;
			case ParserErrTypes::InvalidConstant:                
				msg = "constant is invalid or out of range. "; 
				break;
			case ParserErrTypes::MissingMainDefinition:          
				msg = "missing main definition in function. "; 
				break;
			case ParserErrTypes::InvalidTupleIndex:              
				msg = "invalid tuple element index. "; 
				break;
			default:                                       
				msg = "unknown error. ";
			}
			return msg;
		}

		//-------------------------------------------------------------------------------------------
		void Support::getErrorList(std::ostream & aOutStream) const
		{
			std::vector<ErrorMessage> processed;
			for (auto& errMsg : mErrorList)
			{
				if (std::find(processed.begin(), processed.end(), errMsg) == processed.end()) {
					printError(aOutStream, errMsg.mIdent.Line, errMsg.mIdent.Col, getErrorString(errMsg.mErr) + *errMsg.mIdent.Ptr);
					processed.push_back(errMsg);
				}
			}
		}

		void Support::printError(std::ostream& outStream, const size_t line, const size_t col,	const std::string& message)
		{
			outStream << "Line " << line << ", ch " << col << ": " << message << std::endl;
		}

		//-------------------------------------------------------------------------------------------
		void Support::pushIdent(const Ident & aIdent)
		{
			mIdentStack.push_back(aIdent);
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

		void inputTokenToStream(std::stringstream& inputTupleStream, const std::string& str)
		{
			for (size_t i = 0; i < str.size(); ++i)
			{
				if (str[i] == '\\') inputTupleStream << "\\\\";
				else if (str[i] == '"') inputTupleStream << "\\\"";
				else inputTupleStream << str[i];
			}
		}

		//-------------------------------------------------------------------------------------------
		ASTNode* Support::getAST(std::vector<std::string>& inputTuple, const std::string& programStr)
		{
			std::stringstream program;

			// Сбрасываем состояние.
			mIdentStack.clear();
			mNameTable.clear();
			mConstantTable.clear();

			initializeKeywordTable();

			// Плохая временная реализация получения начального кортежа из параметров запуска.
			// Изменится с реализацией именованных параметров.
			if (!inputTuple.empty())
			{
				std::stringstream inputTupleStream;

				inputTupleStream << "(\"";
				inputTokenToStream(inputTupleStream, inputTuple[0]);
				for (size_t i = 1; i < inputTuple.size(); ++i)
				{
					inputTupleStream << "\", \"";
					inputTokenToStream(inputTupleStream, inputTuple[i]);
				}
				inputTupleStream << "\")";

				const size_t inPos = programStr.rfind('%');
				if (inPos != static_cast<size_t>(-1))
				{
					std::string end = programStr.substr(inPos);
					size_t fPos, lPos = end.rfind(')');
					if (lPos != static_cast<size_t>(-1))
					{
						fPos = end.find('(');
						++lPos;
					}
					else
					{
						fPos = end.find_first_of("\n\r");
						if (fPos == static_cast<size_t>(-1)) fPos = end.length();
						lPos = fPos;
					}
					// Если блок Application не отсутствует в принципе.
					if (fPos != static_cast<size_t>(-1))
					{
						program << programStr.substr(0, inPos);
						program << end.substr(0, fPos);
						program << inputTupleStream.str();
						program << end.substr(lPos, end.length());
					}
					else program << programStr;
				}
				else program << programStr;
			}//*/
			else program << programStr;

			//std::cout << program.str();

			Tokenizer tokenizer(program);
			ASTNode *root = nullptr;
			BisonParser parser(this, &tokenizer, root);

			//parser.set_debug_stream(std::cerr);
			//parser.set_debug_level(1);

			const int result = parser.parse();

			std::unique_ptr<ASTNode> rootPtr(root);

			if (result)
			{
				return nullptr;
			}

			NamesChecker checkNames(this, root);

			if (mWasError)
			{
				return nullptr;
			}

			RecursionFinder recursionFinder(root);

			return rootPtr.release();
		}
	}
}
