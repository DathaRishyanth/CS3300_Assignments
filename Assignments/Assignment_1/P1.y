%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char *s);
int yylex(void);
%}

%union {
    int val;
    char *str;
}

%token CLASS PUBLIC STATIC VOID MAIN STRING EXTENDS RETURN NEW
%token IF ELSE WHILE DO
%token TRUE_ FALSE_ THIS LENGTH
%token PRINT
%token INT BOOLEAN

%token DEFINE

%left OR
%left AND
%left NEQ LEQ
%left '+' '-'
%left '*' '/'
%right '!' UMINUS



%token <val> IDENTIFIER
%token <str> INTEGER_LITERAL


%%

Goal
    : MacroDefinitions MainClass TypeDeclarations
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
    : CLASS Identifier '{' PUBLIC STATIC VOID MAIN '(' STRING '[' ']' Identifier ')' '{'
      PRINT '(' Expression ')' ';' '}'
      '}'
    ;

TypeDeclaration
    : CLASS Identifier '{' VarDecls MethodDeclarations '}'
    | CLASS Identifier EXTENDS Identifier '{' VarDecls MethodDeclarations '}'
    ;

VarDecls :
    Type Identifier ';' VarDecls
    | 

MethodDeclarations :
    MethodDeclaration MethodDeclarations
    | 
    ;

MethodDeclaration
    : PUBLIC Type Identifier '(' OptParams ')' '{' VarDecls Statements RETURN Expression ';' '}'
    ;

OptParams :
    ParamList
    |
    ;

ParamList :
    Type Identifier ParamRests
    ;

ParamRests :
    ',' Type Identifier ParamRests
    | 
    ;

Type
    : INT '[' ']'
    | BOOLEAN
    | INT
    | Identifier
    | '(' Type '-' '>' Type ')' 
    ;

Statements  :
    Statement Statements
    |
    ;




Statement
    : '{' Statements '}'
    | PRINT '(' Expression ')' ';'
    | Identifier '=' Expression ';'
    | Identifier '[' Expression ']' '=' Expression ';'
    | IF '(' Expression ')' Statement
    | IF '(' Expression ')' Statement ELSE Statement
    | WHILE '(' Expression ')' Statement
    | Identifier '(' OptExprs ')' ';'
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
    PrimaryExpr '&' '&' PrimaryExpr
    | PrimaryExpr '|' '|' PrimaryExpr
    | PrimaryExpr '!' '=' PrimaryExpr
    | PrimaryExpr '<' '=' PrimaryExpr
    | PrimaryExpr '+' PrimaryExpr
    | PrimaryExpr '-' PrimaryExpr
    | PrimaryExpr '*' PrimaryExpr
    | PrimaryExpr '/' PrimaryExpr
    | PrimaryExpr '[' PrimaryExpr ']'
    | PrimaryExpr '.' LENGTH
    | PrimaryExpr '.' IDENTIFIER '(' OptExprs ')'
    | IDENTIFIER '(' OptExprs ')'   /* Macro expr call */
    | '(' IDENTIFIER ')' '-' '>' Expression  /* Lambda */


PrimaryExpr
    : INTEGER_LITERAL
    | TRUE_
    | FALSE_
    | IDENTIFIER
    | THIS
    | NEW INT '[' Expression ']'
    | NEW IDENTIFIER '(' ')'
    | '!' Expression
    | '(' Expression ')'
    ;

MacroDefinition :
    MacroDefExpression
    | MacroDefStatement
    ;

MacroDefStatement
    : DEFINE Identifier '(' OptIdList ')' '{' Statements '}'
    ;

MacroDefExpression
    : DEFINE Identifier '(' OptIdList ')' '(' Expression ')'
    ;

OptIdList
    : /* empty */
    | IdList
    ;

IdList :
    Identifier IdRests
    ;

IdRests :
    IdRest IdRests
    | 
    ;

IdRest :
    ',' Identifier
    ;


Identifier
    : IDENTIFIER
    ;



%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
