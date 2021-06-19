// A Bison parser, made by GNU Bison 3.3.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2019 Free Software Foundation, Inc.

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

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "parser.tab.hh"


// Unqualified %code blocks.
#line 55 "parser.yy" // lalr1.cc:435

#include "../Support.h"
#include "../FlexTokenizer.h"
#include "../Nodes.h"

#line 51 "parser.tab.cc" // lalr1.cc:435


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

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
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
      *yycdebug_ << '\n';                       \
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
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 2 "parser.yy" // lalr1.cc:510
namespace FPTL { namespace Parser {
#line 127 "parser.tab.cc" // lalr1.cc:510

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
        std::string yyr;
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
              else
                goto append;

            append:
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

  BisonParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
  BisonParser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value (std::move (that.value))
  {}
#endif

  template <typename Base>
  BisonParser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  BisonParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  BisonParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (semantic_type) v)
    : Base (t)
    , value (YY_MOVE (v))
  {}

  template <typename Base>
  bool
  BisonParser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  BisonParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
  }

  // by_type.
  BisonParser::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
  BisonParser::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  BisonParser::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

  BisonParser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
  BisonParser::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
  BisonParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
  BisonParser::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }


  // by_state.
  BisonParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  BisonParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  BisonParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  BisonParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  BisonParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  BisonParser::symbol_number_type
  BisonParser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  BisonParser::stack_symbol_type::stack_symbol_type ()
  {}

  BisonParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  BisonParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value))
  {
    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  BisonParser::stack_symbol_type&
  BisonParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  BisonParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
      case 12: // NUMBER
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 360 "parser.tab.cc" // lalr1.cc:652
        break;

      case 13: // REALNUMBER
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 370 "parser.tab.cc" // lalr1.cc:652
        break;

      case 14: // STRING
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 380 "parser.tab.cc" // lalr1.cc:652
        break;

      case 58: // FunctionalProgram
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 390 "parser.tab.cc" // lalr1.cc:652
        break;

      case 59: // DataTypeDefinitionsBlocks
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 400 "parser.tab.cc" // lalr1.cc:652
        break;

      case 60: // DataTypeDefinitionsBlock
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 410 "parser.tab.cc" // lalr1.cc:652
        break;

      case 62: // TypeParametersList
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 420 "parser.tab.cc" // lalr1.cc:652
        break;

      case 63: // TypeParameterDef
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 430 "parser.tab.cc" // lalr1.cc:652
        break;

      case 64: // ConstructorsDefinitionList
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 440 "parser.tab.cc" // lalr1.cc:652
        break;

      case 65: // ConstructorDef
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 450 "parser.tab.cc" // lalr1.cc:652
        break;

      case 66: // ConstructorParametersList
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 460 "parser.tab.cc" // lalr1.cc:652
        break;

      case 67: // TypesDefinitionList
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 470 "parser.tab.cc" // lalr1.cc:652
        break;

      case 68: // TypesDefinitionList2
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 480 "parser.tab.cc" // lalr1.cc:652
        break;

      case 69: // TypeDefinition
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 490 "parser.tab.cc" // lalr1.cc:652
        break;

      case 70: // TypeDefConstructor
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 500 "parser.tab.cc" // lalr1.cc:652
        break;

      case 71: // TypeExpression
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 510 "parser.tab.cc" // lalr1.cc:652
        break;

      case 72: // AtomType
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 520 "parser.tab.cc" // lalr1.cc:652
        break;

      case 74: // TypeExpressionsList
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 530 "parser.tab.cc" // lalr1.cc:652
        break;

      case 77: // Scheme
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scFun);
	delete node;

}
#line 540 "parser.tab.cc" // lalr1.cc:652
        break;

      case 79: // FormalParametersList
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 550 "parser.tab.cc" // lalr1.cc:652
        break;

      case 80: // FormalParameter
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 560 "parser.tab.cc" // lalr1.cc:652
        break;

      case 81: // DefinitionsList
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 570 "parser.tab.cc" // lalr1.cc:652
        break;

      case 82: // Definition
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 580 "parser.tab.cc" // lalr1.cc:652
        break;

      case 83: // Term
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 590 "parser.tab.cc" // lalr1.cc:652
        break;

      case 84: // AtomTerm
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 600 "parser.tab.cc" // lalr1.cc:652
        break;

      case 85: // FuncObjectWithParameters
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 610 "parser.tab.cc" // lalr1.cc:652
        break;

      case 86: // FuncArgumentList
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 620 "parser.tab.cc" // lalr1.cc:652
        break;

      case 87: // FuncParameterName
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 630 "parser.tab.cc" // lalr1.cc:652
        break;

      case 88: // SequentialTerm
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 640 "parser.tab.cc" // lalr1.cc:652
        break;

      case 89: // CompositionTerm
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 650 "parser.tab.cc" // lalr1.cc:652
        break;

      case 90: // ConditionTerm
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 660 "parser.tab.cc" // lalr1.cc:652
        break;

      case 91: // VariantTerm
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 670 "parser.tab.cc" // lalr1.cc:652
        break;

      case 92: // FuncObjectName
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 680 "parser.tab.cc" // lalr1.cc:652
        break;

      case 93: // ConstructionFun
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scFun);
	delete node;

}
#line 690 "parser.tab.cc" // lalr1.cc:652
        break;

      case 98: // ElementaryFunctionName
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 700 "parser.tab.cc" // lalr1.cc:652
        break;

      case 99: // Constructor
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 710 "parser.tab.cc" // lalr1.cc:652
        break;

      case 100: // Destructor
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 720 "parser.tab.cc" // lalr1.cc:652
        break;

      case 101: // BuiltInFunction
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 730 "parser.tab.cc" // lalr1.cc:652
        break;

      case 102: // TupleElement
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 740 "parser.tab.cc" // lalr1.cc:652
        break;

      case 103: // Constant
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 750 "parser.tab.cc" // lalr1.cc:652
        break;

      case 104: // BuiltInFunctionName
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 760 "parser.tab.cc" // lalr1.cc:652
        break;

      case 105: // Application
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scApp);
	delete node;

}
#line 770 "parser.tab.cc" // lalr1.cc:652
        break;

      case 106: // DataInit
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 780 "parser.tab.cc" // lalr1.cc:652
        break;

      case 107: // OneDataInit
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 790 "parser.tab.cc" // lalr1.cc:652
        break;

      case 109: // InterpFunProgramName
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 800 "parser.tab.cc" // lalr1.cc:652
        break;

      case 110: // Data
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 810 "parser.tab.cc" // lalr1.cc:652
        break;

      case 111: // OneData
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 820 "parser.tab.cc" // lalr1.cc:652
        break;

      case 112: // ValueAtom
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 830 "parser.tab.cc" // lalr1.cc:652
        break;

      case 113: // ValueConstructor
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 840 "parser.tab.cc" // lalr1.cc:652
        break;

      case 114: // ValueComposition
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 850 "parser.tab.cc" // lalr1.cc:652
        break;

      case 115: // Value
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 860 "parser.tab.cc" // lalr1.cc:652
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
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  BisonParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  BisonParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  BisonParser::yypop_ (int n)
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

  BisonParser::state_type
  BisonParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  BisonParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  BisonParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  BisonParser::operator() ()
  {
    return parse ();
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

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, pSupport, aTokenizer));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
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
    yypush_ ("Shifting", yyn, YY_MOVE (yyla));
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
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
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
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 187 "parser.yy" // lalr1.cc:919
    {
			mASTRoot = new FunctionalProgram( (yystack_[2].value.scList), (yystack_[1].value.scFun), (yystack_[0].value.scApp) );
			(yystack_[2].value.scList)->mParent = mASTRoot;
			(yystack_[1].value.scFun)->mParent = mASTRoot;
			(yystack_[0].value.scApp)->mParent = mASTRoot;
			
			// Возвращаем 0, иначе все дерево будет "срублено" деструктором парсера.
			(yylhs.value.scNode) = 0;
		}
#line 1119 "parser.tab.cc" // lalr1.cc:919
    break;

  case 3:
#line 197 "parser.yy" // lalr1.cc:919
    {
			mASTRoot = new FunctionalProgram( 0, (yystack_[1].value.scFun), (yystack_[0].value.scApp) );
			(yystack_[1].value.scFun)->mParent = mASTRoot;
			(yystack_[0].value.scApp)->mParent = mASTRoot;
			(yylhs.value.scNode) = 0;
		}
#line 1130 "parser.tab.cc" // lalr1.cc:919
    break;

  case 4:
#line 209 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = new ListNode(  ASTNode::DataTypeDefinitionsBlocks );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scList);
		}
#line 1140 "parser.tab.cc" // lalr1.cc:919
    break;

  case 5:
#line 215 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scNode) );
			(yystack_[1].value.scNode)->mParent = (yystack_[0].value.scList);
		}
#line 1149 "parser.tab.cc" // lalr1.cc:919
    break;

  case 6:
#line 223 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[3].value.scIdent), (yystack_[1].value.scList), 0, 0 );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scNode);
		}
#line 1158 "parser.tab.cc" // lalr1.cc:919
    break;

  case 7:
#line 228 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[6].value.scIdent), (yystack_[1].value.scList), (yystack_[4].value.scList), 0 );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scNode);
			(yystack_[4].value.scList)->mParent = (yylhs.value.scNode);
		}
#line 1168 "parser.tab.cc" // lalr1.cc:919
    break;

  case 8:
#line 234 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[7].value.scIdent), (yystack_[1].value.scList), 0, (yystack_[3].value.scList) );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scNode);
			(yystack_[3].value.scList)->mParent = (yylhs.value.scNode);
		}
#line 1178 "parser.tab.cc" // lalr1.cc:919
    break;

  case 9:
#line 240 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[10].value.scIdent), (yystack_[1].value.scList), (yystack_[8].value.scList), (yystack_[3].value.scList) );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scNode);
			(yystack_[8].value.scList)->mParent = (yylhs.value.scNode);
			(yystack_[3].value.scList)->mParent = (yylhs.value.scNode);
		}
#line 1189 "parser.tab.cc" // lalr1.cc:919
    break;

  case 10:
#line 249 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scIdent) = (yystack_[0].value.scIdent); }
#line 1195 "parser.tab.cc" // lalr1.cc:919
    break;

  case 11:
#line 254 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = new ListNode( ASTNode::TypeParametersList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
			(yystack_[0].value.scDef)->mParent = (yylhs.value.scList);
		}
#line 1205 "parser.tab.cc" // lalr1.cc:919
    break;

  case 12:
#line 260 "parser.yy" // lalr1.cc:919
    {		
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scDef) );
			(yystack_[2].value.scDef)->mParent = (yystack_[0].value.scList);
		}
#line 1214 "parser.tab.cc" // lalr1.cc:919
    break;

  case 13:
#line 268 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::TypeParameterDefinition, (yystack_[0].value.scIdent), 0 );
		}
#line 1222 "parser.tab.cc" // lalr1.cc:919
    break;

  case 14:
#line 275 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = new ListNode( ASTNode::ConstructorsDefinitionList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scList);
		}
#line 1232 "parser.tab.cc" // lalr1.cc:919
    break;

  case 15:
#line 281 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scNode) );
			(yystack_[1].value.scNode)->mParent = (yystack_[0].value.scList);
		}
#line 1241 "parser.tab.cc" // lalr1.cc:919
    break;

  case 16:
#line 289 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ConstructorNode( (yystack_[1].value.scIdent), 0, (yystack_[3].value.scIdent) );
		}
#line 1249 "parser.tab.cc" // lalr1.cc:919
    break;

  case 17:
#line 293 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ConstructorNode( (yystack_[1].value.scIdent), (yystack_[5].value.scList), (yystack_[3].value.scIdent) );
			(yystack_[5].value.scList)->mParent = (yylhs.value.scNode);
		}
#line 1258 "parser.tab.cc" // lalr1.cc:919
    break;

  case 18:
#line 300 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = new ListNode( ASTNode::ConstructorParametersList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scName) );
			(yystack_[0].value.scName)->mParent = (yylhs.value.scList);
		}
#line 1268 "parser.tab.cc" // lalr1.cc:919
    break;

  case 19:
#line 306 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scName) );
			(yystack_[2].value.scName)->mParent = (yystack_[0].value.scList);
		}
#line 1277 "parser.tab.cc" // lalr1.cc:919
    break;

  case 20:
#line 315 "parser.yy" // lalr1.cc:919
    {
			if( (yystack_[0].value.scList)->mChilds.size() > 1 )
			{
				for(ASTNode* child : (yystack_[0].value.scList)->mChilds)
					pSupport->semanticError( ParserErrTypes::MultipleTypeExpression, static_cast<DefinitionNode*>(child)->getDefinitionName() );
			}

			(yylhs.value.scList) = (yystack_[0].value.scList);
		}
#line 1291 "parser.tab.cc" // lalr1.cc:919
    break;

  case 21:
#line 328 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = new ListNode( ASTNode::TypesDefinitionList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
			(yystack_[0].value.scDef)->mParent = (yylhs.value.scList);
		}
#line 1301 "parser.tab.cc" // lalr1.cc:919
    break;

  case 22:
#line 334 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scDef) );
			(yystack_[1].value.scDef)->mParent = (yystack_[0].value.scList);
		}
#line 1310 "parser.tab.cc" // lalr1.cc:919
    break;

  case 23:
#line 342 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::TypeDefinition, (yystack_[3].value.scIdent), (yystack_[1].value.scNode) );
			(yystack_[1].value.scNode)->mParent = (yylhs.value.scDef);
		}
#line 1319 "parser.tab.cc" // lalr1.cc:919
    break;

  case 24:
#line 347 "parser.yy" // lalr1.cc:919
    {
			pSupport->semanticError( ParserErrTypes::NestedDataDefinition, static_cast<DataNode*>((yystack_[0].value.scNode))->getDataName() );
			delete (yystack_[0].value.scNode);
			(yylhs.value.scDef) = 0;
		}
#line 1329 "parser.tab.cc" // lalr1.cc:919
    break;

  case 25:
#line 356 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::TypeConstructorDefinition, (yystack_[0].value.scIdent), (yystack_[2].value.scList) );
			(yystack_[2].value.scList)->mParent = (yylhs.value.scNode);
		}
#line 1338 "parser.tab.cc" // lalr1.cc:919
    break;

  case 26:
#line 361 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::TypeConstructorDefinition, (yystack_[0].value.scIdent), 0 );
		}
#line 1346 "parser.tab.cc" // lalr1.cc:919
    break;

  case 27:
#line 367 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1352 "parser.tab.cc" // lalr1.cc:919
    break;

  case 28:
#line 369 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::TypeExpression, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1362 "parser.tab.cc" // lalr1.cc:919
    break;

  case 29:
#line 379 "parser.yy" // lalr1.cc:919
    {	
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scToken), NameRefNode::BaseType, nullptr );
		}
#line 1370 "parser.tab.cc" // lalr1.cc:919
    break;

  case 30:
#line 383 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::Type, nullptr );
		}
#line 1378 "parser.tab.cc" // lalr1.cc:919
    break;

  case 31:
#line 387 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[3].value.scIdent), NameRefNode::Template, (yystack_[1].value.scList) );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scName);
		}
#line 1387 "parser.tab.cc" // lalr1.cc:919
    break;

  case 32:
#line 392 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::TypeParamName, nullptr );
		}
#line 1395 "parser.tab.cc" // lalr1.cc:919
    break;

  case 33:
#line 398 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scToken) = (yystack_[0].value.scToken); }
#line 1401 "parser.tab.cc" // lalr1.cc:919
    break;

  case 34:
#line 399 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scToken) = (yystack_[0].value.scToken); }
#line 1407 "parser.tab.cc" // lalr1.cc:919
    break;

  case 35:
#line 400 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scToken) = (yystack_[0].value.scToken); }
#line 1413 "parser.tab.cc" // lalr1.cc:919
    break;

  case 36:
#line 401 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scToken) = (yystack_[0].value.scToken); }
#line 1419 "parser.tab.cc" // lalr1.cc:919
    break;

  case 37:
#line 402 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scToken) = (yystack_[0].value.scToken); }
#line 1425 "parser.tab.cc" // lalr1.cc:919
    break;

  case 38:
#line 403 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scToken) = (yystack_[0].value.scToken); }
#line 1431 "parser.tab.cc" // lalr1.cc:919
    break;

  case 39:
#line 404 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scToken) = (yystack_[0].value.scToken); }
#line 1437 "parser.tab.cc" // lalr1.cc:919
    break;

  case 40:
#line 409 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = new ListNode( ASTNode::TypeExpressionsList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scName) );
			(yystack_[0].value.scName)->mParent = (yylhs.value.scList);
		}
#line 1447 "parser.tab.cc" // lalr1.cc:919
    break;

  case 41:
#line 415 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scName) );
			(yystack_[2].value.scName)->mParent = (yystack_[0].value.scList);
		}
#line 1456 "parser.tab.cc" // lalr1.cc:919
    break;

  case 42:
#line 421 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scIdent) = (yystack_[0].value.scIdent); }
#line 1462 "parser.tab.cc" // lalr1.cc:919
    break;

  case 43:
#line 423 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scIdent) = (yystack_[0].value.scIdent); }
#line 1468 "parser.tab.cc" // lalr1.cc:919
    break;

  case 44:
#line 429 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[3].value.scIdent), (yystack_[1].value.scList), 0 );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scFun);
			pSupport->popIdent();
		}
#line 1478 "parser.tab.cc" // lalr1.cc:919
    break;

  case 45:
#line 435 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[6].value.scIdent), (yystack_[1].value.scList), (yystack_[4].value.scList) );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scFun);
			(yystack_[4].value.scList)->mParent = (yylhs.value.scFun);
			pSupport->popIdent();
		}
#line 1489 "parser.tab.cc" // lalr1.cc:919
    break;

  case 46:
#line 445 "parser.yy" // lalr1.cc:919
    {
			pSupport->pushIdent( (yystack_[0].value.scIdent) );
			(yylhs.value.scIdent) = (yystack_[0].value.scIdent);
		}
#line 1498 "parser.tab.cc" // lalr1.cc:919
    break;

  case 47:
#line 453 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = new ListNode( ASTNode::FormalParametersList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
			(yystack_[0].value.scDef)->mParent = (yylhs.value.scList);
		}
#line 1508 "parser.tab.cc" // lalr1.cc:919
    break;

  case 48:
#line 459 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scDef) );
			(yystack_[2].value.scDef)->mParent = (yystack_[0].value.scList);
		}
#line 1517 "parser.tab.cc" // lalr1.cc:919
    break;

  case 49:
#line 467 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::FunctionParameterDefinition, (yystack_[0].value.scIdent), 0 );
		}
#line 1525 "parser.tab.cc" // lalr1.cc:919
    break;

  case 50:
#line 474 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = new ListNode( ASTNode::DefinitionsList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scList);
		}
#line 1535 "parser.tab.cc" // lalr1.cc:919
    break;

  case 51:
#line 480 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scNode) );
			(yystack_[1].value.scNode)->mParent = (yystack_[0].value.scList);
		}
#line 1544 "parser.tab.cc" // lalr1.cc:919
    break;

  case 52:
#line 488 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::Definition, pSupport->getTopIdent(), (yystack_[1].value.scNode) );
			(yystack_[1].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1553 "parser.tab.cc" // lalr1.cc:919
    break;

  case 53:
#line 493 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::Definition, (yystack_[3].value.scIdent), (yystack_[1].value.scNode) );
			(yystack_[1].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1562 "parser.tab.cc" // lalr1.cc:919
    break;

  case 54:
#line 498 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scFun); }
#line 1568 "parser.tab.cc" // lalr1.cc:919
    break;

  case 55:
#line 502 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1574 "parser.tab.cc" // lalr1.cc:919
    break;

  case 56:
#line 507 "parser.yy" // lalr1.cc:919
    {	(yylhs.value.scNode) = (yystack_[1].value.scNode); }
#line 1580 "parser.tab.cc" // lalr1.cc:919
    break;

  case 57:
#line 508 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1586 "parser.tab.cc" // lalr1.cc:919
    break;

  case 58:
#line 510 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1592 "parser.tab.cc" // lalr1.cc:919
    break;

  case 59:
#line 512 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new NameRefNode( pSupport->getTopIdent(), ASTNode::FuncObjectName, nullptr );
		}
#line 1600 "parser.tab.cc" // lalr1.cc:919
    break;

  case 60:
#line 519 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[3].value.scIdent), NameRefNode::FuncObjectWithParameters, (yystack_[1].value.scList) );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scName);
		}
#line 1609 "parser.tab.cc" // lalr1.cc:919
    break;

  case 61:
#line 526 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = new ListNode( ASTNode::FuncArgumentsList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scList);
		}
#line 1619 "parser.tab.cc" // lalr1.cc:919
    break;

  case 62:
#line 532 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scNode) );
			(yystack_[2].value.scNode)->mParent = (yystack_[0].value.scList);
		}
#line 1628 "parser.tab.cc" // lalr1.cc:919
    break;

  case 63:
#line 540 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::FuncParameterName, nullptr );
		}
#line 1636 "parser.tab.cc" // lalr1.cc:919
    break;

  case 64:
#line 543 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1642 "parser.tab.cc" // lalr1.cc:919
    break;

  case 65:
#line 545 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1648 "parser.tab.cc" // lalr1.cc:919
    break;

  case 66:
#line 549 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1654 "parser.tab.cc" // lalr1.cc:919
    break;

  case 67:
#line 551 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::SequentialTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1664 "parser.tab.cc" // lalr1.cc:919
    break;

  case 68:
#line 559 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1670 "parser.tab.cc" // lalr1.cc:919
    break;

  case 69:
#line 561 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::CompositionTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1680 "parser.tab.cc" // lalr1.cc:919
    break;

  case 70:
#line 569 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1686 "parser.tab.cc" // lalr1.cc:919
    break;

  case 71:
#line 571 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ConditionNode( ASTNode::ConditionTerm, (yystack_[4].value.scNode), (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
			(yystack_[4].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1697 "parser.tab.cc" // lalr1.cc:919
    break;

  case 72:
#line 578 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ConditionNode( ASTNode::ConditionTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode), nullptr );
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1707 "parser.tab.cc" // lalr1.cc:919
    break;

  case 73:
#line 586 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1713 "parser.tab.cc" // lalr1.cc:919
    break;

  case 74:
#line 588 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::VariantTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1723 "parser.tab.cc" // lalr1.cc:919
    break;

  case 75:
#line 597 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::FuncObjectName, nullptr );
		}
#line 1731 "parser.tab.cc" // lalr1.cc:919
    break;

  case 76:
#line 600 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scName) = (yystack_[0].value.scName); }
#line 1737 "parser.tab.cc" // lalr1.cc:919
    break;

  case 77:
#line 605 "parser.yy" // lalr1.cc:919
    {
			pSupport->pushIdent( (yystack_[0].value.scIdent) );
		}
#line 1745 "parser.tab.cc" // lalr1.cc:919
    break;

  case 78:
#line 609 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[4].value.scIdent), (yystack_[1].value.scList), 0 );
			pSupport->popIdent();
			(yystack_[1].value.scList)->mParent = (yylhs.value.scFun);
		}
#line 1755 "parser.tab.cc" // lalr1.cc:919
    break;

  case 79:
#line 615 "parser.yy" // lalr1.cc:919
    {
			pSupport->pushIdent( (yystack_[0].value.scIdent) );
		}
#line 1763 "parser.tab.cc" // lalr1.cc:919
    break;

  case 80:
#line 619 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[7].value.scIdent), (yystack_[1].value.scList), (yystack_[4].value.scList) );
			pSupport->popIdent();
			(yystack_[1].value.scList)->mParent = (yylhs.value.scFun);
			(yystack_[4].value.scList)->mParent = (yylhs.value.scFun);
		}
#line 1774 "parser.tab.cc" // lalr1.cc:919
    break;

  case 81:
#line 628 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scIdent) = (yystack_[0].value.scIdent); }
#line 1780 "parser.tab.cc" // lalr1.cc:919
    break;

  case 82:
#line 632 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scIdent) = (yystack_[0].value.scIdent); }
#line 1786 "parser.tab.cc" // lalr1.cc:919
    break;

  case 83:
#line 636 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1792 "parser.tab.cc" // lalr1.cc:919
    break;

  case 84:
#line 638 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1798 "parser.tab.cc" // lalr1.cc:919
    break;

  case 85:
#line 640 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1804 "parser.tab.cc" // lalr1.cc:919
    break;

  case 86:
#line 645 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::ConstructorName, nullptr );
		}
#line 1812 "parser.tab.cc" // lalr1.cc:919
    break;

  case 87:
#line 652 "parser.yy" // lalr1.cc:919
    {	
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::DestructorName, nullptr );
		}
#line 1820 "parser.tab.cc" // lalr1.cc:919
    break;

  case 88:
#line 659 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1826 "parser.tab.cc" // lalr1.cc:919
    break;

  case 89:
#line 660 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1832 "parser.tab.cc" // lalr1.cc:919
    break;

  case 90:
#line 661 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1838 "parser.tab.cc" // lalr1.cc:919
    break;

  case 91:
#line 666 "parser.yy" // lalr1.cc:919
    {
			ConstantNode * number = static_cast<ConstantNode*>( (yystack_[1].value.scNode) );
			(yylhs.value.scNode) = new TakeNode( number->getConstant(), number->getConstant() );
			delete number;
		}
#line 1848 "parser.tab.cc" // lalr1.cc:919
    break;

  case 92:
#line 672 "parser.yy" // lalr1.cc:919
    {
			Ident from = { (yystack_[1].value.scToken).Col, (yystack_[1].value.scToken).Line, nullptr };
			Ident to = { (yystack_[1].value.scToken).Col, (yystack_[1].value.scToken).Line, nullptr };
			(yylhs.value.scNode) = new TakeNode( from, to);
		}
#line 1858 "parser.tab.cc" // lalr1.cc:919
    break;

  case 93:
#line 678 "parser.yy" // lalr1.cc:919
    {
			ConstantNode * from = static_cast<ConstantNode*>( (yystack_[2].value.scNode) );
			Ident to = { (yystack_[1].value.scToken).Col, (yystack_[1].value.scToken).Line, nullptr };
			(yylhs.value.scNode) = new TakeNode( from->getConstant(), to);
			delete from;
		}
#line 1869 "parser.tab.cc" // lalr1.cc:919
    break;

  case 94:
#line 685 "parser.yy" // lalr1.cc:919
    {
			Ident from = { (yystack_[2].value.scToken).Col, (yystack_[2].value.scToken).Line, nullptr };
			ConstantNode * to = static_cast<ConstantNode*>( (yystack_[1].value.scNode) );
			(yylhs.value.scNode) = new TakeNode( from, to->getConstant() );
			delete to;
		}
#line 1880 "parser.tab.cc" // lalr1.cc:919
    break;

  case 95:
#line 692 "parser.yy" // lalr1.cc:919
    {
			ConstantNode * from = static_cast<ConstantNode*>( (yystack_[3].value.scNode) );
			ConstantNode * to = static_cast<ConstantNode*>( (yystack_[1].value.scNode) );
			(yylhs.value.scNode) = new TakeNode( from->getConstant(), to->getConstant() );
			delete from;
			delete to;
		}
#line 1892 "parser.tab.cc" // lalr1.cc:919
    break;

  case 96:
#line 701 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1898 "parser.tab.cc" // lalr1.cc:919
    break;

  case 97:
#line 702 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1904 "parser.tab.cc" // lalr1.cc:919
    break;

  case 98:
#line 703 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1910 "parser.tab.cc" // lalr1.cc:919
    break;

  case 99:
#line 705 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ConstantNode( ASTNode::TrueValue, (yystack_[0].value.scToken) );
		}
#line 1918 "parser.tab.cc" // lalr1.cc:919
    break;

  case 100:
#line 709 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ConstantNode( ASTNode::FalseValue, (yystack_[0].value.scToken) );
		}
#line 1926 "parser.tab.cc" // lalr1.cc:919
    break;

  case 101:
#line 717 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::BuildInFunction, nullptr );
		}
#line 1934 "parser.tab.cc" // lalr1.cc:919
    break;

  case 102:
#line 724 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[0].value.scName), 0, 0 );
			(yystack_[0].value.scName)->mParent = (yylhs.value.scApp);
		}
#line 1943 "parser.tab.cc" // lalr1.cc:919
    break;

  case 103:
#line 729 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[3].value.scName), (yystack_[1].value.scNode), 0 );
			(yystack_[3].value.scName)->mParent = (yylhs.value.scApp);
			(yystack_[1].value.scNode)->mParent = (yylhs.value.scApp);
		}
#line 1953 "parser.tab.cc" // lalr1.cc:919
    break;

  case 104:
#line 735 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[0].value.scName), 0, (yystack_[1].value.scList) ); 
			(yystack_[0].value.scName)->mParent = (yylhs.value.scApp);
			(yystack_[1].value.scList)->mParent = (yylhs.value.scApp);
		}
#line 1963 "parser.tab.cc" // lalr1.cc:919
    break;

  case 105:
#line 741 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[3].value.scName), (yystack_[1].value.scNode), (yystack_[4].value.scList) );
			(yystack_[3].value.scName)->mParent = (yylhs.value.scApp);
			(yystack_[1].value.scNode)->mParent = (yylhs.value.scApp);
			(yystack_[4].value.scList)->mParent = (yylhs.value.scApp);
		}
#line 1974 "parser.tab.cc" // lalr1.cc:919
    break;

  case 106:
#line 751 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = new ListNode( ASTNode::InputVarDefinitionList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
			(yystack_[0].value.scDef)->mParent = (yylhs.value.scList);
		}
#line 1984 "parser.tab.cc" // lalr1.cc:919
    break;

  case 107:
#line 757 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scDef) );
			(yystack_[1].value.scDef)->mParent = (yystack_[0].value.scList);
		}
#line 1993 "parser.tab.cc" // lalr1.cc:919
    break;

  case 108:
#line 765 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::InputVarDefinition, (yystack_[3].value.scIdent), (yystack_[1].value.scNode) );
			(yystack_[1].value.scNode)->mParent = (yylhs.value.scDef);
		}
#line 2002 "parser.tab.cc" // lalr1.cc:919
    break;

  case 109:
#line 771 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scIdent) = (yystack_[0].value.scIdent); }
#line 2008 "parser.tab.cc" // lalr1.cc:919
    break;

  case 110:
#line 775 "parser.yy" // lalr1.cc:919
    { 
			(yylhs.value.scName) = new NameRefNode((yystack_[0].value.scIdent), ASTNode::RunningSchemeName, nullptr );
		}
#line 2016 "parser.tab.cc" // lalr1.cc:919
    break;

  case 111:
#line 782 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = (yystack_[0].value.scNode);
		}
#line 2024 "parser.tab.cc" // lalr1.cc:919
    break;

  case 112:
#line 786 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ExpressionNode(ASTNode::InputVarList, (yystack_[2].value.scNode), (yystack_[0].value.scNode));
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 2034 "parser.tab.cc" // lalr1.cc:919
    break;

  case 113:
#line 795 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new NameRefNode( (yystack_[0].value.scIdent), ASTNode::InputVarName, nullptr );
		}
#line 2042 "parser.tab.cc" // lalr1.cc:919
    break;

  case 114:
#line 798 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 2048 "parser.tab.cc" // lalr1.cc:919
    break;

  case 115:
#line 803 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 2054 "parser.tab.cc" // lalr1.cc:919
    break;

  case 116:
#line 805 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 2060 "parser.tab.cc" // lalr1.cc:919
    break;

  case 117:
#line 807 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = (yystack_[1].value.scNode);
		}
#line 2068 "parser.tab.cc" // lalr1.cc:919
    break;

  case 118:
#line 813 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 2074 "parser.tab.cc" // lalr1.cc:919
    break;

  case 119:
#line 815 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ValueConstructor, (yystack_[2].value.scNode), (yystack_[0].value.scName) );
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scName)->mParent = (yylhs.value.scNode);
		}
#line 2084 "parser.tab.cc" // lalr1.cc:919
    break;

  case 120:
#line 823 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 2090 "parser.tab.cc" // lalr1.cc:919
    break;

  case 121:
#line 825 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ValueComposition, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 2100 "parser.tab.cc" // lalr1.cc:919
    break;

  case 122:
#line 832 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 2106 "parser.tab.cc" // lalr1.cc:919
    break;


#line 2110 "parser.tab.cc" // lalr1.cc:919
            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
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
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

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
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
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
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  BisonParser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
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
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
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


  const short BisonParser::yypact_ninf_ = -136;

  const signed char BisonParser::yytable_ninf_ = -80;

  const short
  BisonParser::yypact_[] =
  {
      96,    22,    38,    45,    43,    65,    77,    80,  -136,  -136,
      81,  -136,    77,  -136,    11,  -136,    36,   124,   138,   122,
    -136,  -136,   134,    57,   142,   107,   100,  -136,   149,   111,
     115,    36,  -136,   114,  -136,   127,   128,   131,  -136,   129,
     132,  -136,    73,  -136,   133,   130,  -136,  -136,   135,  -136,
     106,    30,  -136,   136,    24,  -136,  -136,    24,   140,   124,
     105,   137,  -136,  -136,   141,   122,    30,  -136,  -136,  -136,
    -136,  -136,  -136,   106,  -136,  -136,  -136,   139,   143,  -136,
     144,  -136,   145,   146,  -136,   147,   150,   151,  -136,  -136,
      24,   173,    42,   152,  -136,  -136,   153,    29,  -136,   154,
    -136,  -136,  -136,  -136,  -136,  -136,  -136,  -136,   155,    36,
    -136,  -136,  -136,  -136,  -136,  -136,  -136,  -136,    38,   156,
     158,   105,   159,   157,  -136,  -136,   160,   162,   164,  -136,
     148,  -136,   161,   163,   173,   106,  -136,  -136,    30,    36,
     124,    93,   165,  -136,    15,     5,  -136,    24,    24,    24,
      24,  -136,   167,   166,    21,    73,  -136,    38,    21,   173,
     137,  -136,   169,   171,  -136,  -136,  -136,  -136,  -136,   175,
     174,   151,  -136,   176,   177,  -136,  -136,    10,  -136,   168,
    -136,  -136,   103,   153,  -136,  -136,   178,   179,   181,   184,
     172,  -136,  -136,  -136,   105,  -136,  -136,   180,  -136,    93,
     182,  -136,  -136,    24,   187,    21,  -136,  -136,   185,   186,
      36,  -136,  -136,  -136,  -136,  -136,   189,    73,   188,  -136,
     190,  -136,  -136
  };

  const unsigned char
  BisonParser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     4,     0,     0,    46,    10,
       0,     1,     0,     5,     0,     3,     0,     0,     0,     0,
       2,   109,     0,     0,   106,     0,   102,    82,     0,     0,
       0,    50,    54,     0,    49,     0,    47,     0,    24,     0,
       0,    20,    21,    42,     0,    11,    13,   110,   104,   107,
       0,     0,    81,    77,     0,    44,    51,     0,     0,     0,
       0,     0,     6,    22,     0,     0,     0,    43,    96,    97,
      98,    99,   100,     0,    86,   116,   115,   118,   120,   122,
       0,   113,     0,   111,   114,     0,     0,    75,   101,    59,
       0,     0,     0,     0,    66,    76,    68,    70,    73,    55,
      58,    57,    84,    85,    83,    89,    90,    88,     0,     0,
      48,    33,    34,    35,    36,    37,    38,    39,     0,    30,
       0,    14,     0,    18,    29,    32,     0,    27,     0,    26,
       0,    12,     0,     0,     0,     0,   108,   103,     0,     0,
       0,     0,     0,    87,     0,     0,    52,     0,     0,     0,
       0,    53,     0,     0,     0,     0,    15,     0,     0,     0,
       0,    23,     0,     0,   105,   117,   119,   121,   112,     0,
       0,    63,    65,     0,    61,    64,    56,     0,    91,     0,
      92,    67,    72,    69,    74,    45,     0,    40,     0,     0,
       0,    19,    25,    28,     0,     7,    78,     0,    60,     0,
       0,    93,    94,     0,     0,     0,    31,     8,     0,     0,
       0,    62,    95,    71,    16,    41,     0,     0,     0,    17,
       0,    80,     9
  };

  const short
  BisonParser::yypgoto_[] =
  {
    -136,  -136,   197,   110,    -2,   121,  -136,  -111,  -136,   -56,
    -124,   191,  -136,  -136,    47,  -133,  -136,    14,    -1,   -59,
     227,  -136,   -50,  -136,   -30,  -136,   -37,    87,  -130,    37,
    -136,    86,    90,  -135,  -136,  -136,  -136,  -136,  -136,  -136,
    -136,  -128,   -47,  -136,  -136,  -136,   -43,  -136,   228,   215,
    -136,    75,   218,   -54,  -136,  -136,  -136,   108,     8
  };

  const short
  BisonParser::yydefgoto_[] =
  {
      -1,     3,     4,    38,   119,    44,    45,   120,   121,   122,
      40,    41,    42,   127,   128,   123,   124,   188,   125,    74,
       6,     7,    35,    36,    30,    31,    93,    94,    95,   173,
     174,    96,    97,    98,    99,   100,    32,    85,    86,    53,
      33,   101,   102,   103,   104,   105,   106,   107,    15,    23,
      24,    81,    26,    82,    83,    77,    78,    79,    84
  };

  const short
  BisonParser::yytable_[] =
  {
      10,    56,   129,    75,    75,   126,   163,    76,    76,   110,
     156,   172,   132,   175,    21,   184,    39,   179,    46,    75,
     108,   187,   200,    76,     9,     8,    75,    87,    43,    67,
      76,   189,   143,    21,    88,    67,    68,    69,    70,    27,
      39,     9,    68,    69,    70,    11,   111,   112,   113,   114,
     115,   116,   117,   142,   144,   177,    71,    72,    80,    28,
     180,     1,    71,    72,    46,   201,   148,    22,   213,   172,
     178,   175,   187,    89,    90,   149,     9,    91,    92,   152,
      73,   133,   145,   209,   168,    29,     2,   166,    75,    25,
     170,    75,    76,   220,     2,    76,   171,    14,    67,    25,
     192,   129,   191,    88,   126,    68,    69,    70,     9,   169,
       5,    67,    43,    22,     1,     5,   153,     2,    68,    69,
      70,    16,    18,    17,    19,    71,    72,    34,    39,    43,
     111,   112,   113,   114,   115,   116,   117,    47,    71,    72,
       9,     9,    67,   118,    43,    21,    91,    92,   203,   149,
      51,     9,    52,    39,    50,   190,    73,    55,    54,     2,
      37,    57,   111,   112,   113,   114,   115,   116,   117,     2,
     162,    58,    60,    59,    62,    65,    61,    64,    67,   -79,
     218,   109,   130,   204,   136,    66,   131,   134,   139,   135,
     216,   138,   146,   140,   141,   151,   137,   157,   160,   154,
     155,   147,    13,   158,   161,   186,   150,   193,   159,   185,
     194,   208,   164,   195,   165,    39,   176,   196,   197,   215,
     198,   210,   199,   202,   205,   206,   207,   214,   217,   219,
     221,    12,   222,    63,   181,   183,   211,   212,   182,    49,
      20,    48,     0,   167
  };

  const short
  BisonParser::yycheck_[] =
  {
       2,    31,    61,    50,    51,    61,   130,    50,    51,    59,
     121,   141,    66,   141,     3,   150,    18,    12,    19,    66,
      57,   154,    12,    66,     3,     3,    73,     3,     7,     5,
      73,   155,    91,     3,    10,     5,    12,    13,    14,     3,
      42,     3,    12,    13,    14,     0,    25,    26,    27,    28,
      29,    30,    31,    90,    12,    40,    32,    33,    50,    23,
      55,    18,    32,    33,    65,    55,    37,    56,   203,   199,
      55,   199,   205,    49,    50,    46,     3,    53,    54,   109,
      50,    73,    40,   194,   138,    49,    21,   134,   135,    14,
     140,   138,   135,   217,    21,   138,     3,    20,     5,    24,
     159,   160,   158,    10,   160,    12,    13,    14,     3,   139,
       0,     5,     7,    56,    18,     5,   118,    21,    12,    13,
      14,    41,    41,    43,    43,    32,    33,     3,   130,     7,
      25,    26,    27,    28,    29,    30,    31,     3,    32,    33,
       3,     3,     5,    38,     7,     3,    53,    54,    45,    46,
      50,     3,     3,   155,    47,   157,    50,    42,    47,    21,
      22,    47,    25,    26,    27,    28,    29,    30,    31,    21,
      22,    44,    41,    45,    42,    45,    47,    44,     5,    43,
     210,    41,    41,     5,    40,    50,    65,    48,    41,    46,
       5,    45,    40,    43,    43,    40,    51,    38,    36,    43,
      42,    48,     5,    46,    40,    39,    52,   160,    48,    42,
      41,    39,    51,    42,    51,   217,    51,    42,    44,   205,
      44,    41,    45,    55,    45,    44,    42,    40,    42,    40,
      42,     4,    42,    42,   147,   149,   199,    55,   148,    24,
      12,    23,    -1,   135
  };

  const unsigned char
  BisonParser::yystos_[] =
  {
       0,    18,    21,    58,    59,    60,    77,    78,     3,     3,
      61,     0,    77,    59,    20,   105,    41,    43,    41,    43,
     105,     3,    56,   106,   107,   108,   109,     3,    23,    49,
      81,    82,    93,    97,     3,    79,    80,    22,    60,    61,
      67,    68,    69,     7,    62,    63,    75,     3,   109,   106,
      47,    50,     3,    96,    47,    42,    81,    47,    44,    45,
      41,    47,    42,    68,    44,    45,    50,     5,    12,    13,
      14,    32,    33,    50,    76,    99,   103,   112,   113,   114,
     115,   108,   110,   111,   115,    94,    95,     3,    10,    49,
      50,    53,    54,    83,    84,    85,    88,    89,    90,    91,
      92,    98,    99,   100,   101,   102,   103,   104,    83,    41,
      79,    25,    26,    27,    28,    29,    30,    31,    38,    61,
      64,    65,    66,    72,    73,    75,    66,    70,    71,    76,
      41,    62,   110,   115,    48,    46,    40,    51,    45,    41,
      43,    43,    83,    76,    12,    40,    40,    48,    37,    46,
      52,    40,    81,    61,    43,    42,    64,    38,    46,    48,
      36,    40,    22,    67,    51,    51,    99,   114,   110,    81,
      79,     3,    85,    86,    87,    98,    51,    40,    55,    12,
      55,    84,    89,    88,    90,    42,    39,    72,    74,    67,
      61,    66,    76,    71,    41,    42,    42,    44,    44,    45,
      12,    55,    55,    45,     5,    45,    44,    42,    39,    64,
      41,    86,    55,    90,    40,    74,     5,    42,    81,    40,
      67,    42,    42
  };

  const unsigned char
  BisonParser::yyr1_[] =
  {
       0,    57,    58,    58,    59,    59,    60,    60,    60,    60,
      61,    62,    62,    63,    64,    64,    65,    65,    66,    66,
      67,    68,    68,    69,    69,    70,    70,    71,    71,    72,
      72,    72,    72,    73,    73,    73,    73,    73,    73,    73,
      74,    74,    75,    76,    77,    77,    78,    79,    79,    80,
      81,    81,    82,    82,    82,    83,    84,    84,    84,    84,
      85,    86,    86,    87,    87,    87,    88,    88,    89,    89,
      90,    90,    90,    91,    91,    92,    92,    94,    93,    95,
      93,    96,    97,    98,    98,    98,    99,   100,   101,   101,
     101,   102,   102,   102,   102,   102,   103,   103,   103,   103,
     103,   104,   105,   105,   105,   105,   106,   106,   107,   108,
     109,   110,   110,   111,   111,   112,   112,   112,   113,   113,
     114,   114,   115
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
       1,     3,     3,     4,     4,     5,     1,     1,     1,     1,
       1,     1,     2,     5,     3,     6,     1,     2,     4,     1,
       2,     1,     3,     1,     1,     1,     1,     3,     1,     3,
       1,     3,     1
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
  "T_FALSE", "T_ARGET", "T_ID", "T_UNION", "T_FARROW", "T_TARROW",
  "T_COLON", "T_SEMICOLON", "'{'", "'}'", "'<'", "'>'", "','", "'*'",
  "'='", "'.'", "'@'", "'('", "')'", "'+'", "'~'", "'['", "']'", "'%'",
  "$accept", "FunctionalProgram", "DataTypeDefinitionsBlocks",
  "DataTypeDefinitionsBlock", "TypeName", "TypeParametersList",
  "TypeParameterDef", "ConstructorsDefinitionList", "ConstructorDef",
  "ConstructorParametersList", "TypesDefinitionList",
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
  const unsigned short
  BisonParser::yyrline_[] =
  {
       0,   186,   186,   196,   208,   214,   222,   227,   233,   239,
     249,   253,   259,   267,   274,   280,   288,   292,   299,   305,
     314,   327,   333,   341,   346,   355,   360,   367,   368,   378,
     382,   386,   391,   398,   399,   400,   401,   402,   403,   404,
     408,   414,   421,   423,   428,   434,   444,   452,   458,   466,
     473,   479,   487,   492,   497,   502,   506,   508,   509,   511,
     518,   525,   531,   539,   543,   544,   549,   550,   559,   560,
     569,   570,   577,   586,   587,   596,   600,   605,   604,   615,
     614,   628,   632,   636,   637,   639,   644,   651,   658,   660,
     661,   665,   671,   677,   684,   691,   701,   702,   703,   704,
     708,   716,   723,   728,   734,   740,   750,   756,   764,   771,
     774,   781,   785,   794,   798,   803,   804,   806,   813,   814,
     823,   824,   832
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
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  BisonParser::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  BisonParser::token_number_type
  BisonParser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    56,     2,     2,
      50,    51,    46,    52,    45,     2,    48,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      43,    47,    44,     2,    49,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    54,     2,    55,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    42,    53,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40
    };
    const unsigned user_token_number_max_ = 295;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 2 "parser.yy" // lalr1.cc:1242
} } // FPTL::Parser
#line 2717 "parser.tab.cc" // lalr1.cc:1242
