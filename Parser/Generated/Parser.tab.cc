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
#include "../Tokenizer.h"
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

      case 15: // ARG

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 374 "parser.tab.cc" // lalr1.cc:614
        break;

      case 57: // FunctionalProgram

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 385 "parser.tab.cc" // lalr1.cc:614
        break;

      case 58: // DataTypeDefinitionsBlocks

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 396 "parser.tab.cc" // lalr1.cc:614
        break;

      case 59: // DataTypeDefinitionsBlock

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 407 "parser.tab.cc" // lalr1.cc:614
        break;

      case 61: // TypeParametersList

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 418 "parser.tab.cc" // lalr1.cc:614
        break;

      case 62: // TypeParameterDef

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 429 "parser.tab.cc" // lalr1.cc:614
        break;

      case 63: // ConstructorsDefinitionList

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 440 "parser.tab.cc" // lalr1.cc:614
        break;

      case 64: // ConstructorDef

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 451 "parser.tab.cc" // lalr1.cc:614
        break;

      case 65: // ConstructorParametersList

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 462 "parser.tab.cc" // lalr1.cc:614
        break;

      case 66: // TypesDefinitionList

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 473 "parser.tab.cc" // lalr1.cc:614
        break;

      case 67: // TypesDefinitionList2

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 484 "parser.tab.cc" // lalr1.cc:614
        break;

      case 68: // TypeDefinition

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 495 "parser.tab.cc" // lalr1.cc:614
        break;

      case 69: // TypeDefConstructor

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 506 "parser.tab.cc" // lalr1.cc:614
        break;

      case 70: // TypeExpression

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 517 "parser.tab.cc" // lalr1.cc:614
        break;

      case 71: // AtomType

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 528 "parser.tab.cc" // lalr1.cc:614
        break;

      case 73: // TypeExpressionsList

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 539 "parser.tab.cc" // lalr1.cc:614
        break;

      case 76: // Scheme

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scFun);
	delete node;

}
#line 550 "parser.tab.cc" // lalr1.cc:614
        break;

      case 78: // FormalParametersList

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 561 "parser.tab.cc" // lalr1.cc:614
        break;

      case 79: // FormalParameter

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 572 "parser.tab.cc" // lalr1.cc:614
        break;

      case 80: // DefinitionsList

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 583 "parser.tab.cc" // lalr1.cc:614
        break;

      case 81: // Definition

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 594 "parser.tab.cc" // lalr1.cc:614
        break;

      case 82: // NamedArgument

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 605 "parser.tab.cc" // lalr1.cc:614
        break;

      case 83: // NamedArgumentsList

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 616 "parser.tab.cc" // lalr1.cc:614
        break;

      case 84: // Term

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 627 "parser.tab.cc" // lalr1.cc:614
        break;

      case 85: // AtomTerm

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 638 "parser.tab.cc" // lalr1.cc:614
        break;

      case 86: // FuncObjectWithParameters

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 649 "parser.tab.cc" // lalr1.cc:614
        break;

      case 87: // FuncArgumentList

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 660 "parser.tab.cc" // lalr1.cc:614
        break;

      case 88: // FuncParameterName

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 671 "parser.tab.cc" // lalr1.cc:614
        break;

      case 89: // SequentialTerm

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 682 "parser.tab.cc" // lalr1.cc:614
        break;

      case 90: // CompositionTerm

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 693 "parser.tab.cc" // lalr1.cc:614
        break;

      case 91: // ConditionTerm

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 704 "parser.tab.cc" // lalr1.cc:614
        break;

      case 92: // VariantTerm

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 715 "parser.tab.cc" // lalr1.cc:614
        break;

      case 93: // FuncObjectName

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 726 "parser.tab.cc" // lalr1.cc:614
        break;

      case 94: // ConstructionFun

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scFun);
	delete node;

}
#line 737 "parser.tab.cc" // lalr1.cc:614
        break;

      case 99: // ElementaryFunctionName

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 748 "parser.tab.cc" // lalr1.cc:614
        break;

      case 100: // Constructor

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 759 "parser.tab.cc" // lalr1.cc:614
        break;

      case 101: // Destructor

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 770 "parser.tab.cc" // lalr1.cc:614
        break;

      case 102: // BuiltInFunction

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 781 "parser.tab.cc" // lalr1.cc:614
        break;

      case 103: // TupleElement

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 792 "parser.tab.cc" // lalr1.cc:614
        break;

      case 104: // Constant

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 803 "parser.tab.cc" // lalr1.cc:614
        break;

      case 105: // BuiltInFunctionName

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 814 "parser.tab.cc" // lalr1.cc:614
        break;

      case 106: // Application

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scApp);
	delete node;

}
#line 825 "parser.tab.cc" // lalr1.cc:614
        break;

      case 107: // DataInit

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 836 "parser.tab.cc" // lalr1.cc:614
        break;

      case 108: // OneDataInit

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 847 "parser.tab.cc" // lalr1.cc:614
        break;

      case 110: // InterpFunProgramName

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 858 "parser.tab.cc" // lalr1.cc:614
        break;

      case 111: // Data

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 869 "parser.tab.cc" // lalr1.cc:614
        break;

      case 112: // OneData

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 880 "parser.tab.cc" // lalr1.cc:614
        break;

      case 113: // ValueAtom

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 891 "parser.tab.cc" // lalr1.cc:614
        break;

      case 114: // ValueConstructor

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 902 "parser.tab.cc" // lalr1.cc:614
        break;

      case 115: // ValueComposition

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 913 "parser.tab.cc" // lalr1.cc:614
        break;

      case 116: // Value

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 924 "parser.tab.cc" // lalr1.cc:614
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
#line 182 "parser.yy" // lalr1.cc:859
    {
			mASTRoot = new FunctionalProgram( (yystack_[2].value.scList), (yystack_[1].value.scFun), (yystack_[0].value.scApp) );
			
			// Возвращаем 0, иначе все дерево будет "срублено" деструктором парсера.
			(yylhs.value.scNode) = 0;
		}
#line 1159 "parser.tab.cc" // lalr1.cc:859
    break;

  case 3:
#line 189 "parser.yy" // lalr1.cc:859
    {
			mASTRoot = new FunctionalProgram( 0, (yystack_[1].value.scFun), (yystack_[0].value.scApp) );
			(yylhs.value.scNode) = 0;
		}
#line 1168 "parser.tab.cc" // lalr1.cc:859
    break;

  case 4:
#line 199 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode(  ASTNode::DataTypeDefinitionsBlocks );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
		}
#line 1177 "parser.tab.cc" // lalr1.cc:859
    break;

  case 5:
#line 204 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scNode) );
		}
#line 1185 "parser.tab.cc" // lalr1.cc:859
    break;

  case 6:
#line 211 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[3].value.scIdent), (yystack_[1].value.scList), 0, 0 );
		}
#line 1193 "parser.tab.cc" // lalr1.cc:859
    break;

  case 7:
#line 215 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[6].value.scIdent), (yystack_[1].value.scList), (yystack_[4].value.scList), 0 );
		}
#line 1201 "parser.tab.cc" // lalr1.cc:859
    break;

  case 8:
#line 219 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[7].value.scIdent), (yystack_[1].value.scList), 0, (yystack_[3].value.scList) );
		}
#line 1209 "parser.tab.cc" // lalr1.cc:859
    break;

  case 9:
#line 223 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[10].value.scIdent), (yystack_[1].value.scList), (yystack_[8].value.scList), (yystack_[3].value.scList) );
		}
#line 1217 "parser.tab.cc" // lalr1.cc:859
    break;

  case 11:
#line 234 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::TypeParametersList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
		}
#line 1226 "parser.tab.cc" // lalr1.cc:859
    break;

  case 12:
#line 239 "parser.yy" // lalr1.cc:859
    {		
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scDef) );
		}
#line 1234 "parser.tab.cc" // lalr1.cc:859
    break;

  case 13:
#line 246 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::TypeParameterDefinition, (yystack_[0].value.scIdent), 0, 0 );
		}
#line 1242 "parser.tab.cc" // lalr1.cc:859
    break;

  case 14:
#line 253 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::ConstructorsDefinitionList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
		}
#line 1251 "parser.tab.cc" // lalr1.cc:859
    break;

  case 15:
#line 258 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scNode) );
		}
#line 1259 "parser.tab.cc" // lalr1.cc:859
    break;

  case 16:
#line 265 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConstructorNode( (yystack_[1].value.scIdent), 0, (yystack_[3].value.scIdent) );
		}
#line 1267 "parser.tab.cc" // lalr1.cc:859
    break;

  case 17:
#line 269 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConstructorNode( (yystack_[1].value.scIdent), (yystack_[5].value.scList), (yystack_[3].value.scIdent) );
		}
#line 1275 "parser.tab.cc" // lalr1.cc:859
    break;

  case 18:
#line 275 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::ConstructorParametersList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scName) );
		}
#line 1284 "parser.tab.cc" // lalr1.cc:859
    break;

  case 19:
#line 280 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scName) );
		}
#line 1292 "parser.tab.cc" // lalr1.cc:859
    break;

  case 20:
#line 288 "parser.yy" // lalr1.cc:859
    {
			if( (yystack_[0].value.scList)->size() > 1 )
			{
				for( ListNode::iterator it = (yystack_[0].value.scList)->begin(); it != (yystack_[0].value.scList)->end(); ++it )
					pSupport->semanticError( ErrTypes::MultipleTypeExpression, static_cast<DefinitionNode*>( *it )->getDefinitionName() );
			}

			(yylhs.value.scList) = (yystack_[0].value.scList);
		}
#line 1306 "parser.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 301 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::TypesDefinitionList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
		}
#line 1315 "parser.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 306 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scDef) );
		}
#line 1323 "parser.tab.cc" // lalr1.cc:859
    break;

  case 23:
#line 313 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::TypeDefinition, (yystack_[3].value.scIdent), (yystack_[1].value.scNode), 0 );
		}
#line 1331 "parser.tab.cc" // lalr1.cc:859
    break;

  case 24:
#line 317 "parser.yy" // lalr1.cc:859
    {
			pSupport->semanticError( ErrTypes::NestedDataDefinition, static_cast<DataNode*>((yystack_[0].value.scNode))->getDataName() );
			delete (yystack_[0].value.scNode);
			(yylhs.value.scDef) = 0;
		}
#line 1341 "parser.tab.cc" // lalr1.cc:859
    break;

  case 25:
#line 326 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::TypeConstructorDefinition, (yystack_[0].value.scIdent), (yystack_[2].value.scList), 0 );
		}
#line 1349 "parser.tab.cc" // lalr1.cc:859
    break;

  case 26:
#line 330 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::TypeConstructorDefinition, (yystack_[0].value.scIdent), 0, 0 );
		}
#line 1357 "parser.tab.cc" // lalr1.cc:859
    break;

  case 28:
#line 338 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::TypeExpression, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1365 "parser.tab.cc" // lalr1.cc:859
    break;

  case 29:
#line 346 "parser.yy" // lalr1.cc:859
    {	
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scToken), NameRefNode::BaseType );
		}
#line 1373 "parser.tab.cc" // lalr1.cc:859
    break;

  case 30:
#line 350 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::Type );
		}
#line 1381 "parser.tab.cc" // lalr1.cc:859
    break;

  case 31:
#line 354 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[3].value.scIdent), NameRefNode::Template, (yystack_[1].value.scList) );
		}
#line 1389 "parser.tab.cc" // lalr1.cc:859
    break;

  case 32:
#line 358 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::TypeParamName );
		}
#line 1397 "parser.tab.cc" // lalr1.cc:859
    break;

  case 40:
#line 375 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::TypeExpressionsList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scName) );
		}
#line 1406 "parser.tab.cc" // lalr1.cc:859
    break;

  case 41:
#line 380 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scName) );
		}
#line 1414 "parser.tab.cc" // lalr1.cc:859
    break;

  case 44:
#line 393 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[3].value.scIdent), (yystack_[1].value.scList), 0 );
			pSupport->popIdent();
		}
#line 1423 "parser.tab.cc" // lalr1.cc:859
    break;

  case 45:
#line 398 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[6].value.scIdent), (yystack_[1].value.scList), (yystack_[4].value.scList) );
			pSupport->popIdent();
		}
#line 1432 "parser.tab.cc" // lalr1.cc:859
    break;

  case 46:
#line 406 "parser.yy" // lalr1.cc:859
    {
			pSupport->pushIdent( (yystack_[0].value.scIdent) );
			(yylhs.value.scIdent) = (yystack_[0].value.scIdent);
		}
#line 1441 "parser.tab.cc" // lalr1.cc:859
    break;

  case 47:
#line 414 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::FormalParametersList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
		}
#line 1450 "parser.tab.cc" // lalr1.cc:859
    break;

  case 48:
#line 419 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scDef) );
		}
#line 1458 "parser.tab.cc" // lalr1.cc:859
    break;

  case 49:
#line 426 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::FunctionParameterDefinition, (yystack_[0].value.scIdent), 0, 0 );
		}
#line 1466 "parser.tab.cc" // lalr1.cc:859
    break;

  case 50:
#line 433 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::DefinitionsList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
		}
#line 1475 "parser.tab.cc" // lalr1.cc:859
    break;

  case 51:
#line 438 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scNode) );
		}
#line 1483 "parser.tab.cc" // lalr1.cc:859
    break;

  case 52:
#line 445 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::Definition, pSupport->getTopIdent(), (yystack_[1].value.scNode), 0 );
		}
#line 1491 "parser.tab.cc" // lalr1.cc:859
    break;

  case 53:
#line 449 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::Definition, pSupport->getTopIdent(), (yystack_[1].value.scNode), (yystack_[4].value.scList) );
		}
#line 1499 "parser.tab.cc" // lalr1.cc:859
    break;

  case 54:
#line 453 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::Definition, (yystack_[3].value.scIdent), (yystack_[1].value.scNode), 0 );
		}
#line 1507 "parser.tab.cc" // lalr1.cc:859
    break;

  case 55:
#line 457 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::Definition, (yystack_[6].value.scIdent), (yystack_[1].value.scNode), (yystack_[4].value.scList) );
		}
#line 1515 "parser.tab.cc" // lalr1.cc:859
    break;

  case 56:
#line 461 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scFun); }
#line 1521 "parser.tab.cc" // lalr1.cc:859
    break;

  case 57:
#line 466 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::NamedArgument);
		}
#line 1529 "parser.tab.cc" // lalr1.cc:859
    break;

  case 58:
#line 473 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::NamedArgumentsList );
			(yylhs.value.scList) -> addElement( (yystack_[0].value.scName) );
		}
#line 1538 "parser.tab.cc" // lalr1.cc:859
    break;

  case 59:
#line 478 "parser.yy" // lalr1.cc:859
    {
		   (yylhs.value.scList) = (yystack_[0].value.scList) -> addElement( (yystack_[2].value.scName) );
		}
#line 1546 "parser.tab.cc" // lalr1.cc:859
    break;

  case 61:
#line 489 "parser.yy" // lalr1.cc:859
    {	(yylhs.value.scNode) = (yystack_[1].value.scNode); }
#line 1552 "parser.tab.cc" // lalr1.cc:859
    break;

  case 63:
#line 492 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1558 "parser.tab.cc" // lalr1.cc:859
    break;

  case 64:
#line 494 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new NameRefNode( pSupport->getTopIdent(), ASTNode::FuncObjectName );
		}
#line 1566 "parser.tab.cc" // lalr1.cc:859
    break;

  case 65:
#line 501 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[3].value.scIdent), NameRefNode::FuncObjectWithParameters, (yystack_[1].value.scList) );
		}
#line 1574 "parser.tab.cc" // lalr1.cc:859
    break;

  case 66:
#line 507 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::FuncArgumentsList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
		}
#line 1583 "parser.tab.cc" // lalr1.cc:859
    break;

  case 67:
#line 512 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scNode) );
		}
#line 1591 "parser.tab.cc" // lalr1.cc:859
    break;

  case 68:
#line 519 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::FuncParameterName );
		}
#line 1599 "parser.tab.cc" // lalr1.cc:859
    break;

  case 70:
#line 524 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1605 "parser.tab.cc" // lalr1.cc:859
    break;

  case 72:
#line 530 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::SequentialTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1613 "parser.tab.cc" // lalr1.cc:859
    break;

  case 74:
#line 538 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::CompositionTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1621 "parser.tab.cc" // lalr1.cc:859
    break;

  case 76:
#line 546 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ConditionTerm, (yystack_[4].value.scNode), (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1629 "parser.tab.cc" // lalr1.cc:859
    break;

  case 77:
#line 550 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ConditionTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1637 "parser.tab.cc" // lalr1.cc:859
    break;

  case 79:
#line 558 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::VariantTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1645 "parser.tab.cc" // lalr1.cc:859
    break;

  case 80:
#line 565 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::FuncObjectName );
		}
#line 1653 "parser.tab.cc" // lalr1.cc:859
    break;

  case 82:
#line 573 "parser.yy" // lalr1.cc:859
    {
			pSupport->pushIdent( (yystack_[0].value.scIdent) );
		}
#line 1661 "parser.tab.cc" // lalr1.cc:859
    break;

  case 83:
#line 577 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[4].value.scIdent), (yystack_[1].value.scList), 0 );
			pSupport->popIdent();
		}
#line 1670 "parser.tab.cc" // lalr1.cc:859
    break;

  case 84:
#line 582 "parser.yy" // lalr1.cc:859
    {
			pSupport->pushIdent( (yystack_[0].value.scIdent) );
		}
#line 1678 "parser.tab.cc" // lalr1.cc:859
    break;

  case 85:
#line 586 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[7].value.scIdent), (yystack_[1].value.scList), (yystack_[4].value.scList) );
			pSupport->popIdent();
		}
#line 1687 "parser.tab.cc" // lalr1.cc:859
    break;

  case 89:
#line 603 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1693 "parser.tab.cc" // lalr1.cc:859
    break;

  case 90:
#line 605 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1699 "parser.tab.cc" // lalr1.cc:859
    break;

  case 91:
#line 610 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::ConstructorName );
		}
#line 1707 "parser.tab.cc" // lalr1.cc:859
    break;

  case 92:
#line 617 "parser.yy" // lalr1.cc:859
    {	
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::DestructorName );
		}
#line 1715 "parser.tab.cc" // lalr1.cc:859
    break;

  case 93:
#line 624 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1721 "parser.tab.cc" // lalr1.cc:859
    break;

  case 95:
#line 627 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1727 "parser.tab.cc" // lalr1.cc:859
    break;

  case 97:
#line 634 "parser.yy" // lalr1.cc:859
    {
		ConstantNode * number = static_cast<ConstantNode*>( (yystack_[1].value.scNode) );
		if (number->isNatural())
		{
			(yylhs.value.scNode) = new ConstantNode( ASTNode::TupleElemNumber, number->getConstant() );
			delete number;
		}
		else
		{
			pSupport->semanticError(ErrTypes::InvalidTupleIndex, number->getConstant());
			(yylhs.value.scNode) = 0;
		}
	}
#line 1745 "parser.tab.cc" // lalr1.cc:859
    break;

  case 101:
#line 654 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConstantNode( ASTNode::TrueValue, (yystack_[0].value.scToken) );
		}
#line 1753 "parser.tab.cc" // lalr1.cc:859
    break;

  case 102:
#line 658 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConstantNode( ASTNode::FalseValue, (yystack_[0].value.scToken) );
		}
#line 1761 "parser.tab.cc" // lalr1.cc:859
    break;

  case 103:
#line 666 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::BuildInFunction );
		}
#line 1769 "parser.tab.cc" // lalr1.cc:859
    break;

  case 104:
#line 673 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[0].value.scName), 0, 0 );
		}
#line 1777 "parser.tab.cc" // lalr1.cc:859
    break;

  case 105:
#line 677 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[3].value.scName), (yystack_[1].value.scNode), 0 );
		}
#line 1785 "parser.tab.cc" // lalr1.cc:859
    break;

  case 106:
#line 681 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[0].value.scName), 0, (yystack_[1].value.scList) ); 
		}
#line 1793 "parser.tab.cc" // lalr1.cc:859
    break;

  case 107:
#line 685 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[3].value.scName), (yystack_[1].value.scNode), (yystack_[4].value.scList) );
		}
#line 1801 "parser.tab.cc" // lalr1.cc:859
    break;

  case 108:
#line 692 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::InputVarDefinitionList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
		}
#line 1810 "parser.tab.cc" // lalr1.cc:859
    break;

  case 109:
#line 697 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scDef) );
		}
#line 1818 "parser.tab.cc" // lalr1.cc:859
    break;

  case 110:
#line 704 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::InputVarDefinition, (yystack_[3].value.scIdent), (yystack_[1].value.scNode), 0 );
		}
#line 1826 "parser.tab.cc" // lalr1.cc:859
    break;

  case 112:
#line 713 "parser.yy" // lalr1.cc:859
    { 
			(yylhs.value.scName) = new NameRefNode((yystack_[0].value.scIdent), ASTNode::RunningSchemeName);
		}
#line 1834 "parser.tab.cc" // lalr1.cc:859
    break;

  case 113:
#line 720 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = (yystack_[0].value.scNode);
		}
#line 1842 "parser.tab.cc" // lalr1.cc:859
    break;

  case 114:
#line 724 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode(ASTNode::InputVarList, (yystack_[2].value.scNode), (yystack_[0].value.scNode));
		}
#line 1850 "parser.tab.cc" // lalr1.cc:859
    break;

  case 115:
#line 731 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new NameRefNode( (yystack_[0].value.scIdent), ASTNode::InputVarName );
		}
#line 1858 "parser.tab.cc" // lalr1.cc:859
    break;

  case 118:
#line 741 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1864 "parser.tab.cc" // lalr1.cc:859
    break;

  case 119:
#line 743 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = (yystack_[1].value.scNode);
		}
#line 1872 "parser.tab.cc" // lalr1.cc:859
    break;

  case 121:
#line 751 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ValueConstructor, (yystack_[2].value.scNode), (yystack_[0].value.scName) );
		}
#line 1880 "parser.tab.cc" // lalr1.cc:859
    break;

  case 123:
#line 759 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ValueComposition, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1888 "parser.tab.cc" // lalr1.cc:859
    break;


#line 1892 "parser.tab.cc" // lalr1.cc:859
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


  const short int BisonParser::yypact_ninf_ = -146;

  const signed char BisonParser::yytable_ninf_ = -85;

  const short int
  BisonParser::yypact_[] =
  {
      69,    16,    52,    56,    42,    40,    62,   -17,  -146,  -146,
     135,  -146,    62,  -146,    17,  -146,    77,    60,    36,    85,
    -146,  -146,    81,    41,   102,    91,    78,  -146,   130,    83,
      99,    77,  -146,   110,  -146,   101,   104,   109,  -146,   117,
     119,  -146,   116,  -146,   107,   134,  -146,  -146,   123,  -146,
     112,   108,  -146,   137,    31,   177,  -146,  -146,    31,   177,
     141,    60,    21,   125,  -146,  -146,   142,    85,   108,  -146,
    -146,  -146,  -146,  -146,  -146,   112,  -146,  -146,  -146,   136,
     139,  -146,   138,  -146,   131,   143,  -146,   149,   148,   144,
    -146,  -146,   179,  -146,    31,   187,   147,  -146,  -146,   145,
      19,  -146,   146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,
    -146,  -146,   152,   150,   151,   153,    77,  -146,  -146,  -146,
    -146,  -146,  -146,  -146,  -146,    52,   156,   159,    21,   162,
     157,  -146,  -146,   154,   169,   161,  -146,    92,  -146,   158,
     160,   187,   112,  -146,  -146,   108,    77,    60,    64,   165,
     163,  -146,  -146,    31,    31,    31,    31,   177,   166,  -146,
     168,   170,   164,   140,   116,  -146,    52,   140,   187,   125,
    -146,   173,   176,  -146,  -146,  -146,  -146,  -146,   178,   175,
     144,  -146,   171,   181,  -146,  -146,  -146,  -146,   129,   145,
    -146,  -146,    31,    31,  -146,   215,   182,   184,   180,   183,
    -146,  -146,  -146,    21,  -146,  -146,   189,  -146,    64,    31,
     185,   186,   188,   140,  -146,  -146,   217,   192,    77,  -146,
    -146,  -146,  -146,  -146,  -146,   190,   116,   194,  -146,   196,
    -146,  -146
  };

  const unsigned char
  BisonParser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     4,     0,     0,    46,    10,
       0,     1,     0,     5,     0,     3,     0,     0,     0,     0,
       2,   111,     0,     0,   108,     0,   104,    87,     0,     0,
       0,    50,    56,     0,    49,     0,    47,     0,    24,     0,
       0,    20,    21,    42,     0,    11,    13,   112,   106,   109,
       0,     0,    86,    82,     0,     0,    44,    51,     0,     0,
       0,     0,     0,     0,     6,    22,     0,     0,     0,    43,
      98,    99,   100,   101,   102,     0,    91,   118,   117,   120,
     122,   124,     0,   115,     0,   113,   116,     0,     0,    80,
     103,    95,     0,    64,     0,     0,     0,    71,    81,    73,
      75,    78,    60,    63,    62,    89,    90,    88,    94,    96,
      93,    57,    58,     0,     0,     0,     0,    48,    33,    34,
      35,    36,    37,    38,    39,     0,    30,     0,    14,     0,
      18,    29,    32,     0,    27,     0,    26,     0,    12,     0,
       0,     0,     0,   110,   105,     0,     0,     0,     0,     0,
       0,    92,    52,     0,     0,     0,     0,     0,     0,    54,
       0,     0,     0,     0,     0,    15,     0,     0,     0,     0,
      23,     0,     0,   107,   119,   121,   123,   114,     0,     0,
      68,    70,     0,    66,    69,    97,    61,    72,    77,    74,
      79,    59,     0,     0,    45,     0,    40,     0,     0,     0,
      19,    25,    28,     0,     7,    83,     0,    65,     0,     0,
       0,     0,     0,     0,    31,     8,     0,     0,     0,    67,
      76,    53,    55,    16,    41,     0,     0,     0,    17,     0,
      85,     9
  };

  const short int
  BisonParser::yypgoto_[] =
  {
    -146,  -146,   225,    22,    -2,   172,  -146,  -114,  -146,   -57,
    -132,   198,  -146,  -146,    72,  -145,  -146,    25,    23,   -60,
     238,  -146,   -54,  -146,   -30,  -146,  -146,   -55,   -56,    90,
    -137,    37,  -146,    89,    93,  -139,  -146,  -146,  -146,  -146,
    -146,  -146,  -146,  -133,   -42,  -146,  -146,  -146,   -38,  -146,
     234,   224,  -146,     7,   226,   -58,  -146,  -146,  -146,   111,
     -21
  };

  const short int
  BisonParser::yydefgoto_[] =
  {
      -1,     3,     4,    38,   126,    44,    45,   127,   128,   129,
      40,    41,    42,   134,   135,   130,   131,   197,   132,    76,
       6,     7,    35,    36,    30,    31,   112,   113,    96,    97,
      98,   182,   183,    99,   100,   101,   102,   103,    32,    87,
      88,    53,    33,   104,   105,   106,   107,   108,   109,   110,
      15,    23,    24,    83,    26,    84,    85,    79,    80,    81,
      86
  };

  const short int
  BisonParser::yytable_[] =
  {
      10,    57,   114,   136,   115,   172,   133,   117,    77,    77,
     139,   181,    78,    78,   165,   184,    39,   190,   196,     8,
      21,    25,     5,    16,     9,    17,    77,     5,    43,    82,
      78,    25,   198,    77,    89,   151,    69,    78,   150,     9,
      39,    90,    46,    70,    71,    72,    91,   118,   119,   120,
     121,   122,   123,   124,   140,     9,    11,   154,     2,    37,
     125,     1,     2,    34,    73,    74,   155,   180,   196,    69,
     220,   181,    22,    92,    90,   184,    70,    71,    72,    91,
      27,    93,    94,    14,    47,    95,   161,   177,     1,   217,
      46,     2,    43,   179,   229,     9,    22,    73,    74,   175,
      77,    28,   191,    77,    78,    21,    92,    78,   201,   136,
     200,    21,   133,    69,     2,   171,   178,    69,    95,     9,
      70,    71,    72,   162,    70,    71,    72,    29,     9,    51,
      69,    54,    43,    52,    55,    39,   210,   211,     2,    50,
      56,    73,    74,     9,    60,    73,    74,    43,    61,    62,
      66,   118,   119,   120,   121,   122,   123,   124,    58,    75,
      64,    59,    39,    75,   199,    63,   118,   119,   120,   121,
     122,   123,   124,   209,    68,    18,   155,    19,    67,   -84,
     111,   116,   137,   144,   143,   141,   142,   145,   227,   146,
     147,   149,    69,   152,   153,   148,   157,   159,   163,   156,
     164,   166,   158,   168,   167,   160,   169,   170,   185,   195,
     173,   194,   174,   203,   192,   186,   193,   204,   206,   205,
     212,   215,   225,   207,    39,   208,   213,   214,   216,   218,
      13,   221,   222,   226,   223,   230,   228,   231,   224,   138,
      65,   202,    12,   187,   189,   219,    20,   188,    49,    48,
       0,     0,     0,   176
  };

  const short int
  BisonParser::yycheck_[] =
  {
       2,    31,    58,    63,    59,   137,    63,    61,    50,    51,
      68,   148,    50,    51,   128,   148,    18,   156,   163,     3,
       3,    14,     0,    40,     3,    42,    68,     5,     7,    50,
      68,    24,   164,    75,     3,    95,     5,    75,    94,     3,
      42,    10,    19,    12,    13,    14,    15,    26,    27,    28,
      29,    30,    31,    32,    75,     3,     0,    38,    22,    23,
      39,    19,    22,     3,    33,    34,    47,     3,   213,     5,
     209,   208,    55,    42,    10,   208,    12,    13,    14,    15,
       3,    50,    51,    21,     3,    54,   116,   145,    19,   203,
      67,    22,     7,   147,   226,     3,    55,    33,    34,   141,
     142,    24,   157,   145,   142,     3,    42,   145,   168,   169,
     167,     3,   169,     5,    22,    23,   146,     5,    54,     3,
      12,    13,    14,   125,    12,    13,    14,    50,     3,    51,
       5,    48,     7,     3,    51,   137,   192,   193,    22,    48,
      41,    33,    34,     3,    43,    33,    34,     7,    44,    40,
      43,    26,    27,    28,    29,    30,    31,    32,    48,    51,
      41,    51,   164,    51,   166,    48,    26,    27,    28,    29,
      30,    31,    32,    44,    51,    40,    47,    42,    44,    42,
       3,    40,    40,    52,    46,    49,    47,    44,   218,    40,
      42,    12,     5,    46,    49,    51,    44,    46,    42,    53,
      41,    39,    52,    49,    47,    52,    37,    46,    43,    45,
      52,    41,    52,    40,    48,    52,    48,    41,    43,    41,
       5,    41,     5,    52,   226,    44,    44,    43,    45,    40,
       5,    46,    46,    41,    46,    41,    46,    41,   213,    67,
      42,   169,     4,   153,   155,   208,    12,   154,    24,    23,
      -1,    -1,    -1,   142
  };

  const unsigned char
  BisonParser::yystos_[] =
  {
       0,    19,    22,    57,    58,    59,    76,    77,     3,     3,
      60,     0,    76,    58,    21,   106,    40,    42,    40,    42,
     106,     3,    55,   107,   108,   109,   110,     3,    24,    50,
      80,    81,    94,    98,     3,    78,    79,    23,    59,    60,
      66,    67,    68,     7,    61,    62,    74,     3,   110,   107,
      48,    51,     3,    97,    48,    51,    41,    80,    48,    51,
      43,    44,    40,    48,    41,    67,    43,    44,    51,     5,
      12,    13,    14,    33,    34,    51,    75,   100,   104,   113,
     114,   115,   116,   109,   111,   112,   116,    95,    96,     3,
      10,    15,    42,    50,    51,    54,    84,    85,    86,    89,
      90,    91,    92,    93,    99,   100,   101,   102,   103,   104,
     105,     3,    82,    83,    84,    83,    40,    78,    26,    27,
      28,    29,    30,    31,    32,    39,    60,    63,    64,    65,
      71,    72,    74,    65,    69,    70,    75,    40,    61,   111,
     116,    49,    47,    46,    52,    44,    40,    42,    51,    12,
      84,    75,    46,    49,    38,    47,    53,    44,    52,    46,
      52,    80,    60,    42,    41,    63,    39,    47,    49,    37,
      46,    23,    66,    52,    52,   100,   115,   111,    80,    78,
       3,    86,    87,    88,    99,    43,    52,    85,    90,    89,
      91,    83,    48,    48,    41,    45,    71,    73,    66,    60,
      65,    75,    70,    40,    41,    41,    43,    52,    44,    44,
      84,    84,     5,    44,    43,    41,    45,    63,    40,    87,
      91,    46,    46,    46,    73,     5,    41,    80,    46,    66,
      41,    41
  };

  const unsigned char
  BisonParser::yyr1_[] =
  {
       0,    56,    57,    57,    58,    58,    59,    59,    59,    59,
      60,    61,    61,    62,    63,    63,    64,    64,    65,    65,
      66,    67,    67,    68,    68,    69,    69,    70,    70,    71,
      71,    71,    71,    72,    72,    72,    72,    72,    72,    72,
      73,    73,    74,    75,    76,    76,    77,    78,    78,    79,
      80,    80,    81,    81,    81,    81,    81,    82,    83,    83,
      84,    85,    85,    85,    85,    86,    87,    87,    88,    88,
      88,    89,    89,    90,    90,    91,    91,    91,    92,    92,
      93,    93,    95,    94,    96,    94,    97,    98,    99,    99,
      99,   100,   101,   102,   102,   102,   102,   103,   104,   104,
     104,   104,   104,   105,   106,   106,   106,   106,   107,   107,
     108,   109,   110,   111,   111,   112,   112,   113,   113,   113,
     114,   114,   115,   115,   116
  };

  const unsigned char
  BisonParser::yyr2_[] =
  {
       0,     2,     3,     2,     1,     2,     5,     8,     9,    12,
       1,     1,     3,     1,     1,     2,     5,     6,     1,     3,
       1,     1,     2,     4,     1,     3,     1,     1,     3,     1,
       1,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     4,     7,     2,     1,     3,     1,
       1,     2,     4,     7,     4,     7,     1,     1,     1,     3,
       1,     3,     1,     1,     1,     4,     1,     3,     1,     1,
       1,     1,     3,     1,     3,     1,     5,     3,     1,     3,
       1,     1,     0,     6,     0,     9,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     2,     5,     3,     6,     1,     2,
       4,     1,     2,     1,     3,     1,     1,     1,     1,     3,
       1,     3,     1,     3,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const BisonParser::yytname_[] =
  {
  "$end", "error", "$undefined", "NAME", "FUNNAME", "CONSNAME",
  "DESTNAME", "TYPEPARAMNAME", "IPNAME", "FUNCVARNAME", "BFNAME", "IFUNC",
  "NUMBER", "REALNUMBER", "STRING", "ARG", "T_FUNCTIONAL_PROGRAM",
  "T_IMPORT", "T_LIBRARIES", "T_SCHEME", "T_INTERPRETATION",
  "T_APPLICATION", "T_DATA", "T_CONSTRUCTORS", "T_FUN", "T_FUNCTIONS",
  "T_TSTRING", "T_TINT", "T_TUINT", "T_TSIZE", "T_TFLOAT", "T_TDOUBLE",
  "T_TBOOL", "T_TRUE", "T_FALSE", "T_ARGET", "T_ID", "T_UNION", "T_FARROW",
  "T_TARROW", "'{'", "'}'", "'['", "']'", "','", "':'", "';'", "'*'",
  "'='", "'.'", "'@'", "'('", "')'", "'+'", "'~'", "'%'", "$accept",
  "FunctionalProgram", "DataTypeDefinitionsBlocks",
  "DataTypeDefinitionsBlock", "TypeName", "TypeParametersList",
  "TypeParameterDef", "ConstructorsDefinitionList", "ConstructorDef",
  "ConstructorParametersList", "TypesDefinitionList",
  "TypesDefinitionList2", "TypeDefinition", "TypeDefConstructor",
  "TypeExpression", "AtomType", "BaseType", "TypeExpressionsList",
  "TypeParameter", "ConstructorName", "Scheme", "SchemeBegin",
  "FormalParametersList", "FormalParameter", "DefinitionsList",
  "Definition", "NamedArgument", "NamedArgumentsList", "Term", "AtomTerm",
  "FuncObjectWithParameters", "FuncArgumentList", "FuncParameterName",
  "SequentialTerm", "CompositionTerm", "ConditionTerm", "VariantTerm",
  "FuncObjectName", "ConstructionFun", "$@1", "$@2", "ConstructionFunName",
  "FuncVarName", "ElementaryFunctionName", "Constructor", "Destructor",
  "BuiltInFunction", "TupleElement", "Constant", "BuiltInFunctionName",
  "Application", "DataInit", "OneDataInit", "DataName",
  "InterpFunProgramName", "Data", "OneData", "ValueAtom",
  "ValueConstructor", "ValueComposition", "Value", YY_NULLPTR
  };


  const unsigned short int
  BisonParser::yyrline_[] =
  {
       0,   181,   181,   188,   198,   203,   210,   214,   218,   222,
     229,   233,   238,   245,   252,   257,   264,   268,   274,   279,
     287,   300,   305,   312,   316,   325,   329,   336,   337,   345,
     349,   353,   357,   364,   365,   366,   367,   368,   369,   370,
     374,   379,   385,   387,   392,   397,   405,   413,   418,   425,
     432,   437,   444,   448,   452,   456,   460,   465,   472,   477,
     484,   488,   490,   491,   493,   500,   506,   511,   518,   522,
     523,   528,   529,   536,   537,   544,   545,   549,   556,   557,
     564,   568,   573,   572,   582,   581,   593,   597,   601,   602,
     604,   609,   616,   623,   625,   626,   628,   633,   650,   651,
     652,   653,   657,   665,   672,   676,   680,   684,   691,   696,
     703,   709,   712,   719,   723,   730,   734,   739,   740,   742,
     749,   750,   757,   758,   764
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
       2,     2,     2,     2,     2,     2,     2,    55,     2,     2,
      51,    52,    47,    53,    44,     2,    49,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    45,    46,
       2,    48,     2,     2,    50,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    42,     2,    43,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,    54,     2,     2,     2,
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
      35,    36,    37,    38,    39
    };
    const unsigned int user_token_number_max_ = 294;
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
#line 2402 "parser.tab.cc" // lalr1.cc:1167
