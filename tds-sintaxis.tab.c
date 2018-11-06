/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     ID = 259,
     INTEGER = 260,
     BEGINN = 261,
     END = 262,
     EXTERN = 263,
     IF = 264,
     THEN = 265,
     ELSE = 266,
     WHILE = 267,
     BOOL = 268,
     RETURN = 269,
     VOID = 270,
     PROGRAM = 271,
     FALSE = 272,
     TRUE = 273,
     ASIGNACION = 274,
     SUMA = 275,
     RESTA = 276,
     DIV = 277,
     PROD = 278,
     MOD = 279,
     IGUALDAD = 280,
     MENIGUAL = 281,
     MAYIGUAL = 282,
     MENOR = 283,
     MAYOR = 284,
     AND = 285,
     OR = 286,
     NOT = 287,
     MAIN = 288,
     PARA = 289,
     PARC = 290,
     PCOMA = 291,
     COMA = 292,
     NEG = 293
   };
#endif
/* Tokens.  */
#define INT 258
#define ID 259
#define INTEGER 260
#define BEGINN 261
#define END 262
#define EXTERN 263
#define IF 264
#define THEN 265
#define ELSE 266
#define WHILE 267
#define BOOL 268
#define RETURN 269
#define VOID 270
#define PROGRAM 271
#define FALSE 272
#define TRUE 273
#define ASIGNACION 274
#define SUMA 275
#define RESTA 276
#define DIV 277
#define PROD 278
#define MOD 279
#define IGUALDAD 280
#define MENIGUAL 281
#define MAYIGUAL 282
#define MENOR 283
#define MAYOR 284
#define AND 285
#define OR 286
#define NOT 287
#define MAIN 288
#define PARA 289
#define PARC 290
#define PCOMA 291
#define COMA 292
#define NEG 293




/* Copy the first part of user declarations.  */
#line 1 "tds-sintaxis.y"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cod_assembler.c"

extern int yylineno;



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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 12 "tds-sintaxis.y"
{ int i; char *s; struct strings *st; struct nodes *n; struct nodeParams *np; struct Formalparams *pl; struct actualParams *ap;struct stacks *stk;}
/* Line 193 of yacc.c.  */
#line 185 "tds-sintaxis.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 198 "tds-sintaxis.tab.c"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   257

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNRULES -- Number of states.  */
#define YYNSTATES  138

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

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
      35,    36,    37,    38
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,    10,    12,    17,    21,    24,    30,
      32,    36,    39,    43,    45,    48,    55,    62,    68,    74,
      77,    82,    84,    87,    88,    91,    94,    99,   103,   109,
     111,   114,   119,   122,   129,   138,   142,   146,   149,   151,
     153,   155,   157,   161,   166,   168,   172,   174,   176,   178,
     182,   186,   190,   194,   198,   202,   206,   210,   214,   218,
     222,   226,   229,   232,   236,   238,   240,   242,   244
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      40,     0,    -1,    -1,    41,    16,     6,    42,     7,    -1,
      43,    -1,    44,    36,    46,    43,    -1,    44,    36,    43,
      -1,    46,    43,    -1,    15,    33,    34,    35,    50,    -1,
      45,    -1,    44,    36,    45,    -1,    55,     4,    -1,    45,
      37,     4,    -1,    47,    -1,    46,    47,    -1,    55,     4,
      34,    48,    35,    49,    -1,    15,     4,    34,    48,    35,
      49,    -1,    55,     4,    34,    35,    49,    -1,    15,     4,
      34,    35,    49,    -1,    55,     4,    -1,    48,    37,    55,
       4,    -1,    50,    -1,     8,    36,    -1,    -1,    51,    52,
      -1,     6,     7,    -1,     6,    44,    36,     7,    -1,     6,
      53,     7,    -1,     6,    44,    36,    53,     7,    -1,    54,
      -1,    53,    54,    -1,     4,    19,    58,    36,    -1,    56,
      36,    -1,     9,    34,    58,    35,    10,    50,    -1,     9,
      34,    58,    35,    10,    50,    11,    50,    -1,    12,    58,
      50,    -1,    14,    58,    36,    -1,    14,    36,    -1,    36,
      -1,    50,    -1,     5,    -1,    13,    -1,     4,    34,    35,
      -1,     4,    34,    57,    35,    -1,    58,    -1,    57,    37,
      58,    -1,     4,    -1,    56,    -1,    59,    -1,    58,    20,
      58,    -1,    58,    21,    58,    -1,    58,    23,    58,    -1,
      58,    22,    58,    -1,    58,    24,    58,    -1,    58,    29,
      58,    -1,    58,    28,    58,    -1,    58,    25,    58,    -1,
      58,    26,    58,    -1,    58,    27,    58,    -1,    58,    30,
      58,    -1,    58,    31,    58,    -1,    21,    58,    -1,    32,
      58,    -1,    34,    58,    35,    -1,    60,    -1,    61,    -1,
       3,    -1,    18,    -1,    17,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    80,    80,    80,   115,   116,   117,   118,   121,   123,
     124,   128,   130,   133,   134,   137,   139,   141,   143,   146,
     150,   155,   156,   159,   159,   164,   165,   166,   167,   170,
     171,   174,   177,   179,   181,   183,   185,   187,   189,   191,
     195,   196,   200,   209,   219,   220,   223,   225,   227,   229,
     231,   233,   235,   237,   239,   241,   243,   245,   247,   249,
     251,   253,   255,   257,   260,   262,   265,   269,   270
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "ID", "INTEGER", "BEGINN", "END",
  "EXTERN", "IF", "THEN", "ELSE", "WHILE", "BOOL", "RETURN", "VOID",
  "PROGRAM", "FALSE", "TRUE", "ASIGNACION", "SUMA", "RESTA", "DIV", "PROD",
  "MOD", "IGUALDAD", "MENIGUAL", "MAYIGUAL", "MENOR", "MAYOR", "AND", "OR",
  "NOT", "MAIN", "PARA", "PARC", "PCOMA", "COMA", "NEG", "$accept", "prog",
  "@1", "program_block", "main", "dec_vars", "dec_var", "dec_methods",
  "dec_method", "param_list", "block_type", "block", "@2", "block_def",
  "statements", "statement", "type", "method_call", "expr_list", "expr",
  "literal", "integer", "bool", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    41,    40,    42,    42,    42,    42,    43,    44,
      44,    45,    45,    46,    46,    47,    47,    47,    47,    48,
      48,    49,    49,    51,    50,    52,    52,    52,    52,    53,
      53,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      55,    55,    56,    56,    57,    57,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    59,    59,    60,    61,    61
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     5,     1,     4,     3,     2,     5,     1,
       3,     2,     3,     1,     2,     6,     6,     5,     5,     2,
       4,     1,     2,     0,     2,     2,     4,     3,     5,     1,
       2,     4,     2,     6,     8,     3,     3,     2,     1,     1,
       1,     1,     3,     4,     1,     3,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     3,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,    40,    41,     0,     0,
       4,     0,     9,     0,    13,     0,     0,     0,     3,     0,
       0,     7,    14,     0,    11,     0,     0,     6,    10,     0,
      12,     0,     0,    23,     0,     0,    23,     5,    23,     0,
       0,    18,    21,     0,    23,     0,    19,     8,    17,    23,
      22,    23,    24,    16,     0,    15,     0,    25,     0,     0,
       0,    38,     0,    39,    23,    29,     0,     0,    20,     0,
       0,     0,    66,    46,    68,    67,     0,     0,     0,    47,
      23,    48,    64,    65,    37,     0,    23,    27,    30,    11,
      32,     0,    42,     0,    44,     0,    61,    62,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    35,    36,    26,    23,    31,    43,     0,     0,    63,
      49,    50,    52,    51,    53,    56,    57,    58,    55,    54,
      59,    60,    28,    45,    23,    33,    23,    34
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     9,    10,    11,    12,    13,    14,    34,
      41,    42,    43,    52,    64,    65,    15,    79,    93,    80,
      81,    82,    83
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -49
static const yytype_int16 yypact[] =
{
     -49,     8,    27,   -49,    43,    14,   -49,   -49,     2,    61,
     -49,    34,    36,    14,   -49,    75,    47,    49,   -49,    14,
      80,   -49,   -49,    82,    54,    -1,    56,   -49,    36,    14,
     -49,    54,     5,    84,   -28,    90,   -49,   -49,    84,    11,
      59,   -49,   -49,    91,    84,    32,   -49,   -49,   -49,    84,
     -49,    98,   -49,   -49,    92,   -49,    17,   -49,    65,   133,
      72,   -49,    81,   -49,    73,   -49,    97,    83,   -49,   133,
     110,   133,   -49,    87,   -49,   -49,   133,   133,   133,   -49,
     214,   -49,   -49,   -49,   -49,   148,   111,   -49,   -49,   -49,
     -49,   165,   -49,    30,   214,   182,   -49,   -49,   198,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   -49,   -49,   -49,   126,   -49,   -49,   133,   112,   -49,
     -49,   -49,   -49,   -49,   -49,   226,   226,   226,   226,   226,
     -49,   -49,   -49,   214,   -49,   115,   -49,   -49
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -49,   -49,   -49,   -49,    -8,    78,   -17,   113,    13,   107,
       3,   -36,   -49,   -49,    55,   -42,   -12,   -48,   -49,   -46,
     -49,   -49,   -49
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int16 yytable[] =
{
      47,    23,    28,    67,     6,    21,    16,    44,     3,    45,
       6,    27,     7,    35,    85,    63,    67,    23,     7,     6,
      35,    37,    88,    91,    94,    95,    22,     7,    63,     8,
      96,    97,    98,    54,    33,    17,    69,     6,    67,    66,
      38,    48,    22,     4,   111,     7,    49,    53,    45,     5,
      63,    70,    55,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   116,    67,   117,    18,    28,
      19,   133,    88,    20,    66,    72,    73,    56,    63,    24,
      87,    25,    58,    26,    30,    59,    31,    60,    32,    74,
      75,    36,    40,    76,    46,    50,    68,    51,   135,    71,
     137,    89,    56,     6,    77,    57,    78,    58,    84,    61,
      59,     7,    60,    72,    73,    56,     6,    86,   113,    90,
      58,    70,   134,    59,     7,    60,   136,    74,    75,    62,
      56,    76,    29,   132,    61,    58,    72,    73,    59,    39,
      60,   114,    77,     0,    78,    92,     0,    61,     0,     0,
      74,    75,     0,     0,    76,     0,     0,     0,     0,     0,
       0,     0,    61,     0,     0,    77,     0,    78,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
       0,     0,     0,     0,   112,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,     0,     0,     0,
       0,   115,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,     0,     0,     0,   118,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
       0,     0,     0,   119,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,    99,   100,   101,   102,
     103,    -1,    -1,    -1,    -1,    -1,   109,   110
};

static const yytype_int16 yycheck[] =
{
      36,    13,    19,    51,     5,    13,     4,    35,     0,    37,
       5,    19,    13,    25,    60,    51,    64,    29,    13,     5,
      32,    29,    64,    69,    70,    71,    13,    13,    64,    15,
      76,    77,    78,    45,    35,    33,    19,     5,    86,    51,
      35,    38,    29,    16,    80,    13,    35,    44,    37,     6,
      86,    34,    49,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,    35,   114,    37,     7,    86,
      36,   117,   114,    37,    86,     3,     4,     4,   114,     4,
       7,    34,     9,    34,     4,    12,     4,    14,    34,    17,
      18,    35,     8,    21,     4,    36,     4,     6,   134,    34,
     136,     4,     4,     5,    32,     7,    34,     9,    36,    36,
      12,    13,    14,     3,     4,     4,     5,    36,     7,    36,
       9,    34,    10,    12,    13,    14,    11,    17,    18,    51,
       4,    21,    19,     7,    36,     9,     3,     4,    12,    32,
      14,    86,    32,    -1,    34,    35,    -1,    36,    -1,    -1,
      17,    18,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    32,    -1,    34,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,    -1,    36,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    36,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    35,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,    35,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    40,    41,     0,    16,     6,     5,    13,    15,    42,
      43,    44,    45,    46,    47,    55,     4,    33,     7,    36,
      37,    43,    47,    55,     4,    34,    34,    43,    45,    46,
       4,     4,    34,    35,    48,    55,    35,    43,    35,    48,
       8,    49,    50,    51,    35,    37,     4,    50,    49,    35,
      36,     6,    52,    49,    55,    49,     4,     7,     9,    12,
      14,    36,    44,    50,    53,    54,    55,    56,     4,    19,
      34,    34,     3,     4,    17,    18,    21,    32,    34,    56,
      58,    59,    60,    61,    36,    58,    36,     7,    54,     4,
      36,    58,    35,    57,    58,    58,    58,    58,    58,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    50,    36,     7,    53,    36,    35,    37,    35,    35,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,     7,    58,    10,    50,    11,    50
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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
#line 80 "tds-sintaxis.y"
    {init();;}
    break;

  case 3:
#line 80 "tds-sintaxis.y"
    {  //printIndexList();
                                                    //printStack();
                                                    printf("Iniciando chequeo Sintactico...\n");
                                                    if(noErrors()){
                                                      printf(KGRN "%s\n", "Chequeo Sintactico satisfactorio. "); printf(KNRM);
                                                      if(testType == 1){
                                                        printf("Iniciando chequeo Semantico...\n");
                                                        checkFunctions(inicial);
                                                      }
                                                      if(noErrors() && (testType == 1)){
                                                        printf(KGRN "%s\n", "Chequeo Semantico satisfactorio. "); printf(KNRM);
                                                        printf(KGRN "%s\n", "Generando codigo intermedio.... "); printf(KNRM);
                                                        generar_codigo();
                                                        printLista();
                                                        printf(KGRN "%s\n", "Codigo intermedio generado. "); printf(KNRM);
                                                        printf(KGRN "%s\n", "Generando codigo Assembler.... "); printf(KNRM);
                                                        generar_codigo_assembler();
                                                        printf(KGRN "%s\n", "Codigo Assembler generado. "); printf(KNRM);
                                                      }
                                                      else if (!noErrors() && (testType == 1)){
                                                      printf(KRED "%s\n", "TODO MAL, TU CODIGO NO SIRVE, TIENE ERRORES SEMANTICOS: "); printf(KNRM);
                                                      printErrors();
                                                      }
                                                    }
                                                    else{
                                                      printf(KRED "%s\n", "TODO MAL, TU CODIGO NO SIRVE, TIENE ERRORES SINTATICOS: "); printf(KNRM);
                                                      printErrors();
                                                    }

                                                    printf("Tamaño del arbol antes de eliminar: %d\n", treeSize);
                                                    deleteFuncitonBlocks();
                                                    printf("Tamaño del arbol luego de eliminar: %d\n", treeSize);
                                                 ;}
    break;

  case 4:
#line 115 "tds-sintaxis.y"
    {insertar_funcion(crearDataStack(toString("main"), VOIDD, -1, INSERTFUNC, yylineno, (yyvsp[(1) - (1)].n), NULL, true)); (yyval.n) = (yyvsp[(1) - (1)].n);;}
    break;

  case 5:
#line 116 "tds-sintaxis.y"
    {insertar_funcion(crearDataStack(toString("main"), VOIDD, -1, INSERTFUNC, yylineno, (yyvsp[(4) - (4)].n), NULL, true)); (yyval.n) = (yyvsp[(4) - (4)].n);;}
    break;

  case 6:
#line 117 "tds-sintaxis.y"
    {insertar_funcion(crearDataStack(toString("main"), VOIDD, -1, INSERTFUNC, yylineno, (yyvsp[(3) - (3)].n), NULL, true)); (yyval.n) = (yyvsp[(3) - (3)].n);;}
    break;

  case 7:
#line 118 "tds-sintaxis.y"
    {insertar_funcion(crearDataStack(toString("main"), VOIDD, -1, INSERTFUNC, yylineno, (yyvsp[(2) - (2)].n), NULL, true)); (yyval.n) = (yyvsp[(2) - (2)].n);;}
    break;

  case 8:
#line 121 "tds-sintaxis.y"
    {(yyval.n) = (yyvsp[(5) - (5)].n);;}
    break;

  case 9:
#line 123 "tds-sintaxis.y"
    {;}
    break;

  case 10:
#line 124 "tds-sintaxis.y"
    {;}
    break;

  case 11:
#line 128 "tds-sintaxis.y"
    {insertar(crearDataStack(getNombre((yyvsp[(2) - (2)].st)), (yyvsp[(1) - (2)].i), 0, VARR, yylineno, NULL, NULL, false));;}
    break;

  case 12:
#line 130 "tds-sintaxis.y"
    {insertar(crearDataStack(getNombre((yyvsp[(3) - (3)].st)), lastType(), 0, VARR, yylineno, NULL, NULL, false));;}
    break;

  case 13:
#line 133 "tds-sintaxis.y"
    {;}
    break;

  case 14:
#line 134 "tds-sintaxis.y"
    {;}
    break;

  case 15:
#line 137 "tds-sintaxis.y"
    {insertar_funcion(crearDataStack(getNombre((yyvsp[(2) - (6)].st)), (yyvsp[(1) - (6)].i), -1, INSERTFUNC, yylineno, (yyvsp[(6) - (6)].n), fstParam, true));cerrar_nivel(); resetParams();;}
    break;

  case 16:
#line 139 "tds-sintaxis.y"
    {insertar_funcion(crearDataStack(getNombre((yyvsp[(2) - (6)].st)), VOIDD, -1, INSERTFUNC, yylineno, (yyvsp[(6) - (6)].n), fstParam, true));cerrar_nivel(); resetParams();;}
    break;

  case 17:
#line 141 "tds-sintaxis.y"
    {insertar_funcion(crearDataStack(getNombre((yyvsp[(2) - (5)].st)), (yyvsp[(1) - (5)].i), -1, INSERTFUNC, yylineno, (yyvsp[(5) - (5)].n), NULL, true));;}
    break;

  case 18:
#line 143 "tds-sintaxis.y"
    {insertar_funcion(crearDataStack(getNombre((yyvsp[(2) - (5)].st)), VOIDD, -1, INSERTFUNC, yylineno, (yyvsp[(5) - (5)].n), NULL, true));;}
    break;

  case 19:
#line 146 "tds-sintaxis.y"
    { crear_nivel();
                                          insertar(crearDataStack(getNombre((yyvsp[(2) - (2)].st)), (yyvsp[(1) - (2)].i), -1, PARAMETRO, yylineno, NULL, NULL, false));
                                          (yyval.pl) = getFormalParams();
                                        ;}
    break;

  case 20:
#line 150 "tds-sintaxis.y"
    { insertar(crearDataStack(getNombre((yyvsp[(4) - (4)].st)), (yyvsp[(3) - (4)].i), -1, PARAMETRO, yylineno, NULL, NULL, false));
                                          (yyval.pl) = (yyvsp[(1) - (4)].pl);
                                        ;}
    break;

  case 21:
#line 155 "tds-sintaxis.y"
    {  (yyval.n)=(yyvsp[(1) - (1)].n);;}
    break;

  case 22:
#line 156 "tds-sintaxis.y"
    {  (yyval.n) = createNode(createNodeParam(toString("BLOCKNULL"), -1, -1, -1, BLOCKNULL, NULL, NULL, NULL, false, NULL, yylineno));;}
    break;

  case 23:
#line 159 "tds-sintaxis.y"
    {crear_nivel();;}
    break;

  case 24:
#line 159 "tds-sintaxis.y"
    { cerrar_nivel();
                                                      (yyval.n) = createNode(createNodeParam(toString("BLOCK"), 0, BLOCK, NONRETT, BLOCK, (yyvsp[(2) - (2)].n), NULL, NULL, false, NULL, yylineno));
                                                    ;}
    break;

  case 25:
#line 164 "tds-sintaxis.y"
    {(yyval.n) = createNode(createNodeParam(toString("EMPTYBLOCK"), -1, -1, -1, EMPTYBLOCK, NULL, NULL, NULL, false, NULL, yylineno));;}
    break;

  case 26:
#line 165 "tds-sintaxis.y"
    {(yyval.n) = createNode(createNodeParam(toString("BLOCKSINSTATEMENTS"), -1, -1, -1, BLOCKSINSTATEMENTS, NULL, NULL, NULL, false, NULL, yylineno));;}
    break;

  case 27:
#line 166 "tds-sintaxis.y"
    {(yyval.n) = (yyvsp[(2) - (3)].n);;}
    break;

  case 28:
#line 167 "tds-sintaxis.y"
    {(yyval.n) = (yyvsp[(4) - (5)].n);;}
    break;

  case 29:
#line 170 "tds-sintaxis.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);;}
    break;

  case 30:
#line 171 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("STATEMENTS"), 0, UNKNOW, NONRETT, STATEMENTS, (yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].n), NULL, false, NULL, yylineno));;}
    break;

  case 31:
#line 174 "tds-sintaxis.y"
    { nodeParam *node = createNodeParam(toString("ASIGNACIONN"), 0, UNKNOW, NONRET, ASIGNACIONN, createNode(createNodeParam(getNombre((yyvsp[(1) - (4)].st)), 0, 0, NONRETT, VARR, NULL, NULL, NULL, false, NULL, yylineno)), (yyvsp[(3) - (4)].n), NULL, false, NULL,  yylineno);
                                                          (yyval.n) = createNode(node);
                                                        ;}
    break;

  case 32:
#line 177 "tds-sintaxis.y"
    { (yyval.n) = (yyvsp[(1) - (2)].n);;}
    break;

  case 33:
#line 179 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("IFTHEN"), 0, UNKNOW, NONRETT, IFTHENN, (yyvsp[(3) - (6)].n), (yyvsp[(6) - (6)].n), NULL, false, NULL, yylineno));;}
    break;

  case 34:
#line 181 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("IFTHENELSE"), 0, UNKNOW, NONRETT, IFTHENELSEE, (yyvsp[(3) - (8)].n), (yyvsp[(6) - (8)].n), (yyvsp[(8) - (8)].n), false, NULL, yylineno));;}
    break;

  case 35:
#line 183 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("WHILE"), 0, UNKNOW, NONRETT, WHILEE, (yyvsp[(2) - (3)].n), (yyvsp[(3) - (3)].n), NULL, false, NULL, yylineno));;}
    break;

  case 36:
#line 185 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("RETURN"), 0, UNKNOW, getTipo(getNodeData((yyvsp[(2) - (3)].n))), RETURNN, (yyvsp[(2) - (3)].n), NULL, NULL, false, NULL, yylineno));;}
    break;

  case 37:
#line 187 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("RETURN"), 0, UNKNOW, VOIDD, RETURNN, NULL, NULL, NULL, false, NULL, yylineno));;}
    break;

  case 38:
#line 189 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("PCOMA"), -1, -1, -1, PCOMA, NULL, NULL, NULL, false, NULL, yylineno));;}
    break;

  case 39:
#line 191 "tds-sintaxis.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);;}
    break;

  case 40:
#line 195 "tds-sintaxis.y"
    { (yyval.i) = INTEGERR;;}
    break;

  case 41:
#line 196 "tds-sintaxis.y"
    { (yyval.i) = BOOLEAN;;}
    break;

  case 42:
#line 200 "tds-sintaxis.y"
    { data_stack *datas = buscar_func(getNombre((yyvsp[(1) - (3)].st)));
                                          if(datas == NULL){
                                            printNodeError(createError(yylineno, UNDEFINEDFUNC));
                                            exit(0);
                                          }
                                          data_gen *d = datas->data;
                                          (yyval.n) = createNode(createNodeParam(getNombre((yyvsp[(1) - (3)].st)), 0, d->tipo, 0, INVOCC, NULL, NULL, NULL, true, NULL, yylineno));
                                        ;}
    break;

  case 43:
#line 209 "tds-sintaxis.y"
    { data_stack *datas = buscar_func(getNombre((yyvsp[(1) - (4)].st)));
                                          if(datas == NULL){
                                            printNodeError(createError(yylineno, UNDEFINEDFUNC));
                                            exit(0);
                                          }
                                          data_gen *d = datas->data;
                                          (yyval.n) = createNode(createNodeParam(getNombre((yyvsp[(1) - (4)].st)), 0, d->tipo, 0, INVOCC, NULL, NULL, NULL, true, (yyvsp[(3) - (4)].ap), yylineno));
                                        ;}
    break;

  case 44:
#line 219 "tds-sintaxis.y"
    { paramList *param = (paramList *) malloc(sizeof(paramList)); newCall(param, (yyvsp[(1) - (1)].n)); (yyval.ap) = param;;}
    break;

  case 45:
#line 220 "tds-sintaxis.y"
    { newCall((yyvsp[(1) - (3)].ap), (yyvsp[(3) - (3)].n)); (yyval.ap) = (yyvsp[(1) - (3)].ap);;}
    break;

  case 46:
#line 223 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(getNombre((yyvsp[(1) - (1)].st)), 0, 0, NONRETT, VARR, NULL, NULL, NULL, false, NULL, yylineno));;}
    break;

  case 47:
#line 225 "tds-sintaxis.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);;}
    break;

  case 48:
#line 227 "tds-sintaxis.y"
    { (yyval.n) = (yyvsp[(1) - (1)].n);;}
    break;

  case 49:
#line 229 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("SUMA"), 0, INTEGERR, NONRETT, SUMAA,(yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n), NULL, false, NULL, yylineno));;}
    break;

  case 50:
#line 231 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("RESTA"), 0, INTEGERR, NONRETT, RESTAA, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n), NULL, false, NULL, yylineno));;}
    break;

  case 51:
#line 233 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("PROD"), 0, INTEGERR, NONRETT, PRODD, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n), NULL, false, NULL, yylineno));;}
    break;

  case 52:
#line 235 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("DIV"), 0, INTEGERR, NONRETT, DIVV, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n), NULL, false, NULL, yylineno));;}
    break;

  case 53:
#line 237 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("MOD"), 0, INTEGERR, NONRETT, MODD, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n), NULL, false, NULL, yylineno));;}
    break;

  case 54:
#line 239 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("MAYOR"), 0, BOOLEAN, NONRETT, MAYORR, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n), NULL, false, NULL, yylineno));;}
    break;

  case 55:
#line 241 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("MENOR"), 0, BOOLEAN, NONRETT, MENORR, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n), NULL, false, NULL, yylineno));;}
    break;

  case 56:
#line 243 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("IGUALDAD"), 0, BOOLEAN, NONRETT, IGUALDADD, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n), NULL, false, NULL, yylineno));;}
    break;

  case 57:
#line 245 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("MENIGUAL"), 0, BOOLEAN, NONRETT, MENIGUALL, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n), NULL, false, NULL, yylineno));;}
    break;

  case 58:
#line 247 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("MAYIGUAL"), 0, BOOLEAN, NONRETT, MAYIGUALL, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n), NULL, false, NULL, yylineno));;}
    break;

  case 59:
#line 249 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("AND"), 0, BOOLEAN, NONRETT, ANDD, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n), NULL, false, NULL, yylineno));;}
    break;

  case 60:
#line 251 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("OR"), 0, BOOLEAN, NONRETT, ORR, (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n), NULL, false, NULL, yylineno));;}
    break;

  case 61:
#line 253 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("OPUESTO"), 0, INTEGERR, NONRETT, RESTAA, (yyvsp[(2) - (2)].n), NULL, NULL, false, NULL, yylineno));;}
    break;

  case 62:
#line 255 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("NOT"), 0, BOOLEAN, NONRETT, NOTT, (yyvsp[(2) - (2)].n), NULL, NULL, false, NULL, yylineno));;}
    break;

  case 63:
#line 257 "tds-sintaxis.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n);;}
    break;

  case 64:
#line 260 "tds-sintaxis.y"
    { (yyval.n) = createNode( createNodeParam(toString("int_cte"), (yyvsp[(1) - (1)].i), INTEGERR, NONRETT, CONSTANTEE, NULL, NULL, NULL, false, NULL, yylineno));;}
    break;

  case 65:
#line 262 "tds-sintaxis.y"
    { (yyval.n) = createNode(createNodeParam(toString("bool_cte"), (yyvsp[(1) - (1)].i), BOOLEAN, NONRETT, CONSTANTEE, NULL, NULL, NULL, false, NULL, yylineno));;}
    break;

  case 66:
#line 265 "tds-sintaxis.y"
    {(yyval.i) = (yyvsp[(1) - (1)].i);;}
    break;

  case 67:
#line 269 "tds-sintaxis.y"
    {(yyval.i) = 1;;}
    break;

  case 68:
#line 270 "tds-sintaxis.y"
    {(yyval.i) = 0;;}
    break;


/* Line 1267 of yacc.c.  */
#line 1922 "tds-sintaxis.tab.c"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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


#line 273 "tds-sintaxis.y"
