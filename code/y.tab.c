
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
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 2 "cc.y"

#include <cstdlib>
#include <cstdio>
#include <string>

#include "grammarTree.h"

using namespace std;

extern char *yytext;
extern int yycolumn;
extern FILE *yyin;
extern FILE *yyout;
grammarTree *root;
extern int yylineno;

int yylex(void);
void yyerror(const char *);


/* Line 189 of yacc.c  */
#line 94 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
     ERROR = 258,
     NUMBER = 259,
     CONST = 260,
     IDENT = 261,
     INT = 262,
     VOID = 263,
     IF = 264,
     ELSE = 265,
     WHILE = 266,
     BREAK = 267,
     CONTINUE = 268,
     RETURN = 269,
     LE_OP = 270,
     GE_OP = 271,
     EQ_OP = 272,
     NE_OP = 273,
     AND_OP = 274,
     OR_OP = 275
   };
#endif
/* Tokens.  */
#define ERROR 258
#define NUMBER 259
#define CONST 260
#define IDENT 261
#define INT 262
#define VOID 263
#define IF 264
#define ELSE 265
#define WHILE 266
#define BREAK 267
#define CONTINUE 268
#define RETURN 269
#define LE_OP 270
#define GE_OP 271
#define EQ_OP 272
#define NE_OP 273
#define AND_OP 274
#define OR_OP 275




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 22 "cc.y"

    struct grammarTree* tree;
    char type_str[32]; 



/* Line 214 of yacc.c  */
#line 177 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 202 "y.tab.c"

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
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   205

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNRULES -- Number of states.  */
#define YYNSTATES  163

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   275

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    22,     2,     2,     2,    19,     2,     2,
      34,    35,    17,    15,    31,    16,     2,    18,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    30,
      20,    23,    21,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    32,     2,    33,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,    37,     2,     2,     2,     2,
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
      24,    25,    26,    27,    28,    29
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,    11,    13,    15,    17,    23,
      27,    28,    30,    34,    41,    43,    46,    51,    55,    56,
      61,    65,    66,    68,    73,    77,    84,    86,    89,    94,
      98,    99,   105,   112,   115,   119,   120,   123,   128,   132,
     135,   136,   138,   140,   145,   148,   150,   152,   158,   166,
     172,   175,   178,   181,   185,   187,   189,   191,   196,   200,
     202,   204,   206,   210,   215,   218,   220,   222,   224,   227,
     231,   232,   234,   238,   242,   244,   248,   252,   256,   258,
     262,   266,   270,   274,   276,   280,   284,   286,   290,   292,
     296
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    39,    40,    -1,    40,    -1,    39,    52,
      -1,    52,    -1,    41,    -1,    47,    -1,     5,    43,    44,
      42,    30,    -1,    42,    31,    44,    -1,    -1,     7,    -1,
       6,    23,    45,    -1,     6,    32,    74,    33,    23,    45,
      -1,    74,    -1,    36,    37,    -1,    36,    74,    46,    37,
      -1,    46,    31,    74,    -1,    -1,    43,    49,    48,    30,
      -1,    48,    31,    49,    -1,    -1,     6,    -1,     6,    32,
      74,    33,    -1,     6,    23,    50,    -1,     6,    32,    74,
      33,    23,    50,    -1,    60,    -1,    36,    37,    -1,    36,
      60,    51,    37,    -1,    51,    31,    60,    -1,    -1,    43,
       6,    34,    35,    56,    -1,    43,     6,    34,    53,    35,
      56,    -1,    55,    54,    -1,    54,    31,    55,    -1,    -1,
      43,     6,    -1,    43,     6,    32,    33,    -1,    36,    57,
      37,    -1,    57,    58,    -1,    -1,    40,    -1,    59,    -1,
      62,    23,    60,    30,    -1,    60,    30,    -1,    30,    -1,
      56,    -1,     9,    34,    61,    35,    59,    -1,     9,    34,
      61,    35,    59,    10,    59,    -1,    11,    34,    61,    35,
      59,    -1,    12,    30,    -1,    13,    30,    -1,    14,    30,
      -1,    14,    60,    30,    -1,    68,    -1,    73,    -1,     6,
      -1,     6,    32,    60,    33,    -1,    34,    60,    35,    -1,
      62,    -1,     4,    -1,    63,    -1,     6,    34,    35,    -1,
       6,    34,    66,    35,    -1,    65,    64,    -1,    15,    -1,
      16,    -1,    22,    -1,    60,    67,    -1,    67,    31,    60,
      -1,    -1,    69,    -1,    68,    15,    69,    -1,    68,    16,
      69,    -1,    64,    -1,    69,    17,    64,    -1,    69,    18,
      64,    -1,    69,    19,    64,    -1,    68,    -1,    70,    20,
      68,    -1,    70,    21,    68,    -1,    70,    24,    68,    -1,
      70,    25,    68,    -1,    70,    -1,    71,    26,    70,    -1,
      71,    27,    70,    -1,    71,    -1,    72,    28,    71,    -1,
      72,    -1,    73,    29,    72,    -1,    68,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    50,    50,    51,    52,    53,    58,    59,    64,    68,
      69,    74,    79,    80,    85,    86,    87,    90,    91,    96,
     100,   101,   106,   107,   108,   109,   114,   115,   116,   120,
     121,   126,   127,   132,   136,   137,   142,   143,   148,   152,
     153,   158,   159,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   179,   184,   189,   190,   195,   196,
     197,   202,   203,   204,   205,   210,   211,   212,   217,   220,
     221,   226,   227,   228,   233,   234,   235,   236,   241,   242,
     243,   244,   245,   250,   251,   252,   257,   258,   263,   264,
     269
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ERROR", "NUMBER", "CONST", "IDENT",
  "INT", "VOID", "IF", "ELSE", "WHILE", "BREAK", "CONTINUE", "RETURN",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'<'", "'>'", "'!'", "'='", "LE_OP",
  "GE_OP", "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "';'", "','", "'['", "']'",
  "'('", "')'", "'{'", "'}'", "$accept", "CompUnit", "Decl", "ConstDecl",
  "TempA", "BType", "ConstDef", "ConstInitVal", "TempB", "VarDecl",
  "TempC", "VarDef", "InitVal", "TempD", "FuncDef", "FuncFParams", "TempE",
  "FuncFParam", "Block", "TempF", "BlockItem", "Stmt", "Exp", "Cond",
  "LVal", "PrimaryExp", "UnaryExp", "UnaryOp", "FuncRParams", "TempG",
  "AddExp", "MulExp", "RelExp", "EqExp", "LAndExp", "LOrExp", "ConstExp", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,    43,    45,    42,    47,    37,
      60,    62,    33,    61,   270,   271,   272,   273,   274,   275,
      59,    44,    91,    93,    40,    41,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    39,    39,    39,    40,    40,    41,    42,
      42,    43,    44,    44,    45,    45,    45,    46,    46,    47,
      48,    48,    49,    49,    49,    49,    50,    50,    50,    51,
      51,    52,    52,    53,    54,    54,    55,    55,    56,    57,
      57,    58,    58,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    60,    61,    62,    62,    63,    63,
      63,    64,    64,    64,    64,    65,    65,    65,    66,    67,
      67,    68,    68,    68,    69,    69,    69,    69,    70,    70,
      70,    70,    70,    71,    71,    71,    72,    72,    73,    73,
      74
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     2,     1,     1,     1,     5,     3,
       0,     1,     3,     6,     1,     2,     4,     3,     0,     4,
       3,     0,     1,     4,     3,     6,     1,     2,     4,     3,
       0,     5,     6,     2,     3,     0,     2,     4,     3,     2,
       0,     1,     1,     4,     2,     1,     1,     5,     7,     5,
       2,     2,     2,     3,     1,     1,     1,     4,     3,     1,
       1,     1,     3,     4,     2,     1,     1,     1,     2,     3,
       0,     1,     3,     3,     1,     3,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     1,     3,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    11,     0,     3,     6,     0,     7,     5,     0,
       1,     2,     4,    22,    21,     0,    10,     0,     0,     0,
       0,     0,     0,     0,    60,    56,    65,    66,    67,     0,
       0,    24,    26,    59,    61,    74,     0,    54,    71,    90,
       0,     0,     0,     0,    35,    19,     0,     0,    12,    14,
       0,     8,     0,     0,     0,     0,    27,    30,    64,     0,
       0,     0,     0,     0,    23,    40,    31,    36,     0,    33,
      22,    20,    15,    18,     0,     9,     0,    62,    70,     0,
      58,     0,    72,    73,    75,    76,    77,     0,     0,     0,
      32,     0,     0,     0,    57,    68,    63,     0,    28,    25,
       0,     0,     0,     0,     0,    45,    38,    41,     0,    46,
      39,    42,     0,    59,    37,    34,     0,    16,    13,     0,
      29,     0,     0,    50,    51,    52,     0,    44,     0,    17,
      69,     0,    78,    83,    86,    88,    55,     0,    53,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      43,    47,    79,    80,    81,    82,    84,    85,    87,    89,
      49,     0,    48
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,    23,     6,    16,    48,    92,     7,
      20,    14,    31,    81,     8,    43,    69,    44,   109,    88,
     110,   111,   112,   131,    33,    34,    35,    36,    79,    95,
      37,    38,   133,   134,   135,   136,    49
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -82
static const yytype_int16 yypact[] =
{
      72,    24,   -82,   106,   -82,   -82,    35,   -82,   -82,    65,
     -82,   -82,   -82,     5,   -82,     4,   -82,    18,   171,     3,
      15,   131,   171,    79,   -82,    19,   -82,   -82,   -82,   171,
      10,   -82,   -82,   -82,   -82,   -82,   171,    -3,    97,    -3,
      58,    59,   101,    77,   -82,   -82,   116,    68,   -82,   -82,
      99,   -82,    65,   171,   144,   117,   -82,   -82,   -82,   171,
     171,   171,   171,   171,   111,   -82,   -82,   119,    59,   123,
      46,   -82,   -82,   -82,   132,   -82,   125,   -82,   -82,   121,
     -82,   -20,    97,    97,   -82,   -82,   -82,    18,    51,   135,
     -82,    24,   -16,   131,   -82,   138,   -82,   171,   -82,   -82,
     136,   137,   142,   146,   158,   -82,   -82,   -82,   116,   -82,
     -82,   -82,   151,   159,   -82,   -82,   171,   -82,   -82,   171,
     -82,   171,   171,   -82,   -82,   -82,   153,   -82,   171,   -82,
     -82,   149,    -3,    76,    92,   157,   160,   155,   -82,   161,
     127,   171,   171,   171,   171,   171,   171,   171,   171,   127,
     -82,   184,    -3,    -3,    -3,    -3,    76,    76,    92,   157,
     -82,   127,   -82
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -82,   -82,     6,   -82,   -82,     1,   143,   103,   -82,   -82,
     -82,   152,   110,   -82,   196,   -82,   -82,   109,   -33,   -82,
     -82,   -79,   -11,    80,   -81,   -82,   -13,   -82,   -82,   -82,
     -18,    61,    -1,    54,    55,   -82,   -17
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      39,    40,     9,    39,    39,    50,    32,   113,    66,    11,
       2,    97,    59,    60,    24,   116,    25,    98,    55,    57,
      42,   117,    24,    58,    25,    26,    27,    21,    17,    39,
      73,     2,    28,    26,    27,    90,    22,    18,    41,    19,
      28,    13,    76,    78,    29,    45,    46,    56,    84,    85,
      86,    53,    29,    54,    30,    24,     1,    25,     2,   113,
     100,   151,   101,   102,   103,   104,    26,    27,   113,    17,
     160,    15,    24,    28,    25,    39,    32,     1,    18,     2,
     113,   105,   162,    26,    27,    29,   120,    65,   106,   108,
      28,    64,    42,   126,   107,    65,   141,   142,    39,   129,
     143,   144,    29,   132,   132,    72,    10,    67,   130,    51,
      52,     1,    68,     2,    61,    62,    63,   139,   145,   146,
      82,    83,    70,   152,   153,   154,   155,   132,   132,   132,
     132,    24,    74,    25,    87,    24,   100,    25,   101,   102,
     103,   104,    26,    27,   156,   157,    26,    27,    24,    28,
      25,    89,    80,    28,    91,    93,    96,   105,    94,    26,
      27,    29,    24,    65,    25,    29,    28,    47,   114,   119,
     121,   122,   123,    26,    27,    24,   124,    25,    29,    77,
      28,   127,   128,   138,   140,   147,    26,    27,   125,   148,
     149,   150,    29,    28,   161,    75,   118,    99,    71,    12,
     115,   158,   137,   159,     0,    29
};

static const yytype_int16 yycheck[] =
{
      18,    18,     1,    21,    22,    22,    17,    88,    41,     3,
       7,    31,    15,    16,     4,    31,     6,    37,    29,    30,
      19,    37,     4,    36,     6,    15,    16,    23,    23,    47,
      47,     7,    22,    15,    16,    68,    32,    32,    35,    34,
      22,     6,    53,    54,    34,    30,    31,    37,    61,    62,
      63,    32,    34,    34,    36,     4,     5,     6,     7,   140,
       9,   140,    11,    12,    13,    14,    15,    16,   149,    23,
     149,     6,     4,    22,     6,    93,    87,     5,    32,     7,
     161,    30,   161,    15,    16,    34,    97,    36,    37,    88,
      22,    33,    91,   104,    88,    36,    20,    21,   116,   116,
      24,    25,    34,   121,   122,    37,     0,     6,   119,    30,
      31,     5,    35,     7,    17,    18,    19,   128,    26,    27,
      59,    60,     6,   141,   142,   143,   144,   145,   146,   147,
     148,     4,    33,     6,    23,     4,     9,     6,    11,    12,
      13,    14,    15,    16,   145,   146,    15,    16,     4,    22,
       6,    32,    35,    22,    31,    23,    35,    30,    33,    15,
      16,    34,     4,    36,     6,    34,    22,    36,    33,    31,
      34,    34,    30,    15,    16,     4,    30,     6,    34,    35,
      22,    30,    23,    30,    35,    28,    15,    16,    30,    29,
      35,    30,    34,    22,    10,    52,    93,    87,    46,     3,
      91,   147,   122,   148,    -1,    34
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     7,    39,    40,    41,    43,    47,    52,    43,
       0,    40,    52,     6,    49,     6,    44,    23,    32,    34,
      48,    23,    32,    42,     4,     6,    15,    16,    22,    34,
      36,    50,    60,    62,    63,    64,    65,    68,    69,    68,
      74,    35,    43,    53,    55,    30,    31,    36,    45,    74,
      74,    30,    31,    32,    34,    60,    37,    60,    64,    15,
      16,    17,    18,    19,    33,    36,    56,     6,    35,    54,
       6,    49,    37,    74,    33,    44,    60,    35,    60,    66,
      35,    51,    69,    69,    64,    64,    64,    23,    57,    32,
      56,    31,    46,    23,    33,    67,    35,    31,    37,    50,
       9,    11,    12,    13,    14,    30,    37,    40,    43,    56,
      58,    59,    60,    62,    33,    55,    31,    37,    45,    31,
      60,    34,    34,    30,    30,    30,    60,    30,    23,    74,
      60,    61,    68,    70,    71,    72,    73,    61,    30,    60,
      35,    20,    21,    24,    25,    26,    27,    28,    29,    35,
      30,    59,    68,    68,    68,    68,    70,    70,    71,    72,
      59,    10,    59
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
		  Type, Value, Location); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
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
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

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

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

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
       `yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
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
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

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
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
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
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 50 "cc.y"
    {root = createTree("CompUnit", 1, (yyvsp[(1) - (2)].tree));}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 51 "cc.y"
    {root = createTree("CompUnit", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 52 "cc.y"
    {root = createTree("CompUnit", 2, (yyvsp[(1) - (2)].tree), (yyvsp[(2) - (2)].tree));}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 53 "cc.y"
    {root = createTree("CompUnit", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 58 "cc.y"
    {(yyval.tree) = createTree("Decl", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 59 "cc.y"
    {(yyval.tree) = createTree("Decl", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 64 "cc.y"
    {(yyval.tree) = createTree("ConstDecl", 5, (yyvsp[(1) - (5)].tree), (yyvsp[(2) - (5)].tree), (yyvsp[(3) - (5)].tree), (yyvsp[(4) - (5)].tree), (yyvsp[(5) - (5)].tree));}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 68 "cc.y"
    {(yyval.tree) = createTree("TempA", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 69 "cc.y"
    {}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 74 "cc.y"
    {(yyval.tree) = createTree("BType", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 79 "cc.y"
    {(yyval.tree) = createTree("ConstDef", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 80 "cc.y"
    {(yyval.tree) = createTree("ConstDef", 6, (yyvsp[(1) - (6)].tree), (yyvsp[(2) - (6)].tree), (yyvsp[(3) - (6)].tree), (yyvsp[(4) - (6)].tree), (yyvsp[(5) - (6)].tree), (yyvsp[(6) - (6)].tree));}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 85 "cc.y"
    {(yyval.tree) = createTree("ConstInitVal", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 86 "cc.y"
    {(yyval.tree) = createTree("ConstInitVal", 2, (yyvsp[(1) - (2)].tree), (yyvsp[(2) - (2)].tree));}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 87 "cc.y"
    {(yyval.tree) = createTree("ConstInitVal", 4, (yyvsp[(1) - (4)].tree), (yyvsp[(2) - (4)].tree), (yyvsp[(3) - (4)].tree), (yyvsp[(4) - (4)].tree));}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 90 "cc.y"
    {(yyval.tree) = createTree("TempB", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 91 "cc.y"
    {}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 96 "cc.y"
    {(yyval.tree) = createTree("VarDecl", 4, (yyvsp[(1) - (4)].tree), (yyvsp[(2) - (4)].tree), (yyvsp[(3) - (4)].tree), (yyvsp[(4) - (4)].tree));}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 100 "cc.y"
    {(yyval.tree) = createTree("Tempc", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 101 "cc.y"
    {}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 106 "cc.y"
    {(yyval.tree) = createTree("VarDef", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 107 "cc.y"
    {(yyval.tree) = createTree("VarDef", 4, (yyvsp[(1) - (4)].tree), (yyvsp[(2) - (4)].tree), (yyvsp[(3) - (4)].tree), (yyvsp[(4) - (4)].tree));}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 108 "cc.y"
    {(yyval.tree) = createTree("VarDef", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 109 "cc.y"
    {(yyval.tree) = createTree("VarDef", 6, (yyvsp[(1) - (6)].tree), (yyvsp[(2) - (6)].tree), (yyvsp[(3) - (6)].tree), (yyvsp[(4) - (6)].tree), (yyvsp[(5) - (6)].tree), (yyvsp[(6) - (6)].tree));}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 114 "cc.y"
    {(yyval.tree) = createTree("InitVal", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 115 "cc.y"
    {(yyval.tree) = createTree("InitVal", 2, (yyvsp[(1) - (2)].tree), (yyvsp[(2) - (2)].tree));}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 116 "cc.y"
    {(yyval.tree) = createTree("InitVal", 4, (yyvsp[(1) - (4)].tree), (yyvsp[(2) - (4)].tree), (yyvsp[(3) - (4)].tree), (yyvsp[(4) - (4)].tree));}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 120 "cc.y"
    {(yyval.tree) = createTree("TempD", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 121 "cc.y"
    {}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 126 "cc.y"
    {(yyval.tree) = createTree("FuncDef", 5, (yyvsp[(1) - (5)].tree), (yyvsp[(2) - (5)].tree), (yyvsp[(3) - (5)].tree), (yyvsp[(4) - (5)].tree), (yyvsp[(5) - (5)].tree));}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 127 "cc.y"
    {(yyval.tree) = createTree("FuncDef", 6, (yyvsp[(1) - (6)].tree), (yyvsp[(2) - (6)].tree), (yyvsp[(3) - (6)].tree), (yyvsp[(4) - (6)].tree), (yyvsp[(5) - (6)].tree), (yyvsp[(6) - (6)].tree));}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 132 "cc.y"
    {(yyval.tree) = createTree("FuncFparams", 2, (yyvsp[(1) - (2)].tree), (yyvsp[(2) - (2)].tree));}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 136 "cc.y"
    {(yyval.tree) = createTree("TempE", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 137 "cc.y"
    {}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 142 "cc.y"
    {(yyval.tree) = createTree("FuncFparam", 2, (yyvsp[(1) - (2)].tree), (yyvsp[(2) - (2)].tree));}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 143 "cc.y"
    {(yyval.tree) = createTree("FuncFparam", 4, (yyvsp[(1) - (4)].tree), (yyvsp[(2) - (4)].tree), (yyvsp[(3) - (4)].tree), (yyvsp[(4) - (4)].tree));}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 148 "cc.y"
    {(yyval.tree) = createTree("block", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 152 "cc.y"
    {(yyval.tree) = createTree("TempF", 2, (yyvsp[(1) - (2)].tree), (yyvsp[(2) - (2)].tree));}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 153 "cc.y"
    {}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 158 "cc.y"
    {(yyval.tree) = createTree("BlockItem", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 159 "cc.y"
    {(yyval.tree) = createTree("BlockItem", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 164 "cc.y"
    {(yyval.tree) = createTree("Stmt", 4, (yyvsp[(1) - (4)].tree), (yyvsp[(2) - (4)].tree), (yyvsp[(3) - (4)].tree), (yyvsp[(4) - (4)].tree));}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 165 "cc.y"
    {(yyval.tree) = createTree("Stmt", 2, (yyvsp[(1) - (2)].tree), (yyvsp[(2) - (2)].tree));}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 166 "cc.y"
    {(yyval.tree) = createTree("Stmt", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 167 "cc.y"
    {(yyval.tree) = createTree("Stmt", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 168 "cc.y"
    {(yyval.tree) = createTree("Stmt", 5, (yyvsp[(1) - (5)].tree), (yyvsp[(2) - (5)].tree), (yyvsp[(3) - (5)].tree), (yyvsp[(4) - (5)].tree), (yyvsp[(5) - (5)].tree));}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 169 "cc.y"
    {(yyval.tree) = createTree("Stmt", 7, (yyvsp[(1) - (7)].tree), (yyvsp[(2) - (7)].tree), (yyvsp[(3) - (7)].tree), (yyvsp[(4) - (7)].tree), (yyvsp[(5) - (7)].tree), (yyvsp[(6) - (7)].tree), (yyvsp[(7) - (7)].tree));}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 170 "cc.y"
    {(yyval.tree) = createTree("Stmt", 5, (yyvsp[(1) - (5)].tree), (yyvsp[(2) - (5)].tree), (yyvsp[(3) - (5)].tree), (yyvsp[(4) - (5)].tree), (yyvsp[(5) - (5)].tree));}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 171 "cc.y"
    {(yyval.tree) = createTree("Stmt", 2, (yyvsp[(1) - (2)].tree), (yyvsp[(2) - (2)].tree));}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 172 "cc.y"
    {(yyval.tree) = createTree("Stmt", 2, (yyvsp[(1) - (2)].tree), (yyvsp[(2) - (2)].tree));}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 173 "cc.y"
    {(yyval.tree) = createTree("Stmt", 2, (yyvsp[(1) - (2)].tree), (yyvsp[(2) - (2)].tree));}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 174 "cc.y"
    {(yyval.tree) = createTree("Stmt", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 179 "cc.y"
    {(yyval.tree) = createTree("Exp", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 184 "cc.y"
    {(yyval.tree) = createTree("Cond", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 189 "cc.y"
    {(yyval.tree) = createTree("LVal", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 190 "cc.y"
    {(yyval.tree) = createTree("LVal", 4, (yyvsp[(1) - (4)].tree), (yyvsp[(2) - (4)].tree), (yyvsp[(3) - (4)].tree), (yyvsp[(4) - (4)].tree));}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 195 "cc.y"
    {(yyval.tree) = createTree("PrimaryExp", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 196 "cc.y"
    {(yyval.tree) = createTree("PrimaryExp", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 197 "cc.y"
    {(yyval.tree) = createTree("PrimaryExp", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 202 "cc.y"
    {(yyval.tree) = createTree("UnaryExp", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 203 "cc.y"
    {(yyval.tree) = createTree("UnaryExp", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 204 "cc.y"
    {(yyval.tree) = createTree("UnaryExp", 4, (yyvsp[(1) - (4)].tree), (yyvsp[(2) - (4)].tree), (yyvsp[(3) - (4)].tree), (yyvsp[(4) - (4)].tree));}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 205 "cc.y"
    {(yyval.tree) = createTree("UnaryExp", 2, (yyvsp[(1) - (2)].tree), (yyvsp[(2) - (2)].tree));}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 210 "cc.y"
    {(yyval.tree) = createTree("UnaryOP", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 211 "cc.y"
    {(yyval.tree) = createTree("UnaryOP", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 212 "cc.y"
    {(yyval.tree) = createTree("UnaryOP", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 217 "cc.y"
    {(yyval.tree) = createTree("FuncFParams", 2, (yyvsp[(1) - (2)].tree), (yyvsp[(2) - (2)].tree));}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 220 "cc.y"
    {(yyval.tree) = createTree("TempG", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 221 "cc.y"
    {}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 226 "cc.y"
    {(yyval.tree) = createTree("AddExp", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 227 "cc.y"
    {(yyval.tree) = createTree("AddExp", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 228 "cc.y"
    {(yyval.tree) = createTree("AddExp", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 233 "cc.y"
    {(yyval.tree) = createTree("MulExp", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 234 "cc.y"
    {(yyval.tree) = createTree("MulExp", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 235 "cc.y"
    {(yyval.tree) = createTree("MulExp", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 236 "cc.y"
    {(yyval.tree) = createTree("MulExp", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 241 "cc.y"
    {(yyval.tree) = createTree("RelExp", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 242 "cc.y"
    {(yyval.tree) = createTree("RelExp", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 243 "cc.y"
    {(yyval.tree) = createTree("RelExp", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 244 "cc.y"
    {(yyval.tree) = createTree("RelExp", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 245 "cc.y"
    {(yyval.tree) = createTree("RelExp", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 250 "cc.y"
    {(yyval.tree) = createTree("EqExp", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 251 "cc.y"
    {(yyval.tree) = createTree("EqExp", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 252 "cc.y"
    {(yyval.tree) = createTree("EqExp", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 257 "cc.y"
    {(yyval.tree) = createTree("LAndExp", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 258 "cc.y"
    {(yyval.tree) = createTree("LAndExp", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 263 "cc.y"
    {(yyval.tree) = createTree("LOrExp", 1, (yyvsp[(1) - (1)].tree));}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 264 "cc.y"
    {(yyval.tree) = createTree("LOrExp", 3, (yyvsp[(1) - (3)].tree), (yyvsp[(2) - (3)].tree), (yyvsp[(3) - (3)].tree));}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 269 "cc.y"
    {(yyval.tree) = createTree("ConstExp", 1, (yyvsp[(1) - (1)].tree));}
    break;



/* Line 1455 of yacc.c  */
#line 2211 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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

  yyerror_range[0] = yylloc;

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
		      yytoken, &yylval, &yylloc);
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

  yyerror_range[0] = yylsp[1-yylen];
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

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
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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
#line 271 "cc.y"


/* programs */
/* allows for printing of an error message */
void yyerror(char const *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", yycolumn, "^", yycolumn, s);
}

int main(int argc, char* argv[]) {
    /* Read test file from command line */
    bool verbose = false;
    string tmp = argv[1];
    if (tmp == "true"){
        verbose = true;
    }
    
    int start = 1;
    if (tmp != "true" || tmp != "false"){
        start = 2;
    }
    
    if (verbose){
        for (int i=1; i<argc; i++){
            cout << "Argument " << i << " is " << argv[i] << endl;
        }
    }

    for (int i=start; i<argc; i++){
        yyin = fopen(argv[i], "r");
        
        printf("The source code of %s is: \n", argv[i]);
        yyparse();

        if (verbose)
            outputTree(root, 0);
        floorPrint(root, verbose);
        Clean(root);

        fclose(yyin);
    }
    return 0;
}
