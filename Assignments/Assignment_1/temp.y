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

// --- Indentation Logic ---
int indent_level = 0;
string indent() {
    return string(indent_level * 4, ' ');
}

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
map<string, Macro> macroTable;

%}

%union {
   char* val;
}

%token CLASS PUBLIC STATIC VOID MAIN STRING EXTENDS RETURN NEW IMPORT JAVA UTIL FUNCTION APPLY ARROW
%token EQ NEQ LEQ AND OR
%token IF ELSE WHILE DO
%token TRUE_ FALSE_ THIS LENGTH

// All these non-terminals will now return strings
%type<val> Expression MatchedStatement Type ClassType
%type<val> Statements Statement UnmatchedStatement Block
%type<val> TypeDeclarations TypeDeclaration VarDecls VarDecl
%type<val> MethodDeclarations MethodDeclaration
%type<val> OptExprs ExprList ExpressionRests ExpressionRest
%type<val> OptParams ParamList ParamRests
%type<val> FunctionType FunctionDecl

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
    : ImportFunctionOpt MacroDefinitions MainClass TypeDeclarations { cout << $4; free($4); }
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
    TypeDeclaration TypeDeclarations { $$ = strdup((string($1) + $2).c_str()); free($1); free($2); }
    | { $$ = strdup(""); }
    ;

MainClass
    : CLASS IDENTIFIER '{' PUBLIC STATIC VOID MAIN'(' STRING '[' ']' IDENTIFIER ')' '{'
      PRINT'(' Expression')' ';' '}' '}'
      {
        indent_level = 0;
        string s = "class " + string($2) + " {\n";
        indent_level++;
        s += indent() + "public static void main(String[] " + string($12) + ") {\n";
        indent_level++;
        s += indent() + "System.out.println(" + string($17) + ");\n";
        indent_level--;
        s += indent() + "}\n";
        indent_level--;
        s += "}\n";
        cout << s;
        free($2); free($12); free($17);
      }
    ;

TypeDeclaration
    : CLASS IDENTIFIER '{' VarDecls MethodDeclarations '}'
    {
        string s = "\nclass " + string($2) + " {\n";
        s += string($4);
        s += string($5);
        s += "}\n";
        $$ = strdup(s.c_str());
        free($2); free($4); free($5);
    }
    | CLASS IDENTIFIER EXTENDS IDENTIFIER '{' VarDecls MethodDeclarations '}'
    {
        string s = "\nclass " + string($2) + " extends " + string($4) + " {\n";
        s += string($6);
        s += string($7);
        s += "}\n";
        $$ = strdup(s.c_str());
        free($2); free($4); free($6); free($7);
    }
    ;

VarDecls :
    VarDecl VarDecls { $$ = strdup((string($1) + $2).c_str()); free($1); free($2); }
    | { $$ = strdup(""); }
    ;

VarDecl :
    Type IDENTIFIER ';'
    {
        indent_level++;
        $$ = strdup((indent() + string($1) + " " + string($2) + ";\n").c_str());
        indent_level--;
        free($1); free($2);
    }
    | FunctionDecl IDENTIFIER ';' { $$ = strdup(""); /* Not implemented */ }
    ;

FunctionDecl :
    FUNCTION '<' Type ',' Type '>' { $$ = strdup(""); /* Not implemented */ }
    ;

MethodDeclarations :
    MethodDeclaration MethodDeclarations { $$ = strdup((string($1) + $2).c_str()); free($1); free($2); }
    | { $$ = strdup(""); }
    ;

MethodDeclaration
    : FunctionType IDENTIFIER '(' OptParams ')' '{'
      { indent_level++; }
      Statements
      RETURN Expression ';'
      { indent_level--; }
      '}'
    {
        string s = "\n" + indent() + string($1) + " " + string($2) + "(" + string($4) + ") {\n";
        s += string($8);
        indent_level++;
        s += indent() + "return " + string($10) + ";\n";
        indent_level--;
        s += indent() + "}\n";
        $$ = strdup(s.c_str());
        free($1); free($2); free($4); free($8); free($10);
    }
    ;

FunctionType :
    PUBLIC Type { $$ = strdup(("public " + string($2)).c_str()); free($2); }
    ;

OptParams :
    ParamList { $$ = $1; }
    | { $$ = strdup(""); }
    ;

ParamList :
    Type IDENTIFIER ParamRests
    {
        $$ = strdup((string($1) + " " + string($2) + $3).c_str());
        free($1); free($2); free($3);
    }
    ;

ParamRests :
    ',' Type IDENTIFIER ParamRests
    {
        $$ = strdup((", " + string($2) + " " + string($3) + $4).c_str());
        free($2); free($3); free($4);
    }
    | { $$ = strdup(""); }
    ;

Type
    : INT '[' ']' { $$ = strdup("int[]"); }
    | BOOLEAN     { $$ = strdup("boolean"); }
    | INT         { $$ = strdup("int"); }
    | ClassType   { $$ = $1; }
    | '(' Type ARROW Type ')' { $$ = strdup(("(" + string($2) + " -> " + string($4) + ")").c_str()); free($2); free($4); }
    ;

ClassType : IDENTIFIER { $$ = $1; } ;

Statements  :
    Statement Statements { $$ = strdup((string($1) + $2).c_str()); free($1); free($2); }
    | { $$ = strdup(""); }
    ;

Statement
    : MatchedStatement   { $$ = $1; }
    | UnmatchedStatement { $$ = $1; }
    | VarDecl            { $$ = $1; }
    ;

MatchedStatement
    : IF'(' Expression ')' MatchedStatement ELSE MatchedStatement
    {
        string s = indent() + "if (" + string($3) + ")\n";
        indent_level++;
        s += string($5);
        indent_level--;
        s += indent() + "else\n";
        indent_level++;
        s += string($7);
        indent_level--;
        $$ = strdup(s.c_str());
        free($3); free($5); free($7);
    }
    | WHILE '(' Expression ')' MatchedStatement
    {
        string s = indent() + "while (" + string($3) + ")\n";
        indent_level++;
        s += string($5);
        indent_level--;
        $$ = strdup(s.c_str());
        free($3); free($5);
    }
    | PRINT'(' Expression ')' ';'
    {
        $$ = strdup((indent() + "System.out.println(" + string($3) + ");\n").c_str());
        free($3);
    }
    | Block { $$ = $1; }
    | IDENTIFIER '=' Expression ';'
    {
        $$ = strdup((indent() + string($1) + " = " + string($3) + ";\n").c_str());
        free($1); free($3);
    }
    | IDENTIFIER '[' Expression ']' '=' Expression ';'
    {
        $$ = strdup((indent() + string($1) + "[" + string($3) + "] = " + string($6) + ";\n").c_str());
        free($1); free($3); free($6);
    }
    ;

Block :
    '{' { indent_level++; } Statements '}' { indent_level--; }
    { $$ = strdup(("{\n" + string($3) + indent() + "}\n").c_str()); free($3); }
    ;

UnmatchedStatement
    : IF '(' Expression ')' Statement %prec IFX
    {
        string s = indent() + "if (" + string($3) + ")\n";
        indent_level++;
        s += string($5);
        indent_level--;
        $$ = strdup(s.c_str());
        free($3); free($5);
    }
    | IF '(' Expression ')' MatchedStatement ELSE UnmatchedStatement
    {
        string s = indent() + "if (" + string($3) + ")\n";
        indent_level++;
        s += string($5);
        indent_level--;
        s += indent() + "else\n";
        indent_level++;
        s += string($7);
        indent_level--;
        $$ = strdup(s.c_str());
        free($3); free($5); free($7);
    }
    ;

OptExprs
    : ExprList { $$ = $1; }
    | { $$ = strdup(""); }
    ;

ExprList :
    Expression ExpressionRests
    {
        $$ = strdup((string($1) + $2).c_str());
        free($1); free($2);
    }
    ;

ExpressionRests :
    ExpressionRest ExpressionRests
    {
        $$ = strdup((string($1) + $2).c_str());
        free($1); free($2);
    }
    | { $$ = strdup(""); }
    ;

ExpressionRest :
    ',' Expression
    {
        $$ = strdup((", " + string($2)).c_str());
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
        { $$ = strdup((std::string($1) + "." + std::string($3) + "(" + string($5) + ")").c_str()); free($1); free($3); free($5); }
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
        { $$ = strdup((std::string($1) + "(" + string($3) + ")").c_str()); free($1); free($3); }
    | '(' Expression ')'
        { $$ = strdup(("(" + std::string($2) + ")").c_str()); free($2); }
    | Expression ARROW Expression
        { $$ = strdup((std::string($1) + " -> " + std::string($3)).c_str()); free($1); free($3); }
    | Expression '.' APPLY '(' Expression ')'
        { $$ = strdup((std::string($1) + ".apply(" + std::string($5) + ")").c_str()); free($1); free($5); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
}

int main(void) {
    return yyparse();
}