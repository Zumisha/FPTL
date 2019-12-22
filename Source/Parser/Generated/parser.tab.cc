// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "parser.tab.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.tab.hh"

// User implementation prologue.

#line 51 "parser.tab.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 55 "parser.yy" // lalr1.cc:413

#include "../Support.h"
#include "../FlexTokenizer.h"
#include "../Nodes.h"

#line 59 "parser.tab.cc" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif



// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 2 "parser.yy" // lalr1.cc:479
namespace FPTL { namespace Parser {
#line 126 "parser.tab.cc" // lalr1.cc:479

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
              // Fall through.
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
  {}

  BisonParser::~BisonParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  BisonParser::syntax_error::syntax_error (const std::string& m)
    : std::runtime_error (m)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  BisonParser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  BisonParser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
  {
    value = other.value;
  }


  template <typename Base>
  inline
  BisonParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v)
    : Base (t)
    , value (v)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  BisonParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  inline
  BisonParser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  BisonParser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  BisonParser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  BisonParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
  }

  // by_type.
  inline
  BisonParser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  BisonParser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  BisonParser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  BisonParser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  BisonParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  BisonParser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  BisonParser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  BisonParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  BisonParser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  BisonParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  BisonParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  BisonParser::symbol_number_type
  BisonParser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  BisonParser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  BisonParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  BisonParser::stack_symbol_type&
  BisonParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }


  template <typename Base>
  inline
  void
  BisonParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
            case 12: // NUMBER

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 379 "parser.tab.cc" // lalr1.cc:614
        break;

      case 13: // REALNUMBER

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 390 "parser.tab.cc" // lalr1.cc:614
        break;

      case 14: // STRING

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 401 "parser.tab.cc" // lalr1.cc:614
        break;

      case 56: // FunctionalProgram

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 412 "parser.tab.cc" // lalr1.cc:614
        break;

      case 57: // DataTypeDefinitionsBlocks

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 423 "parser.tab.cc" // lalr1.cc:614
        break;

      case 58: // DataTypeDefinitionsBlock

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 434 "parser.tab.cc" // lalr1.cc:614
        break;

      case 60: // TypeParametersList

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 445 "parser.tab.cc" // lalr1.cc:614
        break;

      case 61: // TypeParameterDef

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 456 "parser.tab.cc" // lalr1.cc:614
        break;

      case 62: // ConstructorsDefinitionList

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 467 "parser.tab.cc" // lalr1.cc:614
        break;

      case 63: // ConstructorDef

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 478 "parser.tab.cc" // lalr1.cc:614
        break;

      case 64: // ConstructorParametersList

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 489 "parser.tab.cc" // lalr1.cc:614
        break;

      case 65: // TypesDefinitionList

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 500 "parser.tab.cc" // lalr1.cc:614
        break;

      case 66: // TypesDefinitionList2

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 511 "parser.tab.cc" // lalr1.cc:614
        break;

      case 67: // TypeDefinition

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 522 "parser.tab.cc" // lalr1.cc:614
        break;

      case 68: // TypeDefConstructor

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 533 "parser.tab.cc" // lalr1.cc:614
        break;

      case 69: // TypeExpression

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 544 "parser.tab.cc" // lalr1.cc:614
        break;

      case 70: // AtomType

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 555 "parser.tab.cc" // lalr1.cc:614
        break;

      case 72: // TypeExpressionsList

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 566 "parser.tab.cc" // lalr1.cc:614
        break;

      case 75: // Scheme

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scFun);
	delete node;

}
#line 577 "parser.tab.cc" // lalr1.cc:614
        break;

      case 77: // FormalParametersList

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 588 "parser.tab.cc" // lalr1.cc:614
        break;

      case 78: // FormalParameter

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 599 "parser.tab.cc" // lalr1.cc:614
        break;

      case 79: // DefinitionsList

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 610 "parser.tab.cc" // lalr1.cc:614
        break;

      case 80: // Definition

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 621 "parser.tab.cc" // lalr1.cc:614
        break;

      case 81: // Term

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 632 "parser.tab.cc" // lalr1.cc:614
        break;

      case 82: // AtomTerm

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 643 "parser.tab.cc" // lalr1.cc:614
        break;

      case 83: // FuncObjectWithParameters

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 654 "parser.tab.cc" // lalr1.cc:614
        break;

      case 84: // FuncArgumentList

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 665 "parser.tab.cc" // lalr1.cc:614
        break;

      case 85: // FuncParameterName

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 676 "parser.tab.cc" // lalr1.cc:614
        break;

      case 86: // SequentialTerm

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 687 "parser.tab.cc" // lalr1.cc:614
        break;

      case 87: // CompositionTerm

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 698 "parser.tab.cc" // lalr1.cc:614
        break;

      case 88: // ConditionTerm

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 709 "parser.tab.cc" // lalr1.cc:614
        break;

      case 89: // VariantTerm

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 720 "parser.tab.cc" // lalr1.cc:614
        break;

      case 90: // FuncObjectName

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 731 "parser.tab.cc" // lalr1.cc:614
        break;

      case 91: // ConstructionFun

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scFun);
	delete node;

}
#line 742 "parser.tab.cc" // lalr1.cc:614
        break;

      case 96: // ElementaryFunctionName

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 753 "parser.tab.cc" // lalr1.cc:614
        break;

      case 97: // Constructor

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 764 "parser.tab.cc" // lalr1.cc:614
        break;

      case 98: // Destructor

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 775 "parser.tab.cc" // lalr1.cc:614
        break;

      case 99: // BuiltInFunction

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 786 "parser.tab.cc" // lalr1.cc:614
        break;

      case 100: // TupleElement

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 797 "parser.tab.cc" // lalr1.cc:614
        break;

      case 101: // Constant

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 808 "parser.tab.cc" // lalr1.cc:614
        break;

      case 102: // BuiltInFunctionName

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 819 "parser.tab.cc" // lalr1.cc:614
        break;

      case 103: // Application

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scApp);
	delete node;

}
#line 830 "parser.tab.cc" // lalr1.cc:614
        break;

      case 104: // DataInit

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 841 "parser.tab.cc" // lalr1.cc:614
        break;

      case 105: // OneDataInit

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 852 "parser.tab.cc" // lalr1.cc:614
        break;

      case 107: // InterpFunProgramName

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 863 "parser.tab.cc" // lalr1.cc:614
        break;

      case 108: // Data

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 874 "parser.tab.cc" // lalr1.cc:614
        break;

      case 109: // OneData

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 885 "parser.tab.cc" // lalr1.cc:614
        break;

      case 110: // ValueAtom

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 896 "parser.tab.cc" // lalr1.cc:614
        break;

      case 111: // ValueConstructor

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 907 "parser.tab.cc" // lalr1.cc:614
        break;

      case 112: // ValueComposition

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 918 "parser.tab.cc" // lalr1.cc:614
        break;

      case 113: // Value

#line 62 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 929 "parser.tab.cc" // lalr1.cc:614
        break;


      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  BisonParser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  BisonParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  BisonParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  BisonParser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
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
#endif // YYDEBUG

  inline BisonParser::state_type
  BisonParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  BisonParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  BisonParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  BisonParser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, pSupport, aTokenizer));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 185 "parser.yy" // lalr1.cc:859
    {
			mASTRoot = new FunctionalProgram( (yystack_[2].value.scList), (yystack_[1].value.scFun), (yystack_[0].value.scApp) );
			(yystack_[2].value.scList)->mParent = mASTRoot;
			(yystack_[1].value.scFun)->mParent = mASTRoot;
			(yystack_[0].value.scApp)->mParent = mASTRoot;
			
			// Возвращаем 0, иначе все дерево будет "срублено" деструктором парсера.
			(yylhs.value.scNode) = 0;
		}
#line 1167 "parser.tab.cc" // lalr1.cc:859
    break;

  case 3:
#line 195 "parser.yy" // lalr1.cc:859
    {
			mASTRoot = new FunctionalProgram( 0, (yystack_[1].value.scFun), (yystack_[0].value.scApp) );
			(yystack_[1].value.scFun)->mParent = mASTRoot;
			(yystack_[0].value.scApp)->mParent = mASTRoot;
			(yylhs.value.scNode) = 0;
		}
#line 1178 "parser.tab.cc" // lalr1.cc:859
    break;

  case 4:
#line 207 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode(  ASTNode::DataTypeDefinitionsBlocks );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scList);
		}
#line 1188 "parser.tab.cc" // lalr1.cc:859
    break;

  case 5:
#line 213 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scNode) );
			(yystack_[1].value.scNode)->mParent = (yystack_[0].value.scList);
		}
#line 1197 "parser.tab.cc" // lalr1.cc:859
    break;

  case 6:
#line 221 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[3].value.scIdent), (yystack_[1].value.scList), 0, 0 );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scNode);
		}
#line 1206 "parser.tab.cc" // lalr1.cc:859
    break;

  case 7:
#line 226 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[6].value.scIdent), (yystack_[1].value.scList), (yystack_[4].value.scList), 0 );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scNode);
			(yystack_[4].value.scList)->mParent = (yylhs.value.scNode);
		}
#line 1216 "parser.tab.cc" // lalr1.cc:859
    break;

  case 8:
#line 232 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[7].value.scIdent), (yystack_[1].value.scList), 0, (yystack_[3].value.scList) );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scNode);
			(yystack_[3].value.scList)->mParent = (yylhs.value.scNode);
		}
#line 1226 "parser.tab.cc" // lalr1.cc:859
    break;

  case 9:
#line 238 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[10].value.scIdent), (yystack_[1].value.scList), (yystack_[8].value.scList), (yystack_[3].value.scList) );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scNode);
			(yystack_[8].value.scList)->mParent = (yylhs.value.scNode);
			(yystack_[3].value.scList)->mParent = (yylhs.value.scNode);
		}
#line 1237 "parser.tab.cc" // lalr1.cc:859
    break;

  case 11:
#line 252 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::TypeParametersList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
			(yystack_[0].value.scDef)->mParent = (yylhs.value.scList);
		}
#line 1247 "parser.tab.cc" // lalr1.cc:859
    break;

  case 12:
#line 258 "parser.yy" // lalr1.cc:859
    {		
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scDef) );
			(yystack_[2].value.scDef)->mParent = (yystack_[0].value.scList);
		}
#line 1256 "parser.tab.cc" // lalr1.cc:859
    break;

  case 13:
#line 266 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::TypeParameterDefinition, (yystack_[0].value.scIdent), 0 );
		}
#line 1264 "parser.tab.cc" // lalr1.cc:859
    break;

  case 14:
#line 273 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::ConstructorsDefinitionList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scList);
		}
#line 1274 "parser.tab.cc" // lalr1.cc:859
    break;

  case 15:
#line 279 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scNode) );
			(yystack_[1].value.scNode)->mParent = (yystack_[0].value.scList);
		}
#line 1283 "parser.tab.cc" // lalr1.cc:859
    break;

  case 16:
#line 287 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConstructorNode( (yystack_[1].value.scIdent), 0, (yystack_[3].value.scIdent) );
		}
#line 1291 "parser.tab.cc" // lalr1.cc:859
    break;

  case 17:
#line 291 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConstructorNode( (yystack_[1].value.scIdent), (yystack_[5].value.scList), (yystack_[3].value.scIdent) );
			(yystack_[5].value.scList)->mParent = (yylhs.value.scNode);
		}
#line 1300 "parser.tab.cc" // lalr1.cc:859
    break;

  case 18:
#line 298 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::ConstructorParametersList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scName) );
			(yystack_[0].value.scName)->mParent = (yylhs.value.scList);
		}
#line 1310 "parser.tab.cc" // lalr1.cc:859
    break;

  case 19:
#line 304 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scName) );
			(yystack_[2].value.scName)->mParent = (yystack_[0].value.scList);
		}
#line 1319 "parser.tab.cc" // lalr1.cc:859
    break;

  case 20:
#line 313 "parser.yy" // lalr1.cc:859
    {
			if( (yystack_[0].value.scList)->mChilds.size() > 1 )
			{
				for(ASTNode* child : (yystack_[0].value.scList)->mChilds)
					pSupport->semanticError( ParserErrTypes::MultipleTypeExpression, static_cast<DefinitionNode*>(child)->getDefinitionName() );
			}

			(yylhs.value.scList) = (yystack_[0].value.scList);
		}
#line 1333 "parser.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 326 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::TypesDefinitionList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
			(yystack_[0].value.scDef)->mParent = (yylhs.value.scList);
		}
#line 1343 "parser.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 332 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scDef) );
			(yystack_[1].value.scDef)->mParent = (yystack_[0].value.scList);
		}
#line 1352 "parser.tab.cc" // lalr1.cc:859
    break;

  case 23:
#line 340 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::TypeDefinition, (yystack_[3].value.scIdent), (yystack_[1].value.scNode) );
			(yystack_[1].value.scNode)->mParent = (yylhs.value.scDef);
		}
#line 1361 "parser.tab.cc" // lalr1.cc:859
    break;

  case 24:
#line 345 "parser.yy" // lalr1.cc:859
    {
			pSupport->semanticError( ParserErrTypes::NestedDataDefinition, static_cast<DataNode*>((yystack_[0].value.scNode))->getDataName() );
			delete (yystack_[0].value.scNode);
			(yylhs.value.scDef) = 0;
		}
#line 1371 "parser.tab.cc" // lalr1.cc:859
    break;

  case 25:
#line 354 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::TypeConstructorDefinition, (yystack_[0].value.scIdent), (yystack_[2].value.scList) );
			(yystack_[2].value.scList)->mParent = (yylhs.value.scNode);
		}
#line 1380 "parser.tab.cc" // lalr1.cc:859
    break;

  case 26:
#line 359 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::TypeConstructorDefinition, (yystack_[0].value.scIdent), 0 );
		}
#line 1388 "parser.tab.cc" // lalr1.cc:859
    break;

  case 28:
#line 367 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::TypeExpression, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1398 "parser.tab.cc" // lalr1.cc:859
    break;

  case 29:
#line 377 "parser.yy" // lalr1.cc:859
    {	
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scToken), NameRefNode::BaseType, nullptr );
		}
#line 1406 "parser.tab.cc" // lalr1.cc:859
    break;

  case 30:
#line 381 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::Type, nullptr );
		}
#line 1414 "parser.tab.cc" // lalr1.cc:859
    break;

  case 31:
#line 385 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[3].value.scIdent), NameRefNode::Template, (yystack_[1].value.scList) );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scName);
		}
#line 1423 "parser.tab.cc" // lalr1.cc:859
    break;

  case 32:
#line 390 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::TypeParamName, nullptr );
		}
#line 1431 "parser.tab.cc" // lalr1.cc:859
    break;

  case 40:
#line 407 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::TypeExpressionsList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scName) );
			(yystack_[0].value.scName)->mParent = (yylhs.value.scList);
		}
#line 1441 "parser.tab.cc" // lalr1.cc:859
    break;

  case 41:
#line 413 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scName) );
			(yystack_[2].value.scName)->mParent = (yystack_[0].value.scList);
		}
#line 1450 "parser.tab.cc" // lalr1.cc:859
    break;

  case 44:
#line 427 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[3].value.scIdent), (yystack_[1].value.scList), 0 );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scFun);
			pSupport->popIdent();
		}
#line 1460 "parser.tab.cc" // lalr1.cc:859
    break;

  case 45:
#line 433 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[6].value.scIdent), (yystack_[1].value.scList), (yystack_[4].value.scList) );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scFun);
			(yystack_[4].value.scList)->mParent = (yylhs.value.scFun);
			pSupport->popIdent();
		}
#line 1471 "parser.tab.cc" // lalr1.cc:859
    break;

  case 46:
#line 443 "parser.yy" // lalr1.cc:859
    {
			pSupport->pushIdent( (yystack_[0].value.scIdent) );
			(yylhs.value.scIdent) = (yystack_[0].value.scIdent);
		}
#line 1480 "parser.tab.cc" // lalr1.cc:859
    break;

  case 47:
#line 451 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::FormalParametersList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
			(yystack_[0].value.scDef)->mParent = (yylhs.value.scList);
		}
#line 1490 "parser.tab.cc" // lalr1.cc:859
    break;

  case 48:
#line 457 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scDef) );
			(yystack_[2].value.scDef)->mParent = (yystack_[0].value.scList);
		}
#line 1499 "parser.tab.cc" // lalr1.cc:859
    break;

  case 49:
#line 465 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::FunctionParameterDefinition, (yystack_[0].value.scIdent), 0 );
		}
#line 1507 "parser.tab.cc" // lalr1.cc:859
    break;

  case 50:
#line 472 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::DefinitionsList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scList);
		}
#line 1517 "parser.tab.cc" // lalr1.cc:859
    break;

  case 51:
#line 478 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scNode) );
			(yystack_[1].value.scNode)->mParent = (yystack_[0].value.scList);
		}
#line 1526 "parser.tab.cc" // lalr1.cc:859
    break;

  case 52:
#line 486 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::Definition, pSupport->getTopIdent(), (yystack_[1].value.scNode) );
			(yystack_[1].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1535 "parser.tab.cc" // lalr1.cc:859
    break;

  case 53:
#line 491 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::Definition, (yystack_[3].value.scIdent), (yystack_[1].value.scNode) );
			(yystack_[1].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1544 "parser.tab.cc" // lalr1.cc:859
    break;

  case 54:
#line 496 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scFun); }
#line 1550 "parser.tab.cc" // lalr1.cc:859
    break;

  case 56:
#line 505 "parser.yy" // lalr1.cc:859
    {	(yylhs.value.scNode) = (yystack_[1].value.scNode); }
#line 1556 "parser.tab.cc" // lalr1.cc:859
    break;

  case 58:
#line 508 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1562 "parser.tab.cc" // lalr1.cc:859
    break;

  case 59:
#line 510 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new NameRefNode( pSupport->getTopIdent(), ASTNode::FuncObjectName, nullptr );
		}
#line 1570 "parser.tab.cc" // lalr1.cc:859
    break;

  case 60:
#line 517 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[3].value.scIdent), NameRefNode::FuncObjectWithParameters, (yystack_[1].value.scList) );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scName);
		}
#line 1579 "parser.tab.cc" // lalr1.cc:859
    break;

  case 61:
#line 524 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::FuncArgumentsList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scList);
		}
#line 1589 "parser.tab.cc" // lalr1.cc:859
    break;

  case 62:
#line 530 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scNode) );
			(yystack_[2].value.scNode)->mParent = (yystack_[0].value.scList);
		}
#line 1598 "parser.tab.cc" // lalr1.cc:859
    break;

  case 63:
#line 538 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::FuncParameterName, nullptr );
		}
#line 1606 "parser.tab.cc" // lalr1.cc:859
    break;

  case 65:
#line 543 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1612 "parser.tab.cc" // lalr1.cc:859
    break;

  case 67:
#line 549 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::SequentialTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1622 "parser.tab.cc" // lalr1.cc:859
    break;

  case 69:
#line 559 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::CompositionTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1632 "parser.tab.cc" // lalr1.cc:859
    break;

  case 71:
#line 569 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConditionNode( ASTNode::ConditionTerm, (yystack_[4].value.scNode), (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
			(yystack_[4].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1643 "parser.tab.cc" // lalr1.cc:859
    break;

  case 72:
#line 576 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConditionNode( ASTNode::ConditionTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode), nullptr );
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1653 "parser.tab.cc" // lalr1.cc:859
    break;

  case 74:
#line 586 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::VariantTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1663 "parser.tab.cc" // lalr1.cc:859
    break;

  case 75:
#line 595 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::FuncObjectName, nullptr );
		}
#line 1671 "parser.tab.cc" // lalr1.cc:859
    break;

  case 77:
#line 603 "parser.yy" // lalr1.cc:859
    {
			pSupport->pushIdent( (yystack_[0].value.scIdent) );
		}
#line 1679 "parser.tab.cc" // lalr1.cc:859
    break;

  case 78:
#line 607 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[4].value.scIdent), (yystack_[1].value.scList), 0 );
			pSupport->popIdent();
			(yystack_[1].value.scList)->mParent = (yylhs.value.scFun);
		}
#line 1689 "parser.tab.cc" // lalr1.cc:859
    break;

  case 79:
#line 613 "parser.yy" // lalr1.cc:859
    {
			pSupport->pushIdent( (yystack_[0].value.scIdent) );
		}
#line 1697 "parser.tab.cc" // lalr1.cc:859
    break;

  case 80:
#line 617 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[7].value.scIdent), (yystack_[1].value.scList), (yystack_[4].value.scList) );
			pSupport->popIdent();
			(yystack_[1].value.scList)->mParent = (yylhs.value.scFun);
			(yystack_[4].value.scList)->mParent = (yylhs.value.scFun);
		}
#line 1708 "parser.tab.cc" // lalr1.cc:859
    break;

  case 84:
#line 636 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1714 "parser.tab.cc" // lalr1.cc:859
    break;

  case 85:
#line 638 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1720 "parser.tab.cc" // lalr1.cc:859
    break;

  case 86:
#line 643 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::ConstructorName, nullptr );
		}
#line 1728 "parser.tab.cc" // lalr1.cc:859
    break;

  case 87:
#line 650 "parser.yy" // lalr1.cc:859
    {	
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::DestructorName, nullptr );
		}
#line 1736 "parser.tab.cc" // lalr1.cc:859
    break;

  case 88:
#line 657 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1742 "parser.tab.cc" // lalr1.cc:859
    break;

  case 91:
#line 664 "parser.yy" // lalr1.cc:859
    {
		ConstantNode * number = static_cast<ConstantNode*>( (yystack_[1].value.scNode) );
		(yylhs.value.scNode) = new ConstantNode( ASTNode::TupleElemNumber, number->getConstant() );
		delete number;
	}
#line 1752 "parser.tab.cc" // lalr1.cc:859
    break;

  case 95:
#line 675 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConstantNode( ASTNode::TrueValue, (yystack_[0].value.scToken) );
		}
#line 1760 "parser.tab.cc" // lalr1.cc:859
    break;

  case 96:
#line 679 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConstantNode( ASTNode::FalseValue, (yystack_[0].value.scToken) );
		}
#line 1768 "parser.tab.cc" // lalr1.cc:859
    break;

  case 97:
#line 687 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::BuildInFunction, nullptr );
		}
#line 1776 "parser.tab.cc" // lalr1.cc:859
    break;

  case 98:
#line 694 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[0].value.scName), 0, 0 );
			(yystack_[0].value.scName)->mParent = (yylhs.value.scApp);
		}
#line 1785 "parser.tab.cc" // lalr1.cc:859
    break;

  case 99:
#line 699 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[3].value.scName), (yystack_[1].value.scNode), 0 );
			(yystack_[3].value.scName)->mParent = (yylhs.value.scApp);
			(yystack_[1].value.scNode)->mParent = (yylhs.value.scApp);
		}
#line 1795 "parser.tab.cc" // lalr1.cc:859
    break;

  case 100:
#line 705 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[0].value.scName), 0, (yystack_[1].value.scList) ); 
			(yystack_[0].value.scName)->mParent = (yylhs.value.scApp);
			(yystack_[1].value.scList)->mParent = (yylhs.value.scApp);
		}
#line 1805 "parser.tab.cc" // lalr1.cc:859
    break;

  case 101:
#line 711 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[3].value.scName), (yystack_[1].value.scNode), (yystack_[4].value.scList) );
			(yystack_[3].value.scName)->mParent = (yylhs.value.scApp);
			(yystack_[1].value.scNode)->mParent = (yylhs.value.scApp);
			(yystack_[4].value.scList)->mParent = (yylhs.value.scApp);
		}
#line 1816 "parser.tab.cc" // lalr1.cc:859
    break;

  case 102:
#line 721 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::InputVarDefinitionList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
			(yystack_[0].value.scDef)->mParent = (yylhs.value.scList);
		}
#line 1826 "parser.tab.cc" // lalr1.cc:859
    break;

  case 103:
#line 727 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scDef) );
			(yystack_[1].value.scDef)->mParent = (yystack_[0].value.scList);
		}
#line 1835 "parser.tab.cc" // lalr1.cc:859
    break;

  case 104:
#line 735 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::InputVarDefinition, (yystack_[3].value.scIdent), (yystack_[1].value.scNode) );
			(yystack_[1].value.scNode)->mParent = (yylhs.value.scDef);
		}
#line 1844 "parser.tab.cc" // lalr1.cc:859
    break;

  case 106:
#line 745 "parser.yy" // lalr1.cc:859
    { 
			(yylhs.value.scName) = new NameRefNode((yystack_[0].value.scIdent), ASTNode::RunningSchemeName, nullptr );
		}
#line 1852 "parser.tab.cc" // lalr1.cc:859
    break;

  case 107:
#line 752 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = (yystack_[0].value.scNode);
		}
#line 1860 "parser.tab.cc" // lalr1.cc:859
    break;

  case 108:
#line 756 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode(ASTNode::InputVarList, (yystack_[2].value.scNode), (yystack_[0].value.scNode));
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1870 "parser.tab.cc" // lalr1.cc:859
    break;

  case 109:
#line 765 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new NameRefNode( (yystack_[0].value.scIdent), ASTNode::InputVarName, nullptr );
		}
#line 1878 "parser.tab.cc" // lalr1.cc:859
    break;

  case 112:
#line 775 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1884 "parser.tab.cc" // lalr1.cc:859
    break;

  case 113:
#line 777 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = (yystack_[1].value.scNode);
		}
#line 1892 "parser.tab.cc" // lalr1.cc:859
    break;

  case 115:
#line 785 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ValueConstructor, (yystack_[2].value.scNode), (yystack_[0].value.scName) );
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scName)->mParent = (yylhs.value.scNode);
		}
#line 1902 "parser.tab.cc" // lalr1.cc:859
    break;

  case 117:
#line 795 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ValueComposition, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1912 "parser.tab.cc" // lalr1.cc:859
    break;


#line 1916 "parser.tab.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state, yyla));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
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
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  BisonParser::error (const syntax_error& yyexc)
  {
    error (yyexc.what());
  }

  // Generate an error message.
  std::string
  BisonParser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short int BisonParser::yypact_ninf_ = -135;

  const signed char BisonParser::yytable_ninf_ = -80;

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



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
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
  "OneData", "ValueAtom", "ValueConstructor", "ValueComposition", "Value", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  BisonParser::yyrline_[] =
  {
       0,   184,   184,   194,   206,   212,   220,   225,   231,   237,
     247,   251,   257,   265,   272,   278,   286,   290,   297,   303,
     312,   325,   331,   339,   344,   353,   358,   365,   366,   376,
     380,   384,   389,   396,   397,   398,   399,   400,   401,   402,
     406,   412,   419,   421,   426,   432,   442,   450,   456,   464,
     471,   477,   485,   490,   495,   500,   504,   506,   507,   509,
     516,   523,   529,   537,   541,   542,   547,   548,   557,   558,
     567,   568,   575,   584,   585,   594,   598,   603,   602,   613,
     612,   626,   630,   634,   635,   637,   642,   649,   656,   658,
     659,   663,   671,   672,   673,   674,   678,   686,   693,   698,
     704,   710,   720,   726,   734,   741,   744,   751,   755,   764,
     768,   773,   774,   776,   783,   784,   793,   794,   802
  };

  // Print the state stack on the debug stream.
  void
  BisonParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  BisonParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
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
    const unsigned int user_token_number_max_ = 293;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 2 "parser.yy" // lalr1.cc:1167
} } // FPTL::Parser
#line 2498 "parser.tab.cc" // lalr1.cc:1167
