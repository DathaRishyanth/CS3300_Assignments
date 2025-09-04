/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "P1.y"

#include <bits/stdc++.h>
#include <regex>
#include <stdexcept>
#include <sstream>
using namespace std;

struct Macro {
    bool isExpression;
    vector<string> params;
    string body;
};
map<string, Macro> macroTable;
int indent = 0;
string indentation(int level) {
    return string(level * 4, ' ');
}

static inline string trim(const string& s){
    size_t i=0, j=s.size();
    while(i<j && isspace((unsigned char)s[i])) ++i;
    while(j>i && isspace((unsigned char)s[j-1])) --j;
    return s.substr(i, j-i);
}

static vector<string> parseArgs(const string& s){
    vector<string> out; string cur;
    int depth=0;
    for(size_t i=0;i<s.size();++i){
        char c=s[i];
        if(c=='('||c=='['||c=='{'){ ++depth; cur.push_back(c); }
        else if(c==')'||c==']'||c=='}'){ --depth; cur.push_back(c); }
        else if(c==',' && depth==0){ out.push_back(trim(cur)); cur.clear(); }
        else cur.push_back(c);
    }
    if(!cur.empty()) out.push_back(trim(cur));
    if(out.size()==1 && out[0].empty()) out.clear();
    return out;
}

static vector<string> splitParamsCSV(const string& s){
    vector<string> out; string cur;
    for(char c: s){ if(c==','){ out.push_back(trim(cur)); cur.clear(); } else cur.push_back(c); }
    if(!cur.empty()) out.push_back(trim(cur));
    if(out.size()==1 && out[0].empty()) out.clear();
    return out;
}

static string substituteParams(const string& body,
                               const vector<string>& params,
                               const vector<string>& args){
    string res = body;
    for(size_t i=0;i<params.size();++i){
        const string& p = params[i];
        const string& a = args[i];
        regex re("\\b" + p + "\\b");
        res = regex_replace(res, re, a);
    }
    return res;
}

static string expandMacroCallCommon(const char* nameC, const char* argsStrC, bool expectExpression){
    string name = nameC ? nameC : "";
    string argsStr = argsStrC ? argsStrC : "";

    auto it = macroTable.find(name);
    if(it == macroTable.end()) throw runtime_error("Unknown macro: " + name);

    const Macro& macro = it->second;
    if(expectExpression && !macro.isExpression)
        throw runtime_error("Macro '" + name + "' is a statement macro");
    if(!expectExpression && macro.isExpression)
        throw runtime_error("Macro '" + name + "' is an expression macro");
    vector<string> args = parseArgs(argsStr);
    if(args.size() != macro.params.size()){
        ostringstream oss;
        oss << "Macro '" << name << "' expects "
                               << macro.params.size() << " arg(s), got " << args.size();
        throw runtime_error(oss.str());
    }
    return substituteParams(macro.body, macro.params, args);
}

void yyerror(const char *s){
    fprintf(stderr, "Error: %s\n", s);
}
int yylex(void);

#line 160 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
    IMPORT = 267,                  /* IMPORT  */
    JAVA = 268,                    /* JAVA  */
    UTIL = 269,                    /* UTIL  */
    APPLY = 270,                   /* APPLY  */
    ARROW = 271,                   /* ARROW  */
    FUNCTION = 272,                /* FUNCTION  */
    EQ = 273,                      /* EQ  */
    NEQ = 274,                     /* NEQ  */
    LEQ = 275,                     /* LEQ  */
    AND = 276,                     /* AND  */
    OR = 277,                      /* OR  */
    IF = 278,                      /* IF  */
    ELSE = 279,                    /* ELSE  */
    WHILE = 280,                   /* WHILE  */
    DO = 281,                      /* DO  */
    TRUE_ = 282,                   /* TRUE_  */
    FALSE_ = 283,                  /* FALSE_  */
    THIS = 284,                    /* THIS  */
    LENGTH = 285,                  /* LENGTH  */
    PRINT = 286,                   /* PRINT  */
    INT = 287,                     /* INT  */
    BOOLEAN = 288,                 /* BOOLEAN  */
    IFX = 289,                     /* IFX  */
    DEFINE = 290,                  /* DEFINE  */
    UMINUS = 291,                  /* UMINUS  */
    IDENTIFIER = 292,              /* IDENTIFIER  */
    INTEGER_LITERAL = 293          /* INTEGER_LITERAL  */
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
#define IMPORT 267
#define JAVA 268
#define UTIL 269
#define APPLY 270
#define ARROW 271
#define FUNCTION 272
#define EQ 273
#define NEQ 274
#define LEQ 275
#define AND 276
#define OR 277
#define IF 278
#define ELSE 279
#define WHILE 280
#define DO 281
#define TRUE_ 282
#define FALSE_ 283
#define THIS 284
#define LENGTH 285
#define PRINT 286
#define INT 287
#define BOOLEAN 288
#define IFX 289
#define DEFINE 290
#define UMINUS 291
#define IDENTIFIER 292
#define INTEGER_LITERAL 293

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 91 "P1.y"

   char* val;

#line 293 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CLASS = 3,                      /* CLASS  */
  YYSYMBOL_PUBLIC = 4,                     /* PUBLIC  */
  YYSYMBOL_STATIC = 5,                     /* STATIC  */
  YYSYMBOL_VOID = 6,                       /* VOID  */
  YYSYMBOL_MAIN = 7,                       /* MAIN  */
  YYSYMBOL_STRING = 8,                     /* STRING  */
  YYSYMBOL_EXTENDS = 9,                    /* EXTENDS  */
  YYSYMBOL_RETURN = 10,                    /* RETURN  */
  YYSYMBOL_NEW = 11,                       /* NEW  */
  YYSYMBOL_IMPORT = 12,                    /* IMPORT  */
  YYSYMBOL_JAVA = 13,                      /* JAVA  */
  YYSYMBOL_UTIL = 14,                      /* UTIL  */
  YYSYMBOL_APPLY = 15,                     /* APPLY  */
  YYSYMBOL_ARROW = 16,                     /* ARROW  */
  YYSYMBOL_FUNCTION = 17,                  /* FUNCTION  */
  YYSYMBOL_EQ = 18,                        /* EQ  */
  YYSYMBOL_NEQ = 19,                       /* NEQ  */
  YYSYMBOL_LEQ = 20,                       /* LEQ  */
  YYSYMBOL_AND = 21,                       /* AND  */
  YYSYMBOL_OR = 22,                        /* OR  */
  YYSYMBOL_IF = 23,                        /* IF  */
  YYSYMBOL_ELSE = 24,                      /* ELSE  */
  YYSYMBOL_WHILE = 25,                     /* WHILE  */
  YYSYMBOL_DO = 26,                        /* DO  */
  YYSYMBOL_TRUE_ = 27,                     /* TRUE_  */
  YYSYMBOL_FALSE_ = 28,                    /* FALSE_  */
  YYSYMBOL_THIS = 29,                      /* THIS  */
  YYSYMBOL_LENGTH = 30,                    /* LENGTH  */
  YYSYMBOL_PRINT = 31,                     /* PRINT  */
  YYSYMBOL_INT = 32,                       /* INT  */
  YYSYMBOL_BOOLEAN = 33,                   /* BOOLEAN  */
  YYSYMBOL_IFX = 34,                       /* IFX  */
  YYSYMBOL_DEFINE = 35,                    /* DEFINE  */
  YYSYMBOL_36_ = 36,                       /* '='  */
  YYSYMBOL_37_ = 37,                       /* '+'  */
  YYSYMBOL_38_ = 38,                       /* '-'  */
  YYSYMBOL_39_ = 39,                       /* '*'  */
  YYSYMBOL_40_ = 40,                       /* '/'  */
  YYSYMBOL_41_ = 41,                       /* '!'  */
  YYSYMBOL_UMINUS = 42,                    /* UMINUS  */
  YYSYMBOL_43_ = 43,                       /* '.'  */
  YYSYMBOL_44_ = 44,                       /* '['  */
  YYSYMBOL_45_ = 45,                       /* ']'  */
  YYSYMBOL_IDENTIFIER = 46,                /* IDENTIFIER  */
  YYSYMBOL_INTEGER_LITERAL = 47,           /* INTEGER_LITERAL  */
  YYSYMBOL_48_ = 48,                       /* ';'  */
  YYSYMBOL_49_ = 49,                       /* '{'  */
  YYSYMBOL_50_ = 50,                       /* '('  */
  YYSYMBOL_51_ = 51,                       /* ')'  */
  YYSYMBOL_52_ = 52,                       /* '}'  */
  YYSYMBOL_53_ = 53,                       /* '<'  */
  YYSYMBOL_54_ = 54,                       /* ','  */
  YYSYMBOL_55_ = 55,                       /* '>'  */
  YYSYMBOL_YYACCEPT = 56,                  /* $accept  */
  YYSYMBOL_Goal = 57,                      /* Goal  */
  YYSYMBOL_ImportFunctionOpt = 58,         /* ImportFunctionOpt  */
  YYSYMBOL_MacroDefinitions = 59,          /* MacroDefinitions  */
  YYSYMBOL_TypeDeclarations = 60,          /* TypeDeclarations  */
  YYSYMBOL_MainClass = 61,                 /* MainClass  */
  YYSYMBOL_TypeDeclaration = 62,           /* TypeDeclaration  */
  YYSYMBOL_VarDecls = 63,                  /* VarDecls  */
  YYSYMBOL_VarDecl = 64,                   /* VarDecl  */
  YYSYMBOL_FunctionDecl = 65,              /* FunctionDecl  */
  YYSYMBOL_MethodDeclarations = 66,        /* MethodDeclarations  */
  YYSYMBOL_MethodDeclaration = 67,         /* MethodDeclaration  */
  YYSYMBOL_68_1 = 68,                      /* $@1  */
  YYSYMBOL_FunctionType = 69,              /* FunctionType  */
  YYSYMBOL_OptParams = 70,                 /* OptParams  */
  YYSYMBOL_ParamList = 71,                 /* ParamList  */
  YYSYMBOL_ParamRests = 72,                /* ParamRests  */
  YYSYMBOL_Type = 73,                      /* Type  */
  YYSYMBOL_ClassType = 74,                 /* ClassType  */
  YYSYMBOL_Statements = 75,                /* Statements  */
  YYSYMBOL_Statement = 76,                 /* Statement  */
  YYSYMBOL_MatchedStatement = 77,          /* MatchedStatement  */
  YYSYMBOL_78_2 = 78,                      /* $@2  */
  YYSYMBOL_79_3 = 79,                      /* $@3  */
  YYSYMBOL_80_4 = 80,                      /* $@4  */
  YYSYMBOL_81_5 = 81,                      /* $@5  */
  YYSYMBOL_82_6 = 82,                      /* $@6  */
  YYSYMBOL_83_7 = 83,                      /* $@7  */
  YYSYMBOL_Block = 84,                     /* Block  */
  YYSYMBOL_85_8 = 85,                      /* $@8  */
  YYSYMBOL_UnmatchedStatement = 86,        /* UnmatchedStatement  */
  YYSYMBOL_87_9 = 87,                      /* $@9  */
  YYSYMBOL_88_10 = 88,                     /* $@10  */
  YYSYMBOL_89_11 = 89,                     /* $@11  */
  YYSYMBOL_90_12 = 90,                     /* $@12  */
  YYSYMBOL_91_13 = 91,                     /* $@13  */
  YYSYMBOL_92_14 = 92,                     /* $@14  */
  YYSYMBOL_OptExprs = 93,                  /* OptExprs  */
  YYSYMBOL_ExprList = 94,                  /* ExprList  */
  YYSYMBOL_ExpressionRests = 95,           /* ExpressionRests  */
  YYSYMBOL_ExpressionRest = 96,            /* ExpressionRest  */
  YYSYMBOL_Expression = 97,                /* Expression  */
  YYSYMBOL_MacroDefinition = 98,           /* MacroDefinition  */
  YYSYMBOL_MacroDefExpression = 99,        /* MacroDefExpression  */
  YYSYMBOL_MacroDefStatement = 100,        /* MacroDefStatement  */
  YYSYMBOL_OptIdList = 101,                /* OptIdList  */
  YYSYMBOL_IdList = 102,                   /* IdList  */
  YYSYMBOL_IdRests = 103,                  /* IdRests  */
  YYSYMBOL_IdRest = 104                    /* IdRest  */
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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_uint8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   501

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  243

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


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
       2,     2,     2,    41,     2,     2,     2,     2,     2,     2,
      50,    51,    39,    37,    54,    38,    43,    40,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    48,
      53,    36,    55,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    45,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,    52,     2,     2,     2,     2,
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
      35,    42,    46,    47
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   132,   132,   143,   148,   152,   156,   160,   164,   168,
     187,   197,   210,   214,   218,   223,   231,   239,   243,   247,
     247,   259,   267,   271,   275,   283,   288,   292,   293,   294,
     295,   296,   303,   307,   311,   315,   316,   317,   321,   321,
     321,   321,   321,   329,   329,   329,   335,   340,   341,   346,
     354,   354,   365,   365,   365,   371,   371,   371,   371,   371,
     382,   385,   392,   400,   404,   408,   415,   416,   417,   418,
     419,   420,   422,   424,   426,   428,   430,   432,   434,   436,
     438,   440,   442,   444,   446,   448,   457,   459,   461,   466,
     467,   471,   493,   515,   516,   520,   524,   525,   529
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CLASS", "PUBLIC",
  "STATIC", "VOID", "MAIN", "STRING", "EXTENDS", "RETURN", "NEW", "IMPORT",
  "JAVA", "UTIL", "APPLY", "ARROW", "FUNCTION", "EQ", "NEQ", "LEQ", "AND",
  "OR", "IF", "ELSE", "WHILE", "DO", "TRUE_", "FALSE_", "THIS", "LENGTH",
  "PRINT", "INT", "BOOLEAN", "IFX", "DEFINE", "'='", "'+'", "'-'", "'*'",
  "'/'", "'!'", "UMINUS", "'.'", "'['", "']'", "IDENTIFIER",
  "INTEGER_LITERAL", "';'", "'{'", "'('", "')'", "'}'", "'<'", "','",
  "'>'", "$accept", "Goal", "ImportFunctionOpt", "MacroDefinitions",
  "TypeDeclarations", "MainClass", "TypeDeclaration", "VarDecls",
  "VarDecl", "FunctionDecl", "MethodDeclarations", "MethodDeclaration",
  "$@1", "FunctionType", "OptParams", "ParamList", "ParamRests", "Type",
  "ClassType", "Statements", "Statement", "MatchedStatement", "$@2", "$@3",
  "$@4", "$@5", "$@6", "$@7", "Block", "$@8", "UnmatchedStatement", "$@9",
  "$@10", "$@11", "$@12", "$@13", "$@14", "OptExprs", "ExprList",
  "ExpressionRests", "ExpressionRest", "Expression", "MacroDefinition",
  "MacroDefExpression", "MacroDefStatement", "OptIdList", "IdList",
  "IdRests", "IdRest", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-169)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-53)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       1,    -7,    16,   -17,   -13,  -169,   -20,    30,   -17,  -169,
    -169,    23,    -4,    13,    74,  -169,    41,    37,    36,    49,
    -169,    74,    70,    42,    50,  -169,    98,    -6,  -169,    63,
      62,  -169,    42,   -25,   112,    67,   -10,   102,  -169,  -169,
     306,    28,   115,    86,    83,    99,  -169,  -169,    40,   135,
     -10,    96,   109,  -169,   106,   110,   114,   116,   -27,  -169,
    -169,   113,   306,  -169,  -169,  -169,   -18,  -169,  -169,  -169,
      28,   121,  -169,    28,    72,   172,   -10,    40,   138,   164,
      40,   136,   135,   143,  -169,   149,   150,  -169,    28,    28,
      28,    28,    28,   306,  -169,  -169,   147,   151,    10,    28,
     108,    28,    28,    28,    28,    28,    28,    28,    28,    28,
      12,    28,  -169,   160,   135,   152,  -169,    40,  -169,  -169,
    -169,   161,  -169,  -169,   156,   165,   198,   324,   380,   163,
      28,   162,   170,  -169,    60,  -169,   449,    94,    94,   130,
     457,   118,   118,    10,    10,   174,  -169,   175,   410,   204,
     178,    40,   171,    40,   -12,  -169,   183,  -169,   196,  -169,
     419,  -169,  -169,    28,  -169,   179,    28,    28,  -169,   190,
    -169,   184,  -169,   189,  -169,   197,    95,   306,    95,    95,
    -169,    28,  -169,   449,  -169,   207,   201,   203,  -169,   205,
     199,   213,   -27,  -169,  -169,  -169,  -169,   338,  -169,  -169,
     209,  -169,    40,  -169,    28,   233,  -169,   242,  -169,  -169,
     216,   306,   218,   240,  -169,  -169,   223,   263,   199,  -169,
      95,   251,   244,    28,  -169,  -169,   226,  -169,   231,   368,
    -169,    28,  -169,    28,   230,   249,   282,  -169,  -169,   237,
     238,   243,  -169
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     6,     0,     1,     0,     0,     6,    89,
      90,     0,     0,     0,     8,     5,     0,    94,     0,     0,
       2,     8,     0,    97,     0,    93,     0,     0,     7,     0,
       0,    95,    97,     0,     0,     0,    13,     0,    98,    96,
      34,     0,     0,     0,     0,    29,    28,    32,     0,    18,
      13,     0,     0,    30,     0,     0,     0,     0,    32,    50,
      37,     0,    34,    35,    47,    36,     0,    67,    68,    70,
       0,    69,    66,     0,     0,     0,    13,     0,     0,     0,
       0,     0,    18,     0,    12,     0,     0,     3,     0,     0,
       0,     0,     0,    34,    92,    33,     0,     0,    76,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    91,     0,    18,     0,    27,     0,    21,    10,
      17,     0,    15,    14,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    61,    64,    86,    87,    82,    81,    83,
      84,    79,    80,    77,    78,     0,    71,     0,     0,     0,
       0,     0,     0,    23,    38,    43,     0,    48,     0,    51,
       0,    74,    85,     0,    62,    64,     0,    60,    75,     0,
      11,     0,    31,     0,    22,     0,     0,     0,     0,     0,
      46,     0,    73,    65,    63,     0,     0,     0,    16,     0,
      26,     0,     0,    39,    53,    56,    44,     0,    88,    72,
       0,    19,     0,    24,     0,     0,    54,     0,    45,    49,
       0,    34,     0,     0,    40,    57,     0,     0,    26,    38,
       0,     0,     0,     0,    25,    41,     0,    58,     0,     0,
      42,     0,    59,     0,     0,     0,     0,    20,    52,     0,
       0,     0,     9
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -169,  -169,  -169,   286,   275,  -169,  -169,   -31,   -35,  -169,
     -70,  -169,  -169,  -169,  -169,  -169,    79,   -46,  -169,   -58,
     122,  -168,  -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,
      84,  -169,  -169,  -169,  -169,  -169,  -169,   139,  -169,   142,
    -169,   -41,  -169,  -169,  -169,  -169,  -169,   276,  -169
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     7,    20,    14,    21,    49,    60,    51,
      81,    82,   211,    83,   173,   174,   203,    52,    53,    61,
      62,    63,   176,   205,   220,   230,   179,   208,    64,    93,
      65,   177,   206,   178,   207,   221,   232,   132,   133,   164,
     165,   134,     8,     9,    10,    24,    25,    31,    32
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      74,    50,    79,    35,    95,   -52,     4,    44,   193,    91,
     195,   196,   120,     1,    96,    50,     5,    92,     6,    84,
     -52,   -52,    45,    46,    40,    41,    12,   145,    97,    98,
      11,   115,   100,    13,   118,   129,    47,    16,   -52,    66,
      48,    50,   146,    36,   150,   114,    17,   124,   125,   126,
     127,   128,   225,   110,   111,    67,    68,    69,   147,    18,
     136,   137,   138,   139,   140,   141,   142,   143,   144,    70,
     148,   152,    45,    46,    71,    72,   101,    19,    73,   102,
     103,   104,   105,    23,    22,    26,    47,    29,   101,   160,
      48,   102,   103,   104,   105,    27,    30,   106,   107,   108,
     109,    33,    34,   110,   111,   171,    37,   175,    38,   106,
     107,   108,   109,    43,   163,   110,   111,    42,   191,    54,
      56,    75,   183,   112,   101,   185,    57,   102,   103,   104,
     105,   106,   107,   108,   109,    76,    77,   110,   111,    80,
     197,   192,    85,    78,    59,   106,   107,   108,   109,   102,
     103,   110,   111,   217,    87,    86,   212,   108,   109,   135,
      88,   110,   111,   213,    89,    94,    90,   106,   107,   108,
     109,    99,   101,   110,   111,   102,   103,   104,   105,   113,
     117,   101,   229,   116,   102,   103,   104,   105,   119,   121,
     235,   130,   236,   106,   107,   108,   109,   122,   123,   110,
     111,   131,   106,   107,   108,   109,   151,   154,   110,   111,
     149,   153,   169,   161,   101,   159,   155,   102,   103,   104,
     105,   162,   172,   101,   166,   167,   102,   103,   104,   105,
     170,   180,   181,   163,   187,   106,   107,   108,   109,   188,
     189,   110,   111,   190,   106,   107,   108,   109,   200,   156,
     110,   111,   199,   202,   201,   210,   101,   214,   198,   102,
     103,   104,   105,   204,   218,   101,   215,   216,   102,   103,
     104,   105,   222,   223,   226,   228,   231,   106,   107,   108,
     109,   233,   237,   110,   111,   240,   106,   107,   108,   109,
     241,   219,   110,   111,    15,   242,    28,   224,   101,   194,
     238,   102,   103,   104,   105,   227,   186,   184,    39,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   106,
     107,   108,   109,    44,     0,   110,   111,     0,     0,    55,
       0,    56,     0,   239,     0,     0,     0,    57,    45,    46,
     101,     0,     0,   102,   103,   104,   105,     0,     0,     0,
       0,     0,    58,     0,   101,    59,    48,   102,   103,   104,
     105,   106,   107,   108,   109,     0,     0,   110,   111,     0,
       0,     0,   157,     0,     0,   106,   107,   108,   109,     0,
       0,   110,   111,     0,   101,     0,   209,   102,   103,   104,
     105,     0,     0,     0,     0,     0,   101,     0,     0,   102,
     103,   104,   105,     0,     0,   106,   107,   108,   109,     0,
       0,   110,   111,     0,     0,     0,   234,   106,   107,   108,
     109,     0,     0,   110,   111,   158,   101,     0,     0,   102,
     103,   104,   105,     0,     0,   101,     0,     0,   102,   103,
     104,   105,     0,     0,     0,     0,     0,   106,   107,   108,
     109,     0,     0,   110,   111,   168,   106,   107,   108,   109,
       0,     0,   110,   111,   182,   101,     0,     0,   102,   103,
     104,   105,     0,     0,     0,     0,   102,   103,   104,     0,
       0,     0,     0,     0,     0,     0,   106,   107,   108,   109,
       0,     0,   110,   111,   106,   107,   108,   109,     0,     0,
     110,   111
};

static const yytype_int16 yycheck[] =
{
      41,    36,    48,     9,    62,    17,    13,    17,   176,    36,
     178,   179,    82,    12,    32,    50,     0,    44,    35,    50,
      32,    33,    32,    33,    49,    50,    46,    15,    46,    70,
      43,    77,    73,     3,    80,    93,    46,    14,    50,    11,
      50,    76,    30,    49,   114,    76,    50,    88,    89,    90,
      91,    92,   220,    43,    44,    27,    28,    29,    46,    46,
     101,   102,   103,   104,   105,   106,   107,   108,   109,    41,
     111,   117,    32,    33,    46,    47,    16,     3,    50,    19,
      20,    21,    22,    46,    43,    49,    46,    17,    16,   130,
      50,    19,    20,    21,    22,    46,    54,    37,    38,    39,
      40,    51,     4,    43,    44,   151,    43,   153,    46,    37,
      38,    39,    40,    46,    54,    43,    44,     5,    23,    17,
      25,     6,   163,    51,    16,   166,    31,    19,    20,    21,
      22,    37,    38,    39,    40,    49,    53,    43,    44,     4,
     181,    46,    46,    44,    49,    37,    38,    39,    40,    19,
      20,    43,    44,   211,    48,    46,   202,    39,    40,    51,
      50,    43,    44,   204,    50,    52,    50,    37,    38,    39,
      40,    50,    16,    43,    44,    19,    20,    21,    22,     7,
      16,    16,   223,    45,    19,    20,    21,    22,    52,    46,
     231,    44,   233,    37,    38,    39,    40,    48,    48,    43,
      44,    50,    37,    38,    39,    40,    54,    51,    43,    44,
      50,    50,     8,    51,    16,    52,    51,    19,    20,    21,
      22,    51,    51,    16,    50,    50,    19,    20,    21,    22,
      52,    48,    36,    54,    44,    37,    38,    39,    40,    55,
      51,    43,    44,    46,    37,    38,    39,    40,    45,    51,
      43,    44,    51,    54,    49,    46,    16,    24,    51,    19,
      20,    21,    22,    50,    46,    16,    24,    51,    19,    20,
      21,    22,    49,    10,    23,    31,    50,    37,    38,    39,
      40,    50,    52,    43,    44,    48,    37,    38,    39,    40,
      52,    51,    43,    44,     8,    52,    21,   218,    16,   177,
      51,    19,    20,    21,    22,   221,   167,   165,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    17,    -1,    43,    44,    -1,    -1,    23,
      -1,    25,    -1,    51,    -1,    -1,    -1,    31,    32,    33,
      16,    -1,    -1,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    16,    49,    50,    19,    20,    21,
      22,    37,    38,    39,    40,    -1,    -1,    43,    44,    -1,
      -1,    -1,    48,    -1,    -1,    37,    38,    39,    40,    -1,
      -1,    43,    44,    -1,    16,    -1,    48,    19,    20,    21,
      22,    -1,    -1,    -1,    -1,    -1,    16,    -1,    -1,    19,
      20,    21,    22,    -1,    -1,    37,    38,    39,    40,    -1,
      -1,    43,    44,    -1,    -1,    -1,    48,    37,    38,    39,
      40,    -1,    -1,    43,    44,    45,    16,    -1,    -1,    19,
      20,    21,    22,    -1,    -1,    16,    -1,    -1,    19,    20,
      21,    22,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    -1,    -1,    43,    44,    45,    37,    38,    39,    40,
      -1,    -1,    43,    44,    45,    16,    -1,    -1,    19,    20,
      21,    22,    -1,    -1,    -1,    -1,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,    40,
      -1,    -1,    43,    44,    37,    38,    39,    40,    -1,    -1,
      43,    44
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    12,    57,    58,    13,     0,    35,    59,    98,    99,
     100,    43,    46,     3,    61,    59,    14,    50,    46,     3,
      60,    62,    43,    46,   101,   102,    49,    46,    60,    17,
      54,   103,   104,    51,     4,     9,    49,    43,    46,   103,
      49,    50,     5,    46,    17,    32,    33,    46,    50,    63,
      64,    65,    73,    74,    17,    23,    25,    31,    46,    49,
      64,    75,    76,    77,    84,    86,    11,    27,    28,    29,
      41,    46,    47,    50,    97,     6,    49,    53,    44,    73,
       4,    66,    67,    69,    63,    46,    46,    48,    50,    50,
      50,    36,    44,    85,    52,    75,    32,    46,    97,    50,
      97,    16,    19,    20,    21,    22,    37,    38,    39,    40,
      43,    44,    51,     7,    63,    73,    45,    16,    73,    52,
      66,    46,    48,    48,    97,    97,    97,    97,    97,    75,
      44,    50,    93,    94,    97,    51,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    15,    30,    46,    97,    50,
      66,    54,    73,    50,    51,    51,    51,    48,    45,    52,
      97,    51,    51,    54,    95,    96,    50,    50,    45,     8,
      52,    73,    51,    70,    71,    73,    78,    87,    89,    82,
      48,    36,    45,    97,    95,    97,    93,    44,    55,    51,
      46,    23,    46,    77,    76,    77,    77,    97,    51,    51,
      45,    49,    54,    72,    50,    79,    88,    90,    83,    48,
      46,    68,    73,    97,    24,    24,    51,    75,    46,    51,
      80,    91,    49,    10,    72,    77,    23,    86,    31,    97,
      81,    50,    92,    50,    48,    97,    97,    52,    51,    51,
      48,    52,    52
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    56,    57,    58,    58,    59,    59,    60,    60,    61,
      62,    62,    63,    63,    64,    64,    65,    66,    66,    68,
      67,    69,    70,    70,    71,    72,    72,    73,    73,    73,
      73,    73,    74,    75,    75,    76,    76,    76,    78,    79,
      80,    81,    77,    82,    83,    77,    77,    77,    77,    77,
      85,    84,    87,    88,    86,    89,    90,    91,    92,    86,
      93,    93,    94,    95,    95,    96,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    98,
      98,    99,   100,   101,   101,   102,   103,   103,   104
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     9,     0,     2,     0,     2,     0,    21,
       6,     8,     2,     0,     3,     3,     6,     2,     0,     0,
      12,     2,     1,     0,     3,     4,     0,     3,     1,     1,
       1,     5,     1,     2,     0,     1,     1,     1,     0,     0,
       0,     0,    11,     0,     0,     7,     5,     1,     4,     7,
       0,     4,     0,     0,     7,     0,     0,     0,     0,    11,
       0,     1,     2,     2,     0,     2,     1,     1,     1,     1,
       1,     3,     6,     5,     4,     4,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     3,     3,     6,     1,
       1,     8,     8,     1,     0,     2,     2,     0,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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
    YYNOMEM;
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex ();
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Goal: ImportFunctionOpt MacroDefinitions MainClass TypeDeclarations  */
#line 133 "P1.y"
    {
        string s = "";
        s += string((yyvsp[-3].val));
        s += string((yyvsp[-2].val));
        s += string((yyvsp[-1].val));
        s += string((yyvsp[0].val));
        cout << s;
    }
#line 1595 "y.tab.c"
    break;

  case 3: /* ImportFunctionOpt: IMPORT JAVA '.' UTIL '.' FUNCTION '.' FUNCTION ';'  */
#line 144 "P1.y"
    {
        (yyval.val) = strdup("import java.util.function.Function;\n");
    }
#line 1603 "y.tab.c"
    break;

  case 4: /* ImportFunctionOpt: %empty  */
#line 148 "P1.y"
    { (yyval.val) = strdup(""); }
#line 1609 "y.tab.c"
    break;

  case 5: /* MacroDefinitions: MacroDefinition MacroDefinitions  */
#line 153 "P1.y"
    {
        (yyval.val) = strdup((string((yyvsp[-1].val)) + string((yyvsp[0].val))).c_str());
    }
#line 1617 "y.tab.c"
    break;

  case 6: /* MacroDefinitions: %empty  */
#line 156 "P1.y"
     { (yyval.val) = strdup(""); }
#line 1623 "y.tab.c"
    break;

  case 7: /* TypeDeclarations: TypeDeclaration TypeDeclarations  */
#line 161 "P1.y"
    {
        (yyval.val) = strdup((string((yyvsp[-1].val)) + string((yyvsp[0].val))).c_str());
    }
#line 1631 "y.tab.c"
    break;

  case 8: /* TypeDeclarations: %empty  */
#line 164 "P1.y"
     { (yyval.val) = strdup(""); }
#line 1637 "y.tab.c"
    break;

  case 9: /* MainClass: CLASS IDENTIFIER '{' PUBLIC STATIC VOID MAIN '(' STRING '[' ']' IDENTIFIER ')' '{' PRINT '(' Expression ')' ';' '}' '}'  */
#line 172 "P1.y"
      {
        string s = "class " + string((yyvsp[-19].val)) + " {\n";
        indent++;
        s += indentation(indent) + "public static void main(String[] " + string((yyvsp[-9].val)) + ") {\n";
        indent++;
        s += indentation(indent) + "System.out.println(" + string((yyvsp[-4].val)) + ");\n";
        indent--;
        s += indentation(indent) + "}\n";
        indent--;
        s += "}\n";
        (yyval.val) = strdup(s.c_str());
      }
#line 1654 "y.tab.c"
    break;

  case 10: /* TypeDeclaration: CLASS IDENTIFIER '{' VarDecls MethodDeclarations '}'  */
#line 188 "P1.y"
    {
        string s = "class " + string((yyvsp[-4].val)) + " {\n";
        indent++;
        s += string((yyvsp[-2].val));
        s += string((yyvsp[-1].val));
        indent--;
        s += "}\n";
        (yyval.val) = strdup(s.c_str());
    }
#line 1668 "y.tab.c"
    break;

  case 11: /* TypeDeclaration: CLASS IDENTIFIER EXTENDS IDENTIFIER '{' VarDecls MethodDeclarations '}'  */
#line 198 "P1.y"
    {
        string s = "class " + string((yyvsp[-6].val)) + " extends " + string((yyvsp[-4].val)) + " {\n";
        indent++;
        s += string((yyvsp[-2].val));
        s += string((yyvsp[-1].val));
        indent--;
        s += "}\n";
        (yyval.val) = strdup(s.c_str());
    }
#line 1682 "y.tab.c"
    break;

  case 12: /* VarDecls: VarDecl VarDecls  */
#line 211 "P1.y"
    {
        (yyval.val) = strdup((string((yyvsp[-1].val)) + string((yyvsp[0].val))).c_str());
    }
#line 1690 "y.tab.c"
    break;

  case 13: /* VarDecls: %empty  */
#line 214 "P1.y"
     {(yyval.val) = strdup("");}
#line 1696 "y.tab.c"
    break;

  case 14: /* VarDecl: Type IDENTIFIER ';'  */
#line 219 "P1.y"
    {
        string s = indentation(indent) + string((yyvsp[-2].val)) + " " + string((yyvsp[-1].val)) + ";\n";
        (yyval.val) = strdup(s.c_str());
    }
#line 1705 "y.tab.c"
    break;

  case 15: /* VarDecl: FunctionDecl IDENTIFIER ';'  */
#line 224 "P1.y"
    {
        string s = indentation(indent) + string((yyvsp[-2].val)) + " " + string((yyvsp[-1].val)) + ";\n";
        (yyval.val) = strdup(s.c_str());
    }
#line 1714 "y.tab.c"
    break;

  case 16: /* FunctionDecl: FUNCTION '<' Type ',' Type '>'  */
#line 232 "P1.y"
    {
        string s = "Function<" + string((yyvsp[-3].val)) + ", " + string((yyvsp[-1].val)) + ">";
        (yyval.val) = strdup(s.c_str());
    }
#line 1723 "y.tab.c"
    break;

  case 17: /* MethodDeclarations: MethodDeclaration MethodDeclarations  */
#line 240 "P1.y"
    {
        (yyval.val) = strdup((string((yyvsp[-1].val)) + string((yyvsp[0].val))).c_str());
    }
#line 1731 "y.tab.c"
    break;

  case 18: /* MethodDeclarations: %empty  */
#line 243 "P1.y"
     { (yyval.val) = strdup(""); }
#line 1737 "y.tab.c"
    break;

  case 19: /* $@1: %empty  */
#line 247 "P1.y"
                                                    {indent+= 2;}
#line 1743 "y.tab.c"
    break;

  case 20: /* MethodDeclaration: FunctionType IDENTIFIER '(' OptParams ')' '{' $@1 Statements RETURN Expression ';' '}'  */
#line 248 "P1.y"
    {
        indent-= 2;
        string s = indentation(indent) + string((yyvsp[-11].val)) + string((yyvsp[-10].val)) + "(" + string((yyvsp[-8].val)) + ") {\n";
        s += string((yyvsp[-4].val));
        s += indentation(indent + 2) + "return " + string((yyvsp[-2].val)) + ";\n";
        s += indentation(indent + 1) + "}\n";
        (yyval.val) = strdup(s.c_str());
    }
#line 1756 "y.tab.c"
    break;

  case 21: /* FunctionType: PUBLIC Type  */
#line 260 "P1.y"
    {
        string s = "    public " + string((yyvsp[0].val)) + " ";
        (yyval.val) = strdup(s.c_str());
    }
#line 1765 "y.tab.c"
    break;

  case 22: /* OptParams: ParamList  */
#line 268 "P1.y"
    {
        (yyval.val) = (yyvsp[0].val);
    }
#line 1773 "y.tab.c"
    break;

  case 23: /* OptParams: %empty  */
#line 271 "P1.y"
     {(yyval.val) = strdup("");}
#line 1779 "y.tab.c"
    break;

  case 24: /* ParamList: Type IDENTIFIER ParamRests  */
#line 276 "P1.y"
    {
        string s = string((yyvsp[-2].val)) + " " + string((yyvsp[-1].val)) + string((yyvsp[0].val));
        (yyval.val) = strdup(s.c_str());
    }
#line 1788 "y.tab.c"
    break;

  case 25: /* ParamRests: ',' Type IDENTIFIER ParamRests  */
#line 284 "P1.y"
    {
        string s = ", " + string((yyvsp[-2].val)) + " " + string((yyvsp[-1].val)) + string((yyvsp[0].val));
        (yyval.val) = strdup(s.c_str());
    }
#line 1797 "y.tab.c"
    break;

  case 26: /* ParamRests: %empty  */
#line 288 "P1.y"
      {(yyval.val) = strdup("");}
#line 1803 "y.tab.c"
    break;

  case 27: /* Type: INT '[' ']'  */
#line 292 "P1.y"
                 {(yyval.val) = strdup("int[]");}
#line 1809 "y.tab.c"
    break;

  case 28: /* Type: BOOLEAN  */
#line 293 "P1.y"
             {(yyval.val) = strdup("boolean");}
#line 1815 "y.tab.c"
    break;

  case 29: /* Type: INT  */
#line 294 "P1.y"
         {(yyval.val) = strdup("int");}
#line 1821 "y.tab.c"
    break;

  case 30: /* Type: ClassType  */
#line 295 "P1.y"
               {(yyval.val) = (yyvsp[0].val);}
#line 1827 "y.tab.c"
    break;

  case 31: /* Type: '(' Type ARROW Type ')'  */
#line 296 "P1.y"
                             {
        string s = "(" + string((yyvsp[-3].val)) + " -> " + string((yyvsp[-1].val)) + ")";
        (yyval.val) = strdup(s.c_str());
    }
#line 1836 "y.tab.c"
    break;

  case 32: /* ClassType: IDENTIFIER  */
#line 303 "P1.y"
                { (yyval.val) = (yyvsp[0].val); }
#line 1842 "y.tab.c"
    break;

  case 33: /* Statements: Statement Statements  */
#line 308 "P1.y"
    {
        (yyval.val) = strdup((string((yyvsp[-1].val)) + string((yyvsp[0].val))).c_str());
    }
#line 1850 "y.tab.c"
    break;

  case 34: /* Statements: %empty  */
#line 311 "P1.y"
     { (yyval.val) = strdup(""); }
#line 1856 "y.tab.c"
    break;

  case 35: /* Statement: MatchedStatement  */
#line 315 "P1.y"
                      {(yyval.val) = (yyvsp[0].val);}
#line 1862 "y.tab.c"
    break;

  case 36: /* Statement: UnmatchedStatement  */
#line 316 "P1.y"
                        {(yyval.val) = (yyvsp[0].val);}
#line 1868 "y.tab.c"
    break;

  case 37: /* Statement: VarDecl  */
#line 317 "P1.y"
             {(yyval.val) = (yyvsp[0].val);}
#line 1874 "y.tab.c"
    break;

  case 38: /* $@2: %empty  */
#line 321 "P1.y"
                          {indent++;}
#line 1880 "y.tab.c"
    break;

  case 39: /* $@3: %empty  */
#line 321 "P1.y"
                                                      {indent--;}
#line 1886 "y.tab.c"
    break;

  case 40: /* $@4: %empty  */
#line 321 "P1.y"
                                                                      {indent++;}
#line 1892 "y.tab.c"
    break;

  case 41: /* $@5: %empty  */
#line 321 "P1.y"
                                                                                                  {indent--;}
#line 1898 "y.tab.c"
    break;

  case 42: /* MatchedStatement: IF '(' Expression ')' $@2 MatchedStatement $@3 ELSE $@4 MatchedStatement $@5  */
#line 322 "P1.y"
    {
        string s = indentation(indent) + "if (" + string((yyvsp[-8].val)) + ")\n";
        s += string((yyvsp[-5].val));
        s += indentation(indent) + "else\n";
        s += string((yyvsp[-1].val));
        (yyval.val) = strdup(s.c_str());
    }
#line 1910 "y.tab.c"
    break;

  case 43: /* $@6: %empty  */
#line 329 "P1.y"
                              {indent++;}
#line 1916 "y.tab.c"
    break;

  case 44: /* $@7: %empty  */
#line 329 "P1.y"
                                                          {indent--;}
#line 1922 "y.tab.c"
    break;

  case 45: /* MatchedStatement: WHILE '(' Expression ')' $@6 MatchedStatement $@7  */
#line 330 "P1.y"
    {
        string s = indentation(indent) + "while (" + string((yyvsp[-4].val)) + ")\n";
        s += string((yyvsp[-1].val));
        (yyval.val) = strdup(s.c_str());
    }
#line 1932 "y.tab.c"
    break;

  case 46: /* MatchedStatement: PRINT '(' Expression ')' ';'  */
#line 336 "P1.y"
    {
        string s = indentation(indent) + "System.out.println(" + string((yyvsp[-2].val)) + ");\n";
        (yyval.val) = strdup(s.c_str());
    }
#line 1941 "y.tab.c"
    break;

  case 47: /* MatchedStatement: Block  */
#line 340 "P1.y"
           { (yyval.val) = (yyvsp[0].val); }
#line 1947 "y.tab.c"
    break;

  case 48: /* MatchedStatement: IDENTIFIER '=' Expression ';'  */
#line 342 "P1.y"
    {
        string s = indentation(indent) + string((yyvsp[-3].val)) + " = " + string((yyvsp[-1].val)) + ";\n";
        (yyval.val) = strdup(s.c_str());
    }
#line 1956 "y.tab.c"
    break;

  case 49: /* MatchedStatement: IDENTIFIER '[' Expression ']' '=' Expression ';'  */
#line 347 "P1.y"
    {
        string s = indentation(indent) + string((yyvsp[-6].val)) + "[" + string((yyvsp[-4].val)) + "] = " + string((yyvsp[-1].val)) + ";\n";
        (yyval.val) = strdup(s.c_str());
    }
#line 1965 "y.tab.c"
    break;

  case 50: /* $@8: %empty  */
#line 354 "P1.y"
        {indent++;}
#line 1971 "y.tab.c"
    break;

  case 51: /* Block: '{' $@8 Statements '}'  */
#line 355 "P1.y"
    {
        indent--;
        string s = indentation(indent) + "{\n";
        s += string((yyvsp[-1].val));
        s += indentation(indent) + "}\n";
        (yyval.val) = strdup(s.c_str());
    }
#line 1983 "y.tab.c"
    break;

  case 52: /* $@9: %empty  */
#line 365 "P1.y"
                           {indent++;}
#line 1989 "y.tab.c"
    break;

  case 53: /* $@10: %empty  */
#line 365 "P1.y"
                                                {indent--;}
#line 1995 "y.tab.c"
    break;

  case 54: /* UnmatchedStatement: IF '(' Expression ')' $@9 Statement $@10  */
#line 366 "P1.y"
    {
        string s = indentation(indent) + "if (" + string((yyvsp[-4].val)) + ")\n";
        s += string((yyvsp[-1].val));
        (yyval.val) = strdup(s.c_str());
    }
#line 2005 "y.tab.c"
    break;

  case 55: /* $@11: %empty  */
#line 371 "P1.y"
                           {indent++;}
#line 2011 "y.tab.c"
    break;

  case 56: /* $@12: %empty  */
#line 371 "P1.y"
                                                       {indent--;}
#line 2017 "y.tab.c"
    break;

  case 57: /* $@13: %empty  */
#line 371 "P1.y"
                                                                       {indent++;}
#line 2023 "y.tab.c"
    break;

  case 58: /* $@14: %empty  */
#line 371 "P1.y"
                                                                                                     {indent--;}
#line 2029 "y.tab.c"
    break;

  case 59: /* UnmatchedStatement: IF '(' Expression ')' $@11 MatchedStatement $@12 ELSE $@13 UnmatchedStatement $@14  */
#line 372 "P1.y"
    {
        string s = indentation(indent) + "if (" + string((yyvsp[-8].val)) + ")\n";
        s += string((yyvsp[-5].val));
        s += indentation(indent) + "else\n";
        s += string((yyvsp[-1].val));
        (yyval.val) = strdup(s.c_str());
    }
#line 2041 "y.tab.c"
    break;

  case 60: /* OptExprs: %empty  */
#line 382 "P1.y"
     {
        (yyval.val) = strdup("");
    }
#line 2049 "y.tab.c"
    break;

  case 61: /* OptExprs: ExprList  */
#line 386 "P1.y"
    {
        (yyval.val) = (yyvsp[0].val);
    }
#line 2057 "y.tab.c"
    break;

  case 62: /* ExprList: Expression ExpressionRests  */
#line 393 "P1.y"
    {
        string s = string((yyvsp[-1].val)) + (yyvsp[0].val);
        (yyval.val) = strdup(s.c_str());
    }
#line 2066 "y.tab.c"
    break;

  case 63: /* ExpressionRests: ExpressionRest ExpressionRests  */
#line 401 "P1.y"
    {
        (yyval.val) = strdup((string((yyvsp[-1].val)) + string((yyvsp[0].val))).c_str());
    }
#line 2074 "y.tab.c"
    break;

  case 64: /* ExpressionRests: %empty  */
#line 404 "P1.y"
     { (yyval.val) = strdup(""); }
#line 2080 "y.tab.c"
    break;

  case 65: /* ExpressionRest: ',' Expression  */
#line 409 "P1.y"
    {
        (yyval.val) = strdup((string(", ") + string((yyvsp[0].val))).c_str());
    }
#line 2088 "y.tab.c"
    break;

  case 66: /* Expression: INTEGER_LITERAL  */
#line 415 "P1.y"
                      { (yyval.val) = (yyvsp[0].val); }
#line 2094 "y.tab.c"
    break;

  case 67: /* Expression: TRUE_  */
#line 416 "P1.y"
                      { (yyval.val) = strdup("true"); }
#line 2100 "y.tab.c"
    break;

  case 68: /* Expression: FALSE_  */
#line 417 "P1.y"
                      { (yyval.val) = strdup("false"); }
#line 2106 "y.tab.c"
    break;

  case 69: /* Expression: IDENTIFIER  */
#line 418 "P1.y"
                      { (yyval.val) = (yyvsp[0].val); }
#line 2112 "y.tab.c"
    break;

  case 70: /* Expression: THIS  */
#line 419 "P1.y"
                      { (yyval.val) = strdup("this"); }
#line 2118 "y.tab.c"
    break;

  case 71: /* Expression: Expression '.' LENGTH  */
#line 421 "P1.y"
        { (yyval.val) = strdup((string((yyvsp[-2].val)) + ".length").c_str()); }
#line 2124 "y.tab.c"
    break;

  case 72: /* Expression: Expression '.' IDENTIFIER '(' OptExprs ')'  */
#line 423 "P1.y"
        { (yyval.val) = strdup((string((yyvsp[-5].val)) + "." + string((yyvsp[-3].val)) + "(" + string((yyvsp[-1].val)) + ")").c_str());}
#line 2130 "y.tab.c"
    break;

  case 73: /* Expression: NEW INT '[' Expression ']'  */
#line 425 "P1.y"
        { (yyval.val) = strdup(("new int[" + string((yyvsp[-1].val)) + "]").c_str()); }
#line 2136 "y.tab.c"
    break;

  case 74: /* Expression: NEW IDENTIFIER '(' ')'  */
#line 427 "P1.y"
        { (yyval.val) = strdup(("new " + string((yyvsp[-2].val)) + "()").c_str()); }
#line 2142 "y.tab.c"
    break;

  case 75: /* Expression: Expression '[' Expression ']'  */
#line 429 "P1.y"
        { (yyval.val) = strdup((string((yyvsp[-3].val)) + "[" + string((yyvsp[-1].val)) + "]").c_str()); }
#line 2148 "y.tab.c"
    break;

  case 76: /* Expression: '!' Expression  */
#line 431 "P1.y"
        { (yyval.val) = strdup(("!" + string((yyvsp[0].val))).c_str()); }
#line 2154 "y.tab.c"
    break;

  case 77: /* Expression: Expression '*' Expression  */
#line 433 "P1.y"
        { (yyval.val) = strdup((string((yyvsp[-2].val)) + " * " + string((yyvsp[0].val))).c_str());}
#line 2160 "y.tab.c"
    break;

  case 78: /* Expression: Expression '/' Expression  */
#line 435 "P1.y"
        { (yyval.val) = strdup((string((yyvsp[-2].val)) + " / " + string((yyvsp[0].val))).c_str()); }
#line 2166 "y.tab.c"
    break;

  case 79: /* Expression: Expression '+' Expression  */
#line 437 "P1.y"
        { (yyval.val) = strdup((string((yyvsp[-2].val)) + " + " + string((yyvsp[0].val))).c_str()); }
#line 2172 "y.tab.c"
    break;

  case 80: /* Expression: Expression '-' Expression  */
#line 439 "P1.y"
        { (yyval.val) = strdup((string((yyvsp[-2].val)) + " - " + string((yyvsp[0].val))).c_str()); }
#line 2178 "y.tab.c"
    break;

  case 81: /* Expression: Expression LEQ Expression  */
#line 441 "P1.y"
        { (yyval.val) = strdup((string((yyvsp[-2].val)) + " <= " + string((yyvsp[0].val))).c_str()); }
#line 2184 "y.tab.c"
    break;

  case 82: /* Expression: Expression NEQ Expression  */
#line 443 "P1.y"
        { (yyval.val) = strdup((string((yyvsp[-2].val)) + " != " + string((yyvsp[0].val))).c_str()); }
#line 2190 "y.tab.c"
    break;

  case 83: /* Expression: Expression AND Expression  */
#line 445 "P1.y"
        { (yyval.val) = strdup((string((yyvsp[-2].val)) + " && " + string((yyvsp[0].val))).c_str()); }
#line 2196 "y.tab.c"
    break;

  case 84: /* Expression: Expression OR Expression  */
#line 447 "P1.y"
        { (yyval.val) = strdup((string((yyvsp[-2].val)) + " || " + string((yyvsp[0].val))).c_str()); }
#line 2202 "y.tab.c"
    break;

  case 85: /* Expression: IDENTIFIER '(' OptExprs ')'  */
#line 449 "P1.y"
    {
        try {
            (yyval.val) = strdup(expandMacroCallCommon((yyvsp[-3].val), (yyvsp[-1].val), true).c_str());
        } catch (const runtime_error& e) {
            yyerror(e.what());
            YYERROR;
        }
    }
#line 2215 "y.tab.c"
    break;

  case 86: /* Expression: '(' Expression ')'  */
#line 458 "P1.y"
        { (yyval.val) = strdup(("(" + string((yyvsp[-1].val)) + ")").c_str()); }
#line 2221 "y.tab.c"
    break;

  case 87: /* Expression: Expression ARROW Expression  */
#line 460 "P1.y"
        { (yyval.val) = strdup((string((yyvsp[-2].val)) + " -> " + string((yyvsp[0].val))).c_str());}
#line 2227 "y.tab.c"
    break;

  case 88: /* Expression: Expression '.' APPLY '(' Expression ')'  */
#line 462 "P1.y"
        { (yyval.val) = strdup((string((yyvsp[-5].val)) + ".apply(" + string((yyvsp[-1].val)) + ")").c_str()); }
#line 2233 "y.tab.c"
    break;

  case 91: /* MacroDefExpression: DEFINE IDENTIFIER '(' OptIdList ')' '(' Expression ')'  */
#line 472 "P1.y"
    {
        string name((yyvsp[-6].val) ? (yyvsp[-6].val) : "");
        string paramsStr((yyvsp[-4].val) ? (yyvsp[-4].val) : "");
        string body((yyvsp[-1].val) ? (yyvsp[-1].val) : "");
        vector<string> params = splitParamsCSV(paramsStr);
        set<string> paramSet(params.begin(), params.end());
        if(paramSet.size() != params.size()){
            yyerror("Duplicate parameter in macro definition");
            YYERROR;
        }

        Macro macro;
        macro.isExpression = true;
        macro.params = params;
        macro.body = body;
        macroTable[name] = macro;
        (yyval.val) = strdup("");
    }
#line 2256 "y.tab.c"
    break;

  case 92: /* MacroDefStatement: DEFINE IDENTIFIER '(' OptIdList ')' '{' Statements '}'  */
#line 494 "P1.y"
    {
        string name((yyvsp[-6].val) ? (yyvsp[-6].val) : "");
        string paramsStr((yyvsp[-4].val) ? (yyvsp[-4].val) : "");
        string body((yyvsp[-1].val) ? (yyvsp[-1].val) : "");
        vector<string> params = splitParamsCSV(paramsStr);
        set<string> paramSet(params.begin(), params.end());
        if(paramSet.size() != params.size()){
            yyerror("Duplicate parameter in macro definition");
            YYERROR;
        }

        Macro macro;
        macro.isExpression = false;
        macro.params = params;
        macro.body = body;
        macroTable[name] = macro;
        (yyval.val) = strdup("");
    }
#line 2279 "y.tab.c"
    break;

  case 93: /* OptIdList: IdList  */
#line 515 "P1.y"
          {(yyval.val) = (yyvsp[0].val); }
#line 2285 "y.tab.c"
    break;

  case 94: /* OptIdList: %empty  */
#line 516 "P1.y"
     { (yyval.val) = strdup(""); }
#line 2291 "y.tab.c"
    break;

  case 95: /* IdList: IDENTIFIER IdRests  */
#line 520 "P1.y"
                      {(yyval.val) = strdup((string((yyvsp[-1].val)) + string((yyvsp[0].val))).c_str()); }
#line 2297 "y.tab.c"
    break;

  case 96: /* IdRests: IdRest IdRests  */
#line 524 "P1.y"
                  {(yyval.val) = strdup((string((yyvsp[-1].val)) + string((yyvsp[0].val))).c_str()); }
#line 2303 "y.tab.c"
    break;

  case 97: /* IdRests: %empty  */
#line 525 "P1.y"
     { (yyval.val) = strdup(""); }
#line 2309 "y.tab.c"
    break;

  case 98: /* IdRest: ',' IDENTIFIER  */
#line 530 "P1.y"
    {
        (yyval.val) = strdup((string(", ") + string((yyvsp[0].val))).c_str());
    }
#line 2317 "y.tab.c"
    break;


#line 2321 "y.tab.c"

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
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 535 "P1.y"


int main(void) {
    return yyparse();
}
