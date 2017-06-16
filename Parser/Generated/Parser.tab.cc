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

      case 81: // NamedArgument

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 594 "parser.tab.cc" // lalr1.cc:614
        break;

      case 82: // NamedArgumentsList

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 605 "parser.tab.cc" // lalr1.cc:614
        break;

      case 83: // Term

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 616 "parser.tab.cc" // lalr1.cc:614
        break;

      case 84: // AtomTerm

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 627 "parser.tab.cc" // lalr1.cc:614
        break;

      case 85: // FuncObjectWithParameters

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 638 "parser.tab.cc" // lalr1.cc:614
        break;

      case 86: // FuncArgumentList

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 649 "parser.tab.cc" // lalr1.cc:614
        break;

      case 87: // FuncParameterName

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 660 "parser.tab.cc" // lalr1.cc:614
        break;

      case 88: // SequentialTerm

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 671 "parser.tab.cc" // lalr1.cc:614
        break;

      case 89: // CompositionTerm

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 682 "parser.tab.cc" // lalr1.cc:614
        break;

      case 90: // ConditionTerm

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 693 "parser.tab.cc" // lalr1.cc:614
        break;

      case 91: // VariantTerm

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 704 "parser.tab.cc" // lalr1.cc:614
        break;

      case 92: // FuncObjectName

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 715 "parser.tab.cc" // lalr1.cc:614
        break;

      case 93: // ConstructionFun

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scFun);
	delete node;

}
#line 726 "parser.tab.cc" // lalr1.cc:614
        break;

      case 98: // ElementaryFunctionName

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 737 "parser.tab.cc" // lalr1.cc:614
        break;

      case 99: // Constructor

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 748 "parser.tab.cc" // lalr1.cc:614
        break;

      case 100: // Destructor

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 759 "parser.tab.cc" // lalr1.cc:614
        break;

      case 101: // BuiltInFunction

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 770 "parser.tab.cc" // lalr1.cc:614
        break;

      case 102: // TupleElement

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 781 "parser.tab.cc" // lalr1.cc:614
        break;

      case 103: // Constant

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 792 "parser.tab.cc" // lalr1.cc:614
        break;

      case 104: // BuiltInFunctionName

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 803 "parser.tab.cc" // lalr1.cc:614
        break;

      case 105: // Application

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scApp);
	delete node;

}
#line 814 "parser.tab.cc" // lalr1.cc:614
        break;

      case 106: // DataInit

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 825 "parser.tab.cc" // lalr1.cc:614
        break;

      case 107: // OneDataInit

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 836 "parser.tab.cc" // lalr1.cc:614
        break;

      case 109: // InterpFunProgramName

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 847 "parser.tab.cc" // lalr1.cc:614
        break;

      case 110: // Data

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 858 "parser.tab.cc" // lalr1.cc:614
        break;

      case 111: // OneData

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 869 "parser.tab.cc" // lalr1.cc:614
        break;

      case 112: // ValueAtom

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 880 "parser.tab.cc" // lalr1.cc:614
        break;

      case 113: // ValueConstructor

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 891 "parser.tab.cc" // lalr1.cc:614
        break;

      case 114: // ValueComposition

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 902 "parser.tab.cc" // lalr1.cc:614
        break;

      case 115: // Value

#line 56 "parser.yy" // lalr1.cc:614
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 913 "parser.tab.cc" // lalr1.cc:614
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
#line 181 "parser.yy" // lalr1.cc:859
    {
			mASTRoot = new FunctionalProgram( (yystack_[2].value.scList), (yystack_[1].value.scFun), (yystack_[0].value.scApp) );
			
			// Возвращаем 0, иначе все дерево будет "срублено" деструктором парсера.
			(yylhs.value.scNode) = 0;
		}
#line 1148 "parser.tab.cc" // lalr1.cc:859
    break;

  case 3:
#line 188 "parser.yy" // lalr1.cc:859
    {
			mASTRoot = new FunctionalProgram( 0, (yystack_[1].value.scFun), (yystack_[0].value.scApp) );
			(yylhs.value.scNode) = 0;
		}
#line 1157 "parser.tab.cc" // lalr1.cc:859
    break;

  case 4:
#line 198 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode(  ASTNode::DataTypeDefinitionsBlocks );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
		}
#line 1166 "parser.tab.cc" // lalr1.cc:859
    break;

  case 5:
#line 203 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scNode) );
		}
#line 1174 "parser.tab.cc" // lalr1.cc:859
    break;

  case 6:
#line 210 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[3].value.scIdent), (yystack_[1].value.scList), 0, 0 );
		}
#line 1182 "parser.tab.cc" // lalr1.cc:859
    break;

  case 7:
#line 214 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[6].value.scIdent), (yystack_[1].value.scList), (yystack_[4].value.scList), 0 );
		}
#line 1190 "parser.tab.cc" // lalr1.cc:859
    break;

  case 8:
#line 218 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[7].value.scIdent), (yystack_[1].value.scList), 0, (yystack_[3].value.scList) );
		}
#line 1198 "parser.tab.cc" // lalr1.cc:859
    break;

  case 9:
#line 222 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[10].value.scIdent), (yystack_[1].value.scList), (yystack_[8].value.scList), (yystack_[3].value.scList) );
		}
#line 1206 "parser.tab.cc" // lalr1.cc:859
    break;

  case 11:
#line 233 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::TypeParametersList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
		}
#line 1215 "parser.tab.cc" // lalr1.cc:859
    break;

  case 12:
#line 238 "parser.yy" // lalr1.cc:859
    {		
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scDef) );
		}
#line 1223 "parser.tab.cc" // lalr1.cc:859
    break;

  case 13:
#line 245 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::TypeParameterDefinition, (yystack_[0].value.scIdent), 0, 0 );
		}
#line 1231 "parser.tab.cc" // lalr1.cc:859
    break;

  case 14:
#line 252 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::ConstructorsDefinitionList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
		}
#line 1240 "parser.tab.cc" // lalr1.cc:859
    break;

  case 15:
#line 257 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scNode) );
		}
#line 1248 "parser.tab.cc" // lalr1.cc:859
    break;

  case 16:
#line 264 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConstructorNode( (yystack_[1].value.scIdent), 0, (yystack_[3].value.scIdent) );
		}
#line 1256 "parser.tab.cc" // lalr1.cc:859
    break;

  case 17:
#line 268 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConstructorNode( (yystack_[1].value.scIdent), (yystack_[5].value.scList), (yystack_[3].value.scIdent) );
		}
#line 1264 "parser.tab.cc" // lalr1.cc:859
    break;

  case 18:
#line 274 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::ConstructorParametersList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scName) );
		}
#line 1273 "parser.tab.cc" // lalr1.cc:859
    break;

  case 19:
#line 279 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scName) );
		}
#line 1281 "parser.tab.cc" // lalr1.cc:859
    break;

  case 20:
#line 287 "parser.yy" // lalr1.cc:859
    {
			if( (yystack_[0].value.scList)->size() > 1 )
			{
				for( ListNode::iterator it = (yystack_[0].value.scList)->begin(); it != (yystack_[0].value.scList)->end(); ++it )
					pSupport->semanticError( ErrTypes::MultipleTypeExpression, static_cast<DefinitionNode*>( *it )->getDefinitionName() );
			}

			(yylhs.value.scList) = (yystack_[0].value.scList);
		}
#line 1295 "parser.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 300 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::TypesDefinitionList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
		}
#line 1304 "parser.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 305 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scDef) );
		}
#line 1312 "parser.tab.cc" // lalr1.cc:859
    break;

  case 23:
#line 312 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::TypeDefinition, (yystack_[3].value.scIdent), (yystack_[1].value.scNode), 0 );
		}
#line 1320 "parser.tab.cc" // lalr1.cc:859
    break;

  case 24:
#line 316 "parser.yy" // lalr1.cc:859
    {
			pSupport->semanticError( ErrTypes::NestedDataDefinition, static_cast<DataNode*>((yystack_[0].value.scNode))->getDataName() );
			delete (yystack_[0].value.scNode);
			(yylhs.value.scDef) = 0;
		}
#line 1330 "parser.tab.cc" // lalr1.cc:859
    break;

  case 25:
#line 325 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::TypeConstructorDefinition, (yystack_[0].value.scIdent), (yystack_[2].value.scList), 0 );
		}
#line 1338 "parser.tab.cc" // lalr1.cc:859
    break;

  case 26:
#line 329 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::TypeConstructorDefinition, (yystack_[0].value.scIdent), 0, 0 );
		}
#line 1346 "parser.tab.cc" // lalr1.cc:859
    break;

  case 28:
#line 337 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::TypeExpression, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1354 "parser.tab.cc" // lalr1.cc:859
    break;

  case 29:
#line 345 "parser.yy" // lalr1.cc:859
    {	
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scToken), NameRefNode::BaseType );
		}
#line 1362 "parser.tab.cc" // lalr1.cc:859
    break;

  case 30:
#line 349 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::Type );
		}
#line 1370 "parser.tab.cc" // lalr1.cc:859
    break;

  case 31:
#line 353 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[3].value.scIdent), NameRefNode::Template, (yystack_[1].value.scList) );
		}
#line 1378 "parser.tab.cc" // lalr1.cc:859
    break;

  case 32:
#line 357 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::TypeParamName );
		}
#line 1386 "parser.tab.cc" // lalr1.cc:859
    break;

  case 40:
#line 374 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::TypeExpressionsList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scName) );
		}
#line 1395 "parser.tab.cc" // lalr1.cc:859
    break;

  case 41:
#line 379 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scName) );
		}
#line 1403 "parser.tab.cc" // lalr1.cc:859
    break;

  case 44:
#line 392 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[3].value.scIdent), (yystack_[1].value.scList), 0 );
			pSupport->popIdent();
		}
#line 1412 "parser.tab.cc" // lalr1.cc:859
    break;

  case 45:
#line 397 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[6].value.scIdent), (yystack_[1].value.scList), (yystack_[4].value.scList) );
			pSupport->popIdent();
		}
#line 1421 "parser.tab.cc" // lalr1.cc:859
    break;

  case 46:
#line 405 "parser.yy" // lalr1.cc:859
    {
			pSupport->pushIdent( (yystack_[0].value.scIdent) );
			(yylhs.value.scIdent) = (yystack_[0].value.scIdent);
		}
#line 1430 "parser.tab.cc" // lalr1.cc:859
    break;

  case 47:
#line 413 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::FormalParametersList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
		}
#line 1439 "parser.tab.cc" // lalr1.cc:859
    break;

  case 48:
#line 418 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scDef) );
		}
#line 1447 "parser.tab.cc" // lalr1.cc:859
    break;

  case 49:
#line 425 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::FunctionParameterDefinition, (yystack_[0].value.scIdent), 0, 0 );
		}
#line 1455 "parser.tab.cc" // lalr1.cc:859
    break;

  case 50:
#line 432 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::DefinitionsList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
		}
#line 1464 "parser.tab.cc" // lalr1.cc:859
    break;

  case 51:
#line 437 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scNode) );
		}
#line 1472 "parser.tab.cc" // lalr1.cc:859
    break;

  case 52:
#line 444 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::Definition, pSupport->getTopIdent(), (yystack_[1].value.scNode), 0 );
		}
#line 1480 "parser.tab.cc" // lalr1.cc:859
    break;

  case 53:
#line 448 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::Definition, pSupport->getTopIdent(), (yystack_[1].value.scNode), (yystack_[4].value.scList) );
		}
#line 1488 "parser.tab.cc" // lalr1.cc:859
    break;

  case 54:
#line 452 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::Definition, (yystack_[3].value.scIdent), (yystack_[1].value.scNode), 0 );
		}
#line 1496 "parser.tab.cc" // lalr1.cc:859
    break;

  case 55:
#line 456 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::Definition, (yystack_[6].value.scIdent), (yystack_[1].value.scNode), (yystack_[4].value.scList) );
		}
#line 1504 "parser.tab.cc" // lalr1.cc:859
    break;

  case 56:
#line 460 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scFun); }
#line 1510 "parser.tab.cc" // lalr1.cc:859
    break;

  case 57:
#line 465 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::NamedArgument);
		}
#line 1518 "parser.tab.cc" // lalr1.cc:859
    break;

  case 58:
#line 472 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::NamedArgumentsList );
			(yylhs.value.scList) -> addElement( (yystack_[0].value.scName) );
		}
#line 1527 "parser.tab.cc" // lalr1.cc:859
    break;

  case 59:
#line 477 "parser.yy" // lalr1.cc:859
    {
		   (yylhs.value.scList) = (yystack_[0].value.scList) -> addElement( (yystack_[2].value.scName) );
		}
#line 1535 "parser.tab.cc" // lalr1.cc:859
    break;

  case 61:
#line 488 "parser.yy" // lalr1.cc:859
    {	(yylhs.value.scNode) = (yystack_[1].value.scNode); }
#line 1541 "parser.tab.cc" // lalr1.cc:859
    break;

  case 63:
#line 491 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1547 "parser.tab.cc" // lalr1.cc:859
    break;

  case 64:
#line 493 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new NameRefNode( pSupport->getTopIdent(), ASTNode::FuncObjectName );
		}
#line 1555 "parser.tab.cc" // lalr1.cc:859
    break;

  case 65:
#line 500 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[3].value.scIdent), NameRefNode::FuncObjectWithParameters, (yystack_[1].value.scList) );
		}
#line 1563 "parser.tab.cc" // lalr1.cc:859
    break;

  case 66:
#line 506 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::FuncArgumentsList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
		}
#line 1572 "parser.tab.cc" // lalr1.cc:859
    break;

  case 67:
#line 511 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scNode) );
		}
#line 1580 "parser.tab.cc" // lalr1.cc:859
    break;

  case 68:
#line 518 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::FuncParameterName );
		}
#line 1588 "parser.tab.cc" // lalr1.cc:859
    break;

  case 70:
#line 523 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1594 "parser.tab.cc" // lalr1.cc:859
    break;

  case 72:
#line 529 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::SequentialTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1602 "parser.tab.cc" // lalr1.cc:859
    break;

  case 74:
#line 537 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::CompositionTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1610 "parser.tab.cc" // lalr1.cc:859
    break;

  case 76:
#line 545 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ConditionTerm, (yystack_[4].value.scNode), (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1618 "parser.tab.cc" // lalr1.cc:859
    break;

  case 77:
#line 549 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ConditionTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1626 "parser.tab.cc" // lalr1.cc:859
    break;

  case 79:
#line 557 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::VariantTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1634 "parser.tab.cc" // lalr1.cc:859
    break;

  case 80:
#line 564 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::FuncObjectName );
		}
#line 1642 "parser.tab.cc" // lalr1.cc:859
    break;

  case 82:
#line 572 "parser.yy" // lalr1.cc:859
    {
			pSupport->pushIdent( (yystack_[0].value.scIdent) );
		}
#line 1650 "parser.tab.cc" // lalr1.cc:859
    break;

  case 83:
#line 576 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[4].value.scIdent), (yystack_[1].value.scList), 0 );
			pSupport->popIdent();
		}
#line 1659 "parser.tab.cc" // lalr1.cc:859
    break;

  case 84:
#line 581 "parser.yy" // lalr1.cc:859
    {
			pSupport->pushIdent( (yystack_[0].value.scIdent) );
		}
#line 1667 "parser.tab.cc" // lalr1.cc:859
    break;

  case 85:
#line 585 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[7].value.scIdent), (yystack_[1].value.scList), (yystack_[4].value.scList) );
			pSupport->popIdent();
		}
#line 1676 "parser.tab.cc" // lalr1.cc:859
    break;

  case 89:
#line 602 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1682 "parser.tab.cc" // lalr1.cc:859
    break;

  case 90:
#line 604 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1688 "parser.tab.cc" // lalr1.cc:859
    break;

  case 91:
#line 609 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::ConstructorName );
		}
#line 1696 "parser.tab.cc" // lalr1.cc:859
    break;

  case 92:
#line 616 "parser.yy" // lalr1.cc:859
    {	
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::DestructorName );
		}
#line 1704 "parser.tab.cc" // lalr1.cc:859
    break;

  case 93:
#line 623 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1710 "parser.tab.cc" // lalr1.cc:859
    break;

  case 97:
#line 631 "parser.yy" // lalr1.cc:859
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
#line 1728 "parser.tab.cc" // lalr1.cc:859
    break;

  case 101:
#line 651 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConstantNode( ASTNode::TrueValue, (yystack_[0].value.scToken) );
		}
#line 1736 "parser.tab.cc" // lalr1.cc:859
    break;

  case 102:
#line 655 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ConstantNode( ASTNode::FalseValue, (yystack_[0].value.scToken) );
		}
#line 1744 "parser.tab.cc" // lalr1.cc:859
    break;

  case 103:
#line 663 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::BuildInFunction );
		}
#line 1752 "parser.tab.cc" // lalr1.cc:859
    break;

  case 104:
#line 670 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[0].value.scName), 0, 0 );
		}
#line 1760 "parser.tab.cc" // lalr1.cc:859
    break;

  case 105:
#line 674 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[3].value.scName), (yystack_[1].value.scNode), 0 );
		}
#line 1768 "parser.tab.cc" // lalr1.cc:859
    break;

  case 106:
#line 678 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[0].value.scName), 0, (yystack_[1].value.scList) ); 
		}
#line 1776 "parser.tab.cc" // lalr1.cc:859
    break;

  case 107:
#line 682 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[3].value.scName), (yystack_[1].value.scNode), (yystack_[4].value.scList) );
		}
#line 1784 "parser.tab.cc" // lalr1.cc:859
    break;

  case 108:
#line 689 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = new ListNode( ASTNode::InputVarDefinitionList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
		}
#line 1793 "parser.tab.cc" // lalr1.cc:859
    break;

  case 109:
#line 694 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scDef) );
		}
#line 1801 "parser.tab.cc" // lalr1.cc:859
    break;

  case 110:
#line 701 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::InputVarDefinition, (yystack_[3].value.scIdent), (yystack_[1].value.scNode), 0 );
		}
#line 1809 "parser.tab.cc" // lalr1.cc:859
    break;

  case 112:
#line 710 "parser.yy" // lalr1.cc:859
    { 
			(yylhs.value.scName) = new NameRefNode((yystack_[0].value.scIdent), ASTNode::RunningSchemeName);
		}
#line 1817 "parser.tab.cc" // lalr1.cc:859
    break;

  case 113:
#line 717 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = (yystack_[0].value.scNode);
		}
#line 1825 "parser.tab.cc" // lalr1.cc:859
    break;

  case 114:
#line 721 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode(ASTNode::InputVarList, (yystack_[2].value.scNode), (yystack_[0].value.scNode));
		}
#line 1833 "parser.tab.cc" // lalr1.cc:859
    break;

  case 115:
#line 728 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new NameRefNode( (yystack_[0].value.scIdent), ASTNode::InputVarName );
		}
#line 1841 "parser.tab.cc" // lalr1.cc:859
    break;

  case 118:
#line 738 "parser.yy" // lalr1.cc:859
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1847 "parser.tab.cc" // lalr1.cc:859
    break;

  case 119:
#line 740 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = (yystack_[1].value.scNode);
		}
#line 1855 "parser.tab.cc" // lalr1.cc:859
    break;

  case 121:
#line 748 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ValueConstructor, (yystack_[2].value.scNode), (yystack_[0].value.scName) );
		}
#line 1863 "parser.tab.cc" // lalr1.cc:859
    break;

  case 123:
#line 756 "parser.yy" // lalr1.cc:859
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ValueComposition, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
		}
#line 1871 "parser.tab.cc" // lalr1.cc:859
    break;


#line 1875 "parser.tab.cc" // lalr1.cc:859
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


  const short int BisonParser::yypact_ninf_ = -145;

  const signed char BisonParser::yytable_ninf_ = -85;

  const short int
  BisonParser::yypact_[] =
  {
       9,    22,    26,    49,    52,    54,    63,    37,  -145,  -145,
      43,  -145,    63,  -145,    12,  -145,    16,    86,    25,    83,
    -145,  -145,    88,    39,    92,    57,    55,  -145,   110,     8,
      84,    16,  -145,    27,  -145,    87,    85,    91,  -145,    90,
      93,  -145,    17,  -145,    89,    95,  -145,  -145,    82,  -145,
      31,   107,  -145,   100,    47,   139,  -145,  -145,    47,   139,
     104,    86,   144,   173,  -145,  -145,   105,    83,   107,  -145,
    -145,  -145,  -145,  -145,  -145,    31,  -145,  -145,  -145,   101,
     102,  -145,   108,  -145,    99,   109,  -145,   116,   115,   112,
    -145,   146,  -145,    47,   154,   119,  -145,  -145,   117,   -15,
    -145,   125,  -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,
    -145,   124,   128,   123,   130,    16,  -145,  -145,  -145,  -145,
    -145,  -145,  -145,  -145,    26,   142,   120,   144,   147,   140,
    -145,  -145,   141,   155,   145,  -145,    32,  -145,   143,   162,
     154,    31,  -145,  -145,   107,    16,    86,   113,   150,   163,
    -145,  -145,    47,    47,    47,    47,   139,   148,  -145,   149,
     153,   161,   181,    17,  -145,    26,   181,   154,   173,  -145,
     158,   175,  -145,  -145,  -145,  -145,  -145,   176,   177,   112,
    -145,   166,   178,  -145,  -145,  -145,  -145,    60,   117,  -145,
    -145,    47,    47,  -145,   213,   179,   182,   180,   183,  -145,
    -145,  -145,   144,  -145,  -145,   186,  -145,   113,    47,   184,
     185,   187,   181,  -145,  -145,   221,   188,    16,  -145,  -145,
    -145,  -145,  -145,  -145,   189,    17,   191,  -145,   193,  -145,
    -145
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
     103,     0,    64,     0,     0,     0,    71,    81,    73,    75,
      78,    60,    63,    62,    89,    90,    88,    94,    96,    93,
      57,    58,     0,     0,     0,     0,    48,    33,    34,    35,
      36,    37,    38,    39,     0,    30,     0,    14,     0,    18,
      29,    32,     0,    27,     0,    26,     0,    12,     0,     0,
       0,     0,   110,   105,     0,     0,     0,     0,     0,     0,
      92,    52,     0,     0,     0,     0,     0,     0,    54,     0,
       0,     0,     0,     0,    15,     0,     0,     0,     0,    23,
       0,     0,   107,   119,   121,   123,   114,     0,     0,    68,
      70,     0,    66,    69,    97,    61,    72,    77,    74,    79,
      59,     0,     0,    45,     0,    40,     0,     0,     0,    19,
      25,    28,     0,     7,    83,     0,    65,     0,     0,     0,
       0,     0,     0,    31,     8,     0,     0,     0,    67,    76,
      53,    55,    16,    41,     0,     0,     0,    17,     0,    85,
       9
  };

  const short int
  BisonParser::yypgoto_[] =
  {
    -145,  -145,   230,    51,    -2,   169,  -145,  -115,  -145,   -57,
    -131,   195,  -145,  -145,    70,  -144,  -145,    28,     2,   -60,
     235,  -145,   -54,  -145,   -30,  -145,  -145,   -55,   -56,    94,
    -136,    34,  -145,    96,    98,  -141,  -145,  -145,  -145,  -145,
    -145,  -145,  -145,  -134,   -42,  -145,  -145,  -145,   -27,  -145,
     231,   218,  -145,    48,   222,   -58,  -145,  -145,  -145,   103,
     -33
  };

  const short int
  BisonParser::yydefgoto_[] =
  {
      -1,     3,     4,    38,   125,    44,    45,   126,   127,   128,
      40,    41,    42,   133,   134,   129,   130,   196,   131,    76,
       6,     7,    35,    36,    30,    31,   111,   112,    95,    96,
      97,   181,   182,    98,    99,   100,   101,   102,    32,    87,
      88,    53,    33,   103,   104,   105,   106,   107,   108,   109,
      15,    23,    24,    83,    26,    84,    85,    79,    80,    81,
      86
  };

  const short int
  BisonParser::yytable_[] =
  {
      10,    57,   113,   135,   114,   171,   132,   116,    77,    77,
     138,   180,   164,   183,   189,    21,    39,    82,   195,    27,
       9,    46,   153,    78,    78,     8,    77,     1,     9,     9,
       2,   154,   197,    77,   150,     9,    69,   149,     2,    28,
      39,    78,   139,    70,    71,    72,     2,    37,    78,    11,
      89,     5,    69,     2,   170,    54,     5,    90,    55,    70,
      71,    72,    25,    73,    74,    29,    22,   219,   195,    46,
       1,   180,    25,   183,    58,     2,    16,    59,    17,    73,
      74,    75,    18,    14,    19,   160,   176,   216,    91,    34,
      43,    47,   178,    22,   228,    21,    92,    93,   174,    77,
      94,   190,    77,   208,    50,    51,   154,   200,   135,   199,
      21,   132,    69,    52,    78,   177,   179,    78,    69,    70,
      71,    72,   161,    90,    56,    70,    71,    72,    61,    60,
      62,    66,    68,    64,    39,   209,   210,    63,    67,    73,
      74,   -84,   110,   115,   136,    73,    74,     9,   141,   140,
     143,    43,   144,   142,    91,   145,   146,    75,   148,    69,
     163,    39,   147,   198,   151,   152,    94,   156,   158,   117,
     118,   119,   120,   121,   122,   123,     9,   155,    69,   157,
      43,   159,   124,   162,     9,   165,   166,   226,    43,   167,
     169,   168,   184,   193,   172,   191,   192,   202,   117,   118,
     119,   120,   121,   122,   123,   194,   117,   118,   119,   120,
     121,   122,   123,   173,   185,   203,   204,   206,   211,   205,
     214,   207,   212,    39,   213,   217,   224,   215,   225,   220,
     221,   229,   222,   230,   227,    13,   137,    65,   201,    12,
     223,   218,    49,    20,   175,    48,   186,     0,     0,     0,
     188,   187
  };

  const short int
  BisonParser::yycheck_[] =
  {
       2,    31,    58,    63,    59,   136,    63,    61,    50,    51,
      68,   147,   127,   147,   155,     3,    18,    50,   162,     3,
       3,    19,    37,    50,    51,     3,    68,    18,     3,     3,
      21,    46,   163,    75,    94,     3,     5,    93,    21,    23,
      42,    68,    75,    12,    13,    14,    21,    22,    75,     0,
       3,     0,     5,    21,    22,    47,     5,    10,    50,    12,
      13,    14,    14,    32,    33,    49,    54,   208,   212,    67,
      18,   207,    24,   207,    47,    21,    39,    50,    41,    32,
      33,    50,    39,    20,    41,   115,   144,   202,    41,     3,
       7,     3,   146,    54,   225,     3,    49,    50,   140,   141,
      53,   156,   144,    43,    47,    50,    46,   167,   168,   166,
       3,   168,     5,     3,   141,   145,     3,   144,     5,    12,
      13,    14,   124,    10,    40,    12,    13,    14,    43,    42,
      39,    42,    50,    40,   136,   191,   192,    47,    43,    32,
      33,    41,     3,    39,    39,    32,    33,     3,    46,    48,
      51,     7,    43,    45,    41,    39,    41,    50,    12,     5,
      40,   163,    50,   165,    45,    48,    53,    43,    45,    25,
      26,    27,    28,    29,    30,    31,     3,    52,     5,    51,
       7,    51,    38,    41,     3,    38,    46,   217,     7,    48,
      45,    36,    42,    40,    51,    47,    47,    39,    25,    26,
      27,    28,    29,    30,    31,    44,    25,    26,    27,    28,
      29,    30,    31,    51,    51,    40,    40,    51,     5,    42,
      40,    43,    43,   225,    42,    39,     5,    44,    40,    45,
      45,    40,    45,    40,    45,     5,    67,    42,   168,     4,
     212,   207,    24,    12,   141,    23,   152,    -1,    -1,    -1,
     154,   153
  };

  const unsigned char
  BisonParser::yystos_[] =
  {
       0,    18,    21,    56,    57,    58,    75,    76,     3,     3,
      59,     0,    75,    57,    20,   105,    39,    41,    39,    41,
     105,     3,    54,   106,   107,   108,   109,     3,    23,    49,
      79,    80,    93,    97,     3,    77,    78,    22,    58,    59,
      65,    66,    67,     7,    60,    61,    73,     3,   109,   106,
      47,    50,     3,    96,    47,    50,    40,    79,    47,    50,
      42,    43,    39,    47,    40,    66,    42,    43,    50,     5,
      12,    13,    14,    32,    33,    50,    74,    99,   103,   112,
     113,   114,   115,   108,   110,   111,   115,    94,    95,     3,
      10,    41,    49,    50,    53,    83,    84,    85,    88,    89,
      90,    91,    92,    98,    99,   100,   101,   102,   103,   104,
       3,    81,    82,    83,    82,    39,    77,    25,    26,    27,
      28,    29,    30,    31,    38,    59,    62,    63,    64,    70,
      71,    73,    64,    68,    69,    74,    39,    60,   110,   115,
      48,    46,    45,    51,    43,    39,    41,    50,    12,    83,
      74,    45,    48,    37,    46,    52,    43,    51,    45,    51,
      79,    59,    41,    40,    62,    38,    46,    48,    36,    45,
      22,    65,    51,    51,    99,   114,   110,    79,    77,     3,
      85,    86,    87,    98,    42,    51,    84,    89,    88,    90,
      82,    47,    47,    40,    44,    70,    72,    65,    59,    64,
      74,    69,    39,    40,    40,    42,    51,    43,    43,    83,
      83,     5,    43,    42,    40,    44,    62,    39,    86,    90,
      45,    45,    45,    72,     5,    40,    79,    45,    65,    40,
      40
  };

  const unsigned char
  BisonParser::yyr1_[] =
  {
       0,    55,    56,    56,    57,    57,    58,    58,    58,    58,
      59,    60,    60,    61,    62,    62,    63,    63,    64,    64,
      65,    66,    66,    67,    67,    68,    68,    69,    69,    70,
      70,    70,    70,    71,    71,    71,    71,    71,    71,    71,
      72,    72,    73,    74,    75,    75,    76,    77,    77,    78,
      79,    79,    80,    80,    80,    80,    80,    81,    82,    82,
      83,    84,    84,    84,    84,    85,    86,    86,    87,    87,
      87,    88,    88,    89,    89,    90,    90,    90,    91,    91,
      92,    92,    94,    93,    95,    93,    96,    97,    98,    98,
      98,    99,   100,   101,   101,   101,   101,   102,   103,   103,
     103,   103,   103,   104,   105,   105,   105,   105,   106,   106,
     107,   108,   109,   110,   110,   111,   111,   112,   112,   112,
     113,   113,   114,   114,   115
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
       0,   180,   180,   187,   197,   202,   209,   213,   217,   221,
     228,   232,   237,   244,   251,   256,   263,   267,   273,   278,
     286,   299,   304,   311,   315,   324,   328,   335,   336,   344,
     348,   352,   356,   363,   364,   365,   366,   367,   368,   369,
     373,   378,   384,   386,   391,   396,   404,   412,   417,   424,
     431,   436,   443,   447,   451,   455,   459,   464,   471,   476,
     483,   487,   489,   490,   492,   499,   505,   510,   517,   521,
     522,   527,   528,   535,   536,   543,   544,   548,   555,   556,
     563,   567,   572,   571,   581,   580,   592,   596,   600,   601,
     603,   608,   615,   622,   624,   625,   626,   630,   647,   648,
     649,   650,   654,   662,   669,   673,   677,   681,   688,   693,
     700,   706,   709,   716,   720,   727,   731,   736,   737,   739,
     746,   747,   754,   755,   761
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
#line 2384 "parser.tab.cc" // lalr1.cc:1167
