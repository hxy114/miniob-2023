/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}


#line 115 "yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_CALC = 9,                       /* CALC  */
  YYSYMBOL_SELECT = 10,                    /* SELECT  */
  YYSYMBOL_DESC = 11,                      /* DESC  */
  YYSYMBOL_SHOW = 12,                      /* SHOW  */
  YYSYMBOL_SYNC = 13,                      /* SYNC  */
  YYSYMBOL_INSERT = 14,                    /* INSERT  */
  YYSYMBOL_DELETE = 15,                    /* DELETE  */
  YYSYMBOL_UPDATE = 16,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 17,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 18,                    /* RBRACE  */
  YYSYMBOL_COMMA = 19,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 20,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 21,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 22,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 23,                     /* INT_T  */
  YYSYMBOL_STRING_T = 24,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 25,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 26,                    /* DATE_T  */
  YYSYMBOL_HELP = 27,                      /* HELP  */
  YYSYMBOL_EXIT = 28,                      /* EXIT  */
  YYSYMBOL_DOT = 29,                       /* DOT  */
  YYSYMBOL_INTO = 30,                      /* INTO  */
  YYSYMBOL_VALUES = 31,                    /* VALUES  */
  YYSYMBOL_FROM = 32,                      /* FROM  */
  YYSYMBOL_WHERE = 33,                     /* WHERE  */
  YYSYMBOL_AND = 34,                       /* AND  */
  YYSYMBOL_SET = 35,                       /* SET  */
  YYSYMBOL_ON = 36,                        /* ON  */
  YYSYMBOL_LOAD = 37,                      /* LOAD  */
  YYSYMBOL_DATA = 38,                      /* DATA  */
  YYSYMBOL_INFILE = 39,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 40,                   /* EXPLAIN  */
  YYSYMBOL_EQ = 41,                        /* EQ  */
  YYSYMBOL_LT = 42,                        /* LT  */
  YYSYMBOL_GT = 43,                        /* GT  */
  YYSYMBOL_LE = 44,                        /* LE  */
  YYSYMBOL_GE = 45,                        /* GE  */
  YYSYMBOL_NE = 46,                        /* NE  */
  YYSYMBOL_NOT = 47,                       /* NOT  */
  YYSYMBOL_LK = 48,                        /* LK  */
  YYSYMBOL_INNER = 49,                     /* INNER  */
  YYSYMBOL_JOIN = 50,                      /* JOIN  */
  YYSYMBOL_MAX_agg = 51,                   /* MAX_agg  */
  YYSYMBOL_MIN_agg = 52,                   /* MIN_agg  */
  YYSYMBOL_AVG_agg = 53,                   /* AVG_agg  */
  YYSYMBOL_COUNT_agg = 54,                 /* COUNT_agg  */
  YYSYMBOL_SUM_agg = 55,                   /* SUM_agg  */
  YYSYMBOL_UNIQUE = 56,                    /* UNIQUE  */
  YYSYMBOL_NULLABLE = 57,                  /* NULLABLE  */
  YYSYMBOL_IS = 58,                        /* IS  */
  YYSYMBOL_ORDER = 59,                     /* ORDER  */
  YYSYMBOL_BY = 60,                        /* BY  */
  YYSYMBOL_ASC = 61,                       /* ASC  */
  YYSYMBOL_IN = 62,                        /* IN  */
  YYSYMBOL_EXISTS = 63,                    /* EXISTS  */
  YYSYMBOL_OR = 64,                        /* OR  */
  YYSYMBOL_AS = 65,                        /* AS  */
  YYSYMBOL_TEXT_T = 66,                    /* TEXT_T  */
  YYSYMBOL_NUMBER = 67,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 68,                     /* FLOAT  */
  YYSYMBOL_ID = 69,                        /* ID  */
  YYSYMBOL_SSS = 70,                       /* SSS  */
  YYSYMBOL_DATE = 71,                      /* DATE  */
  YYSYMBOL_PATTERN = 72,                   /* PATTERN  */
  YYSYMBOL_73_ = 73,                       /* '+'  */
  YYSYMBOL_74_ = 74,                       /* '-'  */
  YYSYMBOL_75_ = 75,                       /* '*'  */
  YYSYMBOL_76_ = 76,                       /* '/'  */
  YYSYMBOL_UMINUS = 77,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 78,                  /* $accept  */
  YYSYMBOL_commands = 79,                  /* commands  */
  YYSYMBOL_command_wrapper = 80,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 81,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 82,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 83,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 84,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 85,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 86,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 87,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 88,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 89,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 90,         /* create_index_stmt  */
  YYSYMBOL_id_list = 91,                   /* id_list  */
  YYSYMBOL_drop_index_stmt = 92,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 93,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 94,             /* attr_def_list  */
  YYSYMBOL_attr_def = 95,                  /* attr_def  */
  YYSYMBOL_nullable = 96,                  /* nullable  */
  YYSYMBOL_number = 97,                    /* number  */
  YYSYMBOL_type = 98,                      /* type  */
  YYSYMBOL_insert_stmt = 99,               /* insert_stmt  */
  YYSYMBOL_insert_value = 100,             /* insert_value  */
  YYSYMBOL_insert_values = 101,            /* insert_values  */
  YYSYMBOL_value_list = 102,               /* value_list  */
  YYSYMBOL_value = 103,                    /* value  */
  YYSYMBOL_delete_stmt = 104,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 105,              /* update_stmt  */
  YYSYMBOL_update_list = 106,              /* update_list  */
  YYSYMBOL_select_stmt = 107,              /* select_stmt  */
  YYSYMBOL_order = 108,                    /* order  */
  YYSYMBOL_order_by_list = 109,            /* order_by_list  */
  YYSYMBOL_calc_stmt = 110,                /* calc_stmt  */
  YYSYMBOL_expression_list = 111,          /* expression_list  */
  YYSYMBOL_expression = 112,               /* expression  */
  YYSYMBOL_arg_list = 113,                 /* arg_list  */
  YYSYMBOL_rel_attr = 114,                 /* rel_attr  */
  YYSYMBOL_rel_list = 115,                 /* rel_list  */
  YYSYMBOL_where = 116,                    /* where  */
  YYSYMBOL_on = 117,                       /* on  */
  YYSYMBOL_condition_list = 118,           /* condition_list  */
  YYSYMBOL_condition = 119,                /* condition  */
  YYSYMBOL_comp_op = 120,                  /* comp_op  */
  YYSYMBOL_agg = 121,                      /* agg  */
  YYSYMBOL_as = 122,                       /* as  */
  YYSYMBOL_load_data_stmt = 123,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 124,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 125,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 126             /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  74
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   406

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  150
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  302

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   328


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    75,    73,     2,    74,     2,    76,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    77
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   212,   212,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   243,   249,   254,   260,   266,   272,   278,
     285,   291,   299,   319,   341,   344,   355,   365,   384,   387,
     400,   409,   437,   440,   443,   447,   450,   451,   452,   453,
     454,   457,   471,   482,   485,   496,   499,   510,   514,   518,
     522,   526,   531,   536,   541,   548,   560,   574,   577,   590,
     603,   614,   629,   676,   679,   691,   703,   714,   716,   724,
     732,   742,   752,   756,   773,   784,   795,   806,   817,   822,
     830,   838,   857,   881,   902,   923,   943,   995,   998,  1003,
    1012,  1016,  1025,  1036,  1051,  1063,  1075,  1087,  1120,  1123,
    1140,  1167,  1170,  1176,  1179,  1185,  1188,  1194,  1200,  1437,
    1473,  1496,  1521,  1533,  1541,  1548,  1579,  1580,  1581,  1582,
    1583,  1584,  1585,  1586,  1587,  1588,  1589,  1590,  1593,  1594,
    1595,  1596,  1597,  1600,  1603,  1606,  1611,  1624,  1632,  1642,
    1643
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "CALC", "SELECT", "DESC", "SHOW",
  "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA",
  "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "FLOAT_T", "DATE_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM",
  "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EXPLAIN", "EQ",
  "LT", "GT", "LE", "GE", "NE", "NOT", "LK", "INNER", "JOIN", "MAX_agg",
  "MIN_agg", "AVG_agg", "COUNT_agg", "SUM_agg", "UNIQUE", "NULLABLE", "IS",
  "ORDER", "BY", "ASC", "IN", "EXISTS", "OR", "AS", "TEXT_T", "NUMBER",
  "FLOAT", "ID", "SSS", "DATE", "PATTERN", "'+'", "'-'", "'*'", "'/'",
  "UMINUS", "$accept", "commands", "command_wrapper", "exit_stmt",
  "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_tables_stmt", "desc_table_stmt",
  "create_index_stmt", "id_list", "drop_index_stmt", "create_table_stmt",
  "attr_def_list", "attr_def", "nullable", "number", "type", "insert_stmt",
  "insert_value", "insert_values", "value_list", "value", "delete_stmt",
  "update_stmt", "update_list", "select_stmt", "order", "order_by_list",
  "calc_stmt", "expression_list", "expression", "arg_list", "rel_attr",
  "rel_list", "where", "on", "condition_list", "condition", "comp_op",
  "agg", "as", "load_data_stmt", "explain_stmt", "set_variable_stmt",
  "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,    43,    45,    42,    47,   328
};
#endif

#define YYPACT_NINF (-228)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     329,     6,   139,   192,   192,   -40,    27,  -228,    66,     5,
      37,  -228,  -228,  -228,  -228,  -228,    42,     4,   329,    97,
     114,  -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,
    -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,
    -228,    52,    59,   116,    70,    73,   192,  -228,  -228,  -228,
    -228,  -228,  -228,  -228,  -228,    10,  -228,  -228,  -228,   201,
      51,  -228,  -228,    -6,   143,   129,  -228,  -228,    87,    93,
     128,   132,   130,  -228,  -228,  -228,  -228,   153,   138,   111,
    -228,   147,   -10,    29,   120,  -228,  -228,  -228,  -228,  -228,
    -228,   192,   192,   192,   192,   192,    30,   121,   166,   167,
     133,   222,   131,   134,   137,   171,   150,  -228,    51,    51,
    -228,  -228,     8,     8,  -228,  -228,     7,   189,   202,    51,
     204,   124,  -228,   181,   167,    81,  -228,   195,    -8,   207,
     211,   160,  -228,  -228,  -228,    32,   161,    32,    51,    28,
     222,   213,    83,   172,   217,   330,  -228,    -9,    55,  -228,
    -228,  -228,   230,  -228,  -228,  -228,  -228,  -228,     2,   134,
     220,   170,   223,   232,  -228,   247,  -228,  -228,   208,   191,
     167,   259,   204,  -228,   262,   233,   271,  -228,  -228,  -228,
    -228,  -228,  -228,   -27,  -228,   240,  -228,   231,   124,   124,
     271,   272,   226,   237,   250,  -228,  -228,   207,  -228,   278,
     244,    51,    51,   246,   258,   222,   298,   213,   169,   271,
     300,  -228,  -228,  -228,    83,    57,  -228,  -228,   301,   133,
    -228,  -228,   302,  -228,  -228,   252,   304,   278,  -228,    28,
      51,   263,  -228,   259,  -228,  -228,   257,   312,  -228,   316,
     318,   327,  -228,   -17,   278,  -228,   319,  -228,   311,   113,
    -228,    83,    57,  -228,   222,  -228,   133,  -228,  -228,  -228,
     124,    28,    17,    51,    12,   331,   334,   259,  -228,  -228,
    -228,    39,  -228,  -228,   335,   113,   335,  -228,    40,  -228,
     337,    51,    51,  -228,    13,  -228,    14,   340,  -228,  -228,
    -228,   335,   335,  -228,   284,    51,  -228,  -228,   341,  -228,
      51,  -228
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     149,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,   138,   139,   140,
     141,   142,    64,    57,    59,   143,    61,    62,    63,     0,
     143,    90,    81,    82,     0,     0,    31,    30,     0,     0,
       0,     0,     0,   147,     1,   150,     2,     0,     0,     0,
      29,     0,     0,     0,     0,   145,    91,    57,    59,    89,
      95,     0,     0,     0,     0,     0,    97,     0,     0,   111,
      67,     0,     0,     0,     0,     0,     0,    88,   143,   143,
     144,    83,    84,    85,    86,    87,   100,    98,     0,   143,
       0,   115,    65,     0,   111,     0,   148,     0,     0,    38,
       0,     0,    36,    93,    96,    97,     0,    97,   143,   108,
       0,    53,     0,     0,     0,     0,   112,   116,     0,    66,
      58,    60,     0,    46,    47,    48,    49,    50,    42,     0,
       0,     0,     0,   100,   101,     0,    99,    92,     0,     0,
     111,    55,     0,    51,     0,     0,     0,   126,   127,   128,
     129,   130,   131,     0,   132,   134,   136,     0,   115,   115,
       0,    68,     0,     0,     0,    43,    41,    38,    37,    34,
       0,   143,   143,     0,    73,     0,     0,    53,     0,     0,
       0,   133,   137,   135,     0,   119,   117,   118,     0,    67,
     146,    45,     0,    44,    39,     0,     0,    34,    94,   108,
     143,     0,    72,    55,    52,    54,     0,     0,   123,    90,
       0,    70,    69,    42,    34,    32,     0,   109,   113,     0,
      56,     0,   121,   124,     0,   120,    67,    40,    35,    33,
     115,   108,   143,   143,    77,     0,     0,    55,    71,   114,
     110,     0,   102,   106,    77,     0,    77,    75,    97,   122,
       0,   143,   143,    76,    77,    74,   100,     0,   125,   104,
     107,    77,    77,    79,     0,   143,    80,    78,     0,   103,
     143,   105
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -228,  -228,   342,  -228,  -228,  -228,  -228,  -228,  -228,  -228,
    -228,  -228,  -228,  -200,  -228,  -228,   164,   203,   122,  -228,
    -228,  -228,   196,   156,  -213,   -95,  -228,  -228,  -178,  -138,
    -228,  -189,  -228,     3,    -3,  -132,    92,  -201,  -113,  -228,
    -179,  -228,   162,  -227,   -58,  -228,  -228,  -228,  -228
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   226,    31,    32,   160,   129,   196,   222,
     158,    33,   141,   173,   206,    61,    34,    35,   124,    36,
     232,   277,    37,    62,    82,   118,   264,   170,   122,   261,
     146,   147,   187,    64,    86,    38,    39,    40,    76
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      63,    63,    90,   164,   174,   166,   126,    65,   107,   216,
     217,   149,    41,    91,    42,   153,   154,   155,   156,   193,
     250,   211,   265,   274,   291,   188,   135,   246,   247,    66,
     194,   275,   275,   135,    67,   212,   136,    69,   210,    83,
     195,   242,    72,   294,   258,   171,   271,   168,   265,   194,
     133,   134,   218,   191,   280,   189,    89,   204,   157,   195,
     270,   139,    43,    92,    93,    94,    95,    92,    93,    94,
      95,   237,   190,   276,   292,    84,   240,   169,   268,    85,
     167,   269,    84,    94,    95,   283,    85,   285,    63,   112,
     113,   114,   115,     4,   111,   293,    68,    74,   108,   116,
      46,   163,   296,   297,   109,   117,    70,   117,   281,   286,
     233,    71,    52,   266,   282,   117,    84,    75,   145,   239,
      85,    77,    53,    54,    79,    56,    57,    58,    78,   125,
      92,    93,    94,    95,    47,    48,    49,    50,    51,    80,
      52,   142,    81,   228,   229,    44,   287,    45,   150,   151,
      53,    54,    55,    56,    57,    58,    98,    59,    60,   267,
      96,    97,    99,   100,    47,    48,    49,    50,    51,   102,
     103,   143,   248,   101,   104,    47,    48,    49,    50,    51,
     105,    52,   262,   106,   215,   145,   145,   144,   263,   110,
     119,    53,    54,    55,    56,    57,    58,   120,    59,    60,
     121,   127,   123,   128,   272,   273,   130,   131,   137,    46,
     177,   178,   179,   180,   181,   182,   183,   184,    46,   132,
     138,   140,   148,   289,   290,   152,   159,   185,   161,   162,
     165,   186,   172,   252,   176,   175,   192,   299,   198,   199,
     200,   203,   301,    47,    48,    49,    50,    51,   214,    52,
     209,   135,    47,    48,    49,    50,    51,   145,    52,    53,
      54,    55,    56,    57,    58,   201,    59,    60,    87,    88,
      55,    56,    57,    58,   251,    59,    60,   202,   205,    52,
     208,     4,    47,    48,    49,    50,    51,   213,    52,    53,
      54,   219,    56,    57,    58,   220,   125,   225,    53,    54,
      55,    56,    57,    58,   221,    59,    60,   223,    47,    48,
      49,    50,    51,   227,    52,   230,   234,   231,   238,   241,
     243,   244,   245,   249,    53,    54,    55,    56,    57,    58,
     253,    59,    60,     1,     2,   254,   255,   259,     3,     4,
       5,     6,     7,     8,     9,    10,   256,   260,   278,    11,
      12,    13,   279,   298,   275,   288,    14,    15,   295,   300,
      73,   224,   197,   235,    16,   257,    17,   284,   207,    18,
     236,   177,   178,   179,   180,   181,   182,   183,   184,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   185,     0,
       0,     0,   186,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    92,    93,    94,    95
};

static const yytype_int16 yycheck[] =
{
       3,     4,    60,   135,   142,   137,   101,     4,    18,   188,
     189,   124,     6,    19,     8,    23,    24,    25,    26,    17,
     233,    48,   249,    11,    11,    34,    19,   227,   229,    69,
      47,    19,    19,    19,     7,    62,    29,    32,   176,    29,
      57,   219,    38,    29,   244,   140,    29,    19,   275,    47,
     108,   109,   190,   148,   267,    64,    59,   170,    66,    57,
     261,   119,    56,    73,    74,    75,    76,    73,    74,    75,
      76,   209,    17,    61,    61,    65,   214,    49,   256,    69,
     138,   260,    65,    75,    76,   274,    69,   276,    91,    92,
      93,    94,    95,    10,    91,   284,    30,     0,    69,    69,
      17,    69,   291,   292,    75,    75,    69,    75,    69,    69,
     205,    69,    57,   251,    75,    75,    65,     3,   121,   214,
      69,    69,    67,    68,     8,    70,    71,    72,    69,    74,
      73,    74,    75,    76,    51,    52,    53,    54,    55,    69,
      57,    17,    69,   201,   202,     6,   278,     8,    67,    68,
      67,    68,    69,    70,    71,    72,    69,    74,    75,   254,
      17,    32,    69,    35,    51,    52,    53,    54,    55,    39,
      17,    47,   230,    41,    36,    51,    52,    53,    54,    55,
      69,    57,    69,    36,   187,   188,   189,    63,    75,    69,
      69,    67,    68,    69,    70,    71,    72,    31,    74,    75,
      33,    70,    69,    69,   262,   263,    69,    36,    19,    17,
      41,    42,    43,    44,    45,    46,    47,    48,    17,    69,
      18,    17,    41,   281,   282,    30,    19,    58,    17,    69,
      69,    62,    19,   236,    17,    63,     6,   295,    18,    69,
      17,    50,   300,    51,    52,    53,    54,    55,    17,    57,
      17,    19,    51,    52,    53,    54,    55,   260,    57,    67,
      68,    69,    70,    71,    72,    18,    74,    75,    67,    68,
      69,    70,    71,    72,    17,    74,    75,    69,    19,    57,
      18,    10,    51,    52,    53,    54,    55,    47,    57,    67,
      68,    19,    70,    71,    72,    69,    74,    19,    67,    68,
      69,    70,    71,    72,    67,    74,    75,    57,    51,    52,
      53,    54,    55,    69,    57,    69,    18,    59,    18,    18,
      18,    69,    18,    60,    67,    68,    69,    70,    71,    72,
      18,    74,    75,     4,     5,    19,    18,    18,     9,    10,
      11,    12,    13,    14,    15,    16,    19,    36,    17,    20,
      21,    22,    18,    69,    19,    18,    27,    28,    18,    18,
      18,   197,   159,   207,    35,   243,    37,   275,   172,    40,
     208,    41,    42,    43,    44,    45,    46,    47,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    -1,
      -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    75,    76
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    12,    13,    14,    15,
      16,    20,    21,    22,    27,    28,    35,    37,    40,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    92,    93,    99,   104,   105,   107,   110,   123,   124,
     125,     6,     8,    56,     6,     8,    17,    51,    52,    53,
      54,    55,    57,    67,    68,    69,    70,    71,    72,    74,
      75,   103,   111,   112,   121,   111,    69,     7,    30,    32,
      69,    69,    38,    80,     0,     3,   126,    69,    69,     8,
      69,    69,   112,    29,    65,    69,   122,    67,    68,   112,
     122,    19,    73,    74,    75,    76,    17,    32,    69,    69,
      35,    41,    39,    17,    36,    69,    36,    18,    69,    75,
      69,   111,   112,   112,   112,   112,    69,    75,   113,    69,
      31,    33,   116,    69,   106,    74,   103,    70,    69,    95,
      69,    36,    69,   122,   122,    19,    29,    19,    18,   122,
      17,   100,    17,    47,    63,   112,   118,   119,    41,   116,
      67,    68,    30,    23,    24,    25,    26,    66,    98,    19,
      94,    17,    69,    69,   113,    69,   113,   122,    19,    49,
     115,   103,    19,   101,   107,    63,    17,    41,    42,    43,
      44,    45,    46,    47,    48,    58,    62,   120,    34,    64,
      17,   103,     6,    17,    47,    57,    96,    95,    18,    69,
      17,    18,    69,    50,   116,    19,   102,   100,    18,    17,
     107,    48,    62,    47,    17,   112,   118,   118,   107,    19,
      69,    67,    97,    57,    94,    19,    91,    69,   122,   122,
      69,    59,   108,   103,    18,   101,   120,   107,    18,   103,
     107,    18,   106,    18,    69,    18,    91,   115,   122,    60,
     102,    17,   112,    18,    19,    18,    19,    96,    91,    18,
      36,   117,    69,    75,   114,   121,   107,   103,   106,   118,
     115,    29,   122,   122,    11,    19,    61,   109,    17,    18,
     102,    69,    75,   109,   114,   109,    69,   113,    18,   122,
     122,    11,    61,   109,    29,    18,   109,   109,    69,   122,
      18,   122
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    78,    79,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    90,    91,    91,    92,    93,    94,    94,
      95,    95,    96,    96,    96,    97,    98,    98,    98,    98,
      98,    99,   100,   101,   101,   102,   102,   103,   103,   103,
     103,   103,   103,   103,   103,   104,   105,   106,   106,   106,
     106,   106,   107,   108,   108,   108,   108,   109,   109,   109,
     109,   110,   111,   111,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   113,   113,   113,
     113,   113,   114,   114,   114,   114,   114,   114,   115,   115,
     115,   116,   116,   117,   117,   118,   118,   118,   118,   119,
     119,   119,   119,   119,   119,   119,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   121,   121,
     121,   121,   121,   122,   122,   122,   123,   124,   125,   126,
     126
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     9,    10,     0,     3,     5,     7,     0,     3,
       6,     3,     0,     1,     2,     1,     1,     1,     1,     1,
       1,     6,     4,     0,     3,     0,     3,     1,     2,     1,
       2,     1,     1,     1,     1,     4,     5,     0,     3,     5,
       5,     7,     8,     0,     5,     4,     5,     0,     4,     3,
       4,     2,     1,     3,     3,     3,     3,     3,     3,     2,
       1,     2,     5,     4,     7,     2,     4,     0,     1,     3,
       1,     3,     2,     5,     4,     7,     2,     4,     0,     4,
       6,     0,     2,     0,     2,     0,     1,     3,     3,     3,
       5,     5,     7,     4,     5,     8,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     2,     1,     2,     1,     1,
       1,     1,     1,     0,     2,     1,     7,     2,     4,     0,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 213 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1851 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 243 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1860 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 249 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1868 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 254 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1876 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 260 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1884 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 266 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1892 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 272 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1900 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 278 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1910 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 285 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1918 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 291 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1928 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 300 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);
      create_index.is_unique=false;
      if((yyvsp[-1].relation_list)==nullptr){
      create_index.attribute_name.push_back((yyvsp[-2].string));

      }else{
      (yyvsp[-1].relation_list)->push_back((yyvsp[-2].string));
       create_index.attribute_name.swap(*(yyvsp[-1].relation_list));
      }
      std::reverse(create_index.attribute_name.begin(), create_index.attribute_name.end());
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
      free((yyvsp[-1].relation_list));
    }
#line 1952 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 320 "yacc_sql.y"
         {
           (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
           CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
           create_index.index_name = (yyvsp[-6].string);
           create_index.relation_name = (yyvsp[-4].string);
           create_index.is_unique=true;
           if((yyvsp[-1].relation_list)==nullptr){
           create_index.attribute_name.push_back((yyvsp[-2].string));

           }else{
           (yyvsp[-1].relation_list)->push_back((yyvsp[-2].string));
            create_index.attribute_name.swap(*(yyvsp[-1].relation_list));
           }
           std::reverse(create_index.attribute_name.begin(), create_index.attribute_name.end());
           free((yyvsp[-6].string));
           free((yyvsp[-4].string));
           free((yyvsp[-2].string));
           free((yyvsp[-1].relation_list));
         }
#line 1976 "yacc_sql.cpp"
    break;

  case 34: /* id_list: %empty  */
#line 341 "yacc_sql.y"
  {
  (yyval.relation_list)=nullptr;
  }
#line 1984 "yacc_sql.cpp"
    break;

  case 35: /* id_list: COMMA ID id_list  */
#line 344 "yacc_sql.y"
                   {
   if((yyvsp[0].relation_list)!=nullptr){
   (yyval.relation_list)=(yyvsp[0].relation_list);
   }else{
   (yyval.relation_list)=new std::vector<std::string>;
   }
   (yyval.relation_list)->push_back((yyvsp[-1].string));
   free((yyvsp[-1].string));

  }
#line 1999 "yacc_sql.cpp"
    break;

  case 36: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 356 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2011 "yacc_sql.cpp"
    break;

  case 37: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 366 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-4].string);
      free((yyvsp[-4].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-1].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-2].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-2].attr_info);
    }
#line 2031 "yacc_sql.cpp"
    break;

  case 38: /* attr_def_list: %empty  */
#line 384 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2039 "yacc_sql.cpp"
    break;

  case 39: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 388 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2053 "yacc_sql.cpp"
    break;

  case 40: /* attr_def: ID type LBRACE number RBRACE nullable  */
#line 401 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->is_null=(yyvsp[0].is_null);
      free((yyvsp[-5].string));
    }
#line 2066 "yacc_sql.cpp"
    break;

  case 41: /* attr_def: ID type nullable  */
#line 410 "yacc_sql.y"
    {
    if ((AttrType)(yyvsp[-1].number)==DATES){
    (yyval.attr_info) = new AttrInfoSqlNode;
              (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
              (yyval.attr_info)->name = (yyvsp[-2].string);
              (yyval.attr_info)->length = 10;
              (yyval.attr_info)->is_null=(yyvsp[0].is_null);
              free((yyvsp[-2].string));
    }else if((AttrType)(yyvsp[-1].number)==TEXTS){
    (yyval.attr_info) = new AttrInfoSqlNode;
              (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
              (yyval.attr_info)->name = (yyvsp[-2].string);
              (yyval.attr_info)->length = 8;
              (yyval.attr_info)->is_null=(yyvsp[0].is_null);
              free((yyvsp[-2].string));
    }else{
    (yyval.attr_info) = new AttrInfoSqlNode;
          (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
          (yyval.attr_info)->name = (yyvsp[-2].string);
          (yyval.attr_info)->length = 4;
          (yyval.attr_info)->is_null=(yyvsp[0].is_null);
          free((yyvsp[-2].string));
    }

    }
#line 2096 "yacc_sql.cpp"
    break;

  case 42: /* nullable: %empty  */
#line 437 "yacc_sql.y"
   {
   (yyval.is_null)=true;
   }
#line 2104 "yacc_sql.cpp"
    break;

  case 43: /* nullable: NULLABLE  */
#line 440 "yacc_sql.y"
            {
   (yyval.is_null)=true;
   }
#line 2112 "yacc_sql.cpp"
    break;

  case 44: /* nullable: NOT NULLABLE  */
#line 443 "yacc_sql.y"
                {
   (yyval.is_null)=false;
   }
#line 2120 "yacc_sql.cpp"
    break;

  case 45: /* number: NUMBER  */
#line 447 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2126 "yacc_sql.cpp"
    break;

  case 46: /* type: INT_T  */
#line 450 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2132 "yacc_sql.cpp"
    break;

  case 47: /* type: STRING_T  */
#line 451 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2138 "yacc_sql.cpp"
    break;

  case 48: /* type: FLOAT_T  */
#line 452 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2144 "yacc_sql.cpp"
    break;

  case 49: /* type: DATE_T  */
#line 453 "yacc_sql.y"
              {(yyval.number)=DATES;}
#line 2150 "yacc_sql.cpp"
    break;

  case 50: /* type: TEXT_T  */
#line 454 "yacc_sql.y"
             {(yyval.number)=TEXTS;}
#line 2156 "yacc_sql.cpp"
    break;

  case 51: /* insert_stmt: INSERT INTO ID VALUES insert_value insert_values  */
#line 458 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-3].string);
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[0].value_list));
      }
      (yyval.sql_node)->insertion.values.insert((yyval.sql_node)->insertion.values.end(),(yyvsp[-1].value_list)->begin(),(yyvsp[-1].value_list)->end());
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-1].value_list);
      free((yyvsp[-3].string));
    }
#line 2172 "yacc_sql.cpp"
    break;

  case 52: /* insert_value: LBRACE value value_list RBRACE  */
#line 471 "yacc_sql.y"
                                   {
	if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[-1].value_list);
        } else {
        (yyval.value_list) = new std::vector<Value>;
        }
        (yyval.value_list)->emplace_back(*(yyvsp[-2].value));
         delete (yyvsp[-2].value);
    }
#line 2186 "yacc_sql.cpp"
    break;

  case 53: /* insert_values: %empty  */
#line 482 "yacc_sql.y"
    {
    (yyval.value_list)=nullptr;
    }
#line 2194 "yacc_sql.cpp"
    break;

  case 54: /* insert_values: COMMA insert_value insert_values  */
#line 485 "yacc_sql.y"
                                     {
	if ((yyvsp[0].value_list) != nullptr) {
                (yyval.value_list) = (yyvsp[0].value_list);
              } else {
                (yyval.value_list) = new std::vector<Value>;
              }
              (yyval.value_list)->insert((yyval.value_list)->end(),(yyvsp[-1].value_list)->begin(),(yyvsp[-1].value_list)->end());
              delete (yyvsp[-1].value_list);
    }
#line 2208 "yacc_sql.cpp"
    break;

  case 55: /* value_list: %empty  */
#line 496 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2216 "yacc_sql.cpp"
    break;

  case 56: /* value_list: COMMA value value_list  */
#line 499 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2230 "yacc_sql.cpp"
    break;

  case 57: /* value: NUMBER  */
#line 510 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2239 "yacc_sql.cpp"
    break;

  case 58: /* value: '-' NUMBER  */
#line 514 "yacc_sql.y"
                {
      (yyval.value) = new Value(-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2248 "yacc_sql.cpp"
    break;

  case 59: /* value: FLOAT  */
#line 518 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2257 "yacc_sql.cpp"
    break;

  case 60: /* value: '-' FLOAT  */
#line 522 "yacc_sql.y"
               {
    (yyval.value) = new Value(-(float)(yyvsp[0].floats));
    (yyloc) = (yylsp[0]);
    }
#line 2266 "yacc_sql.cpp"
    break;

  case 61: /* value: SSS  */
#line 526 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp,CHARS);
      free(tmp);
    }
#line 2276 "yacc_sql.cpp"
    break;

  case 62: /* value: DATE  */
#line 531 "yacc_sql.y"
          {
           char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
           (yyval.value) = new Value(tmp,DATES);
           free(tmp);
         }
#line 2286 "yacc_sql.cpp"
    break;

  case 63: /* value: PATTERN  */
#line 536 "yacc_sql.y"
             {
         char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
         (yyval.value) = new Value(tmp,CHARS);
         free(tmp);
         }
#line 2296 "yacc_sql.cpp"
    break;

  case 64: /* value: NULLABLE  */
#line 541 "yacc_sql.y"
             {
      (yyval.value)=new Value();
      (yyval.value)->set_null();
    }
#line 2305 "yacc_sql.cpp"
    break;

  case 65: /* delete_stmt: DELETE FROM ID where  */
#line 549 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2319 "yacc_sql.cpp"
    break;

  case 66: /* update_stmt: UPDATE ID SET update_list where  */
#line 561 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.updateValue_list.swap(*(yyvsp[-1].update_list));

      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-3].string));
      free((yyvsp[-1].update_list));
    }
#line 2336 "yacc_sql.cpp"
    break;

  case 67: /* update_list: %empty  */
#line 574 "yacc_sql.y"
   {
   (yyval.update_list)=nullptr;
   }
#line 2344 "yacc_sql.cpp"
    break;

  case 68: /* update_list: ID EQ value  */
#line 577 "yacc_sql.y"
                {

      (yyval.update_list)=new std::vector<UpdateValue>;



      UpdateValue value;
      value.is_select=false;
      value.value=*(yyvsp[0].value);
      value.attribute_name=(yyvsp[-2].string);
      (yyval.update_list)->push_back(value);

      }
#line 2362 "yacc_sql.cpp"
    break;

  case 69: /* update_list: ID EQ value COMMA update_list  */
#line 590 "yacc_sql.y"
                                 {
   if((yyvsp[0].update_list)==nullptr){
   (yyval.update_list)=new std::vector<UpdateValue>;
   }else{
   (yyval.update_list)=(yyvsp[0].update_list);
   }
   UpdateValue value;
   value.is_select=false;
   value.value=*(yyvsp[-2].value);
   value.attribute_name=(yyvsp[-4].string);
   (yyval.update_list)->push_back(value);

   }
#line 2380 "yacc_sql.cpp"
    break;

  case 70: /* update_list: ID EQ LBRACE select_stmt RBRACE  */
#line 603 "yacc_sql.y"
                                     {

         (yyval.update_list)=new std::vector<UpdateValue>;

         UpdateValue value;
         value.is_select=true;
         value.selectSqlNode=(yyvsp[-1].sql_node)->selection;
         value.attribute_name=(yyvsp[-4].string);
         (yyval.update_list)->push_back(value);

      }
#line 2396 "yacc_sql.cpp"
    break;

  case 71: /* update_list: ID EQ LBRACE select_stmt RBRACE COMMA update_list  */
#line 614 "yacc_sql.y"
                                                      {
   if((yyvsp[0].update_list)==nullptr){
      (yyval.update_list)=new std::vector<UpdateValue>;
      }else{
      (yyval.update_list)=(yyvsp[0].update_list);
      }
      UpdateValue value;
      value.is_select=true;
      value.selectSqlNode=(yyvsp[-3].sql_node)->selection;
      value.attribute_name=(yyvsp[-6].string);
      (yyval.update_list)->push_back(value);

   }
#line 2414 "yacc_sql.cpp"
    break;

  case 72: /* select_stmt: SELECT expression_list FROM ID as rel_list where order  */
#line 630 "yacc_sql.y"
         {
           (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
           if ((yyvsp[-6].expression) != nullptr) {
             (yyval.sql_node)->selection.attributes.swap((yyvsp[-6].expression)->relAttrSqlNodes);
             (yyval.sql_node)->selection.attributes_expression.swap((yyvsp[-6].expression)->expression);
             (yyval.sql_node)->selection.stringsqlExprs.swap((yyvsp[-6].expression)->stringsqlExprs);
             (yyval.sql_node)->selection.fieldExprs.swap((yyvsp[-6].expression)->fieldExprs);
             (yyval.sql_node)->selection.is_expression_select_attr=(yyvsp[-6].expression)->is_expression;
             std::reverse((yyval.sql_node)->selection.attributes_expression.begin(), (yyval.sql_node)->selection.attributes_expression.end());
             delete (yyvsp[-6].expression);
           }
           (yyval.sql_node)->selection.is_alias_right=true;
           if ((yyvsp[-2].inner_join_list) != nullptr) {
             (yyval.sql_node)->selection.relations.swap((yyvsp[-2].inner_join_list)->relations);
             (yyval.sql_node)->selection.conditions.swap((yyvsp[-2].inner_join_list)->conditions);
             (yyval.sql_node)->selection.alias_map.insert((yyvsp[-2].inner_join_list)->alias_map.begin(), (yyvsp[-2].inner_join_list)->alias_map.end());
             (yyval.sql_node)->selection.is_alias_right=(yyvsp[-2].inner_join_list)->is_alias_right;
             delete (yyvsp[-2].inner_join_list);
           }
           (yyval.sql_node)->selection.relations.push_back((yyvsp[-4].string));
           std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());
           if ((yyvsp[-3].string) != nullptr) {
           if((yyval.sql_node)->selection.alias_map.find((yyvsp[-3].string))==(yyval.sql_node)->selection.alias_map.end()){
           (yyval.sql_node)->selection.alias_map.insert(std::pair<std::string, std::string>((yyvsp[-3].string), (yyvsp[-4].string)));
           }else{
           (yyval.sql_node)->selection.is_alias_right=false;
           }

            }

           if ((yyvsp[-1].condition_list) != nullptr) {
             (yyval.sql_node)->selection.conditions.insert((yyval.sql_node)->selection.conditions.begin(),(yyvsp[-1].condition_list)->begin(),(yyvsp[-1].condition_list)->end());
             std::reverse((yyval.sql_node)->selection.conditions.begin(), (yyval.sql_node)->selection.conditions.end());
             delete (yyvsp[-1].condition_list);
           }
           if((yyvsp[0].order_by)!=nullptr){
           (yyval.sql_node)->selection.order_by.insert((yyval.sql_node)->selection.order_by.begin(),(yyvsp[0].order_by)->begin(),(yyvsp[0].order_by)->end());
           std::reverse((yyval.sql_node)->selection.order_by.begin(), (yyval.sql_node)->selection.order_by.end());
                        delete (yyvsp[0].order_by);
           }
           (yyval.sql_node)->selection.is_sub_select=false;
           free((yyvsp[-4].string));
         }
#line 2462 "yacc_sql.cpp"
    break;

  case 73: /* order: %empty  */
#line 676 "yacc_sql.y"
  {
  (yyval.order_by)=nullptr;
  }
#line 2470 "yacc_sql.cpp"
    break;

  case 74: /* order: ORDER BY rel_attr ASC order_by_list  */
#line 679 "yacc_sql.y"
                                      {
  if((yyvsp[0].order_by)!=nullptr){
  (yyval.order_by)=(yyvsp[0].order_by);
  }else{
  (yyval.order_by)=new std::vector<OrderBySqlNode>;
  }
  OrderBySqlNode orderBySqlNode;
      orderBySqlNode.attrs=*(yyvsp[-2].rel_attr);
      orderBySqlNode.orderBySequence=ASC_ORDER_BY;
      (yyval.order_by)->push_back(orderBySqlNode);
   std::reverse((yyval.order_by)->begin(),(yyval.order_by)->end());
  }
#line 2487 "yacc_sql.cpp"
    break;

  case 75: /* order: ORDER BY rel_attr order_by_list  */
#line 691 "yacc_sql.y"
                                   {
    if((yyvsp[0].order_by)!=nullptr){
    (yyval.order_by)=(yyvsp[0].order_by);
    }else{
    (yyval.order_by)=new std::vector<OrderBySqlNode>;
    }
    OrderBySqlNode orderBySqlNode;
    orderBySqlNode.attrs=*(yyvsp[-1].rel_attr);
    orderBySqlNode.orderBySequence=ASC_ORDER_BY;
    (yyval.order_by)->push_back(orderBySqlNode);
     std::reverse((yyval.order_by)->begin(),(yyval.order_by)->end());
    }
#line 2504 "yacc_sql.cpp"
    break;

  case 76: /* order: ORDER BY rel_attr DESC order_by_list  */
#line 703 "yacc_sql.y"
                                       {
  if((yyvsp[0].order_by)!=nullptr){
    (yyval.order_by)=(yyvsp[0].order_by);
    }else{
    (yyval.order_by)=new std::vector<OrderBySqlNode>;
    }
    (yyval.order_by)->push_back({*(yyvsp[-2].rel_attr),DESC_ORDER_BY});
     std::reverse((yyval.order_by)->begin(),(yyval.order_by)->end());

  }
#line 2519 "yacc_sql.cpp"
    break;

  case 77: /* order_by_list: %empty  */
#line 714 "yacc_sql.y"
   {(yyval.order_by)=nullptr;
   }
#line 2526 "yacc_sql.cpp"
    break;

  case 78: /* order_by_list: COMMA rel_attr ASC order_by_list  */
#line 716 "yacc_sql.y"
                                    {
   if((yyvsp[0].order_by)!=nullptr){
     (yyval.order_by)=(yyvsp[0].order_by);
     }else{
     (yyval.order_by)=new std::vector<OrderBySqlNode>;
     }
     (yyval.order_by)->push_back({*(yyvsp[-2].rel_attr),ASC_ORDER_BY});
   }
#line 2539 "yacc_sql.cpp"
    break;

  case 79: /* order_by_list: COMMA rel_attr order_by_list  */
#line 724 "yacc_sql.y"
                                 {
   if((yyvsp[0].order_by)!=nullptr){
        (yyval.order_by)=(yyvsp[0].order_by);
        }else{
        (yyval.order_by)=new std::vector<OrderBySqlNode>;
        }
        (yyval.order_by)->push_back({*(yyvsp[-1].rel_attr),ASC_ORDER_BY});

   }
#line 2553 "yacc_sql.cpp"
    break;

  case 80: /* order_by_list: COMMA rel_attr DESC order_by_list  */
#line 732 "yacc_sql.y"
                                      {
       if((yyvsp[0].order_by)!=nullptr){
            (yyval.order_by)=(yyvsp[0].order_by);
            }else{
            (yyval.order_by)=new std::vector<OrderBySqlNode>;
            }
            (yyval.order_by)->push_back({*(yyvsp[-2].rel_attr),DESC_ORDER_BY});
    }
#line 2566 "yacc_sql.cpp"
    break;

  case 81: /* calc_stmt: CALC expression_list  */
#line 743 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression)->expression.begin(), (yyvsp[0].expression)->expression.end());
      (yyval.sql_node)->calc.expressions.swap((yyvsp[0].expression)->expression);
      delete (yyvsp[0].expression);
    }
#line 2577 "yacc_sql.cpp"
    break;

  case 82: /* expression_list: expression  */
#line 753 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2585 "yacc_sql.cpp"
    break;

  case 83: /* expression_list: expression COMMA expression_list  */
#line 757 "yacc_sql.y"
    {
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.expression) = (yyvsp[0].expression);
      } else {
        (yyval.expression) = new ExpressionSqlNode ;
      }
      (yyval.expression)->relAttrSqlNodes.insert((yyval.expression)->relAttrSqlNodes.end(),(yyvsp[-2].expression)->relAttrSqlNodes.begin(),(yyvsp[-2].expression)->relAttrSqlNodes.end());
      (yyval.expression)->stringsqlExprs.insert((yyval.expression)->stringsqlExprs.end(),(yyvsp[-2].expression)->stringsqlExprs.begin(),(yyvsp[-2].expression)->stringsqlExprs.end());
      (yyval.expression)->fieldExprs.insert((yyval.expression)->fieldExprs.end(),(yyvsp[-2].expression)->fieldExprs.begin(),(yyvsp[-2].expression)->fieldExprs.end());
      (yyval.expression)->expression.insert((yyval.expression)->expression.end(),(yyvsp[-2].expression)->expression.begin(),(yyvsp[-2].expression)->expression.end());
      if((yyvsp[-2].expression)->is_expression){
      (yyval.expression)->is_expression=true;
      }
    }
#line 2604 "yacc_sql.cpp"
    break;

  case 84: /* expression: expression '+' expression  */
#line 773 "yacc_sql.y"
                              {
    (yyval.expression)=new ExpressionSqlNode;
      (yyval.expression)->expression.push_back(create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression)->expression[0], (yyvsp[0].expression)->expression[0], sql_string, &(yyloc)));
      (yyval.expression)->relAttrSqlNodes.insert((yyval.expression)->relAttrSqlNodes.end(),(yyvsp[-2].expression)->relAttrSqlNodes.begin(),(yyvsp[-2].expression)->relAttrSqlNodes.end());
      (yyval.expression)->relAttrSqlNodes.insert((yyval.expression)->relAttrSqlNodes.end(),(yyvsp[0].expression)->relAttrSqlNodes.begin(),(yyvsp[0].expression)->relAttrSqlNodes.end());
      (yyval.expression)->stringsqlExprs.insert((yyval.expression)->stringsqlExprs.end(),(yyvsp[-2].expression)->stringsqlExprs.begin(),(yyvsp[-2].expression)->stringsqlExprs.end());
      (yyval.expression)->stringsqlExprs.insert((yyval.expression)->stringsqlExprs.end(),(yyvsp[0].expression)->stringsqlExprs.begin(),(yyvsp[0].expression)->stringsqlExprs.end());
      (yyval.expression)->fieldExprs.insert((yyval.expression)->fieldExprs.end(),(yyvsp[-2].expression)->fieldExprs.begin(),(yyvsp[-2].expression)->fieldExprs.end());
            (yyval.expression)->fieldExprs.insert((yyval.expression)->fieldExprs.end(),(yyvsp[0].expression)->fieldExprs.begin(),(yyvsp[0].expression)->fieldExprs.end());
            (yyval.expression)->is_expression=true;
    }
#line 2620 "yacc_sql.cpp"
    break;

  case 85: /* expression: expression '-' expression  */
#line 784 "yacc_sql.y"
                                {
    (yyval.expression)=new ExpressionSqlNode;
      (yyval.expression)->expression.push_back( create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression)->expression[0], (yyvsp[0].expression)->expression[0], sql_string, &(yyloc)));
      (yyval.expression)->relAttrSqlNodes.insert((yyval.expression)->relAttrSqlNodes.end(),(yyvsp[-2].expression)->relAttrSqlNodes.begin(),(yyvsp[-2].expression)->relAttrSqlNodes.end());
      (yyval.expression)->relAttrSqlNodes.insert((yyval.expression)->relAttrSqlNodes.end(),(yyvsp[0].expression)->relAttrSqlNodes.begin(),(yyvsp[0].expression)->relAttrSqlNodes.end());
      (yyval.expression)->stringsqlExprs.insert((yyval.expression)->stringsqlExprs.end(),(yyvsp[-2].expression)->stringsqlExprs.begin(),(yyvsp[-2].expression)->stringsqlExprs.end());
      (yyval.expression)->stringsqlExprs.insert((yyval.expression)->stringsqlExprs.end(),(yyvsp[0].expression)->stringsqlExprs.begin(),(yyvsp[0].expression)->stringsqlExprs.end());
      (yyval.expression)->fieldExprs.insert((yyval.expression)->fieldExprs.end(),(yyvsp[-2].expression)->fieldExprs.begin(),(yyvsp[-2].expression)->fieldExprs.end());
                  (yyval.expression)->fieldExprs.insert((yyval.expression)->fieldExprs.end(),(yyvsp[0].expression)->fieldExprs.begin(),(yyvsp[0].expression)->fieldExprs.end());
                  (yyval.expression)->is_expression=true;
    }
#line 2636 "yacc_sql.cpp"
    break;

  case 86: /* expression: expression '*' expression  */
#line 795 "yacc_sql.y"
                                {
    (yyval.expression)=new ExpressionSqlNode;
      (yyval.expression)->expression.push_back( create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression)->expression[0], (yyvsp[0].expression)->expression[0], sql_string, &(yyloc)));
      (yyval.expression)->relAttrSqlNodes.insert((yyval.expression)->relAttrSqlNodes.end(),(yyvsp[-2].expression)->relAttrSqlNodes.begin(),(yyvsp[-2].expression)->relAttrSqlNodes.end());
      (yyval.expression)->relAttrSqlNodes.insert((yyval.expression)->relAttrSqlNodes.end(),(yyvsp[0].expression)->relAttrSqlNodes.begin(),(yyvsp[0].expression)->relAttrSqlNodes.end());
      (yyval.expression)->stringsqlExprs.insert((yyval.expression)->stringsqlExprs.end(),(yyvsp[-2].expression)->stringsqlExprs.begin(),(yyvsp[-2].expression)->stringsqlExprs.end());
      (yyval.expression)->stringsqlExprs.insert((yyval.expression)->stringsqlExprs.end(),(yyvsp[0].expression)->stringsqlExprs.begin(),(yyvsp[0].expression)->stringsqlExprs.end());
      (yyval.expression)->fieldExprs.insert((yyval.expression)->fieldExprs.end(),(yyvsp[-2].expression)->fieldExprs.begin(),(yyvsp[-2].expression)->fieldExprs.end());
                  (yyval.expression)->fieldExprs.insert((yyval.expression)->fieldExprs.end(),(yyvsp[0].expression)->fieldExprs.begin(),(yyvsp[0].expression)->fieldExprs.end());
                  (yyval.expression)->is_expression=true;
    }
#line 2652 "yacc_sql.cpp"
    break;

  case 87: /* expression: expression '/' expression  */
#line 806 "yacc_sql.y"
                                {
    (yyval.expression)=new ExpressionSqlNode;
      (yyval.expression)->expression.push_back(create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression)->expression[0], (yyvsp[0].expression)->expression[0], sql_string, &(yyloc)));
      (yyval.expression)->relAttrSqlNodes.insert((yyval.expression)->relAttrSqlNodes.end(),(yyvsp[-2].expression)->relAttrSqlNodes.begin(),(yyvsp[-2].expression)->relAttrSqlNodes.end());
      (yyval.expression)->relAttrSqlNodes.insert((yyval.expression)->relAttrSqlNodes.end(),(yyvsp[0].expression)->relAttrSqlNodes.begin(),(yyvsp[0].expression)->relAttrSqlNodes.end());
      (yyval.expression)->stringsqlExprs.insert((yyval.expression)->stringsqlExprs.end(),(yyvsp[-2].expression)->stringsqlExprs.begin(),(yyvsp[-2].expression)->stringsqlExprs.end());
      (yyval.expression)->stringsqlExprs.insert((yyval.expression)->stringsqlExprs.end(),(yyvsp[0].expression)->stringsqlExprs.begin(),(yyvsp[0].expression)->stringsqlExprs.end());
      (yyval.expression)->fieldExprs.insert((yyval.expression)->fieldExprs.end(),(yyvsp[-2].expression)->fieldExprs.begin(),(yyvsp[-2].expression)->fieldExprs.end());
                  (yyval.expression)->fieldExprs.insert((yyval.expression)->fieldExprs.end(),(yyvsp[0].expression)->fieldExprs.begin(),(yyvsp[0].expression)->fieldExprs.end());
                  (yyval.expression)->is_expression=true;
    }
#line 2668 "yacc_sql.cpp"
    break;

  case 88: /* expression: LBRACE expression RBRACE  */
#line 817 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->expression[0]->set_name(token_name(sql_string, &(yyloc)));
      (yyval.expression)->is_expression=true;
    }
#line 2678 "yacc_sql.cpp"
    break;

  case 89: /* expression: '-' expression  */
#line 822 "yacc_sql.y"
                                  {
    (yyval.expression)=new ExpressionSqlNode;
    (yyval.expression)->expression.push_back( create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression)->expression[0], nullptr, sql_string, &(yyloc)));
    (yyval.expression)->relAttrSqlNodes.insert((yyval.expression)->relAttrSqlNodes.end(),(yyvsp[0].expression)->relAttrSqlNodes.begin(),(yyvsp[0].expression)->relAttrSqlNodes.end());
    (yyval.expression)->stringsqlExprs.insert((yyval.expression)->stringsqlExprs.end(),(yyvsp[0].expression)->stringsqlExprs.begin(),(yyvsp[0].expression)->stringsqlExprs.end());
    (yyval.expression)->fieldExprs.insert((yyval.expression)->fieldExprs.end(),(yyvsp[0].expression)->fieldExprs.begin(),(yyvsp[0].expression)->fieldExprs.end());
    (yyval.expression)->is_expression=true;
    }
#line 2691 "yacc_sql.cpp"
    break;

  case 90: /* expression: value  */
#line 830 "yacc_sql.y"
            {
      (yyval.expression)=new ExpressionSqlNode;
      (yyval.expression)->expression.push_back( new ValueExpr(*(yyvsp[0].value)));
      (yyval.expression)->expression[0]->set_name(token_name(sql_string, &(yyloc)));
      (yyval.expression)->is_expression=false;
      (yyval.expression)->is_value=true;
      delete (yyvsp[0].value);
    }
#line 2704 "yacc_sql.cpp"
    break;

  case 91: /* expression: ID as  */
#line 838 "yacc_sql.y"
          {
    (yyval.expression)=new ExpressionSqlNode;
           auto relAttrSqlNode = new RelAttrSqlNode;
           relAttrSqlNode->attribute_name = (yyvsp[-1].string);
           relAttrSqlNode->agg=NO_AGG;
           relAttrSqlNode->is_right=true;
           if((yyvsp[0].string)!=nullptr){
           relAttrSqlNode->alias_name=(yyvsp[0].string);
           }
    relAttrSqlNode->sqlString=token_name(sql_string, &(yyloc));
    (yyval.expression)->relAttrSqlNodes.push_back(*relAttrSqlNode);
    auto fieldExpr=new FieldExpr;
    fieldExpr->set_name(token_name(sql_string, &(yyloc)));
    (yyval.expression)->expression.push_back(fieldExpr);
    (yyval.expression)->fieldExprs.push_back(fieldExpr);
    (yyval.expression)->is_expression=false;
    (yyval.expression)->is_value=false;
           free((yyvsp[-1].string));
         }
#line 2728 "yacc_sql.cpp"
    break;

  case 92: /* expression: agg LBRACE arg_list RBRACE as  */
#line 857 "yacc_sql.y"
                                       {
         (yyval.expression)=new ExpressionSqlNode;
         auto relAttrSqlNode = new RelAttrSqlNode;
              if((yyvsp[-2].relation_list)==nullptr||(yyvsp[-2].relation_list)->size()!=1){
              relAttrSqlNode->is_right=false;
              }else{
              relAttrSqlNode->attribute_name = (*(yyvsp[-2].relation_list))[0];
              relAttrSqlNode->is_right=true;
              relAttrSqlNode->agg=(yyvsp[-4].agg);
              }
              if((yyvsp[0].string)!=nullptr){
               relAttrSqlNode->alias_name=(yyvsp[0].string);
              }
              relAttrSqlNode->sqlString=token_name(sql_string, &(yyloc));
              (yyval.expression)->relAttrSqlNodes.push_back(*relAttrSqlNode);
                  auto stringSqlExpr=new StringSqlExpr;
                  stringSqlExpr->set_name(token_name(sql_string, &(yyloc)));
                  (yyval.expression)->expression.push_back(stringSqlExpr);
                  (yyval.expression)->stringsqlExprs.push_back(stringSqlExpr);
                  (yyval.expression)->is_expression=false;
                  (yyval.expression)->is_value=false;
               free((yyvsp[-2].relation_list));

              }
#line 2757 "yacc_sql.cpp"
    break;

  case 93: /* expression: ID DOT ID as  */
#line 881 "yacc_sql.y"
                       {
         (yyval.expression)=new ExpressionSqlNode;
         auto relAttrSqlNode = new RelAttrSqlNode;
           relAttrSqlNode->relation_name  = (yyvsp[-3].string);
           relAttrSqlNode->attribute_name = (yyvsp[-1].string);
           relAttrSqlNode->agg=NO_AGG;
           relAttrSqlNode->is_right=true;
           if((yyvsp[0].string)!=nullptr){
           relAttrSqlNode->alias_name=(yyvsp[0].string);
           }
           relAttrSqlNode->sqlString=token_name(sql_string, &(yyloc));
               (yyval.expression)->relAttrSqlNodes.push_back(*relAttrSqlNode);
               auto fieldExpr=new FieldExpr;
               fieldExpr->set_name(token_name(sql_string, &(yyloc)));
               (yyval.expression)->expression.push_back(fieldExpr);
               (yyval.expression)->fieldExprs.push_back(fieldExpr);
               (yyval.expression)->is_expression=false;
               (yyval.expression)->is_value=false;
           free((yyvsp[-3].string));
           free((yyvsp[-1].string));
         }
#line 2783 "yacc_sql.cpp"
    break;

  case 94: /* expression: agg LBRACE ID DOT ID RBRACE as  */
#line 902 "yacc_sql.y"
                                         {
         (yyval.expression)=new ExpressionSqlNode;
                  auto relAttrSqlNode = new RelAttrSqlNode;
                    relAttrSqlNode->relation_name  = (yyvsp[-4].string);
                    relAttrSqlNode->attribute_name = (yyvsp[-2].string);
                    relAttrSqlNode->is_right=true;
                    relAttrSqlNode->agg=(yyvsp[-6].agg);
                    if((yyvsp[0].string)!=nullptr){
                          relAttrSqlNode->alias_name=(yyvsp[0].string);
                          }
                    relAttrSqlNode->sqlString=token_name(sql_string, &(yyloc));
                    (yyval.expression)->relAttrSqlNodes.push_back(*relAttrSqlNode);
                    auto stringSqlExpr=new StringSqlExpr;
                    stringSqlExpr->set_name(token_name(sql_string, &(yyloc)));
                    (yyval.expression)->expression.push_back(stringSqlExpr);
                    (yyval.expression)->stringsqlExprs.push_back(stringSqlExpr);
                    (yyval.expression)->is_expression=false;
                    (yyval.expression)->is_value=false;
                    free((yyvsp[-4].string));
                    free((yyvsp[-2].string));
         }
#line 2809 "yacc_sql.cpp"
    break;

  case 95: /* expression: '*' as  */
#line 923 "yacc_sql.y"
                 {
         (yyval.expression)=new ExpressionSqlNode;
         auto relAttrSqlNode = new RelAttrSqlNode;
               relAttrSqlNode->relation_name  = "";
               relAttrSqlNode->attribute_name = "*";
               if((yyvsp[0].string)!=nullptr){
               relAttrSqlNode->is_right=false;
               }else{
               relAttrSqlNode->is_right=true;
               }
               relAttrSqlNode->agg=NO_AGG;
               relAttrSqlNode->sqlString=token_name(sql_string, &(yyloc));
               (yyval.expression)->relAttrSqlNodes.push_back(*relAttrSqlNode);
               auto fieldExpr=new FieldExpr;
               fieldExpr->set_name(token_name(sql_string, &(yyloc)));
               (yyval.expression)->expression.push_back(fieldExpr);
               (yyval.expression)->fieldExprs.push_back(fieldExpr);
               (yyval.expression)->is_expression=false;
               (yyval.expression)->is_value=false;
             }
#line 2834 "yacc_sql.cpp"
    break;

  case 96: /* expression: ID DOT '*' as  */
#line 943 "yacc_sql.y"
                        {
         (yyval.expression)=new ExpressionSqlNode;
         auto relAttrSqlNode = new RelAttrSqlNode;
               relAttrSqlNode->relation_name  = (yyvsp[-3].string);
               relAttrSqlNode->attribute_name = "*";
               if((yyvsp[0].string)!=nullptr){
               relAttrSqlNode->is_right=false;
               }else{
               relAttrSqlNode->is_right=true;
               }

               relAttrSqlNode->agg=NO_AGG;
               relAttrSqlNode->sqlString=token_name(sql_string, &(yyloc));
               (yyval.expression)->relAttrSqlNodes.push_back(*relAttrSqlNode);
               auto fieldExpr=new FieldExpr;
               fieldExpr->set_name(token_name(sql_string, &(yyloc)));
               (yyval.expression)->expression.push_back(fieldExpr);
               (yyval.expression)->fieldExprs.push_back(fieldExpr);
               (yyval.expression)->is_expression=false;
               (yyval.expression)->is_value=false;
         }
#line 2860 "yacc_sql.cpp"
    break;

  case 97: /* arg_list: %empty  */
#line 995 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2868 "yacc_sql.cpp"
    break;

  case 98: /* arg_list: '*'  */
#line 998 "yacc_sql.y"
         {
    (yyval.relation_list)=new std::vector<std::string>;
    (yyval.relation_list)->push_back("*");

    }
#line 2878 "yacc_sql.cpp"
    break;

  case 99: /* arg_list: '*' COMMA arg_list  */
#line 1003 "yacc_sql.y"
                       {
    if((yyvsp[0].relation_list)!=nullptr){
    (yyval.relation_list)=(yyvsp[0].relation_list);
    }else{
    (yyval.relation_list)=new std::vector<std::string>;
    }

     (yyval.relation_list)->push_back("*");
    }
#line 2892 "yacc_sql.cpp"
    break;

  case 100: /* arg_list: ID  */
#line 1012 "yacc_sql.y"
         {
    (yyval.relation_list)=new std::vector<std::string>;
    (yyval.relation_list)->push_back((yyvsp[0].string));
    }
#line 2901 "yacc_sql.cpp"
    break;

  case 101: /* arg_list: ID COMMA arg_list  */
#line 1016 "yacc_sql.y"
                      {
    if((yyvsp[0].relation_list)!=nullptr){
        (yyval.relation_list)=(yyvsp[0].relation_list);
        }else{
        (yyval.relation_list)=new std::vector<std::string>;
        }
        (yyval.relation_list)->push_back((yyvsp[-2].string));
    }
#line 2914 "yacc_sql.cpp"
    break;

  case 102: /* rel_attr: ID as  */
#line 1025 "yacc_sql.y"
         {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->agg=NO_AGG;
      (yyval.rel_attr)->is_right=true;
      if((yyvsp[0].string)!=nullptr){
      (yyval.rel_attr)->alias_name=(yyvsp[0].string);
      }

      free((yyvsp[-1].string));
    }
#line 2930 "yacc_sql.cpp"
    break;

  case 103: /* rel_attr: agg LBRACE arg_list RBRACE as  */
#line 1036 "yacc_sql.y"
                                  {
         (yyval.rel_attr) = new RelAttrSqlNode;
         if((yyvsp[-2].relation_list)==nullptr||(yyvsp[-2].relation_list)->size()!=1){
         (yyval.rel_attr)->is_right=false;
         }else{
         (yyval.rel_attr)->attribute_name = (*(yyvsp[-2].relation_list))[0];
         (yyval.rel_attr)->is_right=true;
         (yyval.rel_attr)->agg=(yyvsp[-4].agg);
         }
         if((yyvsp[0].string)!=nullptr){
          (yyval.rel_attr)->alias_name=(yyvsp[0].string);
         }
          free((yyvsp[-2].relation_list));

         }
#line 2950 "yacc_sql.cpp"
    break;

  case 104: /* rel_attr: ID DOT ID as  */
#line 1051 "yacc_sql.y"
                  {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->agg=NO_AGG;
      (yyval.rel_attr)->is_right=true;
      if((yyvsp[0].string)!=nullptr){
      (yyval.rel_attr)->alias_name=(yyvsp[0].string);
      }
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
    }
#line 2967 "yacc_sql.cpp"
    break;

  case 105: /* rel_attr: agg LBRACE ID DOT ID RBRACE as  */
#line 1063 "yacc_sql.y"
                                    {
               (yyval.rel_attr) = new RelAttrSqlNode;
               (yyval.rel_attr)->relation_name  = (yyvsp[-4].string);
               (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
               (yyval.rel_attr)->is_right=true;
               (yyval.rel_attr)->agg=(yyvsp[-6].agg);
               if((yyvsp[0].string)!=nullptr){
                     (yyval.rel_attr)->alias_name=(yyvsp[0].string);
                     }
               free((yyvsp[-4].string));
               free((yyvsp[-2].string));
    }
#line 2984 "yacc_sql.cpp"
    break;

  case 106: /* rel_attr: '*' as  */
#line 1075 "yacc_sql.y"
            {
          (yyval.rel_attr) = new RelAttrSqlNode;
          (yyval.rel_attr)->relation_name  = "";
          (yyval.rel_attr)->attribute_name = "*";
          if((yyvsp[0].string)!=nullptr){
          (yyval.rel_attr)->is_right=false;
          }else{
          (yyval.rel_attr)->is_right=true;
          }

          (yyval.rel_attr)->agg=NO_AGG;
        }
#line 3001 "yacc_sql.cpp"
    break;

  case 107: /* rel_attr: ID DOT '*' as  */
#line 1087 "yacc_sql.y"
                   {
           (yyval.rel_attr) = new RelAttrSqlNode;
          (yyval.rel_attr)->relation_name  = (yyvsp[-3].string);
          (yyval.rel_attr)->attribute_name = "*";
          if((yyvsp[0].string)!=nullptr){
          (yyval.rel_attr)->is_right=false;
          }else{
          (yyval.rel_attr)->is_right=true;
          }

          (yyval.rel_attr)->agg=NO_AGG;
    }
#line 3018 "yacc_sql.cpp"
    break;

  case 108: /* rel_list: %empty  */
#line 1120 "yacc_sql.y"
    {
      (yyval.inner_join_list) = nullptr;
    }
#line 3026 "yacc_sql.cpp"
    break;

  case 109: /* rel_list: COMMA ID as rel_list  */
#line 1123 "yacc_sql.y"
                           {
      if ((yyvsp[0].inner_join_list) != nullptr) {
        (yyval.inner_join_list) = (yyvsp[0].inner_join_list);
      } else {
        (yyval.inner_join_list) = new InnerJoinSqlNode;
      }
      if((yyvsp[-1].string)!=nullptr){
      if((yyval.inner_join_list)->alias_map.find((yyvsp[-1].string))==(yyval.inner_join_list)->alias_map.end()){
      (yyval.inner_join_list)->alias_map[(yyvsp[-1].string)]=(yyvsp[-2].string);
      }else{
      (yyval.inner_join_list)->is_alias_right=false;
      }
      }

      (yyval.inner_join_list)->relations.push_back((yyvsp[-2].string));
      free((yyvsp[-2].string));
    }
#line 3048 "yacc_sql.cpp"
    break;

  case 110: /* rel_list: INNER JOIN ID as on rel_list  */
#line 1140 "yacc_sql.y"
                                  {
           if ((yyvsp[0].inner_join_list) != nullptr) {
             (yyval.inner_join_list) = (yyvsp[0].inner_join_list);
           } else {
             (yyval.inner_join_list) = new InnerJoinSqlNode;
           }

           (yyval.inner_join_list)->relations.push_back((yyvsp[-3].string));
           if((yyvsp[-1].condition_list)!=nullptr){
           (yyval.inner_join_list)->conditions.insert((yyval.inner_join_list)->conditions.end(),(yyvsp[-1].condition_list)->begin(),(yyvsp[-1].condition_list)->end());
           }
           if((yyvsp[-2].string)!=nullptr){
           if((yyval.inner_join_list)->alias_map.find((yyvsp[-2].string))==(yyval.inner_join_list)->alias_map.end()){
           (yyval.inner_join_list)->alias_map[(yyvsp[-2].string)]=(yyvsp[-3].string);
           }else{
           (yyval.inner_join_list)->is_alias_right=false;
           }

           }

           free((yyvsp[-3].string));
         }
#line 3075 "yacc_sql.cpp"
    break;

  case 111: /* where: %empty  */
#line 1167 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3083 "yacc_sql.cpp"
    break;

  case 112: /* where: WHERE condition_list  */
#line 1170 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3091 "yacc_sql.cpp"
    break;

  case 113: /* on: %empty  */
#line 1176 "yacc_sql.y"
     {
        (yyval.condition_list) = nullptr;
     }
#line 3099 "yacc_sql.cpp"
    break;

  case 114: /* on: ON condition_list  */
#line 1179 "yacc_sql.y"
                         {
        (yyval.condition_list) = (yyvsp[0].condition_list);
     }
#line 3107 "yacc_sql.cpp"
    break;

  case 115: /* condition_list: %empty  */
#line 1185 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3115 "yacc_sql.cpp"
    break;

  case 116: /* condition_list: condition  */
#line 1188 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyvsp[0].condition)->is_conjunction_or=false;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3126 "yacc_sql.cpp"
    break;

  case 117: /* condition_list: condition AND condition_list  */
#line 1194 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->is_conjunction_or=false;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3137 "yacc_sql.cpp"
    break;

  case 118: /* condition_list: condition OR condition_list  */
#line 1200 "yacc_sql.y"
                                  {
           (yyval.condition_list) = (yyvsp[0].condition_list);
           (yyvsp[-2].condition)->is_conjunction_or=true;
           (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
           delete (yyvsp[-2].condition);
         }
#line 3148 "yacc_sql.cpp"
    break;

  case 119: /* condition: expression comp_op expression  */
#line 1437 "yacc_sql.y"
                                  {
          (yyval.condition) = new ConditionSqlNode;
          if((yyvsp[-2].expression)->is_expression==false){
          if((yyvsp[-2].expression)->is_value==true){
          (yyval.condition)->left_type=VALUE_TYPE;
          (yyval.condition)->left_value=((ValueExpr*)((yyvsp[-2].expression)->expression[0]))->get_value();
          }else{
             (yyval.condition)->left_type = ATTR_TYPE;
             (yyval.condition)->left_attr = (yyvsp[-2].expression)->relAttrSqlNodes[0];
          }
          }else{
          (yyval.condition)->left_type = EXPR_TYPE;
          (yyval.condition)->left_expr = (yyvsp[-2].expression)->expression[0];
          (yyval.condition)->left_relAttrSqlNodes.insert((yyval.condition)->left_relAttrSqlNodes.end(),(yyvsp[-2].expression)->relAttrSqlNodes.begin(),(yyvsp[-2].expression)->relAttrSqlNodes.end());
          (yyval.condition)->left_fieldExprs.insert((yyval.condition)->left_fieldExprs.end(),(yyvsp[-2].expression)->fieldExprs.begin(),(yyvsp[-2].expression)->fieldExprs.end());
          }

          if((yyvsp[0].expression)->is_expression==false){
          if((yyvsp[0].expression)->is_value==true){
          (yyval.condition)->right_type=VALUE_TYPE;
          (yyval.condition)->right_value=((ValueExpr*)((yyvsp[0].expression)->expression[0]))->get_value();
          }else{
          (yyval.condition)->right_type = ATTR_TYPE;
          (yyval.condition)->right_attr = (yyvsp[0].expression)->relAttrSqlNodes[0];
          }
          }else{
          (yyval.condition)->right_type = EXPR_TYPE;
          (yyval.condition)->right_expr = (yyvsp[0].expression)->expression[0];
          (yyval.condition)->right_relAttrSqlNodes.insert((yyval.condition)->right_relAttrSqlNodes.end(),(yyvsp[0].expression)->relAttrSqlNodes.begin(),(yyvsp[0].expression)->relAttrSqlNodes.end());
          (yyval.condition)->right_fieldExprs.insert((yyval.condition)->right_fieldExprs.end(),(yyvsp[0].expression)->fieldExprs.begin(),(yyvsp[0].expression)->fieldExprs.end());
          }
          (yyval.condition)->comp = (yyvsp[-1].comp);



     }
#line 3189 "yacc_sql.cpp"
    break;

  case 120: /* condition: expression comp_op LBRACE select_stmt RBRACE  */
#line 1473 "yacc_sql.y"
                                                   {
          (yyval.condition) = new ConditionSqlNode;
          if((yyvsp[-4].expression)->is_expression==false){
          if((yyvsp[-4].expression)->is_value==true){
          (yyval.condition)->left_type=VALUE_TYPE;
          (yyval.condition)->left_value=((ValueExpr*)((yyvsp[-4].expression)->expression[0]))->get_value();
          }else{
                 (yyval.condition)->left_type = ATTR_TYPE;
                 (yyval.condition)->left_attr = (yyvsp[-4].expression)->relAttrSqlNodes[0];
          }
          }else{
          (yyval.condition)->left_type = EXPR_TYPE;
          (yyval.condition)->left_expr = (yyvsp[-4].expression)->expression[0];
          (yyval.condition)->left_relAttrSqlNodes.insert((yyval.condition)->left_relAttrSqlNodes.end(),(yyvsp[-4].expression)->relAttrSqlNodes.begin(),(yyvsp[-4].expression)->relAttrSqlNodes.end());
          (yyval.condition)->left_fieldExprs.insert((yyval.condition)->left_fieldExprs.end(),(yyvsp[-4].expression)->fieldExprs.begin(),(yyvsp[-4].expression)->fieldExprs.end());
          }

          (yyval.condition)->right_type = SUB_SELECT_TYPE;
          (yyval.condition)->right_select = &((yyvsp[-1].sql_node)->selection);
          (yyval.condition)->right_select->is_sub_select=true;
          (yyval.condition)->comp = (yyvsp[-3].comp);

     }
#line 3217 "yacc_sql.cpp"
    break;

  case 121: /* condition: LBRACE select_stmt RBRACE comp_op expression  */
#line 1496 "yacc_sql.y"
                                                   {
          (yyval.condition) = new ConditionSqlNode;

          if((yyvsp[0].expression)->is_expression==false){
          if((yyvsp[0].expression)->is_value==true){
          (yyval.condition)->right_type=VALUE_TYPE;
          (yyval.condition)->right_value=((ValueExpr*)((yyvsp[0].expression)->expression[0]))->get_value();
          }else{
          (yyval.condition)->right_type = ATTR_TYPE;
          (yyval.condition)->right_attr = (yyvsp[0].expression)->relAttrSqlNodes[0];
          }
          }else{
          (yyval.condition)->right_type = EXPR_TYPE;
          (yyval.condition)->right_expr = (yyvsp[0].expression)->expression[0];
          (yyval.condition)->right_relAttrSqlNodes.insert((yyval.condition)->right_relAttrSqlNodes.end(),(yyvsp[0].expression)->relAttrSqlNodes.begin(),(yyvsp[0].expression)->relAttrSqlNodes.end());
          (yyval.condition)->right_fieldExprs.insert((yyval.condition)->right_fieldExprs.end(),(yyvsp[0].expression)->fieldExprs.begin(),(yyvsp[0].expression)->fieldExprs.end());
          }


          (yyval.condition)->left_type = SUB_SELECT_TYPE;
          (yyval.condition)->left_select = &((yyvsp[-3].sql_node)->selection);
          (yyval.condition)->left_select->is_sub_select=true;
          (yyval.condition)->comp = (yyvsp[-1].comp);

     }
#line 3247 "yacc_sql.cpp"
    break;

  case 122: /* condition: LBRACE select_stmt RBRACE comp_op LBRACE select_stmt RBRACE  */
#line 1521 "yacc_sql.y"
                                                                 {
         (yyval.condition) = new ConditionSqlNode;
         (yyval.condition)->left_type = SUB_SELECT_TYPE;
         (yyval.condition)->left_select =  &((yyvsp[-5].sql_node)->selection);
         (yyval.condition)->left_select->is_sub_select=true;
         (yyval.condition)->right_type = SUB_SELECT_TYPE;
         (yyval.condition)->right_select =  &((yyvsp[-1].sql_node)->selection);
         (yyval.condition)->right_select->is_sub_select=true;
         (yyval.condition)->comp = (yyvsp[-3].comp);


     }
#line 3264 "yacc_sql.cpp"
    break;

  case 123: /* condition: EXISTS LBRACE select_stmt RBRACE  */
#line 1533 "yacc_sql.y"
                                      {
              (yyval.condition) = new ConditionSqlNode;
              (yyval.condition)->right_type = SUB_SELECT_TYPE;
              (yyval.condition)->right_select =  &((yyvsp[-1].sql_node)->selection);
              (yyval.condition)->right_select->is_sub_select=true;
              (yyval.condition)->comp = EXISTS_OP;

     }
#line 3277 "yacc_sql.cpp"
    break;

  case 124: /* condition: NOT EXISTS LBRACE select_stmt RBRACE  */
#line 1541 "yacc_sql.y"
                                           {
         (yyval.condition) = new ConditionSqlNode;
         (yyval.condition)->right_type = SUB_SELECT_TYPE;
         (yyval.condition)->right_select =  &((yyvsp[-1].sql_node)->selection);
         (yyval.condition)->right_select->is_sub_select=true;
         (yyval.condition)->comp = NOT_EXISTS_OP;
     }
#line 3289 "yacc_sql.cpp"
    break;

  case 125: /* condition: expression comp_op LBRACE value COMMA value value_list RBRACE  */
#line 1548 "yacc_sql.y"
                                                                   {
         (yyval.condition) = new ConditionSqlNode;

         if((yyvsp[-7].expression)->is_expression==false){
         if((yyvsp[-7].expression)->is_value==true){
         (yyval.condition)->left_type=VALUE_TYPE;
         (yyval.condition)->left_value=((ValueExpr*)((yyvsp[-7].expression)->expression[0]))->get_value();
         }else{
         (yyval.condition)->left_type = ATTR_TYPE;
         (yyval.condition)->left_attr = (yyvsp[-7].expression)->relAttrSqlNodes[0];
         }
         }else{
         (yyval.condition)->left_type = EXPR_TYPE;
         (yyval.condition)->left_expr = (yyvsp[-7].expression)->expression[0];
         (yyval.condition)->left_relAttrSqlNodes.insert((yyval.condition)->left_relAttrSqlNodes.end(),(yyvsp[-7].expression)->relAttrSqlNodes.begin(),(yyvsp[-7].expression)->relAttrSqlNodes.end());
         (yyval.condition)->left_fieldExprs.insert((yyval.condition)->left_fieldExprs.end(),(yyvsp[-7].expression)->fieldExprs.begin(),(yyvsp[-7].expression)->fieldExprs.end());
         }

         (yyval.condition)->right_type = VALUE_LIST_TYPE;
         if((yyvsp[-1].value_list)!=nullptr){
         (yyval.condition)->right_value_list.insert((yyval.condition)->right_value_list.end(),(yyvsp[-1].value_list)->begin(),(yyvsp[-1].value_list)->end());
          }
          (yyval.condition)->right_value_list.push_back(*(yyvsp[-2].value));
          (yyval.condition)->right_value_list.push_back(*(yyvsp[-4].value));
          std::reverse((yyval.condition)->right_value_list.begin(),(yyval.condition)->right_value_list.end());
          (yyval.condition)->comp = (yyvsp[-6].comp);
     }
#line 3321 "yacc_sql.cpp"
    break;

  case 126: /* comp_op: EQ  */
#line 1579 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3327 "yacc_sql.cpp"
    break;

  case 127: /* comp_op: LT  */
#line 1580 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3333 "yacc_sql.cpp"
    break;

  case 128: /* comp_op: GT  */
#line 1581 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3339 "yacc_sql.cpp"
    break;

  case 129: /* comp_op: LE  */
#line 1582 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3345 "yacc_sql.cpp"
    break;

  case 130: /* comp_op: GE  */
#line 1583 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3351 "yacc_sql.cpp"
    break;

  case 131: /* comp_op: NE  */
#line 1584 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3357 "yacc_sql.cpp"
    break;

  case 132: /* comp_op: LK  */
#line 1585 "yacc_sql.y"
         {(yyval.comp) = LIKE;}
#line 3363 "yacc_sql.cpp"
    break;

  case 133: /* comp_op: NOT LK  */
#line 1586 "yacc_sql.y"
             {(yyval.comp) = NOT_LIKE;}
#line 3369 "yacc_sql.cpp"
    break;

  case 134: /* comp_op: IS  */
#line 1587 "yacc_sql.y"
            {(yyval.comp)=IS_NULL;}
#line 3375 "yacc_sql.cpp"
    break;

  case 135: /* comp_op: IS NOT  */
#line 1588 "yacc_sql.y"
             {(yyval.comp)=IS_NOT_NULL;}
#line 3381 "yacc_sql.cpp"
    break;

  case 136: /* comp_op: IN  */
#line 1589 "yacc_sql.y"
           {(yyval.comp)=IN_OP;}
#line 3387 "yacc_sql.cpp"
    break;

  case 137: /* comp_op: NOT IN  */
#line 1590 "yacc_sql.y"
             {(yyval.comp)=NOT_IN_OP;}
#line 3393 "yacc_sql.cpp"
    break;

  case 138: /* agg: MAX_agg  */
#line 1593 "yacc_sql.y"
           {(yyval.agg)=MAX_AGG;}
#line 3399 "yacc_sql.cpp"
    break;

  case 139: /* agg: MIN_agg  */
#line 1594 "yacc_sql.y"
            {(yyval.agg)=MIN_AGG;}
#line 3405 "yacc_sql.cpp"
    break;

  case 140: /* agg: AVG_agg  */
#line 1595 "yacc_sql.y"
            {(yyval.agg)=AVG_AGG;}
#line 3411 "yacc_sql.cpp"
    break;

  case 141: /* agg: COUNT_agg  */
#line 1596 "yacc_sql.y"
              {(yyval.agg)=COUNT_AGG;}
#line 3417 "yacc_sql.cpp"
    break;

  case 142: /* agg: SUM_agg  */
#line 1597 "yacc_sql.y"
            {(yyval.agg)=SUM_AGG;}
#line 3423 "yacc_sql.cpp"
    break;

  case 143: /* as: %empty  */
#line 1600 "yacc_sql.y"
  {
    (yyval.string) = nullptr;
  }
#line 3431 "yacc_sql.cpp"
    break;

  case 144: /* as: AS ID  */
#line 1603 "yacc_sql.y"
          {
    (yyval.string) = (yyvsp[0].string);
  }
#line 3439 "yacc_sql.cpp"
    break;

  case 145: /* as: ID  */
#line 1606 "yacc_sql.y"
       {
    (yyval.string) = (yyvsp[0].string);
  }
#line 3447 "yacc_sql.cpp"
    break;

  case 146: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1612 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3461 "yacc_sql.cpp"
    break;

  case 147: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1625 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3470 "yacc_sql.cpp"
    break;

  case 148: /* set_variable_stmt: SET ID EQ value  */
#line 1633 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3482 "yacc_sql.cpp"
    break;


#line 3486 "yacc_sql.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          goto yyexhaustedlab;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
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


#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1645 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
