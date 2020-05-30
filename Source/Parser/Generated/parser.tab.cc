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

      case 59: // FunctionalProgram
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 390 "parser.tab.cc" // lalr1.cc:652
        break;

      case 60: // DataTypeDefinitionsBlocks
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 400 "parser.tab.cc" // lalr1.cc:652
        break;

      case 61: // DataTypeDefinitionsBlock
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 410 "parser.tab.cc" // lalr1.cc:652
        break;

      case 63: // TypeParametersList
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 420 "parser.tab.cc" // lalr1.cc:652
        break;

      case 64: // TypeParameterDef
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 430 "parser.tab.cc" // lalr1.cc:652
        break;

      case 65: // ConstructorsDefinitionList
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 440 "parser.tab.cc" // lalr1.cc:652
        break;

      case 66: // ConstructorDef
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 450 "parser.tab.cc" // lalr1.cc:652
        break;

      case 67: // ConstructorParametersList
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 460 "parser.tab.cc" // lalr1.cc:652
        break;

      case 68: // TypesDefinitionList
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 470 "parser.tab.cc" // lalr1.cc:652
        break;

      case 69: // TypesDefinitionList2
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 480 "parser.tab.cc" // lalr1.cc:652
        break;

      case 70: // TypeDefinition
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 490 "parser.tab.cc" // lalr1.cc:652
        break;

      case 71: // TypeDefConstructor
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 500 "parser.tab.cc" // lalr1.cc:652
        break;

      case 72: // TypeExpression
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 510 "parser.tab.cc" // lalr1.cc:652
        break;

      case 73: // AtomType
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 520 "parser.tab.cc" // lalr1.cc:652
        break;

      case 75: // TypeExpressionsList
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 530 "parser.tab.cc" // lalr1.cc:652
        break;

      case 78: // Scheme
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scFun);
	delete node;

}
#line 540 "parser.tab.cc" // lalr1.cc:652
        break;

      case 80: // FormalParametersList
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 550 "parser.tab.cc" // lalr1.cc:652
        break;

      case 81: // FormalParameter
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 560 "parser.tab.cc" // lalr1.cc:652
        break;

      case 82: // DefinitionsList
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 570 "parser.tab.cc" // lalr1.cc:652
        break;

      case 83: // Definition
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 580 "parser.tab.cc" // lalr1.cc:652
        break;

      case 84: // Term
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 590 "parser.tab.cc" // lalr1.cc:652
        break;

      case 85: // AtomTerm
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 600 "parser.tab.cc" // lalr1.cc:652
        break;

      case 86: // FuncObjectWithParameters
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 610 "parser.tab.cc" // lalr1.cc:652
        break;

      case 87: // FuncArgumentList
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 620 "parser.tab.cc" // lalr1.cc:652
        break;

      case 88: // FuncParameterName
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 630 "parser.tab.cc" // lalr1.cc:652
        break;

      case 89: // SequentialTerm
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 640 "parser.tab.cc" // lalr1.cc:652
        break;

      case 90: // CompositionTerm
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 650 "parser.tab.cc" // lalr1.cc:652
        break;

      case 91: // ConditionTerm
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 660 "parser.tab.cc" // lalr1.cc:652
        break;

      case 92: // VariantTerm
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 670 "parser.tab.cc" // lalr1.cc:652
        break;

      case 93: // FuncObjectName
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 680 "parser.tab.cc" // lalr1.cc:652
        break;

      case 94: // ConstructionFun
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scFun);
	delete node;

}
#line 690 "parser.tab.cc" // lalr1.cc:652
        break;

      case 99: // ElementaryFunctionName
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 700 "parser.tab.cc" // lalr1.cc:652
        break;

      case 100: // Constructor
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 710 "parser.tab.cc" // lalr1.cc:652
        break;

      case 101: // Destructor
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 720 "parser.tab.cc" // lalr1.cc:652
        break;

      case 102: // BuiltInFunction
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 730 "parser.tab.cc" // lalr1.cc:652
        break;

      case 103: // TupleElement
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 740 "parser.tab.cc" // lalr1.cc:652
        break;

      case 104: // Constant
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 750 "parser.tab.cc" // lalr1.cc:652
        break;

      case 105: // BuiltInFunctionName
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 760 "parser.tab.cc" // lalr1.cc:652
        break;

      case 106: // Application
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scApp);
	delete node;

}
#line 770 "parser.tab.cc" // lalr1.cc:652
        break;

      case 107: // DataInit
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scList);
	delete node;

}
#line 780 "parser.tab.cc" // lalr1.cc:652
        break;

      case 108: // OneDataInit
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scDef);
	delete node;

}
#line 790 "parser.tab.cc" // lalr1.cc:652
        break;

      case 110: // InterpFunProgramName
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scName);
	delete node;

}
#line 800 "parser.tab.cc" // lalr1.cc:652
        break;

      case 111: // Data
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 810 "parser.tab.cc" // lalr1.cc:652
        break;

      case 112: // OneData
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 820 "parser.tab.cc" // lalr1.cc:652
        break;

      case 113: // ValueAtom
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 830 "parser.tab.cc" // lalr1.cc:652
        break;

      case 114: // ValueConstructor
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 840 "parser.tab.cc" // lalr1.cc:652
        break;

      case 115: // ValueComposition
#line 62 "parser.yy" // lalr1.cc:652
        {
	ASTNode * node = (yysym.value.scNode);
	delete node;

}
#line 850 "parser.tab.cc" // lalr1.cc:652
        break;

      case 116: // Value
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
#line 186 "parser.yy" // lalr1.cc:919
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
#line 196 "parser.yy" // lalr1.cc:919
    {
			mASTRoot = new FunctionalProgram( 0, (yystack_[1].value.scFun), (yystack_[0].value.scApp) );
			(yystack_[1].value.scFun)->mParent = mASTRoot;
			(yystack_[0].value.scApp)->mParent = mASTRoot;
			(yylhs.value.scNode) = 0;
		}
#line 1130 "parser.tab.cc" // lalr1.cc:919
    break;

  case 4:
#line 208 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = new ListNode(  ASTNode::DataTypeDefinitionsBlocks );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scList);
		}
#line 1140 "parser.tab.cc" // lalr1.cc:919
    break;

  case 5:
#line 214 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scNode) );
			(yystack_[1].value.scNode)->mParent = (yystack_[0].value.scList);
		}
#line 1149 "parser.tab.cc" // lalr1.cc:919
    break;

  case 6:
#line 222 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[3].value.scIdent), (yystack_[1].value.scList), 0, 0 );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scNode);
		}
#line 1158 "parser.tab.cc" // lalr1.cc:919
    break;

  case 7:
#line 227 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[6].value.scIdent), (yystack_[1].value.scList), (yystack_[4].value.scList), 0 );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scNode);
			(yystack_[4].value.scList)->mParent = (yylhs.value.scNode);
		}
#line 1168 "parser.tab.cc" // lalr1.cc:919
    break;

  case 8:
#line 233 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[7].value.scIdent), (yystack_[1].value.scList), 0, (yystack_[3].value.scList) );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scNode);
			(yystack_[3].value.scList)->mParent = (yylhs.value.scNode);
		}
#line 1178 "parser.tab.cc" // lalr1.cc:919
    break;

  case 9:
#line 239 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new DataNode(  (yystack_[10].value.scIdent), (yystack_[1].value.scList), (yystack_[8].value.scList), (yystack_[3].value.scList) );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scNode);
			(yystack_[8].value.scList)->mParent = (yylhs.value.scNode);
			(yystack_[3].value.scList)->mParent = (yylhs.value.scNode);
		}
#line 1189 "parser.tab.cc" // lalr1.cc:919
    break;

  case 10:
#line 248 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scIdent) = (yystack_[0].value.scIdent); }
#line 1195 "parser.tab.cc" // lalr1.cc:919
    break;

  case 11:
#line 253 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = new ListNode( ASTNode::TypeParametersList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
			(yystack_[0].value.scDef)->mParent = (yylhs.value.scList);
		}
#line 1205 "parser.tab.cc" // lalr1.cc:919
    break;

  case 12:
#line 259 "parser.yy" // lalr1.cc:919
    {		
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scDef) );
			(yystack_[2].value.scDef)->mParent = (yystack_[0].value.scList);
		}
#line 1214 "parser.tab.cc" // lalr1.cc:919
    break;

  case 13:
#line 267 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::TypeParameterDefinition, (yystack_[0].value.scIdent), 0 );
		}
#line 1222 "parser.tab.cc" // lalr1.cc:919
    break;

  case 14:
#line 274 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = new ListNode( ASTNode::ConstructorsDefinitionList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scList);
		}
#line 1232 "parser.tab.cc" // lalr1.cc:919
    break;

  case 15:
#line 280 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scNode) );
			(yystack_[1].value.scNode)->mParent = (yystack_[0].value.scList);
		}
#line 1241 "parser.tab.cc" // lalr1.cc:919
    break;

  case 16:
#line 288 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ConstructorNode( (yystack_[1].value.scIdent), 0, (yystack_[3].value.scIdent) );
		}
#line 1249 "parser.tab.cc" // lalr1.cc:919
    break;

  case 17:
#line 292 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ConstructorNode( (yystack_[1].value.scIdent), (yystack_[5].value.scList), (yystack_[3].value.scIdent) );
			(yystack_[5].value.scList)->mParent = (yylhs.value.scNode);
		}
#line 1258 "parser.tab.cc" // lalr1.cc:919
    break;

  case 18:
#line 299 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = new ListNode( ASTNode::ConstructorParametersList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scName) );
			(yystack_[0].value.scName)->mParent = (yylhs.value.scList);
		}
#line 1268 "parser.tab.cc" // lalr1.cc:919
    break;

  case 19:
#line 305 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scName) );
			(yystack_[2].value.scName)->mParent = (yystack_[0].value.scList);
		}
#line 1277 "parser.tab.cc" // lalr1.cc:919
    break;

  case 20:
#line 314 "parser.yy" // lalr1.cc:919
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
#line 327 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = new ListNode( ASTNode::TypesDefinitionList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
			(yystack_[0].value.scDef)->mParent = (yylhs.value.scList);
		}
#line 1301 "parser.tab.cc" // lalr1.cc:919
    break;

  case 22:
#line 333 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scDef) );
			(yystack_[1].value.scDef)->mParent = (yystack_[0].value.scList);
		}
#line 1310 "parser.tab.cc" // lalr1.cc:919
    break;

  case 23:
#line 341 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::TypeDefinition, (yystack_[3].value.scIdent), (yystack_[1].value.scNode) );
			(yystack_[1].value.scNode)->mParent = (yylhs.value.scDef);
		}
#line 1319 "parser.tab.cc" // lalr1.cc:919
    break;

  case 24:
#line 346 "parser.yy" // lalr1.cc:919
    {
			pSupport->semanticError( ParserErrTypes::NestedDataDefinition, static_cast<DataNode*>((yystack_[0].value.scNode))->getDataName() );
			delete (yystack_[0].value.scNode);
			(yylhs.value.scDef) = 0;
		}
#line 1329 "parser.tab.cc" // lalr1.cc:919
    break;

  case 25:
#line 355 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::TypeConstructorDefinition, (yystack_[0].value.scIdent), (yystack_[2].value.scList) );
			(yystack_[2].value.scList)->mParent = (yylhs.value.scNode);
		}
#line 1338 "parser.tab.cc" // lalr1.cc:919
    break;

  case 26:
#line 360 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::TypeConstructorDefinition, (yystack_[0].value.scIdent), 0 );
		}
#line 1346 "parser.tab.cc" // lalr1.cc:919
    break;

  case 27:
#line 366 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1352 "parser.tab.cc" // lalr1.cc:919
    break;

  case 28:
#line 368 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::TypeExpression, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1362 "parser.tab.cc" // lalr1.cc:919
    break;

  case 29:
#line 378 "parser.yy" // lalr1.cc:919
    {	
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scToken), NameRefNode::BaseType, nullptr );
		}
#line 1370 "parser.tab.cc" // lalr1.cc:919
    break;

  case 30:
#line 382 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::Type, nullptr );
		}
#line 1378 "parser.tab.cc" // lalr1.cc:919
    break;

  case 31:
#line 386 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[3].value.scIdent), NameRefNode::Template, (yystack_[1].value.scList) );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scName);
		}
#line 1387 "parser.tab.cc" // lalr1.cc:919
    break;

  case 32:
#line 391 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::TypeParamName, nullptr );
		}
#line 1395 "parser.tab.cc" // lalr1.cc:919
    break;

  case 33:
#line 397 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scToken) = (yystack_[0].value.scToken); }
#line 1401 "parser.tab.cc" // lalr1.cc:919
    break;

  case 34:
#line 398 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scToken) = (yystack_[0].value.scToken); }
#line 1407 "parser.tab.cc" // lalr1.cc:919
    break;

  case 35:
#line 399 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scToken) = (yystack_[0].value.scToken); }
#line 1413 "parser.tab.cc" // lalr1.cc:919
    break;

  case 36:
#line 400 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scToken) = (yystack_[0].value.scToken); }
#line 1419 "parser.tab.cc" // lalr1.cc:919
    break;

  case 37:
#line 401 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scToken) = (yystack_[0].value.scToken); }
#line 1425 "parser.tab.cc" // lalr1.cc:919
    break;

  case 38:
#line 402 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scToken) = (yystack_[0].value.scToken); }
#line 1431 "parser.tab.cc" // lalr1.cc:919
    break;

  case 39:
#line 403 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scToken) = (yystack_[0].value.scToken); }
#line 1437 "parser.tab.cc" // lalr1.cc:919
    break;

  case 40:
#line 408 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = new ListNode( ASTNode::TypeExpressionsList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scName) );
			(yystack_[0].value.scName)->mParent = (yylhs.value.scList);
		}
#line 1447 "parser.tab.cc" // lalr1.cc:919
    break;

  case 41:
#line 414 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scName) );
			(yystack_[2].value.scName)->mParent = (yystack_[0].value.scList);
		}
#line 1456 "parser.tab.cc" // lalr1.cc:919
    break;

  case 42:
#line 420 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scIdent) = (yystack_[0].value.scIdent); }
#line 1462 "parser.tab.cc" // lalr1.cc:919
    break;

  case 43:
#line 422 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scIdent) = (yystack_[0].value.scIdent); }
#line 1468 "parser.tab.cc" // lalr1.cc:919
    break;

  case 44:
#line 428 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[3].value.scIdent), (yystack_[1].value.scList), 0 );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scFun);
			pSupport->popIdent();
		}
#line 1478 "parser.tab.cc" // lalr1.cc:919
    break;

  case 45:
#line 434 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[6].value.scIdent), (yystack_[1].value.scList), (yystack_[4].value.scList) );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scFun);
			(yystack_[4].value.scList)->mParent = (yylhs.value.scFun);
			pSupport->popIdent();
		}
#line 1489 "parser.tab.cc" // lalr1.cc:919
    break;

  case 46:
#line 444 "parser.yy" // lalr1.cc:919
    {
			pSupport->pushIdent( (yystack_[0].value.scIdent) );
			(yylhs.value.scIdent) = (yystack_[0].value.scIdent);
		}
#line 1498 "parser.tab.cc" // lalr1.cc:919
    break;

  case 47:
#line 452 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = new ListNode( ASTNode::FormalParametersList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
			(yystack_[0].value.scDef)->mParent = (yylhs.value.scList);
		}
#line 1508 "parser.tab.cc" // lalr1.cc:919
    break;

  case 48:
#line 458 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scDef) );
			(yystack_[2].value.scDef)->mParent = (yystack_[0].value.scList);
		}
#line 1517 "parser.tab.cc" // lalr1.cc:919
    break;

  case 49:
#line 466 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::FunctionParameterDefinition, (yystack_[0].value.scIdent), 0 );
		}
#line 1525 "parser.tab.cc" // lalr1.cc:919
    break;

  case 50:
#line 473 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = new ListNode( ASTNode::DefinitionsList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scList);
		}
#line 1535 "parser.tab.cc" // lalr1.cc:919
    break;

  case 51:
#line 479 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scNode) );
			(yystack_[1].value.scNode)->mParent = (yystack_[0].value.scList);
		}
#line 1544 "parser.tab.cc" // lalr1.cc:919
    break;

  case 52:
#line 487 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::Definition, pSupport->getTopIdent(), (yystack_[1].value.scNode) );
			(yystack_[1].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1553 "parser.tab.cc" // lalr1.cc:919
    break;

  case 53:
#line 492 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new DefinitionNode( ASTNode::Definition, (yystack_[3].value.scIdent), (yystack_[1].value.scNode) );
			(yystack_[1].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1562 "parser.tab.cc" // lalr1.cc:919
    break;

  case 54:
#line 497 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scFun); }
#line 1568 "parser.tab.cc" // lalr1.cc:919
    break;

  case 55:
#line 501 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1574 "parser.tab.cc" // lalr1.cc:919
    break;

  case 56:
#line 506 "parser.yy" // lalr1.cc:919
    {	(yylhs.value.scNode) = (yystack_[1].value.scNode); }
#line 1580 "parser.tab.cc" // lalr1.cc:919
    break;

  case 57:
#line 507 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1586 "parser.tab.cc" // lalr1.cc:919
    break;

  case 58:
#line 509 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1592 "parser.tab.cc" // lalr1.cc:919
    break;

  case 59:
#line 511 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new NameRefNode( pSupport->getTopIdent(), ASTNode::FuncObjectName, nullptr );
		}
#line 1600 "parser.tab.cc" // lalr1.cc:919
    break;

  case 60:
#line 518 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[3].value.scIdent), NameRefNode::FuncObjectWithParameters, (yystack_[1].value.scList) );
			(yystack_[1].value.scList)->mParent = (yylhs.value.scName);
		}
#line 1609 "parser.tab.cc" // lalr1.cc:919
    break;

  case 61:
#line 525 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = new ListNode( ASTNode::FuncArgumentsList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scNode) );
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scList);
		}
#line 1619 "parser.tab.cc" // lalr1.cc:919
    break;

  case 62:
#line 531 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[2].value.scNode) );
			(yystack_[2].value.scNode)->mParent = (yystack_[0].value.scList);
		}
#line 1628 "parser.tab.cc" // lalr1.cc:919
    break;

  case 63:
#line 539 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::FuncParameterName, nullptr );
		}
#line 1636 "parser.tab.cc" // lalr1.cc:919
    break;

  case 64:
#line 542 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1642 "parser.tab.cc" // lalr1.cc:919
    break;

  case 65:
#line 544 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1648 "parser.tab.cc" // lalr1.cc:919
    break;

  case 66:
#line 548 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1654 "parser.tab.cc" // lalr1.cc:919
    break;

  case 67:
#line 550 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::SequentialTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1664 "parser.tab.cc" // lalr1.cc:919
    break;

  case 68:
#line 558 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1670 "parser.tab.cc" // lalr1.cc:919
    break;

  case 69:
#line 560 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::CompositionTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1680 "parser.tab.cc" // lalr1.cc:919
    break;

  case 70:
#line 568 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1686 "parser.tab.cc" // lalr1.cc:919
    break;

  case 71:
#line 570 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ConditionNode( ASTNode::ConditionTerm, (yystack_[4].value.scNode), (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
			(yystack_[4].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1697 "parser.tab.cc" // lalr1.cc:919
    break;

  case 72:
#line 577 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ConditionNode( ASTNode::ConditionTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode), nullptr );
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1707 "parser.tab.cc" // lalr1.cc:919
    break;

  case 73:
#line 585 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1713 "parser.tab.cc" // lalr1.cc:919
    break;

  case 74:
#line 587 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::VariantTerm, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 1723 "parser.tab.cc" // lalr1.cc:919
    break;

  case 75:
#line 596 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::FuncObjectName, nullptr );
		}
#line 1731 "parser.tab.cc" // lalr1.cc:919
    break;

  case 76:
#line 599 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scName) = (yystack_[0].value.scName); }
#line 1737 "parser.tab.cc" // lalr1.cc:919
    break;

  case 77:
#line 604 "parser.yy" // lalr1.cc:919
    {
			pSupport->pushIdent( (yystack_[0].value.scIdent) );
		}
#line 1745 "parser.tab.cc" // lalr1.cc:919
    break;

  case 78:
#line 608 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[4].value.scIdent), (yystack_[1].value.scList), 0 );
			pSupport->popIdent();
			(yystack_[1].value.scList)->mParent = (yylhs.value.scFun);
		}
#line 1755 "parser.tab.cc" // lalr1.cc:919
    break;

  case 79:
#line 614 "parser.yy" // lalr1.cc:919
    {
			pSupport->pushIdent( (yystack_[0].value.scIdent) );
		}
#line 1763 "parser.tab.cc" // lalr1.cc:919
    break;

  case 80:
#line 618 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scFun) = new FunctionNode( (yystack_[7].value.scIdent), (yystack_[1].value.scList), (yystack_[4].value.scList) );
			pSupport->popIdent();
			(yystack_[1].value.scList)->mParent = (yylhs.value.scFun);
			(yystack_[4].value.scList)->mParent = (yylhs.value.scFun);
		}
#line 1774 "parser.tab.cc" // lalr1.cc:919
    break;

  case 81:
#line 627 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scIdent) = (yystack_[0].value.scIdent); }
#line 1780 "parser.tab.cc" // lalr1.cc:919
    break;

  case 82:
#line 631 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scIdent) = (yystack_[0].value.scIdent); }
#line 1786 "parser.tab.cc" // lalr1.cc:919
    break;

  case 83:
#line 635 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1792 "parser.tab.cc" // lalr1.cc:919
    break;

  case 84:
#line 637 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1798 "parser.tab.cc" // lalr1.cc:919
    break;

  case 85:
#line 639 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1804 "parser.tab.cc" // lalr1.cc:919
    break;

  case 86:
#line 644 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::ConstructorName, nullptr );
		}
#line 1812 "parser.tab.cc" // lalr1.cc:919
    break;

  case 87:
#line 651 "parser.yy" // lalr1.cc:919
    {	
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::DestructorName, nullptr );
		}
#line 1820 "parser.tab.cc" // lalr1.cc:919
    break;

  case 88:
#line 658 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 1826 "parser.tab.cc" // lalr1.cc:919
    break;

  case 89:
#line 659 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1832 "parser.tab.cc" // lalr1.cc:919
    break;

  case 90:
#line 660 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1838 "parser.tab.cc" // lalr1.cc:919
    break;

  case 91:
#line 665 "parser.yy" // lalr1.cc:919
    {
			ConstantNode * number = static_cast<ConstantNode*>( (yystack_[1].value.scNode) );
			(yylhs.value.scNode) = new TakeNode( number->getConstant(), number->getConstant() );
			delete number;
		}
#line 1848 "parser.tab.cc" // lalr1.cc:919
    break;

  case 92:
#line 671 "parser.yy" // lalr1.cc:919
    {
			Ident from = { (yystack_[1].value.scToken).Col, (yystack_[1].value.scToken).Line, nullptr };
			Ident to = { (yystack_[1].value.scToken).Col, (yystack_[1].value.scToken).Line, nullptr };
			(yylhs.value.scNode) = new TakeNode( from, to);
		}
#line 1858 "parser.tab.cc" // lalr1.cc:919
    break;

  case 93:
#line 677 "parser.yy" // lalr1.cc:919
    {
			ConstantNode * from = static_cast<ConstantNode*>( (yystack_[2].value.scNode) );
			Ident to = { (yystack_[1].value.scToken).Col, (yystack_[1].value.scToken).Line, nullptr };
			(yylhs.value.scNode) = new TakeNode( from->getConstant(), to);
			delete from;
		}
#line 1869 "parser.tab.cc" // lalr1.cc:919
    break;

  case 94:
#line 684 "parser.yy" // lalr1.cc:919
    {
			Ident from = { (yystack_[2].value.scToken).Col, (yystack_[2].value.scToken).Line, nullptr };
			ConstantNode * to = static_cast<ConstantNode*>( (yystack_[1].value.scNode) );
			(yylhs.value.scNode) = new TakeNode( from, to->getConstant() );
			delete to;
		}
#line 1880 "parser.tab.cc" // lalr1.cc:919
    break;

  case 95:
#line 691 "parser.yy" // lalr1.cc:919
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
#line 700 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1898 "parser.tab.cc" // lalr1.cc:919
    break;

  case 97:
#line 701 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1904 "parser.tab.cc" // lalr1.cc:919
    break;

  case 98:
#line 702 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 1910 "parser.tab.cc" // lalr1.cc:919
    break;

  case 99:
#line 704 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ConstantNode( ASTNode::TrueValue, (yystack_[0].value.scToken) );
		}
#line 1918 "parser.tab.cc" // lalr1.cc:919
    break;

  case 100:
#line 708 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ConstantNode( ASTNode::FalseValue, (yystack_[0].value.scToken) );
		}
#line 1926 "parser.tab.cc" // lalr1.cc:919
    break;

  case 101:
#line 716 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scName) = new NameRefNode( (yystack_[0].value.scIdent), NameRefNode::BuildInFunction, nullptr );
		}
#line 1934 "parser.tab.cc" // lalr1.cc:919
    break;

  case 102:
#line 723 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[0].value.scName), 0, 0 );
			(yystack_[0].value.scName)->mParent = (yylhs.value.scApp);
		}
#line 1943 "parser.tab.cc" // lalr1.cc:919
    break;

  case 103:
#line 728 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[3].value.scName), (yystack_[1].value.scNode), 0 );
			(yystack_[3].value.scName)->mParent = (yylhs.value.scApp);
			(yystack_[1].value.scNode)->mParent = (yylhs.value.scApp);
		}
#line 1953 "parser.tab.cc" // lalr1.cc:919
    break;

  case 104:
#line 734 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[0].value.scName), 0, (yystack_[1].value.scList) ); 
			(yystack_[0].value.scName)->mParent = (yylhs.value.scApp);
			(yystack_[1].value.scList)->mParent = (yylhs.value.scApp);
		}
#line 1963 "parser.tab.cc" // lalr1.cc:919
    break;

  case 105:
#line 740 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scApp) = new ApplicationBlock( (yystack_[3].value.scName), (yystack_[1].value.scNode), (yystack_[4].value.scList) );
			(yystack_[3].value.scName)->mParent = (yylhs.value.scApp);
			(yystack_[1].value.scNode)->mParent = (yylhs.value.scApp);
			(yystack_[4].value.scList)->mParent = (yylhs.value.scApp);
		}
#line 1974 "parser.tab.cc" // lalr1.cc:919
    break;

  case 106:
#line 750 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = new ListNode( ASTNode::InputVarDefinitionList );
			(yylhs.value.scList)->addElement( (yystack_[0].value.scDef) );
			(yystack_[0].value.scDef)->mParent = (yylhs.value.scList);
		}
#line 1984 "parser.tab.cc" // lalr1.cc:919
    break;

  case 107:
#line 756 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scList) = (yystack_[0].value.scList)->addElement( (yystack_[1].value.scDef) );
			(yystack_[1].value.scDef)->mParent = (yystack_[0].value.scList);
		}
#line 1993 "parser.tab.cc" // lalr1.cc:919
    break;

  case 108:
#line 764 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scDef) = new DefinitionNode( ASTNode::InputVarDefinition, (yystack_[3].value.scIdent), (yystack_[1].value.scNode) );
			(yystack_[1].value.scNode)->mParent = (yylhs.value.scDef);
		}
#line 2002 "parser.tab.cc" // lalr1.cc:919
    break;

  case 109:
#line 770 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scIdent) = (yystack_[0].value.scIdent); }
#line 2008 "parser.tab.cc" // lalr1.cc:919
    break;

  case 110:
#line 774 "parser.yy" // lalr1.cc:919
    { 
			(yylhs.value.scName) = new NameRefNode((yystack_[0].value.scIdent), ASTNode::RunningSchemeName, nullptr );
		}
#line 2016 "parser.tab.cc" // lalr1.cc:919
    break;

  case 111:
#line 781 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = (yystack_[0].value.scNode);
		}
#line 2024 "parser.tab.cc" // lalr1.cc:919
    break;

  case 112:
#line 785 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ExpressionNode(ASTNode::InputVarList, (yystack_[2].value.scNode), (yystack_[0].value.scNode));
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 2034 "parser.tab.cc" // lalr1.cc:919
    break;

  case 113:
#line 794 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new NameRefNode( (yystack_[0].value.scIdent), ASTNode::InputVarName, nullptr );
		}
#line 2042 "parser.tab.cc" // lalr1.cc:919
    break;

  case 114:
#line 797 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 2048 "parser.tab.cc" // lalr1.cc:919
    break;

  case 115:
#line 802 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 2054 "parser.tab.cc" // lalr1.cc:919
    break;

  case 116:
#line 804 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scName); }
#line 2060 "parser.tab.cc" // lalr1.cc:919
    break;

  case 117:
#line 806 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = (yystack_[1].value.scNode);
		}
#line 2068 "parser.tab.cc" // lalr1.cc:919
    break;

  case 118:
#line 812 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 2074 "parser.tab.cc" // lalr1.cc:919
    break;

  case 119:
#line 814 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ValueConstructor, (yystack_[2].value.scNode), (yystack_[0].value.scName) );
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scName)->mParent = (yylhs.value.scNode);
		}
#line 2084 "parser.tab.cc" // lalr1.cc:919
    break;

  case 120:
#line 822 "parser.yy" // lalr1.cc:919
    { (yylhs.value.scNode) = (yystack_[0].value.scNode); }
#line 2090 "parser.tab.cc" // lalr1.cc:919
    break;

  case 121:
#line 824 "parser.yy" // lalr1.cc:919
    {
			(yylhs.value.scNode) = new ExpressionNode( ASTNode::ValueComposition, (yystack_[2].value.scNode), (yystack_[0].value.scNode) );
			(yystack_[2].value.scNode)->mParent = (yylhs.value.scNode);
			(yystack_[0].value.scNode)->mParent = (yylhs.value.scNode);
		}
#line 2100 "parser.tab.cc" // lalr1.cc:919
    break;

  case 122:
#line 831 "parser.yy" // lalr1.cc:919
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


  const short BisonParser::yypact_ninf_ = -140;

  const signed char BisonParser::yytable_ninf_ = -80;

  const short
  BisonParser::yypact_[] =
  {
     104,    21,    59,    74,    71,    75,    98,    -5,  -140,  -140,
      38,  -140,    98,  -140,    11,  -140,    15,    91,    30,   110,
    -140,  -140,   120,    67,   126,    82,    84,  -140,   133,    99,
     108,    15,  -140,   106,  -140,   109,   113,   116,  -140,   114,
     117,  -140,    56,  -140,   118,   121,  -140,  -140,   122,  -140,
      94,   100,  -140,   132,    31,  -140,  -140,    31,   124,    91,
     112,   141,  -140,  -140,   135,   110,   100,  -140,  -140,  -140,
    -140,  -140,  -140,    94,  -140,  -140,  -140,   111,   129,  -140,
     131,  -140,   127,   134,  -140,   148,   147,   149,  -140,  -140,
      31,   185,     8,   146,  -140,  -140,   144,    73,  -140,   142,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,   150,    15,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,    59,   152,
     157,   112,   159,   153,  -140,  -140,   154,   163,   155,  -140,
      39,  -140,   158,   160,   185,    94,  -140,  -140,   100,    15,
      91,    43,   161,  -140,   -17,    16,  -140,    31,    31,    31,
      31,  -140,   164,   162,   156,    56,  -140,    59,   156,   185,
     141,  -140,   166,   167,  -140,  -140,  -140,  -140,  -140,   168,
     171,   149,  -140,   173,   174,  -140,  -140,    17,  -140,   165,
    -140,  -140,    87,   144,  -140,  -140,   197,   175,   177,   170,
     172,  -140,  -140,  -140,   112,  -140,  -140,   182,  -140,    43,
     169,  -140,  -140,    31,   178,   156,  -140,  -140,   199,   186,
      15,  -140,  -140,  -140,  -140,  -140,   180,    56,   187,  -140,
     188,  -140,  -140
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
    -140,  -140,   218,    49,    -2,   176,  -140,  -111,  -140,   -56,
    -124,   189,  -140,  -140,    70,  -139,  -140,    27,     2,   -59,
     229,  -140,   -50,  -140,   -30,  -140,   -32,    88,  -130,    35,
    -140,    89,    92,  -133,  -140,  -140,  -140,  -140,  -140,  -140,
    -140,  -128,   -47,  -140,  -140,  -140,   -43,  -140,   224,   213,
    -140,    97,   216,   -54,  -140,  -140,  -140,   107,   -23
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
     156,   172,   132,   175,    21,   187,    39,   184,    27,    75,
     144,    46,   177,    76,     8,   108,    75,    80,   179,   200,
      76,   189,   143,     9,    87,    16,    67,    17,    28,   178,
      39,    88,     9,    68,    69,    70,   171,   145,    67,     5,
     133,     2,    37,    88,     5,    68,    69,    70,   142,     9,
       2,   162,     9,    71,    72,    29,   187,    46,    22,   172,
     213,   175,   180,   201,    11,    71,    72,     2,    18,   152,
      19,    89,    90,   209,   168,    91,    92,   166,    75,     1,
     170,    75,    76,   220,    34,    76,     2,    91,    92,    67,
     192,   129,   191,    21,   126,    67,    68,    69,    70,   169,
     148,    25,    68,    69,    70,     9,   153,    43,    14,    43,
     149,    25,     1,    47,    22,     2,    71,    72,    39,    21,
      50,   203,    71,    72,   149,    51,    52,   111,   112,   113,
     114,   115,   116,   117,     9,    73,    67,    54,    43,    55,
     118,    73,    58,    39,    57,   190,    60,    59,    62,     9,
     134,    64,    61,    43,   109,    65,   111,   112,   113,   114,
     115,   116,   117,    66,   -79,   130,   135,   136,   138,   137,
     218,   111,   112,   113,   114,   115,   116,   117,   139,   140,
      67,   141,   146,   147,   154,   150,   151,   157,   155,   160,
     158,   161,   204,   159,   216,   185,   194,   186,   195,   196,
     164,   207,   165,   176,   197,    39,   198,   208,   199,   205,
     206,   202,   210,    13,   214,   212,   219,   217,   221,   222,
     193,    63,   215,    12,   211,   181,    20,    49,   183,    48,
     182,   131,   167
  };

  const unsigned char
  BisonParser::yycheck_[] =
  {
       2,    31,    61,    50,    51,    61,   130,    50,    51,    59,
     121,   141,    66,   141,     3,   154,    18,   150,     3,    66,
      12,    19,    39,    66,     3,    57,    73,    50,    12,    12,
      73,   155,    91,     3,     3,    40,     5,    42,    23,    56,
      42,    10,     3,    12,    13,    14,     3,    39,     5,     0,
      73,    21,    22,    10,     5,    12,    13,    14,    90,     3,
      21,    22,     3,    32,    33,    50,   205,    65,    57,   199,
     203,   199,    56,    56,     0,    32,    33,    21,    40,   109,
      42,    50,    51,   194,   138,    54,    55,   134,   135,    18,
     140,   138,   135,   217,     3,   138,    21,    54,    55,     5,
     159,   160,   158,     3,   160,     5,    12,    13,    14,   139,
      37,    14,    12,    13,    14,     3,   118,     7,    20,     7,
      47,    24,    18,     3,    57,    21,    32,    33,   130,     3,
      48,    44,    32,    33,    47,    51,     3,    25,    26,    27,
      28,    29,    30,    31,     3,    51,     5,    48,     7,    41,
      38,    51,    43,   155,    48,   157,    40,    44,    41,     3,
      49,    43,    48,     7,    40,    44,    25,    26,    27,    28,
      29,    30,    31,    51,    42,    40,    47,    46,    44,    52,
     210,    25,    26,    27,    28,    29,    30,    31,    40,    42,
       5,    42,    46,    49,    42,    53,    46,    38,    41,    36,
      47,    46,     5,    49,     5,    41,    40,    45,    41,    41,
      52,    41,    52,    52,    43,   217,    43,    45,    44,    44,
      43,    56,    40,     5,    46,    56,    46,    41,    41,    41,
     160,    42,   205,     4,   199,   147,    12,    24,   149,    23,
     148,    65,   135
  };

  const unsigned char
  BisonParser::yystos_[] =
  {
       0,    18,    21,    59,    60,    61,    78,    79,     3,     3,
      62,     0,    78,    60,    20,   106,    40,    42,    40,    42,
     106,     3,    57,   107,   108,   109,   110,     3,    23,    50,
      82,    83,    94,    98,     3,    80,    81,    22,    61,    62,
      68,    69,    70,     7,    63,    64,    76,     3,   110,   107,
      48,    51,     3,    97,    48,    41,    82,    48,    43,    44,
      40,    48,    41,    69,    43,    44,    51,     5,    12,    13,
      14,    32,    33,    51,    77,   100,   104,   113,   114,   115,
     116,   109,   111,   112,   116,    95,    96,     3,    10,    50,
      51,    54,    55,    84,    85,    86,    89,    90,    91,    92,
      93,    99,   100,   101,   102,   103,   104,   105,    84,    40,
      80,    25,    26,    27,    28,    29,    30,    31,    38,    62,
      65,    66,    67,    73,    74,    76,    67,    71,    72,    77,
      40,    63,   111,   116,    49,    47,    46,    52,    44,    40,
      42,    42,    84,    77,    12,    39,    46,    49,    37,    47,
      53,    46,    82,    62,    42,    41,    65,    38,    47,    49,
      36,    46,    22,    68,    52,    52,   100,   115,   111,    82,
      80,     3,    86,    87,    88,    99,    52,    39,    56,    12,
      56,    85,    90,    89,    91,    41,    45,    73,    75,    68,
      62,    67,    77,    72,    40,    41,    41,    43,    43,    44,
      12,    56,    56,    44,     5,    44,    43,    41,    45,    65,
      40,    87,    56,    91,    46,    75,     5,    41,    82,    46,
      68,    41,    41
  };

  const unsigned char
  BisonParser::yyr1_[] =
  {
       0,    58,    59,    59,    60,    60,    61,    61,    61,    61,
      62,    63,    63,    64,    65,    65,    66,    66,    67,    67,
      68,    69,    69,    70,    70,    71,    71,    72,    72,    73,
      73,    73,    73,    74,    74,    74,    74,    74,    74,    74,
      75,    75,    76,    77,    78,    78,    79,    80,    80,    81,
      82,    82,    83,    83,    83,    84,    85,    85,    85,    85,
      86,    87,    87,    88,    88,    88,    89,    89,    90,    90,
      91,    91,    91,    92,    92,    93,    93,    95,    94,    96,
      94,    97,    98,    99,    99,    99,   100,   101,   102,   102,
     102,   103,   103,   103,   103,   103,   104,   104,   104,   104,
     104,   105,   106,   106,   106,   106,   107,   107,   108,   109,
     110,   111,   111,   112,   112,   113,   113,   113,   114,   114,
     115,   115,   116
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
  "T_COLON", "'{'", "'}'", "'<'", "'>'", "','", "':'", "';'", "'*'", "'='",
  "'.'", "'@'", "'('", "')'", "'+'", "'~'", "'['", "']'", "'%'", "$accept",
  "FunctionalProgram", "DataTypeDefinitionsBlocks",
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
       0,   185,   185,   195,   207,   213,   221,   226,   232,   238,
     248,   252,   258,   266,   273,   279,   287,   291,   298,   304,
     313,   326,   332,   340,   345,   354,   359,   366,   367,   377,
     381,   385,   390,   397,   398,   399,   400,   401,   402,   403,
     407,   413,   420,   422,   427,   433,   443,   451,   457,   465,
     472,   478,   486,   491,   496,   501,   505,   507,   508,   510,
     517,   524,   530,   538,   542,   543,   548,   549,   558,   559,
     568,   569,   576,   585,   586,   595,   599,   604,   603,   614,
     613,   627,   631,   635,   636,   638,   643,   650,   657,   659,
     660,   664,   670,   676,   683,   690,   700,   701,   702,   703,
     707,   715,   722,   727,   733,   739,   749,   755,   763,   770,
     773,   780,   784,   793,   797,   802,   803,   805,   812,   813,
     822,   823,   831
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
       2,     2,     2,     2,     2,     2,     2,    57,     2,     2,
      51,    52,    47,    53,    44,     2,    49,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    45,    46,
      42,    48,    43,     2,    50,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    55,     2,    56,     2,     2,     2,     2,     2,     2,
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
    const unsigned user_token_number_max_ = 294;
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
