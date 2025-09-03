%{
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstring> // For strdup
#include <cstdlib> // For free

using namespace std;
void yyerror(const char *s);
int yylex(void);

// Define the Macro class
class Macro {
public:
    vector<string> params;
    string body;
    bool isExpression;

    Macro() : isExpression(false) {}
    Macro(const vector<string>& p, const string& b, bool isExpr) : params(p), body(b), isExpression(isExpr) {}
};

// Global table to store macro definitions
int indent = 0;
string indentation(int indent) {
    string ind = "";
    for (int i = 0; i < indent; i++) {
        ind += "    ";
    }
    return ind;
}
map<string, Macro> macroTable;

%}

%union {
   char* val;
}

%token CLASS PUBLIC STATIC VOID MAIN STRING EXTENDS RETURN NEW IMPORT JAVA UTIL FUNCTION APPLY ARROW
%token EQ NEQ LEQ AND OR
%token IF ELSE WHILE DO
%token TRUE_ FALSE_ THIS LENGTH

%type<val> Expression MatchedStatement Type ExprList ExpressionRests ExpressionRest
%type<val>  TypeDeclarations TypeDeclaration VarDecls VarDecl
%type<val> Statements Statement UnmatchedStatement Block
%type<val> OptExprs OptParams ParamList ParamRests
%type<val> FunctionType FunctionDecl
%type<val> MacroDefinitions MacroDefinition MacroDefExpression MacroDefStatement
%type<val> OptIdList IdList IdRests IdRest

%token PRINT
%token INT BOOLEAN

%nonassoc IFX
%nonassoc ELSE

%token DEFINE

%right '='
%right ARROW
%left OR
%left AND
%left NEQ LEQ
%left '+' '-'
%left '*' '/'
%right '!'
%token UMINUS
%left '.' '[' ']'

%token <val> IDENTIFIER INTEGER_LITERAL

%%

Goal
    : ImportFunctionOpt MacroDefinitions MainClass TypeDeclarations
    ;

ImportFunctionOpt :
    IMPORT JAVA '.' UTIL '.' FUNCTION '.' FUNCTION ';'
    |
    ;

MacroDefinitions :
    MacroDefinition MacroDefinitions
    |
    ;

TypeDeclarations :
    TypeDeclaration TypeDeclarations
    |
    ;

MainClass
    : CLASS IDENTIFIER '{' PUBLIC STATIC VOID MAIN'(' STRING '[' ']' IDENTIFIER ')' '{'
      PRINT'(' Expression')' ';'
      '}'
      '}'
      {
        cout << "class " << $2 << " {" << endl;
        cout << "    public static void main(String[] " << $12 << ") {" << endl;
        cout << "        System.out.println(" << $17 << ");" << endl;
        cout << "    }" << endl;
        cout << "}" << endl;
        free($2); free($12); free($17);
      }
    ;

TypeDeclaration
    : CLASS IDENTIFIER{cout<<"class "<<$2<<" {\n";indent++;} '{' VarDecls MethodDeclarations '}' {cout<<"}\n";indent--;}
    
    | CLASS IDENTIFIER EXTENDS IDENTIFIER{cout<<"class "<<$2<<" extends "<<$4<<"{\n";indent++;} '{' VarDecls MethodDeclarations '}'
    ;



VarDecls :
    VarDecl VarDecls
    |
    ;

VarDecl :
    Type IDENTIFIER ';'
    {
        cout<<indentation(indent)<<$1<<$2<<";\n";
    }
    | FunctionDecl IDENTIFIER ';'
    ; 

FunctionDecl :
    FUNCTION '<' Type ',' Type '>'
    ;

MethodDeclarations :
    MethodDeclaration MethodDeclarations
    |
    ;

MethodDeclaration
    : FunctionType IDENTIFIER{cout<<$2<<"(";} '(' OptParams ')'{cout<<"){\n";indent++;}'{'Statements {cout<<indentation(indent);}RETURN{cout<<"return ";} Expression ';'{cout<<$13<<" ;\n";indent--;cout<<indentation(indent)<<"}\n";indent--;} '}'
    ;

FunctionType :
    PUBLIC Type
    {cout<<indentation(indent)<<"public"<<" "<<$2;}
    ;


OptParams :
    ParamList
    |
    ;

ParamList :
    Type IDENTIFIER{cout<<$1<<$2;} ParamRests
    ;

ParamRests :
    ','{cout<<", ";} Type IDENTIFIER{cout<<$3<<" "<<$4;} ParamRests
    | 
    ;

Type
    : INT '[' ']'{string s = "int[] "; $$ = strdup(s.c_str());}
    | BOOLEAN{string s = "boolean "; $$ = strdup(s.c_str());}
    | INT{string s = "int "; $$ = strdup(s.c_str());}
    | ClassType
    | '(' Type ARROW Type ')'
    ;


ClassType
    : IDENTIFIER
    ;

Statements  :
    Statement Statements
    |
    ;

Statement
    : MatchedStatement
    | UnmatchedStatement
    | VarDecl
    ;


MatchedStatement
    : IF'(' Expression ')' MatchedStatement ELSE MatchedStatement
    {
        cout<<indentation(indent)<<"if ("<<$3<<")\n";
        indent++;
        cout<<indentation(indent);
        cout<<$5;
        indent--;
        cout<<indentation(indent);
        cout<<"else\n";
        indent++;
        cout<<indentation(indent);
        cout<<$7;
        indent--;
    }
    | WHILE '(' Expression ')' MatchedStatement
    {
        cout<<"while ("<<$3<<") {\n"<<""<<"\n}\n";
    }
    | PRINT'(' Expression ')' ';'
    {
        cout<<"System.out.println("<<$3<<");\n";
    }
    | Block
    | IDENTIFIER '=' Expression ';'
    {
        string s = string($1) + " = " + string($3) + ";\n";
        $$ = strdup(s.c_str());
        free($1); free($3);
    }
    | IDENTIFIER '[' Expression ']' '=' Expression ';'
    {
        string s = string($1) + "[" + string($3) + "] = " + string($6) + ";\n";
        $$ = strdup(s.c_str());
        free($1); free($3); free($6);
    }
    ;

Block :
    '{' Statements '}'
    ;

UnmatchedStatement
    : IF '(' Expression ')' Statement %prec IFX
    | IF '(' Expression ')' MatchedStatement ELSE UnmatchedStatement
    ;

OptExprs
    :{
        $$ = strdup("");
    }
    | ExprList
    {
        $$ = $1;
    }
    ;

ExprList :
    Expression ExpressionRests
    {
        string s = string($1) + $2;
        $$ = strdup(s.c_str());
        free($1);
    }
    ;

ExpressionRests :
    ExpressionRest ExpressionRests
    {
        $$ = strdup((string($1) + string($2)).c_str());
    }
    |{ $$ = strdup(""); }
    ;

ExpressionRest :
    ',' Expression
    {
        $$ = strdup((string(", ") + string($2)).c_str());
        free($2);
    }
    ;

Expression :
      INTEGER_LITERAL { $$ = $1; }
    | TRUE_           { $$ = strdup("true"); }
    | FALSE_          { $$ = strdup("false"); }
    | IDENTIFIER      { $$ = $1; }
    | THIS            { $$ = strdup("this"); }
    | Expression '.' LENGTH
        { $$ = strdup((std::string($1) + ".length").c_str()); free($1); }
    | Expression '.' IDENTIFIER '(' OptExprs ')'
        { $$ = strdup((std::string($1) + "." + std::string($3) + "(" + string($5) + ")").c_str()); free($1); free($3); }
    | NEW INT '[' Expression ']'
        { $$ = strdup(("new int[" + std::string($4) + "]").c_str()); free($4); }
    | NEW IDENTIFIER '(' ')'
        { $$ = strdup(("new " + std::string($2) + "()").c_str()); free($2); }
    | Expression '[' Expression ']'
        { $$ = strdup((std::string($1) + "[" + std::string($3) + "]").c_str()); free($1); free($3); }
    | '!' Expression
        { $$ = strdup(("!" + std::string($2)).c_str()); free($2); }
    | Expression '*' Expression
        { $$ = strdup((std::string($1) + " * " + std::string($3)).c_str()); free($1); free($3); }
    | Expression '/' Expression
        { $$ = strdup((std::string($1) + " / " + std::string($3)).c_str()); free($1); free($3); }
    | Expression '+' Expression
        { $$ = strdup((std::string($1) + " + " + std::string($3)).c_str()); free($1); free($3); }
    | Expression '-' Expression
        { $$ = strdup((std::string($1) + " - " + std::string($3)).c_str()); free($1); free($3); }
    | Expression LEQ Expression
        { $$ = strdup((std::string($1) + " <= " + std::string($3)).c_str()); free($1); free($3); }
    | Expression NEQ Expression
        { $$ = strdup((std::string($1) + " != " + std::string($3)).c_str()); free($1); free($3); }
    | Expression AND Expression
        { $$ = strdup((std::string($1) + " && " + std::string($3)).c_str()); free($1); free($3); }
    | Expression OR Expression
        { $$ = strdup((std::string($1) + " || " + std::string($3)).c_str()); free($1); free($3); }
    | IDENTIFIER '(' OptExprs ')'
        { $$ = strdup((std::string($1) + "()").c_str()); free($1); }
    | '(' Expression ')'
        { $$ = strdup(("(" + std::string($2) + ")").c_str()); free($2); }
    | Expression ARROW Expression
        { $$ = strdup((std::string($1) + " -> " + std::string($3)).c_str()); free($1); free($3); }
    | Expression '.' APPLY '(' Expression ')'
        { $$ = strdup((std::string($1) + ".apply(" + std::string($5) + ")").c_str()); free($1); free($5); }
    ;

MacroDefinition :
    MacroDefExpression
    | MacroDefStatement
    ;

MacroDefExpression
    : DEFINE IDENTIFIER '(' OptIdList ')' '(' Expression ')'
    ;

MacroDefStatement
    : DEFINE IDENTIFIER '(' OptIdList ')' '{' Statements '}'
    ;

OptIdList :
    IdList
    |
    ;

IdList :
    IDENTIFIER IdRests
    ;

IdRests :
    IdRest IdRests
    |
    ;

IdRest :
    ',' IDENTIFIER
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
}

int main(void) {
    return yyparse();
}