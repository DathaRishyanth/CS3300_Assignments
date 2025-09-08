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

void yyerror(const char *s){
    printf("// Failed to parse macrojava code.");
    exit(1);
}
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
    vector<string> placeholders;
    for (size_t i = 0; i < params.size(); ++i) {
        string p_holder = "__MACRO_PARAM_" + to_string(i) + "__";
        placeholders.push_back(p_holder);
        regex re("\\b" + params[i] + "\\b");
        res = regex_replace(res, re, p_holder);
    }

    for (size_t i = 0; i < placeholders.size(); ++i) {
        regex re(placeholders[i]);
        string wrapped = '(' + args[i] + ')';
        res = regex_replace(res, re, wrapped);
    }

    return res;
}


static string reindentTo(const string& s, int level){
    string ind = indentation(level);
    string out;
    bool atLineStart = true;
    for(char c : s){
        if(atLineStart) out += ind;
        out += c;
        atLineStart = (c == '\n');
    }
    return out;
}

static string expandMacroCallCommon(const char* nameC, const char* argsStrC, bool expectExpression){
    string name = nameC ? nameC : "";
    string argsStr = argsStrC ? argsStrC : "";

    auto it = macroTable.find(name);
    if(it == macroTable.end())
    {
        yyerror("error");
    }

    const Macro& macro = it->second;
    if(expectExpression && !macro.isExpression)
        yyerror("error");
    if(!expectExpression && macro.isExpression)
        yyerror("error");
    vector<string> args = parseArgs(argsStr);
    if(args.size() != macro.params.size()){
        yyerror("error");
    }
    return substituteParams(macro.body, macro.params, args);
}


int yylex(void);

#line 183 "P1.tab.c"

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

#include "P1.tab.h"
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
  YYSYMBOL_FUNCTION = 16,                  /* FUNCTION  */
  YYSYMBOL_FUNCTION_ = 17,                 /* FUNCTION_  */
  YYSYMBOL_ARROW = 18,                     /* ARROW  */
  YYSYMBOL_EQ = 19,                        /* EQ  */
  YYSYMBOL_NEQ = 20,                       /* NEQ  */
  YYSYMBOL_LEQ = 21,                       /* LEQ  */
  YYSYMBOL_AND = 22,                       /* AND  */
  YYSYMBOL_OR = 23,                        /* OR  */
  YYSYMBOL_IF = 24,                        /* IF  */
  YYSYMBOL_ELSE = 25,                      /* ELSE  */
  YYSYMBOL_WHILE = 26,                     /* WHILE  */
  YYSYMBOL_DO = 27,                        /* DO  */
  YYSYMBOL_TRUE_ = 28,                     /* TRUE_  */
  YYSYMBOL_FALSE_ = 29,                    /* FALSE_  */
  YYSYMBOL_THIS = 30,                      /* THIS  */
  YYSYMBOL_LENGTH = 31,                    /* LENGTH  */
  YYSYMBOL_PRINT = 32,                     /* PRINT  */
  YYSYMBOL_INT = 33,                       /* INT  */
  YYSYMBOL_BOOLEAN = 34,                   /* BOOLEAN  */
  YYSYMBOL_IFX = 35,                       /* IFX  */
  YYSYMBOL_DEFINE = 36,                    /* DEFINE  */
  YYSYMBOL_37_ = 37,                       /* '='  */
  YYSYMBOL_38_ = 38,                       /* '+'  */
  YYSYMBOL_39_ = 39,                       /* '-'  */
  YYSYMBOL_40_ = 40,                       /* '*'  */
  YYSYMBOL_41_ = 41,                       /* '/'  */
  YYSYMBOL_42_ = 42,                       /* '!'  */
  YYSYMBOL_UMINUS = 43,                    /* UMINUS  */
  YYSYMBOL_44_ = 44,                       /* '.'  */
  YYSYMBOL_45_ = 45,                       /* '['  */
  YYSYMBOL_46_ = 46,                       /* ']'  */
  YYSYMBOL_IDENTIFIER = 47,                /* IDENTIFIER  */
  YYSYMBOL_INTEGER_LITERAL = 48,           /* INTEGER_LITERAL  */
  YYSYMBOL_49_ = 49,                       /* ';'  */
  YYSYMBOL_50_ = 50,                       /* '{'  */
  YYSYMBOL_51_ = 51,                       /* '('  */
  YYSYMBOL_52_ = 52,                       /* ')'  */
  YYSYMBOL_53_ = 53,                       /* '}'  */
  YYSYMBOL_54_ = 54,                       /* '<'  */
  YYSYMBOL_55_ = 55,                       /* ','  */
  YYSYMBOL_56_ = 56,                       /* '>'  */
  YYSYMBOL_YYACCEPT = 57,                  /* $accept  */
  YYSYMBOL_Goal = 58,                      /* Goal  */
  YYSYMBOL_ImportFunctionOpt = 59,         /* ImportFunctionOpt  */
  YYSYMBOL_MacroDefinitions = 60,          /* MacroDefinitions  */
  YYSYMBOL_TypeDeclarations = 61,          /* TypeDeclarations  */
  YYSYMBOL_MainClass = 62,                 /* MainClass  */
  YYSYMBOL_TypeDeclaration = 63,           /* TypeDeclaration  */
  YYSYMBOL_VarDecls = 64,                  /* VarDecls  */
  YYSYMBOL_VarDecl = 65,                   /* VarDecl  */
  YYSYMBOL_FunctionDecl = 66,              /* FunctionDecl  */
  YYSYMBOL_MethodDeclarations = 67,        /* MethodDeclarations  */
  YYSYMBOL_MethodDeclaration = 68,         /* MethodDeclaration  */
  YYSYMBOL_69_1 = 69,                      /* $@1  */
  YYSYMBOL_FunctionType = 70,              /* FunctionType  */
  YYSYMBOL_OptParams = 71,                 /* OptParams  */
  YYSYMBOL_ParamList = 72,                 /* ParamList  */
  YYSYMBOL_ParamRests = 73,                /* ParamRests  */
  YYSYMBOL_Type = 74,                      /* Type  */
  YYSYMBOL_Statements = 75,                /* Statements  */
  YYSYMBOL_Statement = 76,                 /* Statement  */
  YYSYMBOL_MatchedStatement = 77,          /* MatchedStatement  */
  YYSYMBOL_Block = 78,                     /* Block  */
  YYSYMBOL_79_2 = 79,                      /* $@2  */
  YYSYMBOL_UnmatchedStatement = 80,        /* UnmatchedStatement  */
  YYSYMBOL_OptExprs = 81,                  /* OptExprs  */
  YYSYMBOL_ExprList = 82,                  /* ExprList  */
  YYSYMBOL_ExpressionRests = 83,           /* ExpressionRests  */
  YYSYMBOL_ExpressionRest = 84,            /* ExpressionRest  */
  YYSYMBOL_Expression = 85,                /* Expression  */
  YYSYMBOL_PrimaryExpression = 86,         /* PrimaryExpression  */
  YYSYMBOL_MacroDefinition = 87,           /* MacroDefinition  */
  YYSYMBOL_MacroDefExpression = 88,        /* MacroDefExpression  */
  YYSYMBOL_MacroDefStatement = 89,         /* MacroDefStatement  */
  YYSYMBOL_OptIdList = 90,                 /* OptIdList  */
  YYSYMBOL_IdList = 91,                    /* IdList  */
  YYSYMBOL_IdRests = 92,                   /* IdRests  */
  YYSYMBOL_IdRest = 93                     /* IdRest  */
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
#define YYLAST   443

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  229

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


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
       2,     2,     2,    42,     2,     2,     2,     2,     2,     2,
      51,    52,    40,    38,    55,    39,    44,    41,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    49,
      54,    37,    56,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    45,     2,    46,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    50,     2,    53,     2,     2,     2,     2,
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
      35,    36,    43,    47,    48
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   159,   159,   170,   175,   179,   183,   187,   191,   195,
     214,   224,   237,   241,   245,   250,   258,   266,   270,   274,
     274,   286,   294,   298,   302,   310,   315,   319,   320,   321,
     322,   323,   332,   336,   340,   341,   342,   346,   355,   363,
     369,   370,   376,   382,   398,   398,   409,   418,   430,   433,
     440,   448,   452,   456,   463,   465,   467,   469,   471,   473,
     475,   477,   479,   481,   483,   485,   495,   497,   502,   503,
     504,   505,   506,   507,   509,   511,   513,   518,   519,   523,
     545,   567,   568,   572,   576,   577,   581
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
  "JAVA", "UTIL", "APPLY", "FUNCTION", "FUNCTION_", "ARROW", "EQ", "NEQ",
  "LEQ", "AND", "OR", "IF", "ELSE", "WHILE", "DO", "TRUE_", "FALSE_",
  "THIS", "LENGTH", "PRINT", "INT", "BOOLEAN", "IFX", "DEFINE", "'='",
  "'+'", "'-'", "'*'", "'/'", "'!'", "UMINUS", "'.'", "'['", "']'",
  "IDENTIFIER", "INTEGER_LITERAL", "';'", "'{'", "'('", "')'", "'}'",
  "'<'", "','", "'>'", "$accept", "Goal", "ImportFunctionOpt",
  "MacroDefinitions", "TypeDeclarations", "MainClass", "TypeDeclaration",
  "VarDecls", "VarDecl", "FunctionDecl", "MethodDeclarations",
  "MethodDeclaration", "$@1", "FunctionType", "OptParams", "ParamList",
  "ParamRests", "Type", "Statements", "Statement", "MatchedStatement",
  "Block", "$@2", "UnmatchedStatement", "OptExprs", "ExprList",
  "ExpressionRests", "ExpressionRest", "Expression", "PrimaryExpression",
  "MacroDefinition", "MacroDefExpression", "MacroDefStatement",
  "OptIdList", "IdList", "IdRests", "IdRest", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-141)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -4,     4,    14,    20,   -12,  -141,    12,    57,    20,  -141,
    -141,    58,    24,    29,    76,  -141,    44,    42,    47,    45,
    -141,    76,    93,    56,    67,  -141,   108,    -7,  -141,    74,
      75,  -141,    56,   -31,   116,    81,   -10,   113,  -141,  -141,
     100,    10,   124,    85,    82,    92,  -141,  -141,   -22,   134,
     -10,    97,    98,   103,   102,   110,   111,   -15,  -141,  -141,
     101,   100,  -141,  -141,  -141,   -20,  -141,  -141,  -141,    10,
     118,  -141,    66,   119,  -141,   163,   -10,   125,   127,   156,
     -22,   123,   134,   130,  -141,   129,   132,  -141,    10,    10,
      10,    10,    10,    10,   100,  -141,  -141,   137,   128,     1,
      10,     2,   145,    10,    10,    10,    10,    10,    10,    10,
      10,   -21,    10,  -141,   136,   134,   133,  -141,   -22,  -141,
    -141,  -141,   144,  -141,  -141,   171,   180,   206,   250,   322,
     146,  -141,    60,   143,    10,   147,   152,   187,  -141,    46,
      46,   387,   398,    62,    62,     1,     1,  -141,   155,   331,
     199,   160,   161,   162,   -22,   100,    99,   168,  -141,   185,
     181,    10,  -141,   176,  -141,   358,  -141,  -141,    10,    10,
    -141,   188,  -141,   178,  -141,   189,  -141,   192,  -141,   217,
     197,   -15,  -141,  -141,    10,  -141,   372,  -141,  -141,   372,
     191,   194,  -141,   202,   210,   359,    10,   280,  -141,   219,
    -141,   -22,  -141,  -141,  -141,   215,  -141,   205,   100,   221,
      99,   224,   239,   210,   244,   243,    10,  -141,    99,   225,
     292,    10,   230,   241,  -141,   228,   231,   234,  -141
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     6,     0,     1,     0,     0,     6,    77,
      78,     0,     0,     0,     8,     5,     0,    82,     0,     0,
       2,     8,     0,    85,     0,    81,     0,     0,     7,     0,
       0,    83,    85,     0,     0,     0,    13,     0,    86,    84,
      33,     0,     0,     0,     0,    29,    28,    30,     0,    18,
      13,     0,     0,     0,     0,     0,     0,    30,    44,    36,
       0,    33,    34,    40,    35,     0,    69,    70,    72,     0,
      71,    68,     0,     0,    67,     0,    13,     0,     0,     0,
       0,     0,    18,     0,    12,     0,     0,     3,     0,     0,
       0,     0,     0,    48,    33,    80,    32,     0,     0,    75,
      48,    71,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,     0,    18,     0,    27,     0,    21,
      10,    17,     0,    15,    14,     0,     0,     0,     0,     0,
       0,    49,    52,     0,     0,     0,     0,     0,    76,    56,
      57,    55,    54,    58,    59,    60,    61,    63,     0,     0,
       0,     0,     0,     0,    23,     0,     0,     0,    41,     0,
       0,     0,    50,    52,    45,     0,    74,    65,     0,    48,
      62,     0,    11,     0,    31,     0,    22,     0,    46,    34,
       0,     0,    38,    39,     0,    43,    53,    51,    73,    66,
       0,     0,    16,     0,    26,     0,     0,     0,    64,     0,
      19,     0,    24,    37,    47,     0,    42,     0,    33,     0,
       0,     0,     0,    26,     0,     0,     0,    25,     0,     0,
       0,     0,     0,     0,    20,     0,     0,     0,     9
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -141,  -141,  -141,   270,   271,  -141,  -141,   -43,   -32,  -141,
     -73,  -141,  -141,  -141,  -141,  -141,    83,   -45,   -60,   142,
    -140,  -141,  -141,   109,   -95,  -141,   135,  -141,   -41,  -141,
    -141,  -141,  -141,  -141,  -141,   273,  -141
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     7,    20,    14,    21,    49,    59,    51,
      81,    82,   208,    83,   175,   176,   202,    52,    60,    61,
      62,    63,    94,    64,   130,   131,   162,   163,   132,    74,
       8,     9,    10,    24,    25,    31,    32
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      73,    96,    35,    79,    50,   136,    44,    84,     1,   121,
     147,    45,    46,    97,     5,   179,   182,     4,    50,    40,
      41,    65,    91,    45,    46,    47,   148,    98,    99,    48,
      92,   102,    11,   115,   133,   119,    93,    47,    66,    67,
      68,    48,   151,    36,    50,   111,   112,   125,   126,   127,
     128,   129,    69,   100,   137,   203,     6,    70,    71,    12,
      13,    72,   139,   140,   141,   142,   143,   144,   145,   146,
     214,   149,    16,   153,   190,    17,    18,    65,   203,    19,
     103,   104,   105,   106,   107,   108,   109,   110,    22,    23,
     111,   112,    27,   165,    66,    67,    68,    26,   107,   108,
     109,   110,   109,   110,   111,   112,   111,   112,    69,   177,
      29,    30,    34,   101,    71,   161,    44,    72,    37,    33,
     186,    42,    38,   180,    54,    55,    55,   189,    43,    53,
      75,    56,    56,    45,    46,    76,    77,    78,    80,   103,
     104,   105,   106,   197,    85,    86,   181,    57,   212,    58,
      58,    48,    87,    88,    95,   205,   209,   107,   108,   109,
     110,    89,    90,   111,   112,   103,   104,   105,   106,   100,
     114,   113,   116,   117,   118,   220,   120,   122,   123,   135,
     223,   124,   134,   107,   108,   109,   110,   150,   152,   111,
     112,   103,   104,   105,   106,   154,   164,   138,   160,   166,
     103,   104,   105,   106,   167,   168,   169,   171,   173,   107,
     108,   109,   110,   172,   174,   111,   112,   183,   107,   108,
     109,   110,   184,   155,   111,   112,   103,   104,   105,   106,
     185,   161,   156,   191,   192,   103,   104,   105,   106,   194,
     199,   193,   195,   198,   107,   108,   109,   110,   196,   216,
     111,   112,   200,   107,   108,   109,   110,   211,   157,   111,
     112,   103,   104,   105,   106,   201,   207,   210,   213,   218,
     103,   104,   105,   106,   215,   219,   221,   226,    15,   107,
     108,   109,   110,   224,   227,   111,   112,   228,   107,   108,
     109,   110,    28,   225,   111,   112,   217,   178,   187,   158,
     103,   104,   105,   106,   204,    39,     0,     0,     0,     0,
       0,     0,   103,   104,   105,   106,     0,     0,   107,   108,
     109,   110,     0,     0,   111,   112,     0,     0,     0,   206,
     107,   108,   109,   110,     0,     0,   111,   112,     0,     0,
       0,   222,   103,   104,   105,   106,     0,     0,     0,     0,
       0,   103,   104,   105,   106,     0,     0,     0,     0,     0,
     107,   108,   109,   110,     0,     0,   111,   112,   159,   107,
     108,   109,   110,     0,     0,   111,   112,   170,   103,   104,
     105,   106,     0,    54,     0,    55,     0,     0,     0,     0,
       0,    56,   103,   104,   105,   106,   107,   108,   109,   110,
       0,     0,   111,   112,   188,     0,   181,   103,   104,    58,
     107,   108,   109,   110,     0,     0,   111,   112,   103,   104,
     105,     0,     0,     0,     0,   107,   108,   109,   110,     0,
       0,   111,   112,     0,     0,     0,   107,   108,   109,   110,
       0,     0,   111,   112
};

static const yytype_int16 yycheck[] =
{
      41,    61,     9,    48,    36,   100,    16,    50,    12,    82,
      31,    33,    34,    33,     0,   155,   156,    13,    50,    50,
      51,    11,    37,    33,    34,    47,    47,    47,    69,    51,
      45,    72,    44,    76,    94,    80,    51,    47,    28,    29,
      30,    51,   115,    50,    76,    44,    45,    88,    89,    90,
      91,    92,    42,    51,    52,   195,    36,    47,    48,    47,
       3,    51,   103,   104,   105,   106,   107,   108,   109,   110,
     210,   112,    14,   118,   169,    51,    47,    11,   218,     3,
      20,    21,    22,    23,    38,    39,    40,    41,    44,    47,
      44,    45,    47,   134,    28,    29,    30,    50,    38,    39,
      40,    41,    40,    41,    44,    45,    44,    45,    42,   154,
      17,    55,     4,    47,    48,    55,    16,    51,    44,    52,
     161,     5,    47,    24,    24,    26,    26,   168,    47,    16,
       6,    32,    32,    33,    34,    50,    54,    45,     4,    20,
      21,    22,    23,   184,    47,    47,    47,    47,   208,    50,
      50,    51,    49,    51,    53,   196,   201,    38,    39,    40,
      41,    51,    51,    44,    45,    20,    21,    22,    23,    51,
       7,    52,    47,    46,    18,   216,    53,    47,    49,    51,
     221,    49,    45,    38,    39,    40,    41,    51,    55,    44,
      45,    20,    21,    22,    23,    51,    53,    52,    52,    52,
      20,    21,    22,    23,    52,    18,    51,     8,    47,    38,
      39,    40,    41,    53,    52,    44,    45,    49,    38,    39,
      40,    41,    37,    52,    44,    45,    20,    21,    22,    23,
      49,    55,    52,    45,    56,    20,    21,    22,    23,    47,
      46,    52,    25,    52,    38,    39,    40,    41,    51,    10,
      44,    45,    50,    38,    39,    40,    41,    52,    52,    44,
      45,    20,    21,    22,    23,    55,    47,    52,    47,    25,
      20,    21,    22,    23,    50,    32,    51,    49,     8,    38,
      39,    40,    41,    53,    53,    44,    45,    53,    38,    39,
      40,    41,    21,    52,    44,    45,   213,   155,   163,    49,
      20,    21,    22,    23,   195,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    21,    22,    23,    -1,    -1,    38,    39,
      40,    41,    -1,    -1,    44,    45,    -1,    -1,    -1,    49,
      38,    39,    40,    41,    -1,    -1,    44,    45,    -1,    -1,
      -1,    49,    20,    21,    22,    23,    -1,    -1,    -1,    -1,
      -1,    20,    21,    22,    23,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    41,    -1,    -1,    44,    45,    46,    38,
      39,    40,    41,    -1,    -1,    44,    45,    46,    20,    21,
      22,    23,    -1,    24,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    32,    20,    21,    22,    23,    38,    39,    40,    41,
      -1,    -1,    44,    45,    46,    -1,    47,    20,    21,    50,
      38,    39,    40,    41,    -1,    -1,    44,    45,    20,    21,
      22,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,
      -1,    44,    45,    -1,    -1,    -1,    38,    39,    40,    41,
      -1,    -1,    44,    45
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    12,    58,    59,    13,     0,    36,    60,    87,    88,
      89,    44,    47,     3,    62,    60,    14,    51,    47,     3,
      61,    63,    44,    47,    90,    91,    50,    47,    61,    17,
      55,    92,    93,    52,     4,     9,    50,    44,    47,    92,
      50,    51,     5,    47,    16,    33,    34,    47,    51,    64,
      65,    66,    74,    16,    24,    26,    32,    47,    50,    65,
      75,    76,    77,    78,    80,    11,    28,    29,    30,    42,
      47,    48,    51,    85,    86,     6,    50,    54,    45,    74,
       4,    67,    68,    70,    64,    47,    47,    49,    51,    51,
      51,    37,    45,    51,    79,    53,    75,    33,    47,    85,
      51,    47,    85,    20,    21,    22,    23,    38,    39,    40,
      41,    44,    45,    52,     7,    64,    47,    46,    18,    74,
      53,    67,    47,    49,    49,    85,    85,    85,    85,    85,
      81,    82,    85,    75,    45,    51,    81,    52,    52,    85,
      85,    85,    85,    85,    85,    85,    85,    31,    47,    85,
      51,    67,    55,    74,    51,    52,    52,    52,    49,    46,
      52,    55,    83,    84,    53,    85,    52,    52,    18,    51,
      46,     8,    53,    47,    52,    71,    72,    74,    76,    77,
      24,    47,    77,    49,    37,    49,    85,    83,    46,    85,
      81,    45,    56,    52,    47,    25,    51,    85,    52,    46,
      50,    55,    73,    77,    80,    85,    49,    47,    69,    74,
      52,    52,    75,    47,    77,    50,    10,    73,    25,    32,
      85,    51,    49,    85,    53,    52,    49,    53,    53
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    57,    58,    59,    59,    60,    60,    61,    61,    62,
      63,    63,    64,    64,    65,    65,    66,    67,    67,    69,
      68,    70,    71,    71,    72,    73,    73,    74,    74,    74,
      74,    74,    75,    75,    76,    76,    76,    77,    77,    77,
      77,    77,    77,    77,    79,    78,    80,    80,    81,    81,
      82,    83,    83,    84,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    87,    87,    88,
      89,    90,    90,    91,    92,    92,    93
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     9,     0,     2,     0,     2,     0,    21,
       6,     8,     2,     0,     3,     3,     6,     2,     0,     0,
      12,     2,     1,     0,     3,     4,     0,     3,     1,     1,
       1,     5,     2,     0,     1,     1,     1,     7,     5,     5,
       1,     4,     7,     5,     0,     4,     5,     7,     0,     1,
       2,     2,     0,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     4,     3,     6,     4,     5,     1,     1,     1,
       1,     1,     1,     5,     4,     2,     3,     1,     1,     8,
       8,     1,     0,     2,     2,     0,     2
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
#line 160 "P1.y"
    {
        string s = "";
        s += string((yyvsp[-3].val));
        s += string((yyvsp[-2].val));
        s += string((yyvsp[-1].val));
        s += string((yyvsp[0].val));
        cout << s;
    }
#line 1458 "P1.tab.c"
    break;

  case 3: /* ImportFunctionOpt: IMPORT JAVA '.' UTIL '.' FUNCTION_ '.' FUNCTION ';'  */
#line 171 "P1.y"
    {
        (yyval.val) = strdup("import java.util.function.Function;\n");
    }
#line 1466 "P1.tab.c"
    break;

  case 4: /* ImportFunctionOpt: %empty  */
#line 175 "P1.y"
    { (yyval.val) = strdup(""); }
#line 1472 "P1.tab.c"
    break;

  case 5: /* MacroDefinitions: MacroDefinition MacroDefinitions  */
#line 180 "P1.y"
    {
        (yyval.val) = strdup((string((yyvsp[-1].val)) + string((yyvsp[0].val))).c_str());
    }
#line 1480 "P1.tab.c"
    break;

  case 6: /* MacroDefinitions: %empty  */
#line 183 "P1.y"
     { (yyval.val) = strdup(""); }
#line 1486 "P1.tab.c"
    break;

  case 7: /* TypeDeclarations: TypeDeclaration TypeDeclarations  */
#line 188 "P1.y"
    {
        (yyval.val) = strdup((string((yyvsp[-1].val)) + string((yyvsp[0].val))).c_str());
    }
#line 1494 "P1.tab.c"
    break;

  case 8: /* TypeDeclarations: %empty  */
#line 191 "P1.y"
     { (yyval.val) = strdup(""); }
#line 1500 "P1.tab.c"
    break;

  case 9: /* MainClass: CLASS IDENTIFIER '{' PUBLIC STATIC VOID MAIN '(' STRING '[' ']' IDENTIFIER ')' '{' PRINT '(' Expression ')' ';' '}' '}'  */
#line 199 "P1.y"
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
#line 1517 "P1.tab.c"
    break;

  case 10: /* TypeDeclaration: CLASS IDENTIFIER '{' VarDecls MethodDeclarations '}'  */
#line 215 "P1.y"
    {
        string s = "class " + string((yyvsp[-4].val)) + " {\n";
        indent++;
        s += string((yyvsp[-2].val));
        s += string((yyvsp[-1].val));
        indent--;
        s += "}\n";
        (yyval.val) = strdup(s.c_str());
    }
#line 1531 "P1.tab.c"
    break;

  case 11: /* TypeDeclaration: CLASS IDENTIFIER EXTENDS IDENTIFIER '{' VarDecls MethodDeclarations '}'  */
#line 225 "P1.y"
    {
        string s = "class " + string((yyvsp[-6].val)) + " extends " + string((yyvsp[-4].val)) + " {\n";
        indent++;
        s += string((yyvsp[-2].val));
        s += string((yyvsp[-1].val));
        indent--;
        s += "}\n";
        (yyval.val) = strdup(s.c_str());
    }
#line 1545 "P1.tab.c"
    break;

  case 12: /* VarDecls: VarDecl VarDecls  */
#line 238 "P1.y"
    {
        (yyval.val) = strdup((string((yyvsp[-1].val)) + string((yyvsp[0].val))).c_str());
    }
#line 1553 "P1.tab.c"
    break;

  case 13: /* VarDecls: %empty  */
#line 241 "P1.y"
     {(yyval.val) = strdup("");}
#line 1559 "P1.tab.c"
    break;

  case 14: /* VarDecl: Type IDENTIFIER ';'  */
#line 246 "P1.y"
    {
        string s = indentation(indent) + string((yyvsp[-2].val)) + " " + string((yyvsp[-1].val)) + ";\n";
        (yyval.val) = strdup(s.c_str());
    }
#line 1568 "P1.tab.c"
    break;

  case 15: /* VarDecl: FunctionDecl IDENTIFIER ';'  */
#line 251 "P1.y"
    {
        string s = indentation(indent) + string((yyvsp[-2].val)) + " " + string((yyvsp[-1].val)) + ";\n";
        (yyval.val) = strdup(s.c_str());
    }
#line 1577 "P1.tab.c"
    break;

  case 16: /* FunctionDecl: FUNCTION '<' IDENTIFIER ',' IDENTIFIER '>'  */
#line 259 "P1.y"
    {
        string s = "Function <" + string((yyvsp[-3].val)) + ", " + string((yyvsp[-1].val)) + ">";
        (yyval.val) = strdup(s.c_str());
    }
#line 1586 "P1.tab.c"
    break;

  case 17: /* MethodDeclarations: MethodDeclaration MethodDeclarations  */
#line 267 "P1.y"
    {
        (yyval.val) = strdup((string((yyvsp[-1].val)) + string((yyvsp[0].val))).c_str());
    }
#line 1594 "P1.tab.c"
    break;

  case 18: /* MethodDeclarations: %empty  */
#line 270 "P1.y"
     { (yyval.val) = strdup(""); }
#line 1600 "P1.tab.c"
    break;

  case 19: /* $@1: %empty  */
#line 274 "P1.y"
                                                    {indent+= 2;}
#line 1606 "P1.tab.c"
    break;

  case 20: /* MethodDeclaration: FunctionType IDENTIFIER '(' OptParams ')' '{' $@1 Statements RETURN Expression ';' '}'  */
#line 275 "P1.y"
    {
        indent-= 2;
        string s = indentation(indent) + string((yyvsp[-11].val)) + string((yyvsp[-10].val)) + "(" + string((yyvsp[-8].val)) + ") {\n";
        s += string((yyvsp[-4].val));
        s += indentation(indent + 2) + "return " + string((yyvsp[-2].val)) + ";\n";
        s += indentation(indent + 1) + "}\n";
        (yyval.val) = strdup(s.c_str());
    }
#line 1619 "P1.tab.c"
    break;

  case 21: /* FunctionType: PUBLIC Type  */
#line 287 "P1.y"
    {
        string s = "    public " + string((yyvsp[0].val)) + " ";
        (yyval.val) = strdup(s.c_str());
    }
#line 1628 "P1.tab.c"
    break;

  case 22: /* OptParams: ParamList  */
#line 295 "P1.y"
    {
        (yyval.val) = (yyvsp[0].val);
    }
#line 1636 "P1.tab.c"
    break;

  case 23: /* OptParams: %empty  */
#line 298 "P1.y"
     {(yyval.val) = strdup("");}
#line 1642 "P1.tab.c"
    break;

  case 24: /* ParamList: Type IDENTIFIER ParamRests  */
#line 303 "P1.y"
    {
        string s = string((yyvsp[-2].val)) + " " + string((yyvsp[-1].val)) + string((yyvsp[0].val));
        (yyval.val) = strdup(s.c_str());
    }
#line 1651 "P1.tab.c"
    break;

  case 25: /* ParamRests: ',' Type IDENTIFIER ParamRests  */
#line 311 "P1.y"
    {
        string s = ", " + string((yyvsp[-2].val)) + " " + string((yyvsp[-1].val)) + string((yyvsp[0].val));
        (yyval.val) = strdup(s.c_str());
    }
#line 1660 "P1.tab.c"
    break;

  case 26: /* ParamRests: %empty  */
#line 315 "P1.y"
      {(yyval.val) = strdup("");}
#line 1666 "P1.tab.c"
    break;

  case 27: /* Type: INT '[' ']'  */
#line 319 "P1.y"
                 {(yyval.val) = strdup("int[]");}
#line 1672 "P1.tab.c"
    break;

  case 28: /* Type: BOOLEAN  */
#line 320 "P1.y"
             {(yyval.val) = strdup("boolean");}
#line 1678 "P1.tab.c"
    break;

  case 29: /* Type: INT  */
#line 321 "P1.y"
         {(yyval.val) = strdup("int");}
#line 1684 "P1.tab.c"
    break;

  case 30: /* Type: IDENTIFIER  */
#line 322 "P1.y"
                { (yyval.val) = (yyvsp[0].val); }
#line 1690 "P1.tab.c"
    break;

  case 31: /* Type: '(' Type ARROW Type ')'  */
#line 323 "P1.y"
                             {
        string s = "(" + string((yyvsp[-3].val)) + " -> " + string((yyvsp[-1].val)) + ")";
        (yyval.val) = strdup(s.c_str());
    }
#line 1699 "P1.tab.c"
    break;

  case 32: /* Statements: Statement Statements  */
#line 333 "P1.y"
    {
        (yyval.val) = strdup((string((yyvsp[-1].val)) + string((yyvsp[0].val))).c_str());
    }
#line 1707 "P1.tab.c"
    break;

  case 33: /* Statements: %empty  */
#line 336 "P1.y"
     { (yyval.val) = strdup(""); }
#line 1713 "P1.tab.c"
    break;

  case 34: /* Statement: MatchedStatement  */
#line 340 "P1.y"
                      {(yyval.val) = (yyvsp[0].val);}
#line 1719 "P1.tab.c"
    break;

  case 35: /* Statement: UnmatchedStatement  */
#line 341 "P1.y"
                        {(yyval.val) = (yyvsp[0].val);}
#line 1725 "P1.tab.c"
    break;

  case 36: /* Statement: VarDecl  */
#line 342 "P1.y"
             {(yyval.val) = (yyvsp[0].val);}
#line 1731 "P1.tab.c"
    break;

  case 37: /* MatchedStatement: IF '(' Expression ')' MatchedStatement ELSE MatchedStatement  */
#line 347 "P1.y"
      {
          string s = indentation(indent) + "if (" + string((yyvsp[-4].val)) + ")\n";
          indent++; s += string((yyvsp[-2].val)); indent--;
          s += indentation(indent) + "else\n";
          indent++; s += string((yyvsp[0].val)); indent--;
          (yyval.val) = strdup(s.c_str());
          free((yyvsp[-4].val)); free((yyvsp[-2].val)); free((yyvsp[0].val));
      }
#line 1744 "P1.tab.c"
    break;

  case 38: /* MatchedStatement: WHILE '(' Expression ')' MatchedStatement  */
#line 356 "P1.y"
      {
          string s = indentation(indent) + "while (" + string((yyvsp[-2].val)) + ")\n";
          s += string((yyvsp[0].val));
          (yyval.val) = strdup(s.c_str());
          free((yyvsp[-2].val)); free((yyvsp[0].val));
      }
#line 1755 "P1.tab.c"
    break;

  case 39: /* MatchedStatement: PRINT '(' Expression ')' ';'  */
#line 364 "P1.y"
      {
          string s = indentation(indent) + "System.out.println(" + string((yyvsp[-2].val)) + ");\n";
          (yyval.val) = strdup(s.c_str());
          free((yyvsp[-2].val));
      }
#line 1765 "P1.tab.c"
    break;

  case 40: /* MatchedStatement: Block  */
#line 369 "P1.y"
            { (yyval.val) = (yyvsp[0].val); }
#line 1771 "P1.tab.c"
    break;

  case 41: /* MatchedStatement: IDENTIFIER '=' Expression ';'  */
#line 371 "P1.y"
      {
          string s = indentation(indent) + string((yyvsp[-3].val)) + " = " + string((yyvsp[-1].val)) + ";\n";
          (yyval.val) = strdup(s.c_str());
          free((yyvsp[-3].val)); free((yyvsp[-1].val));
      }
#line 1781 "P1.tab.c"
    break;

  case 42: /* MatchedStatement: IDENTIFIER '[' Expression ']' '=' Expression ';'  */
#line 377 "P1.y"
      {
          string s = indentation(indent) + string((yyvsp[-6].val)) + "[" + string((yyvsp[-4].val)) + "] = " + string((yyvsp[-1].val)) + ";\n";
          (yyval.val) = strdup(s.c_str());
          free((yyvsp[-6].val)); free((yyvsp[-4].val)); free((yyvsp[-1].val));
      }
#line 1791 "P1.tab.c"
    break;

  case 43: /* MatchedStatement: IDENTIFIER '(' OptExprs ')' ';'  */
#line 383 "P1.y"
      {
          try {
              string expanded = expandMacroCallCommon((yyvsp[-4].val), (yyvsp[-2].val), false);
              string s = reindentTo(expanded, indent);
              (yyval.val) = strdup(s.c_str());
          } catch (const runtime_error& e) {
              yyerror(e.what());
              YYERROR;
          }
          free((yyvsp[-4].val)); free((yyvsp[-2].val));
      }
#line 1807 "P1.tab.c"
    break;

  case 44: /* $@2: %empty  */
#line 398 "P1.y"
        {indent++;}
#line 1813 "P1.tab.c"
    break;

  case 45: /* Block: '{' $@2 Statements '}'  */
#line 399 "P1.y"
    {
        indent--;
        string s = indentation(indent) + "{\n";
        s += string((yyvsp[-1].val));
        s += indentation(indent) + "}\n";
        (yyval.val) = strdup(s.c_str());
    }
#line 1825 "P1.tab.c"
    break;

  case 46: /* UnmatchedStatement: IF '(' Expression ')' Statement  */
#line 410 "P1.y"
      {
          string s = indentation(indent) + "if (" + string((yyvsp[-2].val)) + ")\n";
          indent++;
          s += string((yyvsp[0].val));
          indent--;
          (yyval.val) = strdup(s.c_str());
          free((yyvsp[-2].val)); free((yyvsp[0].val));
      }
#line 1838 "P1.tab.c"
    break;

  case 47: /* UnmatchedStatement: IF '(' Expression ')' MatchedStatement ELSE UnmatchedStatement  */
#line 419 "P1.y"
      {
          string s = indentation(indent) + "if (" + string((yyvsp[-4].val)) + ")\n";
          indent++; s += string((yyvsp[-2].val)); indent--;
          s += indentation(indent) + "else\n";
          indent++; s += string((yyvsp[0].val)); indent--;
          (yyval.val) = strdup(s.c_str());
          free((yyvsp[-4].val)); free((yyvsp[-2].val)); free((yyvsp[0].val));
      }
#line 1851 "P1.tab.c"
    break;

  case 48: /* OptExprs: %empty  */
#line 430 "P1.y"
     {
        (yyval.val) = strdup("");
    }
#line 1859 "P1.tab.c"
    break;

  case 49: /* OptExprs: ExprList  */
#line 434 "P1.y"
    {
        (yyval.val) = (yyvsp[0].val);
    }
#line 1867 "P1.tab.c"
    break;

  case 50: /* ExprList: Expression ExpressionRests  */
#line 441 "P1.y"
    {
        string s = string((yyvsp[-1].val)) + (yyvsp[0].val);
        (yyval.val) = strdup(s.c_str());
    }
#line 1876 "P1.tab.c"
    break;

  case 51: /* ExpressionRests: ExpressionRest ExpressionRests  */
#line 449 "P1.y"
    {
        (yyval.val) = strdup((string((yyvsp[-1].val)) + string((yyvsp[0].val))).c_str());
    }
#line 1884 "P1.tab.c"
    break;

  case 52: /* ExpressionRests: %empty  */
#line 452 "P1.y"
     { (yyval.val) = strdup(""); }
#line 1890 "P1.tab.c"
    break;

  case 53: /* ExpressionRest: ',' Expression  */
#line 457 "P1.y"
    {
        (yyval.val) = strdup((string(", ") + string((yyvsp[0].val))).c_str());
    }
#line 1898 "P1.tab.c"
    break;

  case 54: /* Expression: Expression OR Expression  */
#line 464 "P1.y"
      { (yyval.val) = strdup((string((yyvsp[-2].val)) + " || " + string((yyvsp[0].val))).c_str()); free((yyvsp[-2].val)); free((yyvsp[0].val)); }
#line 1904 "P1.tab.c"
    break;

  case 55: /* Expression: Expression AND Expression  */
#line 466 "P1.y"
      { (yyval.val) = strdup((string((yyvsp[-2].val)) + " && " + string((yyvsp[0].val))).c_str()); free((yyvsp[-2].val)); free((yyvsp[0].val)); }
#line 1910 "P1.tab.c"
    break;

  case 56: /* Expression: Expression NEQ Expression  */
#line 468 "P1.y"
      { (yyval.val) = strdup((string((yyvsp[-2].val)) + " != " + string((yyvsp[0].val))).c_str()); free((yyvsp[-2].val)); free((yyvsp[0].val)); }
#line 1916 "P1.tab.c"
    break;

  case 57: /* Expression: Expression LEQ Expression  */
#line 470 "P1.y"
      { (yyval.val) = strdup((string((yyvsp[-2].val)) + " <= " + string((yyvsp[0].val))).c_str()); free((yyvsp[-2].val)); free((yyvsp[0].val)); }
#line 1922 "P1.tab.c"
    break;

  case 58: /* Expression: Expression '+' Expression  */
#line 472 "P1.y"
      { (yyval.val) = strdup((string((yyvsp[-2].val)) + " + " + string((yyvsp[0].val))).c_str()); free((yyvsp[-2].val)); free((yyvsp[0].val)); }
#line 1928 "P1.tab.c"
    break;

  case 59: /* Expression: Expression '-' Expression  */
#line 474 "P1.y"
      { (yyval.val) = strdup((string((yyvsp[-2].val)) + " - " + string((yyvsp[0].val))).c_str()); free((yyvsp[-2].val)); free((yyvsp[0].val)); }
#line 1934 "P1.tab.c"
    break;

  case 60: /* Expression: Expression '*' Expression  */
#line 476 "P1.y"
      { (yyval.val) = strdup((string((yyvsp[-2].val)) + " * " + string((yyvsp[0].val))).c_str()); free((yyvsp[-2].val)); free((yyvsp[0].val)); }
#line 1940 "P1.tab.c"
    break;

  case 61: /* Expression: Expression '/' Expression  */
#line 478 "P1.y"
      { (yyval.val) = strdup((string((yyvsp[-2].val)) + " / " + string((yyvsp[0].val))).c_str()); free((yyvsp[-2].val)); free((yyvsp[0].val)); }
#line 1946 "P1.tab.c"
    break;

  case 62: /* Expression: Expression '[' Expression ']'  */
#line 480 "P1.y"
      { (yyval.val) = strdup((string((yyvsp[-3].val)) + "[" + string((yyvsp[-1].val)) + "]").c_str()); free((yyvsp[-3].val)); free((yyvsp[-1].val)); }
#line 1952 "P1.tab.c"
    break;

  case 63: /* Expression: Expression '.' LENGTH  */
#line 482 "P1.y"
      { (yyval.val) = strdup((string((yyvsp[-2].val)) + ".length").c_str()); free((yyvsp[-2].val)); }
#line 1958 "P1.tab.c"
    break;

  case 64: /* Expression: Expression '.' IDENTIFIER '(' OptExprs ')'  */
#line 484 "P1.y"
      { (yyval.val) = strdup((string((yyvsp[-5].val)) + "." + string((yyvsp[-3].val)) + "(" + string((yyvsp[-1].val)) + ")").c_str()); free((yyvsp[-5].val)); free((yyvsp[-3].val)); free((yyvsp[-1].val)); }
#line 1964 "P1.tab.c"
    break;

  case 65: /* Expression: IDENTIFIER '(' OptExprs ')'  */
#line 486 "P1.y"
      {
          try {
              (yyval.val) = strdup(expandMacroCallCommon((yyvsp[-3].val), (yyvsp[-1].val), true).c_str());
          } catch (const runtime_error& e) {
              yyerror(e.what());
              YYERROR;
          }
          free((yyvsp[-3].val)); free((yyvsp[-1].val));
      }
#line 1978 "P1.tab.c"
    break;

  case 66: /* Expression: '(' IDENTIFIER ')' ARROW Expression  */
#line 496 "P1.y"
      { (yyval.val) = strdup(("( " + string((yyvsp[-3].val)) + " ) -> " + string((yyvsp[0].val))).c_str()); free((yyvsp[-3].val)); free((yyvsp[0].val)); }
#line 1984 "P1.tab.c"
    break;

  case 67: /* Expression: PrimaryExpression  */
#line 498 "P1.y"
      { (yyval.val) = (yyvsp[0].val); }
#line 1990 "P1.tab.c"
    break;

  case 68: /* PrimaryExpression: INTEGER_LITERAL  */
#line 502 "P1.y"
                      { (yyval.val) = (yyvsp[0].val); }
#line 1996 "P1.tab.c"
    break;

  case 69: /* PrimaryExpression: TRUE_  */
#line 503 "P1.y"
                      { (yyval.val) = strdup("true"); }
#line 2002 "P1.tab.c"
    break;

  case 70: /* PrimaryExpression: FALSE_  */
#line 504 "P1.y"
                      { (yyval.val) = strdup("false"); }
#line 2008 "P1.tab.c"
    break;

  case 71: /* PrimaryExpression: IDENTIFIER  */
#line 505 "P1.y"
                      { (yyval.val) = (yyvsp[0].val); }
#line 2014 "P1.tab.c"
    break;

  case 72: /* PrimaryExpression: THIS  */
#line 506 "P1.y"
                      { (yyval.val) = strdup("this"); }
#line 2020 "P1.tab.c"
    break;

  case 73: /* PrimaryExpression: NEW INT '[' Expression ']'  */
#line 508 "P1.y"
      { (yyval.val) = strdup(("new int[" + string((yyvsp[-1].val)) + "]").c_str()); free((yyvsp[-1].val)); }
#line 2026 "P1.tab.c"
    break;

  case 74: /* PrimaryExpression: NEW IDENTIFIER '(' ')'  */
#line 510 "P1.y"
      { (yyval.val) = strdup(("new " + string((yyvsp[-2].val)) + "()").c_str()); free((yyvsp[-2].val)); }
#line 2032 "P1.tab.c"
    break;

  case 75: /* PrimaryExpression: '!' Expression  */
#line 512 "P1.y"
      { (yyval.val) = strdup(("!" + string((yyvsp[0].val))).c_str()); free((yyvsp[0].val)); }
#line 2038 "P1.tab.c"
    break;

  case 76: /* PrimaryExpression: '(' Expression ')'  */
#line 514 "P1.y"
      { (yyval.val) = strdup(("(" + string((yyvsp[-1].val)) + ")").c_str()); free((yyvsp[-1].val)); }
#line 2044 "P1.tab.c"
    break;

  case 79: /* MacroDefExpression: DEFINE IDENTIFIER '(' OptIdList ')' '(' Expression ')'  */
#line 524 "P1.y"
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
#line 2067 "P1.tab.c"
    break;

  case 80: /* MacroDefStatement: DEFINE IDENTIFIER '(' OptIdList ')' '{' Statements '}'  */
#line 546 "P1.y"
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
#line 2090 "P1.tab.c"
    break;

  case 81: /* OptIdList: IdList  */
#line 567 "P1.y"
          {(yyval.val) = (yyvsp[0].val); }
#line 2096 "P1.tab.c"
    break;

  case 82: /* OptIdList: %empty  */
#line 568 "P1.y"
     { (yyval.val) = strdup(""); }
#line 2102 "P1.tab.c"
    break;

  case 83: /* IdList: IDENTIFIER IdRests  */
#line 572 "P1.y"
                      {(yyval.val) = strdup((string((yyvsp[-1].val)) + string((yyvsp[0].val))).c_str()); }
#line 2108 "P1.tab.c"
    break;

  case 84: /* IdRests: IdRest IdRests  */
#line 576 "P1.y"
                  {(yyval.val) = strdup((string((yyvsp[-1].val)) + string((yyvsp[0].val))).c_str()); }
#line 2114 "P1.tab.c"
    break;

  case 85: /* IdRests: %empty  */
#line 577 "P1.y"
     { (yyval.val) = strdup(""); }
#line 2120 "P1.tab.c"
    break;

  case 86: /* IdRest: ',' IDENTIFIER  */
#line 582 "P1.y"
    {
        (yyval.val) = strdup((string(", ") + string((yyvsp[0].val))).c_str());
    }
#line 2128 "P1.tab.c"
    break;


#line 2132 "P1.tab.c"

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

#line 589 "P1.y"


int main(void) {
    return yyparse();
}
