﻿#pragma once

#include <string>
#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>

#include "Ident.h"
#include "AST.h"

namespace FPTL
{
	namespace Parser
	{
		/*
		 * Идентификаторы кодов синтаксических и семантических ошибок.
		 */
		namespace ParserErrTypes
		{
			enum ErrType
			{
				NoError = 0,
				UnknownError,
				GeneralSyntaxError,
				EOFInComment,
				IntConstOverflow,
				IllegalCharacter,
				MissingMainTypeDef,
				DuplicateDefinition,
				InvalidFuncCall,
				FuncCallMissingFuncParams,
				MissingMainDefinition,
				UndefinedIdentifier,
				InvalidNumberOfParameters,
				InvalidParametersUsage,
				UndefinedSchemeName,
				IncorrectIdentifierUsage,
				InvalidConstructorUsage,
				NotATemplateType,
				InvalidTemplateArgumentsNumber,
				MissingTypeParametersList,
				NestedConstructor,
				InvalidTypeDefinition,
				InvalidConstructorParametersNumber,
				TypeMismatch,
				NotAParameterizedFunction,
				InvalidNumberOfFunctionalParameters,
				DataBlockWithoutConstructors,
				NestedDataDefinition,
				MultipleTypeExpression,
				InvalidFunCallParameters,
				InvalidConstant,
				InvalidTupleIndex
			};
		}

		/*
		 * Сообщение об ошибке: код ошибки, идентификатор,
		 * таблица соотв формальных/фактических типовых параметров.
		 */
		class ErrorMessage
		{
		public:

			ErrorMessage(ParserErrTypes::ErrType aErr, Ident aIdent);

			ParserErrTypes::ErrType mErr;
			Ident mIdent;

			bool operator == (const ErrorMessage & other) const {
				return mErr == other.mErr
					&& mIdent == other.mIdent
					&& mIdent.Col == other.mIdent.Col
					&& mIdent.Line == other.mIdent.Line;
			}
		};

		/*
		 * Support - реализует сбор и хранение семантической информации.
		 */
		class Support
		{
		public:

			Support();
			~Support();

			// Методы обработки ошибок.

			void               semanticError(ParserErrTypes::ErrType aErr, Ident aIdent);

			static const std::string getErrorString(const ErrorMessage& aErr);
			void printErrorList(std::ostream & aOutStream) const;
			static void printPositionalMessage(std::ostream & outStream, const size_t line, const size_t col, const std::string& message);

			// Методы для работы с таблицей имен.

			void		       initializeKeywordTable(void);
			void		       registerKeyword(const std::string & aName, int aId);
			void		       newIdent(const std::string & aName, int aId, Ident & aIdent);
			int				   lookForIdent(const std::string & aName, Ident & aIdent);

			Ident              newConstant(const std::string& aConstant, size_t aLine, size_t aCol);

			// Проводит синтаксический разбор, семантическую проверку и возвращает AST-дерево.
			ASTNode*           getAST(std::vector<std::string>& inputTuple, const std::string& programStr);

			// Вспомогательные методы для парсера.
			void               pushIdent(const Ident & aIdent);
			void               popIdent();
			Ident              getTopIdent() const;
			bool WasErrors() const { return mWasError; }

		private:

			std::list<ErrorMessage> mErrorList;

			std::unordered_map<std::string, int> mNameTable;
			std::unordered_set<std::string> mConstantTable;

			bool mWasError;

			std::vector<Ident> mIdentStack;
		};
	}
}
