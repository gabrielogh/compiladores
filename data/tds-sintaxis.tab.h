/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 12 "tds-sintaxis.y"
{ int i; char *s; struct strings *st; struct nodes *n; struct nodeParams *np; struct Formalparams *pl; struct actualParams *ap;struct stacks *stk;}
/* Line 1529 of yacc.c.  */
#line 127 "tds-sintaxis.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

