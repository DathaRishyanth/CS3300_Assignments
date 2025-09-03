/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CLASS = 258,                   /* CLASS  */
    PUBLIC = 259,                  /* PUBLIC  */
    STATIC = 260,                  /* STATIC  */
    VOID = 261,                    /* VOID  */
    MAIN = 262,                    /* MAIN  */
    STRING = 263,                  /* STRING  */
    EXTENDS = 264,                 /* EXTENDS  */
    RETURN = 265,                  /* RETURN  */
    NEW = 266,                     /* NEW  */
    IF = 267,                      /* IF  */
    ELSE = 268,                    /* ELSE  */
    WHILE = 269,                   /* WHILE  */
    DO = 270,                      /* DO  */
    TRUE_ = 271,                   /* TRUE_  */
    FALSE_ = 272,                  /* FALSE_  */
    THIS = 273,                    /* THIS  */
    LENGTH = 274,                  /* LENGTH  */
    PRINT = 275,                   /* PRINT  */
    INT = 276,                     /* INT  */
    BOOLEAN = 277,                 /* BOOLEAN  */
    DEFINE = 278,                  /* DEFINE  */
    OR = 279,                      /* OR  */
    AND = 280,                     /* AND  */
    NEQ = 281,                     /* NEQ  */
    LEQ = 282,                     /* LEQ  */
    UMINUS = 283,                  /* UMINUS  */
    IDENTIFIER = 284,              /* IDENTIFIER  */
    INTEGER_LITERAL = 285          /* INTEGER_LITERAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define CLASS 258
#define PUBLIC 259
#define STATIC 260
#define VOID 261
#define MAIN 262
#define STRING 263
#define EXTENDS 264
#define RETURN 265
#define NEW 266
#define IF 267
#define ELSE 268
#define WHILE 269
#define DO 270
#define TRUE_ 271
#define FALSE_ 272
#define THIS 273
#define LENGTH 274
#define PRINT 275
#define INT 276
#define BOOLEAN 277
#define DEFINE 278
#define OR 279
#define AND 280
#define NEQ 281
#define LEQ 282
#define UMINUS 283
#define IDENTIFIER 284
#define INTEGER_LITERAL 285

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 8 "P1.y"

    int val;
    char *str;

#line 132 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
