
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* First part of user declarations.  */


/* Line 311 of lalr1.cc  */
#line 41 "parser.tab.cc"


#include "Parser.tab.hh"

/* User implementation prologue.  */


/* Line 317 of lalr1.cc  */
#line 50 "parser.tab.cc"
/* Unqualified %code blocks.  */

/* Line 318 of lalr1.cc  */
#line 49 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"

#include "../Support.h"
#include "../Tokenizer.h"
#include "../Nodes.h"



/* Line 318 of lalr1.cc  */
#line 63 "parser.tab.cc"

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


/* Line 380 of lalr1.cc  */
#line 2 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
namespace FPTL { namespace Parser {

/* Line 380 of lalr1.cc  */
#line 131 "parser.tab.cc"
#if YYERROR_VERBOSE

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  BisonParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

#endif

  /// Build a parser object.
  BisonParser::BisonParser (Support * pSupport_yyarg, Tokenizer * aTokenizer_yyarg, ASTNode* & mASTRoot_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      pSupport (pSupport_yyarg),
      aTokenizer (aTokenizer_yyarg),
      mASTRoot (mASTRoot_yyarg)
  {
  }

  BisonParser::~BisonParser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  BisonParser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  BisonParser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  BisonParser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
        case 12: /* "NUMBER" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 244 "parser.tab.cc"
	break;
      case 13: /* "REALNUMBER" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 257 "parser.tab.cc"
	break;
      case 14: /* "STRING" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 270 "parser.tab.cc"
	break;
      case 56: /* "FunctionalProgram" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 283 "parser.tab.cc"
	break;
      case 57: /* "DataTypeDefinitionsBlocks" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scList);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 296 "parser.tab.cc"
	break;
      case 58: /* "DataTypeDefinitionsBlock" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 309 "parser.tab.cc"
	break;
      case 60: /* "TypeParametersList" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scList);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 322 "parser.tab.cc"
	break;
      case 61: /* "TypeParameterDef" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scDef);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 335 "parser.tab.cc"
	break;
      case 62: /* "ConstructorsDefinitionList" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scList);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 348 "parser.tab.cc"
	break;
      case 63: /* "ConstructorDef" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 361 "parser.tab.cc"
	break;
      case 64: /* "ConstructorParametersList" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scList);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 374 "parser.tab.cc"
	break;
      case 65: /* "TypesDefinitionList" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scList);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 387 "parser.tab.cc"
	break;
      case 66: /* "TypesDefinitionList2" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scList);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 400 "parser.tab.cc"
	break;
      case 67: /* "TypeDefinition" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scDef);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 413 "parser.tab.cc"
	break;
      case 68: /* "TypeDefConstructor" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 426 "parser.tab.cc"
	break;
      case 69: /* "TypeExpression" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 439 "parser.tab.cc"
	break;
      case 70: /* "AtomType" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scName);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 452 "parser.tab.cc"
	break;
      case 72: /* "TypeExpressionsList" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scList);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 465 "parser.tab.cc"
	break;
      case 75: /* "Scheme" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scFun);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 478 "parser.tab.cc"
	break;
      case 77: /* "FormalParametersList" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scList);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 491 "parser.tab.cc"
	break;
      case 78: /* "FormalParameter" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scDef);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 504 "parser.tab.cc"
	break;
      case 79: /* "DefinitionsList" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scList);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 517 "parser.tab.cc"
	break;
      case 80: /* "Definition" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 530 "parser.tab.cc"
	break;
      case 81: /* "Term" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 543 "parser.tab.cc"
	break;
      case 82: /* "AtomTerm" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 556 "parser.tab.cc"
	break;
      case 83: /* "FuncObjectWithParameters" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scName);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 569 "parser.tab.cc"
	break;
      case 84: /* "FuncArgumentList" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scList);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 582 "parser.tab.cc"
	break;
      case 85: /* "FuncParameterName" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 595 "parser.tab.cc"
	break;
      case 86: /* "SequentialTerm" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 608 "parser.tab.cc"
	break;
      case 87: /* "CompositionTerm" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 621 "parser.tab.cc"
	break;
      case 88: /* "ConditionTerm" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 634 "parser.tab.cc"
	break;
      case 89: /* "VariantTerm" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 647 "parser.tab.cc"
	break;
      case 90: /* "FuncObjectName" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scName);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 660 "parser.tab.cc"
	break;
      case 91: /* "ConstructionFun" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scFun);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 673 "parser.tab.cc"
	break;
      case 96: /* "ElementaryFunctionName" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 686 "parser.tab.cc"
	break;
      case 97: /* "Constructor" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scName);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 699 "parser.tab.cc"
	break;
      case 98: /* "Destructor" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scName);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 712 "parser.tab.cc"
	break;
      case 99: /* "BuiltInFunction" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 725 "parser.tab.cc"
	break;
      case 100: /* "TupleElement" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 738 "parser.tab.cc"
	break;
      case 101: /* "Constant" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 751 "parser.tab.cc"
	break;
      case 102: /* "BuiltInFunctionName" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scName);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 764 "parser.tab.cc"
	break;
      case 103: /* "Application" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scApp);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 777 "parser.tab.cc"
	break;
      case 104: /* "DataInit" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scList);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 790 "parser.tab.cc"
	break;
      case 105: /* "OneDataInit" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scDef);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 803 "parser.tab.cc"
	break;
      case 107: /* "InterpFunProgramName" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scName);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 816 "parser.tab.cc"
	break;
      case 108: /* "Data" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 829 "parser.tab.cc"
	break;
      case 109: /* "OneData" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 842 "parser.tab.cc"
	break;
      case 110: /* "ValueAtom" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 855 "parser.tab.cc"
	break;
      case 111: /* "ValueConstructor" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 868 "parser.tab.cc"
	break;
      case 112: /* "ValueComposition" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 881 "parser.tab.cc"
	break;
      case 113: /* "Value" */

/* Line 480 of lalr1.cc  */
#line 56 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
	{
	ASTNode * node = (yyvaluep->scNode);
	delete node;

};

/* Line 480 of lalr1.cc  */
#line 894 "parser.tab.cc"
	break;

	default:
	  break;
      }
  }

  void
  BisonParser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  BisonParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  BisonParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  BisonParser::debug_level_type
  BisonParser::debug_level () const
  {
    return yydebug_;
  }

  void
  BisonParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  int
  BisonParser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    semantic_type yylval;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[2];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yyn == yypact_ninf_)
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, pSupport, aTokenizer);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yyn == 0 || yyn == yytable_ninf_)
	goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 2:

/* Line 678 of lalr1.cc  */
#line 179 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			mASTRoot = new FunctionalProgram( (yysemantic_stack_[(3) - (1)].scList), (yysemantic_stack_[(3) - (2)].scFun), (yysemantic_stack_[(3) - (3)].scApp) );
			
			// Возвращаем 0, иначе все дерево будет "срублено" деструктором парсера.
			(yyval.scNode) = 0;
		}
    break;

  case 3:

/* Line 678 of lalr1.cc  */
#line 186 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			mASTRoot = new FunctionalProgram( 0, (yysemantic_stack_[(2) - (1)].scFun), (yysemantic_stack_[(2) - (2)].scApp) );
			(yyval.scNode) = 0;
		}
    break;

  case 4:

/* Line 678 of lalr1.cc  */
#line 196 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scList) = new ListNode(  ASTNode::DataTypeDefinitionsBlocks );
			(yyval.scList)->addElement( (yysemantic_stack_[(1) - (1)].scNode) );
		}
    break;

  case 5:

/* Line 678 of lalr1.cc  */
#line 201 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scList) = (yysemantic_stack_[(2) - (2)].scList)->addElement( (yysemantic_stack_[(2) - (1)].scNode) );
		}
    break;

  case 6:

/* Line 678 of lalr1.cc  */
#line 208 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new DataNode(  (yysemantic_stack_[(5) - (2)].scIdent), (yysemantic_stack_[(5) - (4)].scList), 0, 0 );
		}
    break;

  case 7:

/* Line 678 of lalr1.cc  */
#line 212 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new DataNode(  (yysemantic_stack_[(8) - (2)].scIdent), (yysemantic_stack_[(8) - (7)].scList), (yysemantic_stack_[(8) - (4)].scList), 0 );
		}
    break;

  case 8:

/* Line 678 of lalr1.cc  */
#line 216 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new DataNode(  (yysemantic_stack_[(9) - (2)].scIdent), (yysemantic_stack_[(9) - (8)].scList), 0, (yysemantic_stack_[(9) - (6)].scList) );
		}
    break;

  case 9:

/* Line 678 of lalr1.cc  */
#line 220 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new DataNode(  (yysemantic_stack_[(12) - (2)].scIdent), (yysemantic_stack_[(12) - (11)].scList), (yysemantic_stack_[(12) - (4)].scList), (yysemantic_stack_[(12) - (9)].scList) );
		}
    break;

  case 11:

/* Line 678 of lalr1.cc  */
#line 231 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scList) = new ListNode( ASTNode::TypeParametersList );
			(yyval.scList)->addElement( (yysemantic_stack_[(1) - (1)].scDef) );
		}
    break;

  case 12:

/* Line 678 of lalr1.cc  */
#line 236 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {		
			(yyval.scList) = (yysemantic_stack_[(3) - (3)].scList)->addElement( (yysemantic_stack_[(3) - (1)].scDef) );
		}
    break;

  case 13:

/* Line 678 of lalr1.cc  */
#line 243 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scDef) = new DefinitionNode( ASTNode::TypeParameterDefinition, (yysemantic_stack_[(1) - (1)].scIdent), 0 );
		}
    break;

  case 14:

/* Line 678 of lalr1.cc  */
#line 250 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scList) = new ListNode( ASTNode::ConstructorsDefinitionList );
			(yyval.scList)->addElement( (yysemantic_stack_[(1) - (1)].scNode) );
		}
    break;

  case 15:

/* Line 678 of lalr1.cc  */
#line 255 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scList) = (yysemantic_stack_[(2) - (2)].scList)->addElement( (yysemantic_stack_[(2) - (1)].scNode) );
		}
    break;

  case 16:

/* Line 678 of lalr1.cc  */
#line 262 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new ConstructorNode( (yysemantic_stack_[(5) - (4)].scIdent), 0, (yysemantic_stack_[(5) - (2)].scIdent) );
		}
    break;

  case 17:

/* Line 678 of lalr1.cc  */
#line 266 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new ConstructorNode( (yysemantic_stack_[(6) - (5)].scIdent), (yysemantic_stack_[(6) - (1)].scList), (yysemantic_stack_[(6) - (3)].scIdent) );
		}
    break;

  case 18:

/* Line 678 of lalr1.cc  */
#line 272 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scList) = new ListNode( ASTNode::ConstructorParametersList );
			(yyval.scList)->addElement( (yysemantic_stack_[(1) - (1)].scName) );
		}
    break;

  case 19:

/* Line 678 of lalr1.cc  */
#line 277 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scList) = (yysemantic_stack_[(3) - (3)].scList)->addElement( (yysemantic_stack_[(3) - (1)].scName) );
		}
    break;

  case 20:

/* Line 678 of lalr1.cc  */
#line 285 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			if( (yysemantic_stack_[(1) - (1)].scList)->size() > 1 )
			{
				for( ListNode::iterator it = (yysemantic_stack_[(1) - (1)].scList)->begin(); it != (yysemantic_stack_[(1) - (1)].scList)->end(); ++it )
					pSupport->semanticError( ErrTypes::MultipleTypeExpression, static_cast<DefinitionNode*>( *it )->getDefinitionName() );
			}

			(yyval.scList) = (yysemantic_stack_[(1) - (1)].scList);
		}
    break;

  case 21:

/* Line 678 of lalr1.cc  */
#line 298 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scList) = new ListNode( ASTNode::TypesDefinitionList );
			(yyval.scList)->addElement( (yysemantic_stack_[(1) - (1)].scDef) );
		}
    break;

  case 22:

/* Line 678 of lalr1.cc  */
#line 303 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scList) = (yysemantic_stack_[(2) - (2)].scList)->addElement( (yysemantic_stack_[(2) - (1)].scDef) );
		}
    break;

  case 23:

/* Line 678 of lalr1.cc  */
#line 310 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scDef) = new DefinitionNode( ASTNode::TypeDefinition, (yysemantic_stack_[(4) - (1)].scIdent), (yysemantic_stack_[(4) - (3)].scNode) );
		}
    break;

  case 24:

/* Line 678 of lalr1.cc  */
#line 314 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			pSupport->semanticError( ErrTypes::NestedDataDefinition, static_cast<DataNode*>((yysemantic_stack_[(1) - (1)].scNode))->getDataName() );
			delete (yysemantic_stack_[(1) - (1)].scNode);
			(yyval.scDef) = 0;
		}
    break;

  case 25:

/* Line 678 of lalr1.cc  */
#line 323 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new DefinitionNode( ASTNode::TypeConstructorDefinition, (yysemantic_stack_[(3) - (3)].scIdent), (yysemantic_stack_[(3) - (1)].scList) );
		}
    break;

  case 26:

/* Line 678 of lalr1.cc  */
#line 327 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new DefinitionNode( ASTNode::TypeConstructorDefinition, (yysemantic_stack_[(1) - (1)].scIdent), 0 );
		}
    break;

  case 28:

/* Line 678 of lalr1.cc  */
#line 335 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new ExpressionNode( ASTNode::TypeExpression, (yysemantic_stack_[(3) - (1)].scNode), (yysemantic_stack_[(3) - (3)].scNode) );
		}
    break;

  case 29:

/* Line 678 of lalr1.cc  */
#line 343 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {	
			(yyval.scName) = new NameRefNode( (yysemantic_stack_[(1) - (1)].scToken), NameRefNode::BaseType );
		}
    break;

  case 30:

/* Line 678 of lalr1.cc  */
#line 347 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scName) = new NameRefNode( (yysemantic_stack_[(1) - (1)].scIdent), NameRefNode::Type );
		}
    break;

  case 31:

/* Line 678 of lalr1.cc  */
#line 351 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scName) = new NameRefNode( (yysemantic_stack_[(4) - (1)].scIdent), NameRefNode::Template, (yysemantic_stack_[(4) - (3)].scList) );
		}
    break;

  case 32:

/* Line 678 of lalr1.cc  */
#line 355 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scName) = new NameRefNode( (yysemantic_stack_[(1) - (1)].scIdent), NameRefNode::TypeParamName );
		}
    break;

  case 40:

/* Line 678 of lalr1.cc  */
#line 372 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scList) = new ListNode( ASTNode::TypeExpressionsList );
			(yyval.scList)->addElement( (yysemantic_stack_[(1) - (1)].scName) );
		}
    break;

  case 41:

/* Line 678 of lalr1.cc  */
#line 377 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scList) = (yysemantic_stack_[(3) - (3)].scList)->addElement( (yysemantic_stack_[(3) - (1)].scName) );
		}
    break;

  case 44:

/* Line 678 of lalr1.cc  */
#line 390 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scFun) = new FunctionNode( (yysemantic_stack_[(4) - (1)].scIdent), (yysemantic_stack_[(4) - (3)].scList), 0 );
			pSupport->popIdent();
		}
    break;

  case 45:

/* Line 678 of lalr1.cc  */
#line 395 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scFun) = new FunctionNode( (yysemantic_stack_[(7) - (1)].scIdent), (yysemantic_stack_[(7) - (6)].scList), (yysemantic_stack_[(7) - (3)].scList) );
			pSupport->popIdent();
		}
    break;

  case 46:

/* Line 678 of lalr1.cc  */
#line 403 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			pSupport->pushIdent( (yysemantic_stack_[(2) - (2)].scIdent) );
			(yyval.scIdent) = (yysemantic_stack_[(2) - (2)].scIdent);
		}
    break;

  case 47:

/* Line 678 of lalr1.cc  */
#line 411 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scList) = new ListNode( ASTNode::FormalParametersList );
			(yyval.scList)->addElement( (yysemantic_stack_[(1) - (1)].scDef) );
		}
    break;

  case 48:

/* Line 678 of lalr1.cc  */
#line 416 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scList) = (yysemantic_stack_[(3) - (3)].scList)->addElement( (yysemantic_stack_[(3) - (1)].scDef) );
		}
    break;

  case 49:

/* Line 678 of lalr1.cc  */
#line 423 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scDef) = new DefinitionNode( ASTNode::FunctionParameterDefinition, (yysemantic_stack_[(1) - (1)].scIdent), 0 );
		}
    break;

  case 50:

/* Line 678 of lalr1.cc  */
#line 430 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scList) = new ListNode( ASTNode::DefinitionsList );
			(yyval.scList)->addElement( (yysemantic_stack_[(1) - (1)].scNode) );
		}
    break;

  case 51:

/* Line 678 of lalr1.cc  */
#line 435 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scList) = (yysemantic_stack_[(2) - (2)].scList)->addElement( (yysemantic_stack_[(2) - (1)].scNode) );
		}
    break;

  case 52:

/* Line 678 of lalr1.cc  */
#line 442 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new DefinitionNode( ASTNode::Definition, pSupport->getTopIdent(), (yysemantic_stack_[(4) - (3)].scNode) );
		}
    break;

  case 53:

/* Line 678 of lalr1.cc  */
#line 446 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new DefinitionNode( ASTNode::Definition, (yysemantic_stack_[(4) - (1)].scIdent), (yysemantic_stack_[(4) - (3)].scNode) );
		}
    break;

  case 54:

/* Line 678 of lalr1.cc  */
#line 450 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    { (yyval.scNode) = (yysemantic_stack_[(1) - (1)].scFun); }
    break;

  case 56:

/* Line 678 of lalr1.cc  */
#line 459 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {	(yyval.scNode) = (yysemantic_stack_[(3) - (2)].scNode); }
    break;

  case 58:

/* Line 678 of lalr1.cc  */
#line 462 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    { (yyval.scNode) = (yysemantic_stack_[(1) - (1)].scName); }
    break;

  case 59:

/* Line 678 of lalr1.cc  */
#line 464 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new NameRefNode( pSupport->getTopIdent(), ASTNode::FuncObjectName );
		}
    break;

  case 60:

/* Line 678 of lalr1.cc  */
#line 471 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scName) = new NameRefNode( (yysemantic_stack_[(4) - (1)].scIdent), NameRefNode::FuncObjectWithParameters, (yysemantic_stack_[(4) - (3)].scList) );
		}
    break;

  case 61:

/* Line 678 of lalr1.cc  */
#line 477 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scList) = new ListNode( ASTNode::FuncArgumentsList );
			(yyval.scList)->addElement( (yysemantic_stack_[(1) - (1)].scNode) );
		}
    break;

  case 62:

/* Line 678 of lalr1.cc  */
#line 482 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scList) = (yysemantic_stack_[(3) - (3)].scList)->addElement( (yysemantic_stack_[(3) - (1)].scNode) );
		}
    break;

  case 63:

/* Line 678 of lalr1.cc  */
#line 489 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new NameRefNode( (yysemantic_stack_[(1) - (1)].scIdent), NameRefNode::FuncParameterName );
		}
    break;

  case 65:

/* Line 678 of lalr1.cc  */
#line 494 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    { (yyval.scNode) = (yysemantic_stack_[(1) - (1)].scName); }
    break;

  case 67:

/* Line 678 of lalr1.cc  */
#line 500 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new ExpressionNode( ASTNode::SequentialTerm, (yysemantic_stack_[(3) - (1)].scNode), (yysemantic_stack_[(3) - (3)].scNode) );
		}
    break;

  case 69:

/* Line 678 of lalr1.cc  */
#line 508 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new ExpressionNode( ASTNode::CompositionTerm, (yysemantic_stack_[(3) - (1)].scNode), (yysemantic_stack_[(3) - (3)].scNode) );
		}
    break;

  case 71:

/* Line 678 of lalr1.cc  */
#line 516 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new ExpressionNode( ASTNode::ConditionTerm, (yysemantic_stack_[(5) - (1)].scNode), (yysemantic_stack_[(5) - (3)].scNode), (yysemantic_stack_[(5) - (5)].scNode) );
		}
    break;

  case 72:

/* Line 678 of lalr1.cc  */
#line 520 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new ExpressionNode( ASTNode::ConditionTerm, (yysemantic_stack_[(3) - (1)].scNode), (yysemantic_stack_[(3) - (3)].scNode) );
		}
    break;

  case 74:

/* Line 678 of lalr1.cc  */
#line 528 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new ExpressionNode( ASTNode::VariantTerm, (yysemantic_stack_[(3) - (1)].scNode), (yysemantic_stack_[(3) - (3)].scNode) );
		}
    break;

  case 75:

/* Line 678 of lalr1.cc  */
#line 535 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scName) = new NameRefNode( (yysemantic_stack_[(1) - (1)].scIdent), NameRefNode::FuncObjectName );
		}
    break;

  case 77:

/* Line 678 of lalr1.cc  */
#line 543 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			pSupport->pushIdent( (yysemantic_stack_[(2) - (2)].scIdent) );
		}
    break;

  case 78:

/* Line 678 of lalr1.cc  */
#line 547 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scFun) = new FunctionNode( (yysemantic_stack_[(6) - (2)].scIdent), (yysemantic_stack_[(6) - (5)].scList), 0 );
			pSupport->popIdent();
		}
    break;

  case 79:

/* Line 678 of lalr1.cc  */
#line 552 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			pSupport->pushIdent( (yysemantic_stack_[(2) - (2)].scIdent) );
		}
    break;

  case 80:

/* Line 678 of lalr1.cc  */
#line 556 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scFun) = new FunctionNode( (yysemantic_stack_[(9) - (2)].scIdent), (yysemantic_stack_[(9) - (8)].scList), (yysemantic_stack_[(9) - (5)].scList) );
			pSupport->popIdent();
		}
    break;

  case 84:

/* Line 678 of lalr1.cc  */
#line 573 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    { (yyval.scNode) = (yysemantic_stack_[(1) - (1)].scName); }
    break;

  case 85:

/* Line 678 of lalr1.cc  */
#line 575 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    { (yyval.scNode) = (yysemantic_stack_[(1) - (1)].scName); }
    break;

  case 86:

/* Line 678 of lalr1.cc  */
#line 580 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scName) = new NameRefNode( (yysemantic_stack_[(1) - (1)].scIdent), NameRefNode::ConstructorName );
		}
    break;

  case 87:

/* Line 678 of lalr1.cc  */
#line 587 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {	
			(yyval.scName) = new NameRefNode( (yysemantic_stack_[(2) - (2)].scIdent), NameRefNode::DestructorName );
		}
    break;

  case 88:

/* Line 678 of lalr1.cc  */
#line 594 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    { (yyval.scNode) = (yysemantic_stack_[(1) - (1)].scName); }
    break;

  case 91:

/* Line 678 of lalr1.cc  */
#line 601 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
		ConstantNode * number = static_cast<ConstantNode*>( (yysemantic_stack_[(3) - (2)].scNode) );
		if (number->isNatural())
		{
			(yyval.scNode) = new ConstantNode( ASTNode::TupleElemNumber, number->getConstant() );
			delete number;
		}
		else
		{
			pSupport->semanticError(ErrTypes::InvalidTupleIndex, number->getConstant());
			(yyval.scNode) = 0;
		}
	}
    break;

  case 95:

/* Line 678 of lalr1.cc  */
#line 620 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new ConstantNode( ASTNode::TrueValue, (yysemantic_stack_[(1) - (1)].scToken) );
		}
    break;

  case 96:

/* Line 678 of lalr1.cc  */
#line 624 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new ConstantNode( ASTNode::FalseValue, (yysemantic_stack_[(1) - (1)].scToken) );
		}
    break;

  case 97:

/* Line 678 of lalr1.cc  */
#line 632 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scName) = new NameRefNode( (yysemantic_stack_[(1) - (1)].scIdent), NameRefNode::BuildInFunction );
		}
    break;

  case 98:

/* Line 678 of lalr1.cc  */
#line 639 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scApp) = new ApplicationBlock( (yysemantic_stack_[(2) - (2)].scName), 0, 0 );
		}
    break;

  case 99:

/* Line 678 of lalr1.cc  */
#line 643 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scApp) = new ApplicationBlock( (yysemantic_stack_[(5) - (2)].scName), (yysemantic_stack_[(5) - (4)].scNode), 0 );
		}
    break;

  case 100:

/* Line 678 of lalr1.cc  */
#line 647 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scApp) = new ApplicationBlock( (yysemantic_stack_[(3) - (3)].scName), 0, (yysemantic_stack_[(3) - (2)].scList) ); 
		}
    break;

  case 101:

/* Line 678 of lalr1.cc  */
#line 651 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scApp) = new ApplicationBlock( (yysemantic_stack_[(6) - (3)].scName), (yysemantic_stack_[(6) - (5)].scNode), (yysemantic_stack_[(6) - (2)].scList) );
		}
    break;

  case 102:

/* Line 678 of lalr1.cc  */
#line 658 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scList) = new ListNode( ASTNode::InputVarDefinitionList );
			(yyval.scList)->addElement( (yysemantic_stack_[(1) - (1)].scDef) );
		}
    break;

  case 103:

/* Line 678 of lalr1.cc  */
#line 663 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scList) = (yysemantic_stack_[(2) - (2)].scList)->addElement( (yysemantic_stack_[(2) - (1)].scDef) );
		}
    break;

  case 104:

/* Line 678 of lalr1.cc  */
#line 670 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scDef) = new DefinitionNode( ASTNode::InputVarDefinition, (yysemantic_stack_[(4) - (1)].scIdent), (yysemantic_stack_[(4) - (3)].scNode) );
		}
    break;

  case 106:

/* Line 678 of lalr1.cc  */
#line 679 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    { 
			(yyval.scName) = new NameRefNode((yysemantic_stack_[(2) - (2)].scIdent), ASTNode::RunningSchemeName);
		}
    break;

  case 107:

/* Line 678 of lalr1.cc  */
#line 686 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = (yysemantic_stack_[(1) - (1)].scNode);
		}
    break;

  case 108:

/* Line 678 of lalr1.cc  */
#line 690 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new ExpressionNode(ASTNode::InputVarList, (yysemantic_stack_[(3) - (1)].scNode), (yysemantic_stack_[(3) - (3)].scNode));
		}
    break;

  case 109:

/* Line 678 of lalr1.cc  */
#line 697 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new NameRefNode( (yysemantic_stack_[(1) - (1)].scIdent), ASTNode::InputVarName );
		}
    break;

  case 112:

/* Line 678 of lalr1.cc  */
#line 707 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    { (yyval.scNode) = (yysemantic_stack_[(1) - (1)].scName); }
    break;

  case 113:

/* Line 678 of lalr1.cc  */
#line 709 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = (yysemantic_stack_[(3) - (2)].scNode);
		}
    break;

  case 115:

/* Line 678 of lalr1.cc  */
#line 717 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new ExpressionNode( ASTNode::ValueConstructor, (yysemantic_stack_[(3) - (1)].scNode), (yysemantic_stack_[(3) - (3)].scName) );
		}
    break;

  case 117:

/* Line 678 of lalr1.cc  */
#line 725 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
    {
			(yyval.scNode) = new ExpressionNode( ASTNode::ValueComposition, (yysemantic_stack_[(3) - (1)].scNode), (yysemantic_stack_[(3) - (3)].scNode) );
		}
    break;



/* Line 678 of lalr1.cc  */
#line 1864 "parser.tab.cc"
	default:
          break;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	error (yylloc, yysyntax_error_ (yystate));
      }

    yyerror_range[0] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[0] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (yyn != yypact_ninf_)
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[0] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[1] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc);

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  BisonParser::yysyntax_error_ (int yystate)
  {
    std::string res;
    YYUSE (yystate);
#if YYERROR_VERBOSE
    int yyn = yypact_[yystate];
    if (yypact_ninf_ < yyn && yyn <= yylast_)
      {
	/* Start YYX at -YYN if negative to avoid negative indexes in
	   YYCHECK.  */
	int yyxbegin = yyn < 0 ? -yyn : 0;

	/* Stay within bounds of both yycheck and yytname.  */
	int yychecklim = yylast_ - yyn + 1;
	int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
	int count = 0;
	for (int x = yyxbegin; x < yyxend; ++x)
	  if (yycheck_[x + yyn] == x && x != yyterror_)
	    ++count;

	// FIXME: This method of building the message is not compatible
	// with internationalization.  It should work like yacc.c does it.
	// That is, first build a string that looks like this:
	// "syntax error, unexpected %s or %s or %s"
	// Then, invoke YY_ on this string.
	// Finally, use the string as a format to output
	// yytname_[tok], etc.
	// Until this gets fixed, this message appears in English only.
	res = "syntax error, unexpected ";
	res += yytnamerr_ (yytname_[tok]);
	if (count < 5)
	  {
	    count = 0;
	    for (int x = yyxbegin; x < yyxend; ++x)
	      if (yycheck_[x + yyn] == x && x != yyterror_)
		{
		  res += (!count++) ? ", expecting " : " or ";
		  res += yytnamerr_ (yytname_[x]);
		}
	  }
      }
    else
#endif
      res = YY_("syntax error");
    return res;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const short int BisonParser::yypact_ninf_ = -135;
  const short int
  BisonParser::yypact_[] =
  {
        50,    22,    32,    52,    42,    48,    53,     9,  -135,  -135,
      20,  -135,    53,  -135,    11,  -135,    14,    67,    17,    68,
    -135,  -135,    71,    28,    78,    36,    34,  -135,    83,    55,
      74,    14,  -135,    73,  -135,    79,    80,    85,  -135,    75,
      87,  -135,    25,  -135,    88,    86,  -135,  -135,    84,  -135,
      99,    93,  -135,    92,    44,  -135,  -135,    44,    96,    67,
     137,   152,  -135,  -135,    97,    68,    93,  -135,  -135,  -135,
    -135,  -135,  -135,    99,  -135,  -135,  -135,    91,    95,  -135,
     100,  -135,   102,   104,  -135,   103,   107,   101,  -135,   138,
    -135,    44,   151,   115,  -135,  -135,   113,     7,  -135,   117,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,   126,    14,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,    32,   131,
     136,   137,   146,   139,  -135,  -135,   140,   150,   142,  -135,
      21,  -135,   148,   149,   151,    99,  -135,  -135,    93,    14,
      67,   105,   147,   153,  -135,  -135,    44,    44,    44,    44,
    -135,   161,   158,   167,    25,  -135,    32,   167,   151,   152,
    -135,   164,   165,  -135,  -135,  -135,  -135,  -135,   166,   168,
     101,  -135,   157,   169,  -135,  -135,  -135,  -135,   -14,   113,
    -135,  -135,   185,   170,   172,   171,   173,  -135,  -135,  -135,
     137,  -135,  -135,   176,  -135,   105,    44,   174,   167,  -135,
    -135,   186,   178,    14,  -135,  -135,  -135,  -135,   175,    25,
     181,  -135,   182,  -135,  -135
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  BisonParser::yydefact_[] =
  {
         0,     0,     0,     0,     0,     4,     0,     0,    46,    10,
       0,     1,     0,     5,     0,     3,     0,     0,     0,     0,
       2,   105,     0,     0,   102,     0,    98,    82,     0,     0,
       0,    50,    54,     0,    49,     0,    47,     0,    24,     0,
       0,    20,    21,    42,     0,    11,    13,   106,   100,   103,
       0,     0,    81,    77,     0,    44,    51,     0,     0,     0,
       0,     0,     6,    22,     0,     0,     0,    43,    92,    93,
      94,    95,    96,     0,    86,   112,   111,   114,   116,   118,
       0,   109,     0,   107,   110,     0,     0,    75,    97,     0,
      59,     0,     0,     0,    66,    76,    68,    70,    73,    55,
      58,    57,    84,    85,    83,    89,    90,    88,     0,     0,
      48,    33,    34,    35,    36,    37,    38,    39,     0,    30,
       0,    14,     0,    18,    29,    32,     0,    27,     0,    26,
       0,    12,     0,     0,     0,     0,   104,    99,     0,     0,
       0,     0,     0,     0,    87,    52,     0,     0,     0,     0,
      53,     0,     0,     0,     0,    15,     0,     0,     0,     0,
      23,     0,     0,   101,   113,   115,   117,   108,     0,     0,
      63,    65,     0,    61,    64,    91,    56,    67,    72,    69,
      74,    45,     0,    40,     0,     0,     0,    19,    25,    28,
       0,     7,    78,     0,    60,     0,     0,     0,     0,    31,
       8,     0,     0,     0,    62,    71,    16,    41,     0,     0,
       0,    17,     0,    80,     9
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  BisonParser::yypgoto_[] =
  {
      -135,  -135,   204,    31,    -2,   159,  -135,  -110,  -135,   -56,
    -120,   183,  -135,  -135,    57,  -126,  -135,    29,    -1,   -59,
     219,  -135,   -50,  -135,   -30,  -135,   -36,    82,  -129,    35,
    -135,    81,    89,  -134,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,  -128,   -47,  -135,  -135,  -135,   -43,  -135,   214,   207,
    -135,    27,   209,   -60,  -135,  -135,  -135,    98,   -28
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  BisonParser::yydefgoto_[] =
  {
        -1,     3,     4,    38,   119,    44,    45,   120,   121,   122,
      40,    41,    42,   127,   128,   123,   124,   184,   125,    74,
       6,     7,    35,    36,    30,    31,    93,    94,    95,   172,
     173,    96,    97,    98,    99,   100,    32,    85,    86,    53,
      33,   101,   102,   103,   104,   105,   106,   107,    15,    23,
      24,    81,    26,    82,    83,    77,    78,    79,    84
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char BisonParser::yytable_ninf_ = -80;
  const short int
  BisonParser::yytable_[] =
  {
        10,    56,   129,    75,    75,   126,   132,    76,    76,   110,
     162,   155,   171,   174,    21,   180,    39,    27,    46,    75,
       9,   108,    80,    76,     9,     8,    75,   183,     9,   196,
      76,     5,   148,   144,   185,     9,     5,    28,     2,    37,
      39,    25,     2,   161,   147,   133,     2,    87,    16,    67,
      17,    25,    11,   148,    88,   143,    68,    69,    70,    18,
       1,    19,   205,    29,    46,    22,   171,   174,     1,     2,
      34,     2,   183,    14,    47,    43,    71,    72,   167,   151,
     202,    21,    22,    50,    51,    89,    52,   165,    75,   212,
     169,    75,    76,    90,    91,    76,    21,    92,    67,   188,
     129,   187,    54,   126,    67,    68,    69,    70,   170,   168,
      67,    68,    69,    70,    55,    88,   152,    68,    69,    70,
      57,    58,    61,    59,    60,    71,    72,    62,    39,    65,
      64,    71,    72,   -79,    66,   109,   130,    71,    72,   134,
       9,   135,   139,    73,    43,   136,    89,   138,   140,    73,
     142,   141,    39,   137,   186,     9,    67,    67,    92,    43,
     145,   146,   111,   112,   113,   114,   115,   116,   117,   149,
       9,   150,   153,   210,    43,   118,   154,   111,   112,   113,
     114,   115,   116,   117,   156,   157,   159,   160,   158,   175,
     197,   208,   111,   112,   113,   114,   115,   116,   117,   163,
     164,   181,   182,   190,   176,   191,   192,    39,   194,    13,
     193,   200,   195,   198,   199,   203,   189,   201,   209,   206,
     211,   213,   214,    12,   131,    63,    20,   207,   177,   179,
     204,    49,    48,   166,     0,     0,   178
  };

  /* YYCHECK.  */
  const short int
  BisonParser::yycheck_[] =
  {
         2,    31,    61,    50,    51,    61,    66,    50,    51,    59,
     130,   121,   141,   141,     3,   149,    18,     3,    19,    66,
       3,    57,    50,    66,     3,     3,    73,   153,     3,    43,
      73,     0,    46,    92,   154,     3,     5,    23,    21,    22,
      42,    14,    21,    22,    37,    73,    21,     3,    39,     5,
      41,    24,     0,    46,    10,    91,    12,    13,    14,    39,
      18,    41,   196,    49,    65,    54,   195,   195,    18,    21,
       3,    21,   198,    20,     3,     7,    32,    33,   138,   109,
     190,     3,    54,    47,    50,    41,     3,   134,   135,   209,
     140,   138,   135,    49,    50,   138,     3,    53,     5,   158,
     159,   157,    47,   159,     5,    12,    13,    14,     3,   139,
       5,    12,    13,    14,    40,    10,   118,    12,    13,    14,
      47,    42,    47,    43,    39,    32,    33,    40,   130,    43,
      42,    32,    33,    41,    50,    39,    39,    32,    33,    48,
       3,    46,    39,    50,     7,    45,    41,    43,    41,    50,
      12,    50,   154,    51,   156,     3,     5,     5,    53,     7,
      45,    48,    25,    26,    27,    28,    29,    30,    31,    52,
       3,    45,    41,   203,     7,    38,    40,    25,    26,    27,
      28,    29,    30,    31,    38,    46,    36,    45,    48,    42,
       5,     5,    25,    26,    27,    28,    29,    30,    31,    51,
      51,    40,    44,    39,    51,    40,    40,   209,    51,     5,
      42,    40,    43,    43,    42,    39,   159,    44,    40,    45,
      45,    40,    40,     4,    65,    42,    12,   198,   146,   148,
     195,    24,    23,   135,    -1,    -1,   147
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  BisonParser::yystos_[] =
  {
         0,    18,    21,    56,    57,    58,    75,    76,     3,     3,
      59,     0,    75,    57,    20,   103,    39,    41,    39,    41,
     103,     3,    54,   104,   105,   106,   107,     3,    23,    49,
      79,    80,    91,    95,     3,    77,    78,    22,    58,    59,
      65,    66,    67,     7,    60,    61,    73,     3,   107,   104,
      47,    50,     3,    94,    47,    40,    79,    47,    42,    43,
      39,    47,    40,    66,    42,    43,    50,     5,    12,    13,
      14,    32,    33,    50,    74,    97,   101,   110,   111,   112,
     113,   106,   108,   109,   113,    92,    93,     3,    10,    41,
      49,    50,    53,    81,    82,    83,    86,    87,    88,    89,
      90,    96,    97,    98,    99,   100,   101,   102,    81,    39,
      77,    25,    26,    27,    28,    29,    30,    31,    38,    59,
      62,    63,    64,    70,    71,    73,    64,    68,    69,    74,
      39,    60,   108,   113,    48,    46,    45,    51,    43,    39,
      41,    50,    12,    81,    74,    45,    48,    37,    46,    52,
      45,    79,    59,    41,    40,    62,    38,    46,    48,    36,
      45,    22,    65,    51,    51,    97,   112,   108,    79,    77,
       3,    83,    84,    85,    96,    42,    51,    82,    87,    86,
      88,    40,    44,    70,    72,    65,    59,    64,    74,    69,
      39,    40,    40,    42,    51,    43,    43,     5,    43,    42,
      40,    44,    62,    39,    84,    88,    45,    72,     5,    40,
      79,    45,    65,    40,    40
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  BisonParser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   123,
     125,    91,    93,    44,    58,    59,    42,    61,    46,    64,
      40,    41,    43,   126,    37
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  BisonParser::yyr1_[] =
  {
         0,    55,    56,    56,    57,    57,    58,    58,    58,    58,
      59,    60,    60,    61,    62,    62,    63,    63,    64,    64,
      65,    66,    66,    67,    67,    68,    68,    69,    69,    70,
      70,    70,    70,    71,    71,    71,    71,    71,    71,    71,
      72,    72,    73,    74,    75,    75,    76,    77,    77,    78,
      79,    79,    80,    80,    80,    81,    82,    82,    82,    82,
      83,    84,    84,    85,    85,    85,    86,    86,    87,    87,
      88,    88,    88,    89,    89,    90,    90,    92,    91,    93,
      91,    94,    95,    96,    96,    96,    97,    98,    99,    99,
      99,   100,   101,   101,   101,   101,   101,   102,   103,   103,
     103,   103,   104,   104,   105,   106,   107,   108,   108,   109,
     109,   110,   110,   110,   111,   111,   112,   112,   113
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  BisonParser::yyr2_[] =
  {
         0,     2,     3,     2,     1,     2,     5,     8,     9,    12,
       1,     1,     3,     1,     1,     2,     5,     6,     1,     3,
       1,     1,     2,     4,     1,     3,     1,     1,     3,     1,
       1,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     4,     7,     2,     1,     3,     1,
       1,     2,     4,     4,     1,     1,     3,     1,     1,     1,
       4,     1,     3,     1,     1,     1,     1,     3,     1,     3,
       1,     5,     3,     1,     3,     1,     1,     0,     6,     0,
       9,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     2,     5,
       3,     6,     1,     2,     4,     1,     2,     1,     3,     1,
       1,     1,     1,     3,     1,     3,     1,     3,     1
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const BisonParser::yytname_[] =
  {
    "$end", "error", "$undefined", "NAME", "FUNNAME", "CONSNAME",
  "DESTNAME", "TYPEPARAMNAME", "IPNAME", "FUNCVARNAME", "BFNAME", "IFUNC",
  "NUMBER", "REALNUMBER", "STRING", "T_FUNCTIONAL_PROGRAM", "T_IMPORT",
  "T_LIBRARIES", "T_SCHEME", "T_INTERPRETATION", "T_APPLICATION", "T_DATA",
  "T_CONSTRUCTORS", "T_FUN", "T_FUNCTIONS", "T_TSTRING", "T_TINT",
  "T_TUINT", "T_TSIZE", "T_TFLOAT", "T_TDOUBLE", "T_TBOOL", "T_TRUE",
  "T_FALSE", "T_ARGET", "T_ID", "T_UNION", "T_FARROW", "T_TARROW", "'{'",
  "'}'", "'['", "']'", "','", "':'", "';'", "'*'", "'='", "'.'", "'@'",
  "'('", "')'", "'+'", "'~'", "'%'", "$accept", "FunctionalProgram",
  "DataTypeDefinitionsBlocks", "DataTypeDefinitionsBlock", "TypeName",
  "TypeParametersList", "TypeParameterDef", "ConstructorsDefinitionList",
  "ConstructorDef", "ConstructorParametersList", "TypesDefinitionList",
  "TypesDefinitionList2", "TypeDefinition", "TypeDefConstructor",
  "TypeExpression", "AtomType", "BaseType", "TypeExpressionsList",
  "TypeParameter", "ConstructorName", "Scheme", "SchemeBegin",
  "FormalParametersList", "FormalParameter", "DefinitionsList",
  "Definition", "Term", "AtomTerm", "FuncObjectWithParameters",
  "FuncArgumentList", "FuncParameterName", "SequentialTerm",
  "CompositionTerm", "ConditionTerm", "VariantTerm", "FuncObjectName",
  "ConstructionFun", "$@1", "$@2", "ConstructionFunName", "FuncVarName",
  "ElementaryFunctionName", "Constructor", "Destructor", "BuiltInFunction",
  "TupleElement", "Constant", "BuiltInFunctionName", "Application",
  "DataInit", "OneDataInit", "DataName", "InterpFunProgramName", "Data",
  "OneData", "ValueAtom", "ValueConstructor", "ValueComposition", "Value", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const BisonParser::rhs_number_type
  BisonParser::yyrhs_[] =
  {
        56,     0,    -1,    57,    75,   103,    -1,    75,   103,    -1,
      58,    -1,    58,    57,    -1,    21,    59,    39,    65,    40,
      -1,    21,    59,    41,    60,    42,    39,    65,    40,    -1,
      21,    59,    39,    22,    39,    62,    40,    65,    40,    -1,
      21,    59,    41,    60,    42,    39,    22,    39,    62,    40,
      65,    40,    -1,     3,    -1,    61,    -1,    61,    43,    60,
      -1,    73,    -1,    63,    -1,    63,    62,    -1,    38,    59,
      44,     5,    45,    -1,    64,    38,    59,    44,     5,    45,
      -1,    70,    -1,    70,    46,    64,    -1,    66,    -1,    67,
      -1,    67,    66,    -1,    59,    47,    69,    45,    -1,    58,
      -1,    64,    48,    74,    -1,    74,    -1,    68,    -1,    68,
      36,    69,    -1,    71,    -1,    59,    -1,    59,    41,    72,
      42,    -1,    73,    -1,    25,    -1,    26,    -1,    27,    -1,
      28,    -1,    29,    -1,    30,    -1,    31,    -1,    70,    -1,
      70,    43,    72,    -1,     7,    -1,     5,    -1,    76,    39,
      79,    40,    -1,    76,    41,    77,    42,    39,    79,    40,
      -1,    18,     3,    -1,    78,    -1,    78,    43,    77,    -1,
       3,    -1,    80,    -1,    80,    79,    -1,    49,    47,    81,
      45,    -1,    95,    47,    81,    45,    -1,    91,    -1,    89,
      -1,    50,    81,    51,    -1,    96,    -1,    90,    -1,    49,
      -1,     3,    50,    84,    51,    -1,    85,    -1,    85,    43,
      84,    -1,     3,    -1,    96,    -1,    83,    -1,    82,    -1,
      86,    48,    82,    -1,    86,    -1,    87,    46,    86,    -1,
      87,    -1,    87,    37,    87,    43,    88,    -1,    87,    37,
      87,    -1,    88,    -1,    89,    52,    88,    -1,     3,    -1,
      83,    -1,    -1,    23,    94,    92,    39,    79,    40,    -1,
      -1,    23,    94,    93,    41,    77,    42,    39,    79,    40,
      -1,     3,    -1,     3,    -1,    99,    -1,    97,    -1,    98,
      -1,    74,    -1,    53,    74,    -1,   102,    -1,   100,    -1,
     101,    -1,    41,    12,    42,    -1,    12,    -1,    13,    -1,
      14,    -1,    32,    -1,    33,    -1,    10,    -1,    20,   107,
      -1,    20,   107,    50,   108,    51,    -1,    20,   104,   107,
      -1,    20,   104,   107,    50,   108,    51,    -1,   105,    -1,
     105,   104,    -1,   106,    47,   113,    45,    -1,     3,    -1,
      54,     3,    -1,   109,    -1,   109,    43,   108,    -1,   106,
      -1,   113,    -1,   101,    -1,    97,    -1,    50,   113,    51,
      -1,   110,    -1,   110,    48,    97,    -1,   111,    -1,   111,
      46,   112,    -1,   112,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  BisonParser::yyprhs_[] =
  {
         0,     0,     3,     7,    10,    12,    15,    21,    30,    40,
      53,    55,    57,    61,    63,    65,    68,    74,    81,    83,
      87,    89,    91,    94,    99,   101,   105,   107,   109,   113,
     115,   117,   122,   124,   126,   128,   130,   132,   134,   136,
     138,   140,   144,   146,   148,   153,   161,   164,   166,   170,
     172,   174,   177,   182,   187,   189,   191,   195,   197,   199,
     201,   206,   208,   212,   214,   216,   218,   220,   224,   226,
     230,   232,   238,   242,   244,   248,   250,   252,   253,   260,
     261,   271,   273,   275,   277,   279,   281,   283,   286,   288,
     290,   292,   296,   298,   300,   302,   304,   306,   308,   311,
     317,   321,   328,   330,   333,   338,   340,   343,   345,   349,
     351,   353,   355,   357,   361,   363,   367,   369,   373
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  BisonParser::yyrline_[] =
  {
         0,   178,   178,   185,   195,   200,   207,   211,   215,   219,
     226,   230,   235,   242,   249,   254,   261,   265,   271,   276,
     284,   297,   302,   309,   313,   322,   326,   333,   334,   342,
     346,   350,   354,   361,   362,   363,   364,   365,   366,   367,
     371,   376,   382,   384,   389,   394,   402,   410,   415,   422,
     429,   434,   441,   445,   449,   454,   458,   460,   461,   463,
     470,   476,   481,   488,   492,   493,   498,   499,   506,   507,
     514,   515,   519,   526,   527,   534,   538,   543,   542,   552,
     551,   563,   567,   571,   572,   574,   579,   586,   593,   595,
     596,   600,   616,   617,   618,   619,   623,   631,   638,   642,
     646,   650,   657,   662,   669,   675,   678,   685,   689,   696,
     700,   705,   706,   708,   715,   716,   723,   724,   730
  };

  // Print the state stack on the debug stream.
  void
  BisonParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  BisonParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  BisonParser::token_number_type
  BisonParser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    54,     2,     2,
      50,    51,    46,    52,    43,     2,    48,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    44,    45,
       2,    47,     2,     2,    49,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    41,     2,    42,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,    40,    53,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int BisonParser::yyeof_ = 0;
  const int BisonParser::yylast_ = 236;
  const int BisonParser::yynnts_ = 59;
  const int BisonParser::yyempty_ = -2;
  const int BisonParser::yyfinal_ = 11;
  const int BisonParser::yyterror_ = 1;
  const int BisonParser::yyerrcode_ = 256;
  const int BisonParser::yyntokens_ = 55;

  const unsigned int BisonParser::yyuser_token_number_max_ = 293;
  const BisonParser::token_number_type BisonParser::yyundef_token_ = 2;


/* Line 1054 of lalr1.cc  */
#line 2 "e:\\FPTL1\\Src\\Interpreter\\Parser\\parser.yy"
} } // FPTL::Parser

/* Line 1054 of lalr1.cc  */
#line 2501 "parser.tab.cc"


