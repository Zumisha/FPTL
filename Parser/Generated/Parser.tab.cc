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

      case 103: // Argument

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 792 "parser.tab.cc" // lalr1.cc:614
        break;

      case 104: // TupleElement

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 803 "parser.tab.cc" // lalr1.cc:614
        break;

      case 105: // Constant

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 814 "parser.tab.cc" // lalr1.cc:614
        break;

      case 106: // BuiltInFunctionName

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 825 "parser.tab.cc" // lalr1.cc:614
        break;

      case 107: // Application

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scApp);
	delete node;

}
#line 836 "parser.tab.cc" // lalr1.cc:614
        break;

      case 108: // DataInit

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 847 "parser.tab.cc" // lalr1.cc:614
        break;

      case 109: // OneDataInit

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 858 "parser.tab.cc" // lalr1.cc:614
        break;

      case 111: // InterpFunProgramName

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 869 "parser.tab.cc" // lalr1.cc:614
        break;

      case 112: // Data

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 880 "parser.tab.cc" // lalr1.cc:614
        break;

      case 113: // OneData

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 891 "parser.tab.cc" // lalr1.cc:614
        break;

      case 114: // ValueAtom

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 902 "parser.tab.cc" // lalr1.cc:614
        break;

      case 115: // ValueConstructor

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 913 "parser.tab.cc" // lalr1.cc:614
        break;

      case 116: // ValueComposition

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 924 "parser.tab.cc" // lalr1.cc:614
        break;

      case 117: // Value

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 935 "parser.tab.cc" // lalr1.cc:614
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
#line 183 "parser.yy" // lalr1.cc:859
    {
			mASTRoot = new FunctionalProgram( (yystack_[2].value.scList), (yystack_[1].value.scFun), (yystack_[0].value.scApp) );
			
			// Возвращаем 0, иначе все дерево будет "срублено" деструктором парсера.
			(yylhs.value.scNode) = 0;
		}
#line 1170 "parser.tab.cc" // lalr1.cc:859
    break;

  case 3:
#line 190 "parser.yy" // lalr1.cc:859
    {
			mASTRoot = new FunctionalProgram( 0, (yystack_[1].value.scFun), (yystack_[0].value.scApp) );
			(yylhs.value.scNode) = 0;
		}
#line 1179 "parser.tab.cc" // lalr1.cc:859
    break;

  case 4:
#line 200 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode(  ASTNode::DataTypeDefinitionsBlocks );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
		}
#line 1188 "parser.tab.cc" // lalr1.cc:859
    break;

  case 5:
#line 205 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scNode) );
		}
#line 1196 "parser.tab.cc" // lalr1.cc:859
    break;

  case 6:
#line 212 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[3].value.scIdent), (yystack_[1].value.scList), 0, 0 );
		}
#line 1204 "parser.tab.cc" // lalr1.cc:859
    break;

  case 7:
#line 216 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[6].value.scIdent), (yystack_[1].value.scList), (yystack_[4].value.scList), 0 );
		}
#line 1212 "parser.tab.cc" // lalr1.cc:859
    break;

  case 8:
#line 220 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[7].value.scIdent), (yystack_[1].value.scList), 0, (yystack_[3].value.scList) );
		}
#line 1220 "parser.tab.cc" // lalr1.cc:859
    break;

  case 9:
#line 224 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[10].value.scIdent), (yystack_[1].value.scList), (yystack_[8].value.scList), (yystack_[3].value.scList) );
		}
#line 1228 "parser.tab.cc" // lalr1.cc:859
    break;

  case 11:
#line 235 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::TypeParametersList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
		}
#line 1237 "parser.tab.cc" // lalr1.cc:859
    break;

  case 12:
#line 240 "parser.yy" // lalr1.cc:859
    {		
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scDef) );
		}
#line 1245 "parser.tab.cc" // lalr1.cc:859
    break;

  case 13:
#line 247 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::TypeParameterDefinition, (yystack_[0].value.scIdent), 0, 0 );
		}
#line 1253 "parser.tab.cc" // lalr1.cc:859
    break;

  case 14:
#line 254 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::ConstructorsDefinitionList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
		}
#line 1262 "parser.tab.cc" // lalr1.cc:859
    break;

  case 15:
#line 259 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scNode) );
		}
#line 1270 "parser.tab.cc" // lalr1.cc:859
    break;

  case 16:
#line 266 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConstructorNode( (yystack_[1].value.scIdent), 0, (yystack_[3].value.scIdent) );
		}
#line 1278 "parser.tab.cc" // lalr1.cc:859
    break;

  case 17:
#line 270 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConstructorNode( (yystack_[1].value.scIdent), (yystack_[5].value.scList), (yystack_[3].value.scIdent) );
		}
#line 1286 "parser.tab.cc" // lalr1.cc:859
    break;

  case 18:
#line 276 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::ConstructorParametersList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scName) );
		}
#line 1295 "parser.tab.cc" // lalr1.cc:859
    break;

  case 19:
#line 281 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scName) );
		}
#line 1303 "parser.tab.cc" // lalr1.cc:859
    break;

  case 20:
#line 289 "parser.yy" // lalr1.cc:859
    {
			if( (yystack_[0].value.scList)->size() > 1 )
			{
				for( ListNode::iterator it = (yystack_[0].value.scList)->begin(); it != (yystack_[0].value.scList)->end(); ++it )
					pSupport->semanticError( ErrTypes::MultipleTypeExpression, static_cast<DefinitionNode*>( *it )->getDefinitionName() );
			}

			(yylhs.value.scList) = (yystack_[0].value.scList);
		}
#line 1317 "parser.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 302 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::TypesDefinitionList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
		}
#line 1326 "parser.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 307 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scDef) );
		}
#line 1334 "parser.tab.cc" // lalr1.cc:859
    break;

  case 23:
#line 314 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::TypeDefinition, (yystack_[3].value.scIdent), (yystack_[1].value.scNode), 0 );
		}
#line 1342 "parser.tab.cc" // lalr1.cc:859
    break;

  case 24:
#line 318 "parser.yy" // lalr1.cc:859
    {
			pSupport->semanticError( ErrTypes::NestedDataDefinition, static_cast<DataNode*>((yystack_[0].value.scNode))->getDataName() );
			delete (yystack_[0].value.scNode);
			(yylhs.value.scDef) = 0;
		}
#line 1352 "parser.tab.cc" // lalr1.cc:859
    break;

  case 25:
#line 327 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::TypeConstructorDefinition, (yystack_[0].value.scIdent), (yystack_[2].value.scList), 0 );
		}
#line 1360 "parser.tab.cc" // lalr1.cc:859
    break;

  case 26:
#line 331 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::TypeConstructorDefinition, (yystack_[0].value.scIdent), 0, 0 );
		}
#line 1368 "parser.tab.cc" // lalr1.cc:859
    break;

  case 28:
#line 339 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::TypeExpression, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1376 "parser.tab.cc" // lalr1.cc:859
    break;

  case 29:
#line 347 "parser.yy" // lalr1.cc:859
    {	
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scToken), NameRefNode::BaseType );
		}
#line 1384 "parser.tab.cc" // lalr1.cc:859
    break;

  case 30:
#line 351 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::Type );
		}
#line 1392 "parser.tab.cc" // lalr1.cc:859
    break;

  case 31:
#line 355 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[3].value.scIdent), NameRefNode::Template, (yystack_[1].value.scList) );
		}
#line 1400 "parser.tab.cc" // lalr1.cc:859
    break;

  case 32:
#line 359 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::TypeParamName );
		}
#line 1408 "parser.tab.cc" // lalr1.cc:859
    break;

  case 40:
#line 376 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::TypeExpressionsList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scName) );
		}
#line 1417 "parser.tab.cc" // lalr1.cc:859
    break;

  case 41:
#line 381 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scName) );
		}
#line 1425 "parser.tab.cc" // lalr1.cc:859
    break;

  case 44:
#line 394 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[3].value.scIdent), (yystack_[1].value.scList), 0 );
			pSupport->popIdent();
		}
#line 1434 "parser.tab.cc" // lalr1.cc:859
    break;

  case 45:
#line 399 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[6].value.scIdent), (yystack_[1].value.scList), (yystack_[4].value.scList) );
			pSupport->popIdent();
		}
#line 1443 "parser.tab.cc" // lalr1.cc:859
    break;

  case 46:
#line 407 "parser.yy" // lalr1.cc:859
    {
			pSupport->pushIdent( (yystack_[0].value.scIdent) );
			(yylhs.value.scIdent) = (yystack_[0].value.scIdent);
		}
#line 1452 "parser.tab.cc" // lalr1.cc:859
    break;

  case 47:
#line 415 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::FormalParametersList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
		}
#line 1461 "parser.tab.cc" // lalr1.cc:859
    break;

  case 48:
#line 420 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scDef) );
		}
#line 1469 "parser.tab.cc" // lalr1.cc:859
    break;

  case 49:
#line 427 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::FunctionParameterDefinition, (yystack_[0].value.scIdent), 0, 0 );
		}
#line 1477 "parser.tab.cc" // lalr1.cc:859
    break;

  case 50:
#line 434 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::DefinitionsList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
		}
#line 1486 "parser.tab.cc" // lalr1.cc:859
    break;

  case 51:
#line 439 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scNode) );
		}
#line 1494 "parser.tab.cc" // lalr1.cc:859
    break;

  case 52:
#line 446 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::Definition, pSupport->getTopIdent(), (yystack_[1].value.scNode), 0 );
		}
#line 1502 "parser.tab.cc" // lalr1.cc:859
    break;

  case 53:
#line 450 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::Definition, pSupport->getTopIdent(), (yystack_[1].value.scNode), (yystack_[4].value.scList) );
		}
#line 1510 "parser.tab.cc" // lalr1.cc:859
    break;

  case 54:
#line 454 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::Definition, (yystack_[3].value.scIdent), (yystack_[1].value.scNode), 0 );
		}
#line 1518 "parser.tab.cc" // lalr1.cc:859
    break;

  case 55:
#line 458 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::Definition, (yystack_[6].value.scIdent), (yystack_[1].value.scNode), (yystack_[4].value.scList) );
		}
#line 1526 "parser.tab.cc" // lalr1.cc:859
    break;

  case 56:
#line 462 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scFun); }
#line 1532 "parser.tab.cc" // lalr1.cc:859
    break;

  case 57:
#line 467 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::NamedArgument);
		}
#line 1540 "parser.tab.cc" // lalr1.cc:859
    break;

  case 58:
#line 474 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::NamedArgumentsList );
			(yylhs.value.scList) -> addElement( (yystack_[0].value.scName) );
		}
#line 1549 "parser.tab.cc" // lalr1.cc:859
    break;

  case 59:
#line 479 "parser.yy" // lalr1.cc:859
    {
		   (yylhs.value.scList) = (yystack_[0].value.scList) -> addElement( (yystack_[2].value.scName) );
		}
#line 1557 "parser.tab.cc" // lalr1.cc:859
    break;

  case 61:
#line 490 "parser.yy" // lalr1.cc:859
    {	(yylhs.value.scNode) = (yystack_[1].value.scNode); }
#line 1563 "parser.tab.cc" // lalr1.cc:859
    break;

  case 63:
#line 493 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1569 "parser.tab.cc" // lalr1.cc:859
    break;

  case 64:
#line 495 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new NameRefNode( pSupport->getTopIdent(), ASTNode::FuncObjectName );
		}
#line 1577 "parser.tab.cc" // lalr1.cc:859
    break;

  case 65:
#line 502 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[3].value.scIdent), NameRefNode::FuncObjectWithParameters, (yystack_[1].value.scList) );
		}
#line 1585 "parser.tab.cc" // lalr1.cc:859
    break;

  case 66:
#line 508 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::FuncArgumentsList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
		}
#line 1594 "parser.tab.cc" // lalr1.cc:859
    break;

  case 67:
#line 513 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scNode) );
		}
#line 1602 "parser.tab.cc" // lalr1.cc:859
    break;

  case 68:
#line 520 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::FuncParameterName );
		}
#line 1610 "parser.tab.cc" // lalr1.cc:859
    break;

  case 70:
#line 525 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1616 "parser.tab.cc" // lalr1.cc:859
    break;

  case 72:
#line 531 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::SequentialTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1624 "parser.tab.cc" // lalr1.cc:859
    break;

  case 74:
#line 539 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::CompositionTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1632 "parser.tab.cc" // lalr1.cc:859
    break;

  case 76:
#line 547 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ConditionTerm, (yystack_[4].value.scNode), (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1640 "parser.tab.cc" // lalr1.cc:859
    break;

  case 77:
#line 551 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ConditionTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1648 "parser.tab.cc" // lalr1.cc:859
    break;

  case 79:
#line 559 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::VariantTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1656 "parser.tab.cc" // lalr1.cc:859
    break;

  case 80:
#line 566 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::FuncObjectName );
		}
#line 1664 "parser.tab.cc" // lalr1.cc:859
    break;

  case 82:
#line 574 "parser.yy" // lalr1.cc:859
    {
			pSupport->pushIdent( (yystack_[0].value.scIdent) );
		}
#line 1672 "parser.tab.cc" // lalr1.cc:859
    break;

  case 83:
#line 578 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[4].value.scIdent), (yystack_[1].value.scList), 0 );
			pSupport->popIdent();
		}
#line 1681 "parser.tab.cc" // lalr1.cc:859
    break;

  case 84:
#line 583 "parser.yy" // lalr1.cc:859
    {
			pSupport->pushIdent( (yystack_[0].value.scIdent) );
		}
#line 1689 "parser.tab.cc" // lalr1.cc:859
    break;

  case 85:
#line 587 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[7].value.scIdent), (yystack_[1].value.scList), (yystack_[4].value.scList) );
			pSupport->popIdent();
		}
#line 1698 "parser.tab.cc" // lalr1.cc:859
    break;

  case 89:
#line 604 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1704 "parser.tab.cc" // lalr1.cc:859
    break;

  case 90:
#line 606 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1710 "parser.tab.cc" // lalr1.cc:859
    break;

  case 91:
#line 611 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::ConstructorName );
		}
#line 1718 "parser.tab.cc" // lalr1.cc:859
    break;

  case 92:
#line 618 "parser.yy" // lalr1.cc:859
    {	
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::DestructorName );
		}
#line 1726 "parser.tab.cc" // lalr1.cc:859
    break;

  case 93:
#line 625 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1732 "parser.tab.cc" // lalr1.cc:859
    break;

  case 98:
#line 637 "parser.yy" // lalr1.cc:859
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
#line 1750 "parser.tab.cc" // lalr1.cc:859
    break;

  case 102:
#line 657 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConstantNode( ASTNode::TrueValue, (yystack_[0].value.scToken) );
		}
#line 1758 "parser.tab.cc" // lalr1.cc:859
    break;

  case 103:
#line 661 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConstantNode( ASTNode::FalseValue, (yystack_[0].value.scToken) );
		}
#line 1766 "parser.tab.cc" // lalr1.cc:859
    break;

  case 104:
#line 669 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::BuildInFunction );
		}
#line 1774 "parser.tab.cc" // lalr1.cc:859
    break;

  case 105:
#line 676 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[0].value.scName), 0, 0 );
		}
#line 1782 "parser.tab.cc" // lalr1.cc:859
    break;

  case 106:
#line 680 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[3].value.scName), (yystack_[1].value.scNode), 0 );
		}
#line 1790 "parser.tab.cc" // lalr1.cc:859
    break;

  case 107:
#line 684 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[0].value.scName), 0, (yystack_[1].value.scList) ); 
		}
#line 1798 "parser.tab.cc" // lalr1.cc:859
    break;

  case 108:
#line 688 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[3].value.scName), (yystack_[1].value.scNode), (yystack_[4].value.scList) );
		}
#line 1806 "parser.tab.cc" // lalr1.cc:859
    break;

  case 109:
#line 695 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::InputVarDefinitionList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
		}
#line 1815 "parser.tab.cc" // lalr1.cc:859
    break;

  case 110:
#line 700 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scDef) );
		}
#line 1823 "parser.tab.cc" // lalr1.cc:859
    break;

  case 111:
#line 707 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::InputVarDefinition, (yystack_[3].value.scIdent), (yystack_[1].value.scNode), 0 );
		}
#line 1831 "parser.tab.cc" // lalr1.cc:859
    break;

  case 113:
#line 716 "parser.yy" // lalr1.cc:859
    { 
			(yylhs.value.scName) = new NameRefNode((yystack_[0].value.scIdent), ASTNode::RunningSchemeName);
		}
#line 1839 "parser.tab.cc" // lalr1.cc:859
    break;

  case 114:
#line 723 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = (yystack_[0].value.scNode);
		}
#line 1847 "parser.tab.cc" // lalr1.cc:859
    break;

  case 115:
#line 727 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode(ASTNode::InputVarList, (yystack_[2].value.scNode), (yystack_[0].value.scNode));
		}
#line 1855 "parser.tab.cc" // lalr1.cc:859
    break;

  case 116:
#line 734 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new NameRefNode( (yystack_[0].value.scIdent), ASTNode::InputVarName );
		}
#line 1863 "parser.tab.cc" // lalr1.cc:859
    break;

  case 119:
#line 744 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1869 "parser.tab.cc" // lalr1.cc:859
    break;

  case 120:
#line 746 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = (yystack_[1].value.scNode);
		}
#line 1877 "parser.tab.cc" // lalr1.cc:859
    break;

  case 122:
#line 754 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ValueConstructor, (yystack_[2].value.scNode), (yystack_[0].value.scName) );
		}
#line 1885 "parser.tab.cc" // lalr1.cc:859
    break;

  case 124:
#line 762 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ValueComposition, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1893 "parser.tab.cc" // lalr1.cc:859
    break;


#line 1897 "parser.tab.cc" // lalr1.cc:859
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


  const short int BisonParser::yypact_ninf_ = -147;

  const signed char BisonParser::yytable_ninf_ = -85;

  const short int
  BisonParser::yypact_[] =
  {
      42,    22,    36,    60,    26,    43,    62,   -11,  -147,  -147,
      89,  -147,    62,  -147,    16,  -147,    17,    63,    33,    69,
    -147,  -147,    81,    37,    85,    58,    56,  -147,   111,    29,
      74,    17,  -147,    47,  -147,    79,    86,    92,  -147,    87,
      93,  -147,    24,  -147,    90,    95,  -147,  -147,    91,  -147,
     107,    45,  -147,   101,    39,   141,  -147,  -147,    39,   141,
     108,    63,   142,   172,  -147,  -147,   110,    69,    45,  -147,
    -147,  -147,  -147,  -147,  -147,   107,  -147,  -147,  -147,   102,
     105,  -147,   114,  -147,   104,   109,  -147,   117,   112,   115,
    -147,  -147,   147,  -147,    39,   156,   116,  -147,  -147,   127,
      44,  -147,   125,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,   120,   128,   137,   132,    17,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,    36,   143,   146,   142,
     149,   144,  -147,  -147,   145,   153,   150,  -147,    40,  -147,
     140,   160,   156,   107,  -147,  -147,    45,    17,    63,   113,
     152,   161,  -147,  -147,    39,    39,    39,    39,   141,   166,
    -147,   167,   175,   148,   179,    24,  -147,    36,   179,   156,
     172,  -147,   157,   176,  -147,  -147,  -147,  -147,  -147,   177,
     178,   115,  -147,   168,   180,  -147,  -147,  -147,  -147,    55,
     127,  -147,  -147,    39,    39,  -147,   214,   182,   184,   181,
     183,  -147,  -147,  -147,   142,  -147,  -147,   189,  -147,   113,
      39,   185,   186,   187,   179,  -147,  -147,   218,   193,    17,
    -147,  -147,  -147,  -147,  -147,  -147,   190,    24,   194,  -147,
     196,  -147,  -147
  };

  const unsigned char
  BisonParser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     4,     0,     0,    46,    10,
       0,     1,     0,     5,     0,     3,     0,     0,     0,     0,
       2,   112,     0,     0,   109,     0,   105,    87,     0,     0,
       0,    50,    56,     0,    49,     0,    47,     0,    24,     0,
       0,    20,    21,    42,     0,    11,    13,   113,   107,   110,
       0,     0,    86,    82,     0,     0,    44,    51,     0,     0,
       0,     0,     0,     0,     6,    22,     0,     0,     0,    43,
      99,   100,   101,   102,   103,     0,    91,   119,   118,   121,
     123,   125,     0,   116,     0,   114,   117,     0,     0,    80,
     104,    97,     0,    64,     0,     0,     0,    71,    81,    73,
      75,    78,    60,    63,    62,    89,    90,    88,    95,    94,
      96,    93,    57,    58,     0,     0,     0,     0,    48,    33,
      34,    35,    36,    37,    38,    39,     0,    30,     0,    14,
       0,    18,    29,    32,     0,    27,     0,    26,     0,    12,
       0,     0,     0,     0,   111,   106,     0,     0,     0,     0,
       0,     0,    92,    52,     0,     0,     0,     0,     0,     0,
      54,     0,     0,     0,     0,     0,    15,     0,     0,     0,
       0,    23,     0,     0,   108,   120,   122,   124,   115,     0,
       0,    68,    70,     0,    66,    69,    98,    61,    72,    77,
      74,    79,    59,     0,     0,    45,     0,    40,     0,     0,
       0,    19,    25,    28,     0,     7,    83,     0,    65,     0,
       0,     0,     0,     0,     0,    31,     8,     0,     0,     0,
      67,    76,    53,    55,    16,    41,     0,     0,     0,    17,
       0,    85,     9
  };

  const short int
  BisonParser::yypgoto_[] =
  {
    -147,  -147,   225,    23,    -2,   171,  -147,  -118,  -147,   -57,
    -133,   197,  -147,  -147,    70,  -146,  -147,    27,     2,   -60,
     238,  -147,   -51,  -147,   -30,  -147,  -147,   -55,   -56,    94,
    -135,    34,  -147,    88,    96,  -140,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,  -134,   -42,  -147,  -147,  -147,  -147,   -38,
    -147,   233,   222,  -147,    10,   224,   -61,  -147,  -147,  -147,
     106,   -28
  };

  const short int
  BisonParser::yydefgoto_[] =
  {
      -1,     3,     4,    38,   127,    44,    45,   128,   129,   130,
      40,    41,    42,   135,   136,   131,   132,   198,   133,    76,
       6,     7,    35,    36,    30,    31,   113,   114,    96,    97,
      98,   183,   184,    99,   100,   101,   102,   103,    32,    87,
      88,    53,    33,   104,   105,   106,   107,   108,   109,   110,
     111,    15,    23,    24,    83,    26,    84,    85,    79,    80,
      81,    86
  };

  const short int
  BisonParser::yytable_[] =
  {
      10,    57,   115,   137,   116,   173,   134,   140,    77,    77,
     118,   166,    78,    78,   182,   185,    39,   191,   197,    21,
      27,    46,    82,     5,    25,     8,    77,     9,     5,    16,
      78,    17,   199,    77,    25,   152,     9,    78,   151,     9,
      39,    28,    89,     9,    69,     1,     2,   141,    21,    90,
      69,    70,    71,    72,    91,     2,    37,    70,    71,    72,
      11,     1,     2,   172,     2,     2,    34,    29,   197,    46,
     221,    22,    73,    74,   182,   185,    43,    54,    73,    74,
      55,    92,   155,    14,    47,   178,   218,   162,    21,    93,
      94,   156,    22,    95,   230,    58,    75,   180,    59,   210,
     176,    77,   156,   192,    77,    78,    50,    51,    78,   202,
     137,   201,    69,   134,    52,    56,   181,   179,    69,    70,
      71,    72,    60,    90,   163,    70,    71,    72,    91,    18,
      61,    19,    62,    66,    64,    63,    39,   211,   212,    67,
      73,    74,    68,   -84,   112,     9,    73,    74,   117,    43,
     138,   142,   143,   146,   148,    92,   145,   147,    75,   150,
     144,    69,   153,    39,   158,   200,   149,    95,   119,   120,
     121,   122,   123,   124,   125,     9,   154,    69,   157,    43,
     159,   126,     9,   160,   161,   164,    43,   165,   167,   228,
     170,   168,   174,   196,   169,   186,   171,   204,   119,   120,
     121,   122,   123,   124,   125,   119,   120,   121,   122,   123,
     124,   125,   175,   187,   193,   194,   195,   205,   206,   213,
     208,   207,   216,   226,   209,    39,   214,   215,   217,   219,
      13,   222,   223,   224,   227,   231,   229,   232,   139,    65,
     203,   225,    12,   220,   190,    20,    49,    48,   188,   177,
       0,   189
  };

  const short int
  BisonParser::yycheck_[] =
  {
       2,    31,    58,    63,    59,   138,    63,    68,    50,    51,
      61,   129,    50,    51,   149,   149,    18,   157,   164,     3,
       3,    19,    50,     0,    14,     3,    68,     3,     5,    40,
      68,    42,   165,    75,    24,    95,     3,    75,    94,     3,
      42,    24,     3,     3,     5,    19,    22,    75,     3,    10,
       5,    12,    13,    14,    15,    22,    23,    12,    13,    14,
       0,    19,    22,    23,    22,    22,     3,    50,   214,    67,
     210,    55,    33,    34,   209,   209,     7,    48,    33,    34,
      51,    42,    38,    21,     3,   146,   204,   117,     3,    50,
      51,    47,    55,    54,   227,    48,    51,   148,    51,    44,
     142,   143,    47,   158,   146,   143,    48,    51,   146,   169,
     170,   168,     5,   170,     3,    41,     3,   147,     5,    12,
      13,    14,    43,    10,   126,    12,    13,    14,    15,    40,
      44,    42,    40,    43,    41,    48,   138,   193,   194,    44,
      33,    34,    51,    42,     3,     3,    33,    34,    40,     7,
      40,    49,    47,    44,    42,    42,    52,    40,    51,    12,
      46,     5,    46,   165,    44,   167,    51,    54,    26,    27,
      28,    29,    30,    31,    32,     3,    49,     5,    53,     7,
      52,    39,     3,    46,    52,    42,     7,    41,    39,   219,
      37,    47,    52,    45,    49,    43,    46,    40,    26,    27,
      28,    29,    30,    31,    32,    26,    27,    28,    29,    30,
      31,    32,    52,    52,    48,    48,    41,    41,    41,     5,
      52,    43,    41,     5,    44,   227,    44,    43,    45,    40,
       5,    46,    46,    46,    41,    41,    46,    41,    67,    42,
     170,   214,     4,   209,   156,    12,    24,    23,   154,   143,
      -1,   155
  };

  const unsigned char
  BisonParser::yystos_[] =
  {
       0,    19,    22,    57,    58,    59,    76,    77,     3,     3,
      60,     0,    76,    58,    21,   107,    40,    42,    40,    42,
     107,     3,    55,   108,   109,   110,   111,     3,    24,    50,
      80,    81,    94,    98,     3,    78,    79,    23,    59,    60,
      66,    67,    68,     7,    61,    62,    74,     3,   111,   108,
      48,    51,     3,    97,    48,    51,    41,    80,    48,    51,
      43,    44,    40,    48,    41,    67,    43,    44,    51,     5,
      12,    13,    14,    33,    34,    51,    75,   100,   105,   114,
     115,   116,   117,   110,   112,   113,   117,    95,    96,     3,
      10,    15,    42,    50,    51,    54,    84,    85,    86,    89,
      90,    91,    92,    93,    99,   100,   101,   102,   103,   104,
     105,   106,     3,    82,    83,    84,    83,    40,    78,    26,
      27,    28,    29,    30,    31,    32,    39,    60,    63,    64,
      65,    71,    72,    74,    65,    69,    70,    75,    40,    61,
     112,   117,    49,    47,    46,    52,    44,    40,    42,    51,
      12,    84,    75,    46,    49,    38,    47,    53,    44,    52,
      46,    52,    80,    60,    42,    41,    63,    39,    47,    49,
      37,    46,    23,    66,    52,    52,   100,   116,   112,    80,
      78,     3,    86,    87,    88,    99,    43,    52,    85,    90,
      89,    91,    83,    48,    48,    41,    45,    71,    73,    66,
      60,    65,    75,    70,    40,    41,    41,    43,    52,    44,
      44,    84,    84,     5,    44,    43,    41,    45,    63,    40,
      87,    91,    46,    46,    46,    73,     5,    41,    80,    46,
      66,    41,    41
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
      99,   100,   101,   102,   102,   102,   102,   103,   104,   105,
     105,   105,   105,   105,   106,   107,   107,   107,   107,   108,
     108,   109,   110,   111,   112,   112,   113,   113,   114,   114,
     114,   115,   115,   116,   116,   117
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
       1,     1,     2,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     2,     5,     3,     6,     1,
       2,     4,     1,     2,     1,     3,     1,     1,     1,     1,
       3,     1,     3,     1,     3,     1
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
  "BuiltInFunction", "Argument", "TupleElement", "Constant",
  "BuiltInFunctionName", "Application", "DataInit", "OneDataInit",
  "DataName", "InterpFunProgramName", "Data", "OneData", "ValueAtom",
  "ValueConstructor", "ValueComposition", "Value", YY_NULLPTR
  };


  const unsigned short int
  BisonParser::yyrline_[] =
  {
       0,   182,   182,   189,   199,   204,   211,   215,   219,   223,
     230,   234,   239,   246,   253,   258,   265,   269,   275,   280,
     288,   301,   306,   313,   317,   326,   330,   337,   338,   346,
     350,   354,   358,   365,   366,   367,   368,   369,   370,   371,
     375,   380,   386,   388,   393,   398,   406,   414,   419,   426,
     433,   438,   445,   449,   453,   457,   461,   466,   473,   478,
     485,   489,   491,   492,   494,   501,   507,   512,   519,   523,
     524,   529,   530,   537,   538,   545,   546,   550,   557,   558,
     565,   569,   574,   573,   583,   582,   594,   598,   602,   603,
     605,   610,   617,   624,   626,   627,   628,   632,   636,   653,
     654,   655,   656,   660,   668,   675,   679,   683,   687,   694,
     699,   706,   712,   715,   722,   726,   733,   737,   742,   743,
     745,   752,   753,   760,   761,   767
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
#line 2407 "parser.tab.cc" // lalr1.cc:1167
