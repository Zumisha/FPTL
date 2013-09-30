#ifndef SUPPORT_H
#define SUPPORT_H

#include <vector>
#include <hash_set>
#include "Ident.h"
#include "NodeVisitor.h"

namespace FPTL
{
	namespace Parser
	{

	/*
	 * �������������� ����� �������������� � ������������� ������.
	 */
	namespace ErrTypes
	{
		enum ErrType
		{
			NoError						= 0,
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
			InvalidFuncallParameters,
			InvalidConstant,
			InvalidTupleIndex
		};
	};

	/*
	 * ��������� �� ������: ��� ������, �������������,
	 * ������� ����� ����������/����������� ������� ����������.
	 */
	class ErrorMessage
	{
	public:

		ErrorMessage( ErrTypes::ErrType aErr, Ident aIdent );

		ErrTypes::ErrType mErr;
		Ident mIdent;
	};

	/*
	 * Support - ��������� ���� � �������� ������������� ����������.
	 */
	class Support
	{
	public:

		Support();
		~Support();

		// ������ ��������� ������.

		void               semanticError( ErrTypes::ErrType aErr, Ident aIdent );

		const char *       getErrorString( ErrTypes::ErrType aErr ) const;
		void               getErrorList( std::ostream & aOutStream );

		// ������ ��� ������ � �������� ����.

		void		       initializeKeywordTable( void );
		void		       registerKeyword( const std::string & aName, int aId );
		void		       newIdent( const std::string & aName, int aId, Ident & aIdent );
		int			       lookForIdent( const std::string & aName, Ident & aIdent );

		Ident              newConstant( const std::string & aConstant, int aLine, int aCol );

		// �������� ������������� ������, ������������� �������� � ���������� AST-������.
		ASTNode *          getInternalForm( class Tokenizer * aTokenizer );

		// ��������������� ������ ��� �������.
		void               pushIdent( const Ident & aIdent );
		void               popIdent();
		Ident              getTopIdent() const;

	private:

		std::list<ErrorMessage> mErrorList;

		stdext::hash_map<std::string, int> mNameTable;
		stdext::hash_set<std::string> mConstantTable;

		bool mWasError;

		std::vector<Ident> mIdentStack;
	};

	} // Parser
} // FPTL

#endif