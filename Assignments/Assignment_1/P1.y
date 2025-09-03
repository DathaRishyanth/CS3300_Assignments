%{
#include <bits/stdc++.h>
using namespace std;
void yyerror(const char *s);
int yylex(void);

class Macro {
public:
    vector<string> params;
    string body;
    bool isExpression; // true if expression macro, false if statement macro
    Macro(const vector<string>& p, const string& b, bool isExpr) : params(p), body(b), isExpression(isExpr) {}
    map<string,Macro> macroTable;
};

%}



%union {
   char* val;
}

%token CLASS PUBLIC STATIC VOID MAIN STRING EXTENDS RETURN NEW IMPORT JAVA UTIL FUNCTION APPLY ARROW NL
%token EQ NEQ LEQ AND OR 
%token IF ELSE WHILE DO
%token TRUE_ FALSE_ THIS LENGTH

%token PRINT
%token INT BOOLEAN

/* Add these lines to your precedence section */
%nonassoc IFX /* Precedence for IF without ELSE */
%nonassoc ELSE

%token DEFINE

%right '='
%right ARROW
%left OR
%left AND
%left NEQ LEQ
%left '+' '-'
%left '*' '/'
%right '!' UMINUS
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
      PRINT'(' Expression')' ';' '}'
      '}'
      {
        cout<<"class "<<$2<<" {"<<endl;
        cout<<"    public static void main(String[] "<<$12<<") {"<<endl;
        cout<<"        System.out.println(" ");"<<endl;
        cout<<"    }"<<endl;
        cout<<"}"<<endl;
      }
    ;

TypeDeclaration
    : CLASS IDENTIFIER{cout<<"class "<<$2<<"{\n";} '{' VarDecls MethodDeclarations '}' 
    
    | CLASS IDENTIFIER EXTENDS IDENTIFIER{cout<<"class "<<$2<<" extends "<<$4<<"{\n";} '{' VarDecls MethodDeclarations '}'
    ;

VarDecls :
    VarDecl VarDecls
    | 
    ;

VarDecl :
    Type IDENTIFIER ';'
    {
        cout<<$2<<";\n";
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
    : PUBLIC{cout<<"public ";} Type IDENTIFIER{cout<<$4<<"( ";} '(' OptParams ')' '{'Statements RETURN Expression ';' '}'
    ;

OptParams :
    ParamList
    |
    ;

ParamList :
    Type IDENTIFIER ParamRests
    ;

ParamRests :
    ',' Type IDENTIFIER ParamRests
    | 
    ;

Type
    : INT '[' ']'
    | BOOLEAN
    | INT
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
    : IF '(' Expression ')' MatchedStatement ELSE MatchedStatement
    | WHILE '(' Expression ')' MatchedStatement
    | PRINT'(' Expression ')' ';'
    | Block
    | IDENTIFIER '=' Expression ';'
    | IDENTIFIER '[' Expression ']' '=' Expression ';'
    ;

Block :
    '{' Statements '}'
    ;

UnmatchedStatement
    : IF '(' Expression ')' Statement %prec IFX 
    | IF '(' Expression ')' MatchedStatement ELSE UnmatchedStatement
    ;


OptExprs
    : /* empty */
    | ExprList
    ;

ExprList :
    Expression ExpressionRests
    ;

ExpressionRests :
    ExpressionRest ExpressionRests
    |
    ;

ExpressionRest :
    ',' Expression
    ;
Expression :
      INTEGER_LITERAL
    | TRUE_
    | FALSE_
    | IDENTIFIER
    | THIS
    | Expression '.' LENGTH
    | Expression '.' IDENTIFIER '(' OptExprs ')'
    | NEW INT '[' Expression ']'
    | NEW IDENTIFIER '(' ')'
    | Expression '[' Expression ']'
    | '!' Expression
    | Expression '*' Expression
    | Expression '/' Expression
    | Expression '+' Expression
    | Expression '-' Expression
    | Expression LEQ Expression
    | Expression NEQ Expression
    | Expression AND Expression
    | Expression OR Expression
    | IDENTIFIER '(' OptExprs ')'
    | '(' Expression ')'
    | Expression ARROW Expression
    | Expression '.' APPLY '(' Expression ')'
    ;

/* PrimaryExpr is no longer needed and can be removed */

MacroDefinition :
    MacroDefExpression
    | MacroDefStatement
    ;

MacroDefExpression
    : DEFINE IDENTIFIER '(' OptIdList ')' '(' Expression ')'
    // {
    //     string macroName = $2;
    //     if (macroTable.find(macroName) != macroTable.end()) {
    //         cerr << "Error: Macro " << macroName << " already defined." << endl;
    //         exit(1);
    //     }
    //     vector<string> params;
    //     for (auto param : $4) {
    //         params.push_back(param);
    //     }
    //     string body = $7;
    //     macroTable[macroName] = {params.size(), Macro(params, body, true)};
    // }
    ;

MacroDefStatement
    : DEFINE IDENTIFIER '(' OptIdList ')' '{' Statements '}'
    // {
    //     string macroName = $2;
    //     if (macroTable.find(macroName) != macroTable.end()) {
    //         cerr << "Error: Macro " << macroName << " already defined." << endl;
    //         exit(1);
    //     }
    //     vector<string> params;
    //     for (auto param : $4) {
    //         params.push_back(param);
    //     }
    //     string body = ""; // You can serialize statements if needed
    //     macroTable[macroName] = {params.size(), Macro(params, body, false)};
    // }
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
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    return yyparse();
}
