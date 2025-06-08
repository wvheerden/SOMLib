
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 6 "ingest.y"

static char *SccsId = "@(#)ingest.y 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";

/* Parsing routines for RealID */

#include "mdep.h"

#include <stdio.h>
#include <strings.h>


#define _MC68881_
#include <math.h>

#include "cn_externs.h"

/* Other C declarations for example reading */

void attr_error(), print_att_value(), dc_error(), uk_error();
int number_of_errors;
EList example_list;
EList *e_ptr;
EList *ex_ptr_array;

List attribute_list, new_list, tree_att_list;
List *attr_ptr;

binary_action default_binary_flag, current_binary_flag;

Attribute *IDclass, *current_attr;

int att_num, number_of_attributes, number_of_classes;
BOOL ukdc_flag;
long number_of_examples;
int errflag, ex_errflag;
char temp[BUFSIZ];

/* Other C declarations for tree reading */

int att_val, count_index;



/* Line 189 of yacc.c  */
#line 117 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     STRING = 258,
     INTEGER_TOKEN = 259,
     FLOAT_TOKEN = 260,
     BOTH_FILE_HEADER = 261,
     ATTRIBUTE_FILE_HEADER = 262,
     EXAMPLE_FILE_HEADER = 263,
     TREE_FILE_HEADER = 264,
     RULE_FILE_HEADER = 265,
     ORDERED_RULE_TOKEN = 266,
     UNORDERED_RULE_TOKEN = 267,
     BEFORE_TOKEN = 268,
     ORDERING_TOKEN = 269,
     IF_TOKEN = 270,
     THEN_TOKEN = 271,
     AND_TOKEN = 272,
     ELSE_TOKEN = 273,
     DEFAULT_TOKEN = 274,
     BINARY_TOKEN = 275,
     MULTIPLE_TOKEN = 276,
     DONT_CARE = 277,
     UNKNOWN = 278,
     FLOAT_TYPE = 279,
     INTEGER_TYPE = 280,
     SEPARATOR = 281,
     COLON = 282,
     EOE_CHAR = 283,
     LEQ = 284,
     GE = 285,
     LE = 286,
     EQUALS = 287,
     NULL_DECISION = 288,
     CLASH_DECISION = 289,
     OPEN_PARENTHESIS = 290,
     CLOSE_PARENTHESIS = 291,
     OPEN_BRACKET = 292,
     CLOSE_BRACKET = 293,
     OPEN_SQUARE = 294,
     CLOSE_SQUARE = 295,
     W_TOKEN = 296
   };
#endif
/* Tokens.  */
#define STRING 258
#define INTEGER_TOKEN 259
#define FLOAT_TOKEN 260
#define BOTH_FILE_HEADER 261
#define ATTRIBUTE_FILE_HEADER 262
#define EXAMPLE_FILE_HEADER 263
#define TREE_FILE_HEADER 264
#define RULE_FILE_HEADER 265
#define ORDERED_RULE_TOKEN 266
#define UNORDERED_RULE_TOKEN 267
#define BEFORE_TOKEN 268
#define ORDERING_TOKEN 269
#define IF_TOKEN 270
#define THEN_TOKEN 271
#define AND_TOKEN 272
#define ELSE_TOKEN 273
#define DEFAULT_TOKEN 274
#define BINARY_TOKEN 275
#define MULTIPLE_TOKEN 276
#define DONT_CARE 277
#define UNKNOWN 278
#define FLOAT_TYPE 279
#define INTEGER_TYPE 280
#define SEPARATOR 281
#define COLON 282
#define EOE_CHAR 283
#define LEQ 284
#define GE 285
#define LE 286
#define EQUALS 287
#define NULL_DECISION 288
#define CLASH_DECISION 289
#define OPEN_PARENTHESIS 290
#define CLOSE_PARENTHESIS 291
#define OPEN_BRACKET 292
#define CLOSE_BRACKET 293
#define OPEN_SQUARE 294
#define CLOSE_SQUARE 295
#define W_TOKEN 296




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 49 "ingest.y"

	int ival;
	float fval;
	char *sval;



/* Line 214 of yacc.c  */
#line 243 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 255 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   138

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  70
/* YYNRULES -- Number of rules.  */
#define YYNRULES  109
/* YYNRULES -- Number of states.  */
#define YYNSTATES  170

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    11,    13,    15,    17,
      18,    25,    26,    30,    31,    35,    37,    38,    43,    44,
      48,    49,    53,    57,    58,    59,    62,    63,    66,    68,
      69,    76,    80,    84,    88,    92,    94,    95,    99,   103,
     105,   108,   110,   113,   114,   118,   120,   124,   128,   130,
     131,   135,   137,   139,   141,   143,   145,   146,   149,   152,
     154,   159,   160,   164,   165,   172,   174,   176,   179,   182,
     184,   187,   188,   189,   190,   191,   200,   202,   203,   204,
     205,   212,   214,   218,   222,   226,   230,   236,   238,   242,
     243,   249,   250,   255,   257,   260,   262,   264,   267,   269,
     273,   277,   281,   285,   293,   295,   297,   299,   305,   307
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      43,     0,    -1,    -1,    44,    45,    -1,    46,    -1,    48,
      -1,    50,    -1,    78,    -1,   111,    -1,    -1,     6,    47,
      52,    26,    57,    26,    -1,    -1,     7,    49,    52,    -1,
      -1,     8,    51,    57,    -1,    54,    -1,    -1,    54,    53,
      14,    74,    -1,    -1,    56,    55,    59,    -1,    -1,    35,
      20,    36,    -1,    35,    21,    36,    -1,    -1,    -1,    58,
      67,    -1,    -1,    59,    60,    -1,    60,    -1,    -1,     3,
      27,    62,    61,    66,    28,    -1,     3,    27,    65,    -1,
       3,    27,    64,    -1,    35,    20,    36,    -1,    35,    21,
      36,    -1,    63,    -1,    -1,    35,    25,    36,    -1,    35,
      24,    36,    -1,     3,    -1,    66,     3,    -1,    68,    -1,
      67,    68,    -1,    -1,    69,    71,    70,    -1,    28,    -1,
      41,     4,    28,    -1,    41,     5,    28,    -1,    73,    -1,
      -1,    71,    72,    73,    -1,     3,    -1,     5,    -1,     4,
      -1,    22,    -1,    23,    -1,    -1,    75,    76,    -1,    76,
      77,    -1,    77,    -1,     3,    13,     3,    28,    -1,    -1,
      10,    79,    80,    -1,    -1,    26,    81,   103,    26,    82,
      83,    -1,    11,    -1,    12,    -1,    84,    91,    -1,    85,
      91,    -1,    86,    -1,    84,    86,    -1,    -1,    -1,    -1,
      -1,    87,    15,    88,    94,    16,    89,    97,    90,    -1,
      18,    -1,    -1,    -1,    -1,    92,    35,    19,    36,    93,
      97,    -1,    95,    -1,    94,    17,    95,    -1,    96,    32,
       3,    -1,    96,    31,     5,    -1,    96,    30,     5,    -1,
       5,    31,    96,    31,     5,    -1,     3,    -1,     3,    32,
       3,    -1,    -1,     3,    32,     3,    98,    99,    -1,    -1,
      39,   100,   101,    40,    -1,   102,    -1,   101,   102,    -1,
       4,    -1,     5,    -1,   103,   104,    -1,   104,    -1,     3,
      27,   105,    -1,     3,    27,     3,    -1,     3,    27,     5,
      -1,     3,    27,     4,    -1,    39,   106,   107,   108,   109,
     110,    40,    -1,     3,    -1,     3,    -1,     4,    -1,     4,
      27,     4,    27,     4,    -1,     4,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    77,    77,    77,    81,    82,    83,    84,    85,    91,
      90,   113,   112,   129,   128,   145,   152,   151,   162,   161,
     189,   196,   202,   208,   217,   217,   234,   241,   244,   249,
     248,   269,   283,   296,   302,   308,   311,   315,   318,   322,
     326,   332,   333,   337,   337,   353,   356,   359,   365,   368,
     367,   382,   395,   404,   418,   440,   466,   466,   471,   473,
     476,   489,   488,   505,   504,   512,   520,   529,   531,   535,
     536,   538,   542,   544,   551,   542,   560,   561,   566,   572,
     566,   579,   580,   583,   605,   622,   640,   662,   674,   686,
     685,   699,   699,   709,   710,   714,   727,   741,   743,   747,
     752,   757,   762,   768,   776,   777,   778,   779,   780,   785
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "STRING", "INTEGER_TOKEN", "FLOAT_TOKEN",
  "BOTH_FILE_HEADER", "ATTRIBUTE_FILE_HEADER", "EXAMPLE_FILE_HEADER",
  "TREE_FILE_HEADER", "RULE_FILE_HEADER", "ORDERED_RULE_TOKEN",
  "UNORDERED_RULE_TOKEN", "BEFORE_TOKEN", "ORDERING_TOKEN", "IF_TOKEN",
  "THEN_TOKEN", "AND_TOKEN", "ELSE_TOKEN", "DEFAULT_TOKEN", "BINARY_TOKEN",
  "MULTIPLE_TOKEN", "DONT_CARE", "UNKNOWN", "FLOAT_TYPE", "INTEGER_TYPE",
  "SEPARATOR", "COLON", "EOE_CHAR", "LEQ", "GE", "LE", "EQUALS",
  "NULL_DECISION", "CLASH_DECISION", "OPEN_PARENTHESIS",
  "CLOSE_PARENTHESIS", "OPEN_BRACKET", "CLOSE_BRACKET", "OPEN_SQUARE",
  "CLOSE_SQUARE", "W_TOKEN", "$accept", "input", "$@1", "input_file",
  "both_file", "$@2", "attribute_file", "$@3", "example_file", "$@4",
  "attributes_etc", "$@5", "all_attributes", "$@6", "binary_flag",
  "all_examples", "$@7", "att_declarations", "att_declaration", "$@8",
  "binary_att_flag", "empty", "integer_type", "float_type", "att_vals",
  "examples", "example", "$@9", "example_terminator", "example_values",
  "$@10", "example_value", "attribute_ordering", "$@11", "att_orders",
  "att_order", "rule_file", "$@12", "root", "$@13",
  "rule_type_declaration", "all_rules", "rule_list", "empty_rule_list",
  "rule", "$@14", "$@15", "$@16", "rule_separator", "default_rule", "$@17",
  "$@18", "premise", "condition", "att_string", "conclusion", "$@19",
  "count_array", "$@20", "count_numbers", "count_number",
  "rule_parameters", "rule_parameter", "time_stamp", "weekday", "month",
  "day", "time", "year", "rubbish", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    44,    43,    45,    45,    45,    45,    45,    47,
      46,    49,    48,    51,    50,    52,    53,    52,    55,    54,
      54,    56,    56,    56,    58,    57,    57,    59,    59,    61,
      60,    60,    60,    62,    62,    62,    63,    64,    65,    66,
      66,    67,    67,    69,    68,    70,    70,    70,    71,    72,
      71,    73,    73,    73,    73,    73,    75,    74,    76,    76,
      77,    79,    78,    81,    80,    82,    82,    83,    83,    84,
      84,    85,    87,    88,    89,    86,    90,    90,    92,    93,
      91,    94,    94,    95,    95,    95,    95,    96,    97,    98,
      97,   100,    99,   101,   101,   102,   102,   103,   103,   104,
     104,   104,   104,   105,   106,   107,   108,   109,   110,   111
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     0,
       6,     0,     3,     0,     3,     1,     0,     4,     0,     3,
       0,     3,     3,     0,     0,     2,     0,     2,     1,     0,
       6,     3,     3,     3,     3,     1,     0,     3,     3,     1,
       2,     1,     2,     0,     3,     1,     3,     3,     1,     0,
       3,     1,     1,     1,     1,     1,     0,     2,     2,     1,
       4,     0,     3,     0,     6,     1,     1,     2,     2,     1,
       2,     0,     0,     0,     0,     8,     1,     0,     0,     0,
       6,     1,     3,     3,     3,     3,     5,     1,     3,     0,
       5,     0,     4,     1,     2,     1,     1,     2,     1,     3,
       3,     3,     3,     7,     1,     1,     1,     5,     1,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,   109,     1,     9,    11,    13,    61,     3,     4,
       5,     6,     7,     8,    20,    20,    24,     0,     0,     0,
      15,    18,    12,    14,    43,    63,    62,     0,     0,    24,
       0,     0,    43,    41,     0,     0,    21,    22,     0,    56,
       0,    19,    28,    42,    51,    53,    52,    54,    55,    49,
      48,     0,     0,    98,    10,    17,     0,    36,    27,    45,
       0,    44,     0,     0,     0,    97,     0,    57,    59,     0,
      29,    35,    32,    31,     0,     0,    50,   100,   102,   101,
       0,    99,    65,    66,    71,     0,    58,     0,     0,     0,
       0,     0,    46,    47,   104,     0,    64,    72,    78,    69,
       0,     0,    33,    34,    38,    37,    39,     0,   105,     0,
      70,    67,     0,    68,    73,    60,    40,    30,   106,     0,
       0,     0,     0,     0,     0,    87,     0,     0,    81,     0,
       0,   108,     0,    79,     0,    74,     0,     0,     0,     0,
       0,   103,     0,     0,     0,    82,    85,    84,    83,     0,
       0,    80,     0,    77,   107,     0,    86,    76,    75,    88,
       0,    91,    90,     0,    95,    96,     0,    93,    92,    94
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     8,     9,    14,    10,    15,    11,    16,
      19,    30,    20,    31,    21,    23,    24,    41,    42,    91,
      70,    71,    72,    73,   107,    32,    33,    34,    61,    49,
      62,    50,    55,    56,    67,    68,    12,    17,    26,    35,
      84,    96,    97,    98,    99,   100,   121,   144,   158,   111,
     112,   142,   127,   128,   129,   151,   160,   162,   163,   166,
     167,    52,    53,    81,    95,   109,   119,   123,   132,    13
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -58
static const yytype_int8 yypact[] =
{
     -58,    23,    21,   -58,   -58,   -58,   -58,   -58,   -58,   -58,
     -58,   -58,   -58,   -58,     2,     2,    26,    22,    -7,    24,
      33,   -58,   -58,   -58,   -58,   -58,   -58,    13,    15,    28,
      38,    50,     6,   -58,    12,    52,   -58,   -58,    31,   -58,
      29,    50,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -19,
     -58,    32,     4,   -58,   -58,   -58,    55,    25,   -58,   -58,
      14,   -58,    12,    -3,    30,   -58,    48,    55,   -58,     0,
     -58,   -58,   -58,   -58,    34,    36,   -58,   -58,   -58,   -58,
      60,   -58,   -58,   -58,    51,    62,   -58,    37,    39,    40,
      42,    64,   -58,   -58,   -58,    65,   -58,    44,   -58,   -58,
      54,    43,   -58,   -58,   -58,   -58,   -58,     5,   -58,    66,
     -58,   -58,    45,   -58,   -58,   -58,   -58,   -58,   -58,    68,
      58,    35,    47,    77,    46,   -58,    53,    27,   -58,   -20,
      79,   -58,    49,   -58,    82,   -58,    35,    81,    83,    84,
      63,   -58,    88,    61,    88,   -58,   -58,   -58,   -58,    89,
      67,   -58,    90,    76,   -58,    93,   -58,   -58,   -58,    59,
      69,   -58,   -58,    41,   -58,   -58,    -1,   -58,   -58,   -58
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,
      85,   -58,   -58,   -58,   -58,    72,   -58,   -58,    56,   -58,
     -58,   -58,   -58,   -58,   -58,   -58,    70,   -58,   -58,   -58,
     -58,    57,   -58,   -58,   -58,    71,   -58,   -58,   -58,   -58,
     -58,   -58,   -58,   -58,     7,   -58,   -58,   -58,   -58,     8,
     -58,   -58,   -58,   -33,   -29,   -37,   -58,   -58,   -58,   -58,
     -57,   -58,    73,   -58,   -58,   -58,   -58,   -58,   -58,   -58
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -90
static const yytype_int16 yytable[] =
{
      77,    78,    79,   164,   165,   -23,   -25,    51,   116,    59,
     137,   138,   139,    27,    28,    44,    45,    46,    74,    75,
      87,    88,    60,     3,    89,    90,   -26,     4,     5,     6,
      64,     7,   -25,   117,    47,    48,    80,    18,   125,   168,
     126,    82,    83,   135,   136,   164,   165,   -16,    25,    36,
      29,    37,    39,    40,   -26,    51,    57,    54,    66,    63,
      69,    85,    92,    94,    93,   101,   -72,   106,   108,   114,
     118,   115,   122,   102,   130,   103,   104,   124,   105,   -78,
     120,   131,   133,   140,   134,   125,   146,   148,   147,   141,
     149,   150,   152,   154,   157,   156,   159,    58,   -89,   155,
      22,    38,    43,   145,   110,   143,   113,   153,   161,   169,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    76,
       0,     0,     0,     0,     0,    65,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    86
};

static const yytype_int16 yycheck[] =
{
       3,     4,     5,     4,     5,     3,     0,     3,     3,    28,
      30,    31,    32,    20,    21,     3,     4,     5,     4,     5,
      20,    21,    41,     0,    24,    25,     0,     6,     7,     8,
      26,    10,    26,    28,    22,    23,    39,    35,     3,    40,
       5,    11,    12,    16,    17,     4,     5,    14,    26,    36,
      26,    36,    14,     3,    26,     3,    27,    26,     3,    27,
      35,    13,    28,     3,    28,     3,    15,     3,     3,    15,
       4,    28,     4,    36,    27,    36,    36,    19,    36,    35,
      35,     4,    36,     4,    31,     3,     5,     3,     5,    40,
      27,     3,    31,     4,    18,     5,     3,    41,    39,    32,
      15,    29,    32,   136,    97,   134,    98,   144,    39,   166,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    43,    44,     0,     6,     7,     8,    10,    45,    46,
      48,    50,    78,   111,    47,    49,    51,    79,    35,    52,
      54,    56,    52,    57,    58,    26,    80,    20,    21,    26,
      53,    55,    67,    68,    69,    81,    36,    36,    57,    14,
       3,    59,    60,    68,     3,     4,     5,    22,    23,    71,
      73,     3,   103,   104,    26,    74,    75,    27,    60,    28,
      41,    70,    72,    27,    26,   104,     3,    76,    77,    35,
      62,    63,    64,    65,     4,     5,    73,     3,     4,     5,
      39,   105,    11,    12,    82,    13,    77,    20,    21,    24,
      25,    61,    28,    28,     3,   106,    83,    84,    85,    86,
      87,     3,    36,    36,    36,    36,     3,    66,     3,   107,
      86,    91,    92,    91,    15,    28,     3,    28,     4,   108,
      35,    88,     4,   109,    19,     3,     5,    94,    95,    96,
      27,     4,   110,    36,    31,    16,    17,    30,    31,    32,
       4,    40,    93,    96,    89,    95,     5,     5,     3,    27,
       3,    97,    31,    97,     4,    32,     5,    18,    90,     3,
      98,    39,    99,   100,     4,     5,   101,   102,    40,   102
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 77 "ingest.y"
    { ln = 1; }
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 91 "ingest.y"
    {
                if (input_type == ATTRIBUTES_AND_EXAMPLES){
		     fprintf(stdout,
			     "Reading attributes and examples...\n");
		}
		else {
		     input_type_error(ATTRIBUTES_AND_EXAMPLES);
   		     YYERROR;
		}
	      }
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 105 "ingest.y"
    { fprintf(stdout, "%d examples!\n", (int) number_of_examples);
                fprintf(stdout,
			"Finished reading attribute and example file!\n"); }
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 113 "ingest.y"
    {
                if (input_type == ATTRIBUTES){
		     fprintf(stdout,
			     "Reading attributes...\n");
		}
		else {
		     input_type_error(ATTRIBUTES);
   		     YYERROR;
		}
	      }
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 124 "ingest.y"
    { fprintf(stdout, "Finished reading attribute file!\n");
	      }
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 129 "ingest.y"
    {
                 if (input_type == EXAMPLES){
		     fprintf(stdout,
			     "Reading examples...\n");
		}
		else {
		     input_type_error(EXAMPLES);
   		     YYERROR;
		}
	      }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 140 "ingest.y"
    { fprintf(stdout, "%d examples!\n", (int) number_of_examples);
                fprintf(stdout, "Finished reading example file!\n"); }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 146 "ingest.y"
    {
#ifdef DEBUG_INPUT
                fprintf(stdout, "No order declarations.\n"); 
#endif
	      }
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 152 "ingest.y"
    {
#ifdef DEBUG_INPUT
                fprintf(stdout, "Order declarations....\n"); 
#endif
	      }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 162 "ingest.y"
    {  errflag = FALSE;      
	       attribute_list = new_listelement();
	       attr_ptr = &attribute_list;
	       att_num = 0;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 167 "ingest.y"
    { number_of_attributes = (yyvsp[(3) - (3)].ival);  /* att_declarations */
#ifdef DEBUG_INPUT
	       fprintf(stdout, "I reckon there were %d attributes\n\n",
		                                      number_of_attributes);
#endif
	       FREE(*attr_ptr);
               (*attr_ptr) = (List)0;
   	       IDclass = (last(attribute_list)) -> head -> value;
	       if (ATT_TYPE(IDclass) == ORDERED_TYPE) 
		 num_class_error();
	       number_of_classes = N_VALUES(IDclass);
	       
	       if (errflag) {
		    fprintf(stdout, "Aborting parse.\n");
		    YYERROR;
	       }
	       else
		 setup_attribute_array();
	      }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 189 "ingest.y"
    {    fprintf(stdout, "ERROR: No attributes declarations\n");
	      fprintf(stdout, "Aborting parse.\n");
	      YYERROR;
	 }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 197 "ingest.y"
    {
#ifdef DEBUG_INPUT
	              fprintf(stdout, "Default discrete split is binary\n");
#endif
		      default_binary_flag = TWOWAY; }
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 203 "ingest.y"
    {
#ifdef DEBUG_INPUT
	              fprintf(stdout, "Default discrete split is multiple\n");
#endif
		      default_binary_flag = MULTIPLE; }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 208 "ingest.y"
    {
#ifdef DEBUG_INPUT
	              fprintf(stdout, "No default split declaration,\n");
	              fprintf(stdout, "so default will be multiple.\n");
#endif
	              default_binary_flag = MULTIPLE; }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 217 "ingest.y"
    {  errflag = FALSE;
		ukdc_flag = FALSE;
	        example_list = new_elistelement();
	        e_ptr = &example_list;  }
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 222 "ingest.y"
    { (*e_ptr) = (EList)0;
	       number_of_examples = (long ) 1 + (yyvsp[(2) - (2)].ival);    /* examples */
	       ex_ptr_array = (EList *) ALLOC((number_of_examples + 1)
					      * sizeof(EList));
               if (errflag) {
		    fprintf(stdout, "Aborting parse.\n");
		    YYERROR;
	       }
	      }
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 234 "ingest.y"
    {    fprintf(stdout, "ERROR: No examples\n");
	      fprintf(stdout, "Aborting parse.\n");
	      YYERROR;
	 }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 243 "ingest.y"
    {(yyval.ival) = (yyvsp[(1) - (2)].ival) + 1;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 245 "ingest.y"
    { (yyval.ival) = 1; }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 249 "ingest.y"
    { value_list = new_listelement();
		     value_ptr = &value_list; }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 252 "ingest.y"
    { ((*attr_ptr) -> head) = new_object();
#ifdef DEBUG_INPUT
                   fprintf(stdout, "\nAttribute:%s\n", (yyvsp[(1) - (6)].sval));
#endif
                  ((*attr_ptr) -> head -> value) =       /* att_vals */  
   		    new_attribute(intern((yyvsp[(1) - (6)].sval)), DISCRETE_TYPE, 0, (yyvsp[(5) - (6)].ival), value_list, att_num);
                  ((*attr_ptr) -> head -> otype) =  ATTRIBUTE_TYPE;
                  ((Attribute *)((*attr_ptr) -> head -> value))->bin_action =
		    current_binary_flag;
		  
		  (*attr_ptr) -> tail = new_listelement();
                  attr_ptr = &((*attr_ptr) -> tail); 
		  att_num++;
#ifdef DEBUG_INPUT
                   fprintf(stdout, "\n");
#endif
    	        }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 270 "ingest.y"
    {  ((*attr_ptr) -> head) = new_object();

#ifdef DEBUG_INPUT
                   fprintf(stdout, "\nAttribute:%s FLOAT\n", (yyvsp[(1) - (3)].sval));
#endif		  
                  ((*attr_ptr) -> head -> value) =
		     new_attribute(intern((yyvsp[(1) - (3)].sval)), ORDERED_TYPE, REAL, 2, (List)NULL, att_num);
                  ((*attr_ptr) -> head -> otype) =  ATTRIBUTE_TYPE;  
                  ((Attribute *)((*attr_ptr) -> head -> value))->bin_action =
		    MULTIPLE;
		  (*attr_ptr) -> tail = new_listelement();		  
                   attr_ptr = &((*attr_ptr) -> tail);
		   att_num++; }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 284 "ingest.y"
    {  ((*attr_ptr) -> head) = new_object();
                  ((*attr_ptr) -> head -> value) =
  		     new_attribute(intern((yyvsp[(1) - (3)].sval)), ORDERED_TYPE, INTEGRAL, 2, (List)NULL, att_num);
                  ((*attr_ptr) -> head -> otype) =  ATTRIBUTE_TYPE;
                  ((Attribute *)((*attr_ptr) -> head -> value))->bin_action =
		    MULTIPLE;		  
		  (*attr_ptr) -> tail = new_listelement();		  
                   attr_ptr = &((*attr_ptr) -> tail);
		   att_num++; }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 297 "ingest.y"
    {
#ifdef DEBUG_INPUT
	          fprintf(stdout, "Binary split coming up...\n");
#endif
		  current_binary_flag = TWOWAY; }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 303 "ingest.y"
    {
#ifdef DEBUG_INPUT
	          fprintf(stdout, "Multiple split coming up...\n");
#endif
		  current_binary_flag = MULTIPLE; }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 309 "ingest.y"
    { current_binary_flag = default_binary_flag; }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 323 "ingest.y"
    {  add_att_val((yyvsp[(1) - (1)].sval));
                 (yyval.ival) = 1;
              }
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 327 "ingest.y"
    {  add_att_val((yyvsp[(2) - (2)].sval));
                 (yyval.ival) = (yyvsp[(1) - (2)].ival) + 1;
              }
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 332 "ingest.y"
    {(yyval.ival) = 0;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 333 "ingest.y"
    {(yyval.ival) = (yyvsp[(1) - (2)].ival) + 1;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 337 "ingest.y"
    { att_num = 0;
		  attr_ptr = &attribute_list;
	          current_attr = (Attribute *) (*attr_ptr) -> head -> value;
		  ex_errflag = FALSE; }
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 342 "ingest.y"
    { if (! (att_num == (number_of_attributes-1)))
		    attr_num_error(ln, att_num, number_of_attributes);
		  (*e_ptr)->next = new_elistelement();
	          e_ptr = &((*e_ptr) -> next);
#ifdef DEBUG_INPUT
		  fprintf(stdout, "\n");
#endif
	        }
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 354 "ingest.y"
    {(*e_ptr)->weight = 1.0;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 358 "ingest.y"
    {(*e_ptr)->weight = (float) (yyvsp[(2) - (3)].ival);}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 361 "ingest.y"
    {(*e_ptr)->weight = (yyvsp[(2) - (3)].fval);}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 368 "ingest.y"
    {
			  if (att_num++ > (number_of_attributes - 2))
			    ex_errflag = TRUE;			     
			  if (! ex_errflag) {
			       attr_ptr = &((*attr_ptr) -> tail);
			       current_attr = (Attribute *)
				   (*attr_ptr) -> head -> value;
		          }
		     }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 382 "ingest.y"
    {if (! ex_errflag) {
		if (((current_attr ->atype) == DISCRETE_TYPE)
		     && value_id(intern((yyvsp[(1) - (1)].sval)), att_num,
				  (&(*e_ptr) -> values[att_num].d))){
#ifdef DEBUG_INPUT		     
		     fprintf(stdout, "%d:", att_num);
		     fprintf(stdout, "%s ", (yyvsp[(1) - (1)].sval));
#endif
		    }
		      else
			attr_error(ln, att_num,(yyvsp[(1) - (1)].sval));
 		    }
	           }
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 395 "ingest.y"
    {if (! ex_errflag) {
	               if ((current_attr -> atype) == ORDERED_TYPE)
			 (*e_ptr) -> values[att_num].o = (yyvsp[(1) - (1)].fval);
		       else {
			    sprintf(temp, "%f", (yyvsp[(1) - (1)].fval));
			    attr_error(ln, att_num, temp);
		       }
		    }
                   }
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 404 "ingest.y"
    {if (! ex_errflag) {
	               if ((current_attr->atype) == ORDERED_TYPE){
#ifdef DEBUG_INPUT		     
			 fprintf(stdout, "%d:", att_num);
		         fprintf(stdout, "%d ", (yyvsp[(1) - (1)].ival));
#endif			 
			 (*e_ptr) -> values[att_num].o = (float) (yyvsp[(1) - (1)].ival);
		       }
		       else {
			    sprintf(temp, "%d", (yyvsp[(1) - (1)].ival));		      
			    attr_error(ln, att_num, temp);
		       }
		    }
	           }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 418 "ingest.y"
    {if (! ex_errflag) {
	               ukdc_flag = TRUE;
	               if (att_num == (number_of_attributes-1)) 
			      dc_error(ln);		       
	               switch (current_attr -> atype){
		       case ORDERED_TYPE:
			    (*e_ptr) -> values[att_num].o = DC_FLOAT;
#ifdef DEBUG_INPUT		     
			    fprintf(stdout, "%d:", att_num);
			    fprintf(stdout, "DONT_CARE ");
#endif			    			    
			    break;
		       case DISCRETE_TYPE:
			    (*e_ptr) -> values[att_num].d = DC_INT;
#ifdef DEBUG_INPUT		     
			    fprintf(stdout, "%d:", att_num);
			    fprintf(stdout, "DONT_CARE ");
#endif			    
			    break;
		       }
		    }
		 }
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 440 "ingest.y"
    {if (! ex_errflag) {
	               if (att_num == (number_of_attributes-1)) 
			    uk_error(ln);	      
	               ukdc_flag = TRUE;	      
	               switch (current_attr -> atype){
		       case ORDERED_TYPE:
			    (*e_ptr) -> values[att_num].o = UK_FLOAT;
#ifdef DEBUG_INPUT		     
			    fprintf(stdout, "%d:", att_num);
			    fprintf(stdout, "UNKNOWN ");
#endif			    			    
			    break;
		       case DISCRETE_TYPE:
			    (*e_ptr) -> values[att_num].d = UK_INT;
#ifdef DEBUG_INPUT		     
			    fprintf(stdout, "%d:", att_num);
			    fprintf(stdout, "UNKNOWN ");
#endif			    			    
			    break;
		       }
		    }
	       }
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 466 "ingest.y"
    { initialise_order_array(); }
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 468 "ingest.y"
    { transform_order_array(); }
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 477 "ingest.y"
    {
#ifdef DEBUG_INPUT
	     fprintf(stdout, "%s before %s\n", (yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].sval));
#endif	     
	     insert_order_array((yyvsp[(1) - (4)].sval),(yyvsp[(3) - (4)].sval));
	}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 489 "ingest.y"
    {
                if (input_type == RULES){
		     fprintf(stdout,
			     "Reading rules...\n");
		}
		else {
		     input_type_error(RULES);
   		     YYERROR;
		}
	      }
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 500 "ingest.y"
    { fprintf(stdout, "Finished reading rules!\n"); }
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 505 "ingest.y"
    { init_rule_reader(); }
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 513 "ingest.y"
    { algorithm_flag |= A_ORDERED;
#ifdef DEBUG_INPUT		     
		 fprintf(stdout, "Rules will be Ordered\n");
#endif
	    }
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 521 "ingest.y"
    { algorithm_flag &= ~A_ORDERED;
#ifdef DEBUG_INPUT		     
		 fprintf(stdout, "Rules will be Un-Ordered\n");
#endif
	    }
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 542 "ingest.y"
    { add_rule(); }
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 544 "ingest.y"
    {
#ifdef DEBUG_INPUT		     
	     fprintf(stdout, "If ");
#endif
	    }
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 551 "ingest.y"
    {
#ifdef DEBUG_INPUT		     
	     fprintf(stdout, "Then ");
#endif
	    }
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 561 "ingest.y"
    {  }
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 566 "ingest.y"
    {
#ifdef DEBUG_INPUT		     
	     fprintf(stdout, "Default Rule:\n");
#endif
	    }
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 572 "ingest.y"
    { add_rule(); }
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 584 "ingest.y"
    {
		if (((current_attr ->atype) == DISCRETE_TYPE)
		     && value_id(intern((yyvsp[(3) - (3)].sval)), att_num, &att_val)){
#ifdef DEBUG_INPUT		     
		     fprintf(stdout, "= %s\n ", (yyvsp[(3) - (3)].sval));
#endif
		     if (! (current_rule -> selector)[att_num].discriminant)
		       (current_rule -> selector)[att_num].discriminant =
			 new_discriminant(nth_attribute(att_num));
		
		     (current_rule -> selector)[att_num].discriminant->attval =
                      att_val;
		     (current_rule -> selector)[att_num].setp =
		       TOTAL_INSTANTIATION;
		}
		      else
			attr_error(ln, att_num,(yyvsp[(3) - (3)].sval));
          }
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 606 "ingest.y"
    {
                     if (! (current_rule -> selector)[att_num].discriminant)
		       (current_rule -> selector)[att_num].discriminant =
			 new_discriminant(nth_attribute(att_num));

		     (current_rule -> selector)[att_num].discriminant
		       ->bounds->instantiation = UPPER_BOUND;
		     (current_rule -> selector)[att_num].discriminant
		       ->bounds->upper = (yyvsp[(3) - (3)].fval);
		     (current_rule -> selector)[att_num].setp = INSTANTIATION;
#ifdef DEBUG_INPUT		     
		     fprintf(stdout, "< %.2f\n ", (yyvsp[(3) - (3)].fval));
#endif
                 }
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 623 "ingest.y"
    {
		     if (! (current_rule -> selector)[att_num].discriminant)
		       (current_rule -> selector)[att_num].discriminant =
			 new_discriminant(nth_attribute(att_num));
		      
		     (current_rule -> selector)[att_num].discriminant
		       ->bounds->instantiation = LOWER_BOUND;
		     (current_rule -> selector)[att_num].discriminant
		       ->bounds->lower = (yyvsp[(3) - (3)].fval);
		     (current_rule -> selector)[att_num].setp = INSTANTIATION;
#ifdef DEBUG_INPUT		     
		     fprintf(stdout, "> %.2f\n ", (yyvsp[(3) - (3)].fval));
#endif
                 }
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 641 "ingest.y"
    {
		     if (! (current_rule -> selector)[att_num].discriminant)
		       (current_rule -> selector)[att_num].discriminant =
			 new_discriminant(nth_attribute(att_num));
			
		     (current_rule -> selector)[att_num].discriminant
		       ->bounds->instantiation = DOUBLE_BOUND;
		     (current_rule -> selector)[att_num].discriminant
		       ->bounds->upper = (yyvsp[(5) - (5)].fval);
		     (current_rule -> selector)[att_num].discriminant
		       ->bounds->lower = (yyvsp[(1) - (5)].fval);		     
		     (current_rule -> selector)[att_num].setp =
		       TOTAL_INSTANTIATION;
#ifdef DEBUG_INPUT		     
		     fprintf(stdout, "between %.2f and %.2f\n", (yyvsp[(1) - (5)].fval), (yyvsp[(5) - (5)].fval));
#endif
                 }
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 663 "ingest.y"
    {  if (current_attr = string_to_attribute((yyvsp[(1) - (1)].sval))){
	     att_num = ATT_NO(current_attr);
#ifdef DEBUG_INPUT		     
	     fprintf(stdout, "%s ", (yyvsp[(1) - (1)].sval));
#endif	     
        }
     else
       YYERROR;
       }
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 675 "ingest.y"
    {
	     errflag |= ! value_id(string_to_atom((yyvsp[(3) - (3)].sval)),
				   ATT_NO(IDclass),
				   &(current_rule->class));
#ifdef DEBUG_INPUT		     
	     fprintf(stdout, "%s = %s\n ", (yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].sval));
#endif	     	     
	}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 686 "ingest.y"
    {
	     errflag |= ! value_id(string_to_atom((yyvsp[(3) - (3)].sval)),
				   ATT_NO(IDclass),
				   &(current_rule->class));
#ifdef DEBUG_INPUT		     
	     fprintf(stdout, "%s = %s\n ", (yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].sval));
#endif
	     current_rule->distribution = (double *) ALLOC(number_of_classes *
					  sizeof(double));
        }
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 699 "ingest.y"
    {
#ifdef DEBUG_INPUT
                fprintf(stdout, "Found a count_array!\n");
		fflush(stdout);		
#endif       
                count_index = 0;
	      }
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 715 "ingest.y"
    { current_rule->distribution[count_index++] = (double) (yyvsp[(1) - (1)].ival);
#ifdef DEBUG_INPUT
                fprintf(stdout, "INTEGER ");
                fprintf(stdout, "Index %d, Count %f\n",
			count_index-1,
			current_rule->distribution[count_index-1]);
		fflush(stdout);	       
#endif
             }
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 728 "ingest.y"
    { current_rule->distribution[count_index++] = (double) (yyvsp[(1) - (1)].fval);
#ifdef DEBUG_INPUT
                fprintf(stdout, "FLOAT %.2f  ", (yyvsp[(1) - (1)].fval));	       
                fprintf(stdout, "Index %d, Count %f\n",
			count_index-1,
			current_rule->distribution[count_index-1]);
		fflush(stdout);	       
#endif
	     }
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 755 "ingest.y"
    { rule_par_sread((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].sval));}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 760 "ingest.y"
    { rule_par_fread((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].fval));}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 765 "ingest.y"
    { rule_par_nread((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].ival));}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 785 "ingest.y"
    { input_type_error(ERROR);
	   YYERROR;}
    break;



/* Line 1455 of yacc.c  */
#line 2479 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



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
		      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 789 "ingest.y"


#include "lex.yy.c"
yywrap()
{
     return(1);
}


void attr_error(ln, att_num, entry)
long ln;
int att_num;
char *entry;
{    errflag = TRUE;
     fprintf(stdout, "ERROR: Inappropriate value for attribute ");
     fprintf(stdout, "%d\n", att_num);
     fprintf(stdout, " ->  %s\n", entry);          
     fprintf(stdout, "Line number: %ld\n", ln);
}

void dc_error(ln)
long ln;
{    errflag = TRUE;
     fprintf(stdout, "\nERROR: \"Don't Care\" is not a  permitted ");
     fprintf(stdout, "class value!\n");
     fprintf(stdout, "Line number: %ld\n", ln);
}

void uk_error(ln)
long ln;
{    errflag = TRUE;
     fprintf(stdout, "\nERROR: \"Unknown\" is not a permitted ");
     fprintf(stdout, "class value!\n");
     fprintf(stdout, "Line number: %ld\n", ln);
}


     
attr_num_error(ln, att_num, number_of_attributes)
long ln;
int att_num, number_of_attributes;
{
     errflag = TRUE;
     fprintf(stdout, "ERROR: Wrong number of attributes\n");
     fprintf(stdout, "Line number: %ld\n", ln);
     fprintf(stdout, "\tAttributes expected (including class): %d\n", number_of_attributes);
     fprintf(stdout, "\tAttributes found:                      %d\n", att_num+1);
}

     




/* Make into a #define
void print_att_value(stream, attno, value)
FILE *stream;
Attval value;
SHORT attno;
{
	switch (attribute[attno]->type)
	{
	case name:
		if (value.ivalue == UK_INT)
			fprintf(stream, "? ");
		else
			fprintf(stream, "%s ", id_value(value.ivalue, attno)->name);
		break;
	case ivalue:
		if (value.ivalue == UK_INT)
			fprintf(stream, "? ");
		else
			fprintf(stream, "%d ", value.ivalue);
		break;
	case fvalue:
		if (value.fvalue == UK_FLOAT)
			fprintf(stream, "? ");
		else
			fprintf(stream, "%5.1f ", value.fvalue);
		break;
	}
}
                                                                    */
input_type_error(type_found)
InputType type_found;
{
     fprintf(stdout,  "ERROR: wrong type of file\n");
     fprintf(stdout, "   Type expected: ");
     print_input_type(stdout, input_type);
     fprintf(stdout, "   Type found: ");
     print_input_type(stdout, type_found);
}


 
num_class_error()
{
     fprintf(stdout,
	     "ERROR: CN2 doesn't handle numeric classes.\n");
     fprintf(stdout,
	     "You must either discretise the class attribute, \n");
     fprintf(stdout,
	     "or use NewId instead.\n\n");
     errflag = TRUE;
}



