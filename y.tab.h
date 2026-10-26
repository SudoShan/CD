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
     ID = 258,
     NUM = 259,
     INT = 260,
     FLOAT = 261,
     CHAR = 262,
     DOUBLE = 263,
     IF = 264,
     ELSE = 265,
     WHILE = 266,
     FOR = 267,
     CONTINUE = 268,
     BREAK = 269,
     DO = 270,
     LE = 271,
     GE = 272,
     NE = 273,
     EQ = 274,
     AND = 275,
     OR = 276,
     NOT = 277,
     ADD_ASSIGN = 278,
     SUB_ASSIGN = 279,
     MUL_ASSIGN = 280,
     DIV_ASSIGN = 281,
     INC = 282,
     DEC = 283,
     IFX = 284
   };
#endif
/* Tokens.  */
#define ID 258
#define NUM 259
#define INT 260
#define FLOAT 261
#define CHAR 262
#define DOUBLE 263
#define IF 264
#define ELSE 265
#define WHILE 266
#define FOR 267
#define CONTINUE 268
#define BREAK 269
#define DO 270
#define LE 271
#define GE 272
#define NE 273
#define EQ 274
#define AND 275
#define OR 276
#define NOT 277
#define ADD_ASSIGN 278
#define SUB_ASSIGN 279
#define MUL_ASSIGN 280
#define DIV_ASSIGN 281
#define INC 282
#define DEC 283
#define IFX 284




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 22 "parser.y"
{
    char str[20];
}
/* Line 1529 of yacc.c.  */
#line 111 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

