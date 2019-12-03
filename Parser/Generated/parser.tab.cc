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
#line 49 "parser.yy" // lalr1.cc:413

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

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 341 "parser.tab.cc" // lalr1.cc:614
        break;

      case 13: // REALNUMBER

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 352 "parser.tab.cc" // lalr1.cc:614
        break;

      case 14: // STRING

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 363 "parser.tab.cc" // lalr1.cc:614
        break;

      case 56: // FunctionalProgram

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 374 "parser.tab.cc" // lalr1.cc:614
        break;

      case 57: // DataTypeDefinitionsBlocks

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 385 "parser.tab.cc" // lalr1.cc:614
        break;

      case 58: // DataTypeDefinitionsBlock

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 396 "parser.tab.cc" // lalr1.cc:614
        break;

      case 60: // TypeParametersList

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 407 "parser.tab.cc" // lalr1.cc:614
        break;

      case 61: // TypeParameterDef

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 418 "parser.tab.cc" // lalr1.cc:614
        break;

      case 62: // ConstructorsDefinitionList

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 429 "parser.tab.cc" // lalr1.cc:614
        break;

      case 63: // ConstructorDef

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 440 "parser.tab.cc" // lalr1.cc:614
        break;

      case 64: // ConstructorParametersList

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 451 "parser.tab.cc" // lalr1.cc:614
        break;

      case 65: // TypesDefinitionList

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 462 "parser.tab.cc" // lalr1.cc:614
        break;

      case 66: // TypesDefinitionList2

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 473 "parser.tab.cc" // lalr1.cc:614
        break;

      case 67: // TypeDefinition

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 484 "parser.tab.cc" // lalr1.cc:614
        break;

      case 68: // TypeDefConstructor

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 495 "parser.tab.cc" // lalr1.cc:614
        break;

      case 69: // TypeExpression

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 506 "parser.tab.cc" // lalr1.cc:614
        break;

      case 70: // AtomType

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 517 "parser.tab.cc" // lalr1.cc:614
        break;

      case 72: // TypeExpressionsList

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 528 "parser.tab.cc" // lalr1.cc:614
        break;

      case 75: // Scheme

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scFun);
	delete node;

}
#line 539 "parser.tab.cc" // lalr1.cc:614
        break;

      case 77: // FormalParametersList

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 550 "parser.tab.cc" // lalr1.cc:614
        break;

      case 78: // FormalParameter

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 561 "parser.tab.cc" // lalr1.cc:614
        break;

      case 79: // DefinitionsList

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 572 "parser.tab.cc" // lalr1.cc:614
        break;

      case 80: // Definition

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 583 "parser.tab.cc" // lalr1.cc:614
        break;

      case 81: // Term

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 594 "parser.tab.cc" // lalr1.cc:614
        break;

      case 82: // AtomTerm

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 605 "parser.tab.cc" // lalr1.cc:614
        break;

      case 83: // FuncObjectWithParameters

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 616 "parser.tab.cc" // lalr1.cc:614
        break;

      case 84: // FuncArgumentList

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 627 "parser.tab.cc" // lalr1.cc:614
        break;

      case 85: // FuncParameterName

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 638 "parser.tab.cc" // lalr1.cc:614
        break;

      case 86: // SequentialTerm

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 649 "parser.tab.cc" // lalr1.cc:614
        break;

      case 87: // CompositionTerm

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 660 "parser.tab.cc" // lalr1.cc:614
        break;

      case 88: // ConditionTerm

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 671 "parser.tab.cc" // lalr1.cc:614
        break;

      case 89: // VariantTerm

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 682 "parser.tab.cc" // lalr1.cc:614
        break;

      case 90: // FuncObjectName

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 693 "parser.tab.cc" // lalr1.cc:614
        break;

      case 91: // ConstructionFun

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scFun);
	delete node;

}
#line 704 "parser.tab.cc" // lalr1.cc:614
        break;

      case 96: // ElementaryFunctionName

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 715 "parser.tab.cc" // lalr1.cc:614
        break;

      case 97: // Constructor

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 726 "parser.tab.cc" // lalr1.cc:614
        break;

      case 98: // Destructor

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 737 "parser.tab.cc" // lalr1.cc:614
        break;

      case 99: // BuiltInFunction

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 748 "parser.tab.cc" // lalr1.cc:614
        break;

      case 100: // TupleElement

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 759 "parser.tab.cc" // lalr1.cc:614
        break;

      case 101: // Constant

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 770 "parser.tab.cc" // lalr1.cc:614
        break;

      case 102: // BuiltInFunctionName

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 781 "parser.tab.cc" // lalr1.cc:614
        break;

      case 103: // Application

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scApp);
	delete node;

}
#line 792 "parser.tab.cc" // lalr1.cc:614
        break;

      case 104: // DataInit

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 803 "parser.tab.cc" // lalr1.cc:614
        break;

      case 105: // OneDataInit

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 814 "parser.tab.cc" // lalr1.cc:614
        break;

      case 107: // InterpFunProgramName

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 825 "parser.tab.cc" // lalr1.cc:614
        break;

      case 108: // Data

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 836 "parser.tab.cc" // lalr1.cc:614
        break;

      case 109: // OneData

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 847 "parser.tab.cc" // lalr1.cc:614
        break;

      case 110: // ValueAtom

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 858 "parser.tab.cc" // lalr1.cc:614
        break;

      case 111: // ValueConstructor

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 869 "parser.tab.cc" // lalr1.cc:614
        break;

      case 112: // ValueComposition

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 880 "parser.tab.cc" // lalr1.cc:614
        break;

      case 113: // Value

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 891 "parser.tab.cc" // lalr1.cc:614
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
#line 179 "parser.yy" // lalr1.cc:859
    {
			mASTRoot = new FunctionalProgram( (yystack_[2].value.scList), (yystack_[1].value.scFun), (yystack_[0].value.scApp) );
			
			// Возвращаем 0, иначе все дерево будет "срублено" деструктором парсера.
			(yylhs.value.scNode) = 0;
		}
#line 1126 "parser.tab.cc" // lalr1.cc:859
    break;

  case 3:
#line 186 "parser.yy" // lalr1.cc:859
    {
			mASTRoot = new FunctionalProgram( 0, (yystack_[1].value.scFun), (yystack_[0].value.scApp) );
			(yylhs.value.scNode) = 0;
		}
#line 1135 "parser.tab.cc" // lalr1.cc:859
    break;

  case 4:
#line 196 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode(  ASTNode::DataTypeDefinitionsBlocks );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
		}
#line 1144 "parser.tab.cc" // lalr1.cc:859
    break;

  case 5:
#line 201 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scNode) );
		}
#line 1152 "parser.tab.cc" // lalr1.cc:859
    break;

  case 6:
#line 208 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[3].value.scIdent), (yystack_[1].value.scList), 0, 0 );
		}
#line 1160 "parser.tab.cc" // lalr1.cc:859
    break;

  case 7:
#line 212 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[6].value.scIdent), (yystack_[1].value.scList), (yystack_[4].value.scList), 0 );
		}
#line 1168 "parser.tab.cc" // lalr1.cc:859
    break;

  case 8:
#line 216 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[7].value.scIdent), (yystack_[1].value.scList), 0, (yystack_[3].value.scList) );
		}
#line 1176 "parser.tab.cc" // lalr1.cc:859
    break;

  case 9:
#line 220 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[10].value.scIdent), (yystack_[1].value.scList), (yystack_[8].value.scList), (yystack_[3].value.scList) );
		}
#line 1184 "parser.tab.cc" // lalr1.cc:859
    break;

  case 11:
#line 231 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::TypeParametersList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
		}
#line 1193 "parser.tab.cc" // lalr1.cc:859
    break;

  case 12:
#line 236 "parser.yy" // lalr1.cc:859
    {		
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scDef) );
		}
#line 1201 "parser.tab.cc" // lalr1.cc:859
    break;

  case 13:
#line 243 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::TypeParameterDefinition, (yystack_[0].value.scIdent), 0 );
		}
#line 1209 "parser.tab.cc" // lalr1.cc:859
    break;

  case 14:
#line 250 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::ConstructorsDefinitionList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
		}
#line 1218 "parser.tab.cc" // lalr1.cc:859
    break;

  case 15:
#line 255 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scNode) );
		}
#line 1226 "parser.tab.cc" // lalr1.cc:859
    break;

  case 16:
#line 262 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConstructorNode( (yystack_[1].value.scIdent), 0, (yystack_[3].value.scIdent) );
		}
#line 1234 "parser.tab.cc" // lalr1.cc:859
    break;

  case 17:
#line 266 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConstructorNode( (yystack_[1].value.scIdent), (yystack_[5].value.scList), (yystack_[3].value.scIdent) );
		}
#line 1242 "parser.tab.cc" // lalr1.cc:859
    break;

  case 18:
#line 272 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::ConstructorParametersList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scName) );
		}
#line 1251 "parser.tab.cc" // lalr1.cc:859
    break;

  case 19:
#line 277 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scName) );
		}
#line 1259 "parser.tab.cc" // lalr1.cc:859
    break;

  case 20:
#line 285 "parser.yy" // lalr1.cc:859
    {
			if( (yystack_[0].value.scList)->size() > 1 )
			{
				for( ListNode::iterator it = (yystack_[0].value.scList)->begin(); it != (yystack_[0].value.scList)->end(); ++it )
					pSupport->semanticError( ErrTypes::MultipleTypeExpression, static_cast<DefinitionNode*>( *it )->getDefinitionName() );
			}

			(yylhs.value.scList) = (yystack_[0].value.scList);
		}
#line 1273 "parser.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 298 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::TypesDefinitionList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
		}
#line 1282 "parser.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 303 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scDef) );
		}
#line 1290 "parser.tab.cc" // lalr1.cc:859
    break;

  case 23:
#line 310 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::TypeDefinition, (yystack_[3].value.scIdent), (yystack_[1].value.scNode) );
		}
#line 1298 "parser.tab.cc" // lalr1.cc:859
    break;

  case 24:
#line 314 "parser.yy" // lalr1.cc:859
    {
			pSupport->semanticError( ErrTypes::NestedDataDefinition, static_cast<DataNode*>((yystack_[0].value.scNode))->getDataName() );
			delete (yystack_[0].value.scNode);
			(yylhs.value.scDef) = 0;
		}
#line 1308 "parser.tab.cc" // lalr1.cc:859
    break;

  case 25:
#line 323 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::TypeConstructorDefinition, (yystack_[0].value.scIdent), (yystack_[2].value.scList) );
		}
#line 1316 "parser.tab.cc" // lalr1.cc:859
    break;

  case 26:
#line 327 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::TypeConstructorDefinition, (yystack_[0].value.scIdent), 0 );
		}
#line 1324 "parser.tab.cc" // lalr1.cc:859
    break;

  case 28:
#line 335 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::TypeExpression, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1332 "parser.tab.cc" // lalr1.cc:859
    break;

  case 29:
#line 343 "parser.yy" // lalr1.cc:859
    {	
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scToken), NameRefNode::BaseType );
		}
#line 1340 "parser.tab.cc" // lalr1.cc:859
    break;

  case 30:
#line 347 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::Type );
		}
#line 1348 "parser.tab.cc" // lalr1.cc:859
    break;

  case 31:
#line 351 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[3].value.scIdent), NameRefNode::Template, (yystack_[1].value.scList) );
		}
#line 1356 "parser.tab.cc" // lalr1.cc:859
    break;

  case 32:
#line 355 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::TypeParamName );
		}
#line 1364 "parser.tab.cc" // lalr1.cc:859
    break;

  case 40:
#line 372 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::TypeExpressionsList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scName) );
		}
#line 1373 "parser.tab.cc" // lalr1.cc:859
    break;

  case 41:
#line 377 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scName) );
		}
#line 1381 "parser.tab.cc" // lalr1.cc:859
    break;

  case 44:
#line 390 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[3].value.scIdent), (yystack_[1].value.scList), 0 );
			pSupport->popIdent();
		}
#line 1390 "parser.tab.cc" // lalr1.cc:859
    break;

  case 45:
#line 395 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[6].value.scIdent), (yystack_[1].value.scList), (yystack_[4].value.scList) );
			pSupport->popIdent();
		}
#line 1399 "parser.tab.cc" // lalr1.cc:859
    break;

  case 46:
#line 403 "parser.yy" // lalr1.cc:859
    {
			pSupport->pushIdent( (yystack_[0].value.scIdent) );
			(yylhs.value.scIdent) = (yystack_[0].value.scIdent);
		}
#line 1408 "parser.tab.cc" // lalr1.cc:859
    break;

  case 47:
#line 411 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::FormalParametersList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
		}
#line 1417 "parser.tab.cc" // lalr1.cc:859
    break;

  case 48:
#line 416 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scDef) );
		}
#line 1425 "parser.tab.cc" // lalr1.cc:859
    break;

  case 49:
#line 423 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::FunctionParameterDefinition, (yystack_[0].value.scIdent), 0 );
		}
#line 1433 "parser.tab.cc" // lalr1.cc:859
    break;

  case 50:
#line 430 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::DefinitionsList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
		}
#line 1442 "parser.tab.cc" // lalr1.cc:859
    break;

  case 51:
#line 435 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scNode) );
		}
#line 1450 "parser.tab.cc" // lalr1.cc:859
    break;

  case 52:
#line 442 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::Definition, pSupport->getTopIdent(), (yystack_[1].value.scNode) );
		}
#line 1458 "parser.tab.cc" // lalr1.cc:859
    break;

  case 53:
#line 446 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::Definition, (yystack_[3].value.scIdent), (yystack_[1].value.scNode) );
		}
#line 1466 "parser.tab.cc" // lalr1.cc:859
    break;

  case 54:
#line 450 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scFun); }
#line 1472 "parser.tab.cc" // lalr1.cc:859
    break;

  case 56:
#line 459 "parser.yy" // lalr1.cc:859
    {	(yylhs.value.scNode) = (yystack_[1].value.scNode); }
#line 1478 "parser.tab.cc" // lalr1.cc:859
    break;

  case 58:
#line 462 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1484 "parser.tab.cc" // lalr1.cc:859
    break;

  case 59:
#line 464 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new NameRefNode( pSupport->getTopIdent(), ASTNode::FuncObjectName );
		}
#line 1492 "parser.tab.cc" // lalr1.cc:859
    break;

  case 60:
#line 471 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[3].value.scIdent), NameRefNode::FuncObjectWithParameters, (yystack_[1].value.scList) );
		}
#line 1500 "parser.tab.cc" // lalr1.cc:859
    break;

  case 61:
#line 477 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::FuncArgumentsList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
		}
#line 1509 "parser.tab.cc" // lalr1.cc:859
    break;

  case 62:
#line 482 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scNode) );
		}
#line 1517 "parser.tab.cc" // lalr1.cc:859
    break;

  case 63:
#line 489 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::FuncParameterName );
		}
#line 1525 "parser.tab.cc" // lalr1.cc:859
    break;

  case 65:
#line 494 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1531 "parser.tab.cc" // lalr1.cc:859
    break;

  case 67:
#line 500 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::SequentialTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1539 "parser.tab.cc" // lalr1.cc:859
    break;

  case 69:
#line 508 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::CompositionTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1547 "parser.tab.cc" // lalr1.cc:859
    break;

  case 71:
#line 516 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ConditionTerm, (yystack_[4].value.scNode), (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1555 "parser.tab.cc" // lalr1.cc:859
    break;

  case 72:
#line 520 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ConditionTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1563 "parser.tab.cc" // lalr1.cc:859
    break;

  case 74:
#line 528 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::VariantTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1571 "parser.tab.cc" // lalr1.cc:859
    break;

  case 75:
#line 535 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::FuncObjectName );
		}
#line 1579 "parser.tab.cc" // lalr1.cc:859
    break;

  case 77:
#line 543 "parser.yy" // lalr1.cc:859
    {
			pSupport->pushIdent( (yystack_[0].value.scIdent) );
		}
#line 1587 "parser.tab.cc" // lalr1.cc:859
    break;

  case 78:
#line 547 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[4].value.scIdent), (yystack_[1].value.scList), 0 );
			pSupport->popIdent();
		}
#line 1596 "parser.tab.cc" // lalr1.cc:859
    break;

  case 79:
#line 552 "parser.yy" // lalr1.cc:859
    {
			pSupport->pushIdent( (yystack_[0].value.scIdent) );
		}
#line 1604 "parser.tab.cc" // lalr1.cc:859
    break;

  case 80:
#line 556 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[7].value.scIdent), (yystack_[1].value.scList), (yystack_[4].value.scList) );
			pSupport->popIdent();
		}
#line 1613 "parser.tab.cc" // lalr1.cc:859
    break;

  case 84:
#line 573 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1619 "parser.tab.cc" // lalr1.cc:859
    break;

  case 85:
#line 575 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1625 "parser.tab.cc" // lalr1.cc:859
    break;

  case 86:
#line 580 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::ConstructorName );
		}
#line 1633 "parser.tab.cc" // lalr1.cc:859
    break;

  case 87:
#line 587 "parser.yy" // lalr1.cc:859
    {	
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::DestructorName );
		}
#line 1641 "parser.tab.cc" // lalr1.cc:859
    break;

  case 88:
#line 594 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1647 "parser.tab.cc" // lalr1.cc:859
    break;

  case 91:
#line 601 "parser.yy" // lalr1.cc:859
    {
		ConstantNode * number = static_cast<ConstantNode*>( (yystack_[1].value.scNode) );
		(yylhs.value.scNode) = new ConstantNode( ASTNode::TupleElemNumber, number->getConstant() );
		delete number;
	}
#line 1657 "parser.tab.cc" // lalr1.cc:859
    break;

  case 95:
#line 612 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConstantNode( ASTNode::TrueValue, (yystack_[0].value.scToken) );
		}
#line 1665 "parser.tab.cc" // lalr1.cc:859
    break;

  case 96:
#line 616 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConstantNode( ASTNode::FalseValue, (yystack_[0].value.scToken) );
		}
#line 1673 "parser.tab.cc" // lalr1.cc:859
    break;

  case 97:
#line 624 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::BuildInFunction );
		}
#line 1681 "parser.tab.cc" // lalr1.cc:859
    break;

  case 98:
#line 631 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[0].value.scName), 0, 0 );
		}
#line 1689 "parser.tab.cc" // lalr1.cc:859
    break;

  case 99:
#line 635 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[3].value.scName), (yystack_[1].value.scNode), 0 );
		}
#line 1697 "parser.tab.cc" // lalr1.cc:859
    break;

  case 100:
#line 639 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[0].value.scName), 0, (yystack_[1].value.scList) ); 
		}
#line 1705 "parser.tab.cc" // lalr1.cc:859
    break;

  case 101:
#line 643 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[3].value.scName), (yystack_[1].value.scNode), (yystack_[4].value.scList) );
		}
#line 1713 "parser.tab.cc" // lalr1.cc:859
    break;

  case 102:
#line 650 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::InputVarDefinitionList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
		}
#line 1722 "parser.tab.cc" // lalr1.cc:859
    break;

  case 103:
#line 655 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scDef) );
		}
#line 1730 "parser.tab.cc" // lalr1.cc:859
    break;

  case 104:
#line 662 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::InputVarDefinition, (yystack_[3].value.scIdent), (yystack_[1].value.scNode) );
		}
#line 1738 "parser.tab.cc" // lalr1.cc:859
    break;

  case 106:
#line 671 "parser.yy" // lalr1.cc:859
    { 
			(yylhs.value.scName) = new NameRefNode((yystack_[0].value.scIdent), ASTNode::RunningSchemeName);
		}
#line 1746 "parser.tab.cc" // lalr1.cc:859
    break;

  case 107:
#line 678 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = (yystack_[0].value.scNode);
		}
#line 1754 "parser.tab.cc" // lalr1.cc:859
    break;

  case 108:
#line 682 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode(ASTNode::InputVarList, (yystack_[2].value.scNode), (yystack_[0].value.scNode));
		}
#line 1762 "parser.tab.cc" // lalr1.cc:859
    break;

  case 109:
#line 689 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new NameRefNode( (yystack_[0].value.scIdent), ASTNode::InputVarName );
		}
#line 1770 "parser.tab.cc" // lalr1.cc:859
    break;

  case 112:
#line 699 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1776 "parser.tab.cc" // lalr1.cc:859
    break;

  case 113:
#line 701 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = (yystack_[1].value.scNode);
		}
#line 1784 "parser.tab.cc" // lalr1.cc:859
    break;

  case 115:
#line 709 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ValueConstructor, (yystack_[2].value.scNode), (yystack_[0].value.scName) );
		}
#line 1792 "parser.tab.cc" // lalr1.cc:859
    break;

  case 117:
#line 717 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ValueComposition, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1800 "parser.tab.cc" // lalr1.cc:859
    break;


#line 1804 "parser.tab.cc" // lalr1.cc:859
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
  BisonParser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
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


#if YYDEBUG
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
     596,   600,   608,   609,   610,   611,   615,   623,   630,   634,
     638,   642,   649,   654,   661,   667,   670,   677,   681,   688,
     692,   697,   698,   700,   707,   708,   715,   716,   722
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
#line 2297 "parser.tab.cc" // lalr1.cc:1167
