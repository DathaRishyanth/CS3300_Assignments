%{
    #include <bits/stdc++.h>
    using namespace std;
    void yyerror(char *);
    int yylex(void);
%}

%union {
    char* str;
    int val;
}



%token<str> IDENTIFIER
%token<val> INTEGER_LITERAL
%token TRUE_ FALSE_ CLASS PUBLIC STATIC VOID MAIN STRING EXTENDS RETURN INT BOOLEAN LENGTH IF ELSE WHILE THIS NEW DO
%token DEFINE PRINT LEFTPAR RIGHTPAR CURLYCLOSE CURLYOPEN SQUAREOPEN SQUARECLOSE SEMICOLON PLUS MINUS MULTIPLY DIVIDE ASIGN EQUAL NOTEQUAL LESSTHAN GREATERTHAN LESSEQUAL ARROW ANDAND AND OR OROR NOT DOT COMMA

%right  ASSIGN
%left   OROR
%left   ANDAND
%left   EQUAL NOTEQUAL
%left   LESSTHAN GREATERTHAN LESSEQUAL // Add any other comparison ops
%left   PLUS MINUS
%left   MULTIPLY DIVIDE
%right  NOT


%%

Goal :
    Macrodefinitions MainClass TypeDeclarations
    ;

MainClass :
    CLASS IDENTIFIER CURLYOPEN PUBLIC STATIC VOID MAIN LEFTPAR STRING SQUAREOPEN SQUARECLOSE IDENTIFIER RIGHTPAR CURLYOPEN PrintStatement CURLYCLOSE CURLYCLOSE
    ;

TypeDeclarations :
    TypeDeclaration TypeDeclarations
    | 
    ;

TypeDeclaration :
    ClassDeclaration
    | ClassExtendsDeclaration
    ;

Macrodefinitions :
    Macrodefinition Macrodefinitions
    | 
    ;



PrintStatement :
    PRINT LEFTPAR Expression RIGHTPAR SEMICOLON
    ;



ClassDeclaration :
    CLASS IDENTIFIER CURLYOPEN VariableDeclarations MethodDeclarations CURLYCLOSE
    ;

ClassExtendsDeclaration :
    CLASS IDENTIFIER EXTENDS IDENTIFIER CURLYOPEN VariableDeclarations MethodDeclarations CURLYCLOSE
    ;

VariableDeclarations :
    VariableDeclaration VariableDeclarations
    | 
    ;
VariableDeclaration :
    Type IDENTIFIER SEMICOLON
    ;

MethodDeclarations :
    MethodDeclaration MethodDeclarations
    |
    ;

MethodDeclaration :
    PUBLIC Type IDENTIFIER LEFTPAR FormalParamaterListOpt RIGHTPAR CURLYOPEN VariableDeclarations Statements RETURN Expression SEMICOLON CURLYCLOSE
    ;

FormalParamaterListOpt :
    FormalParameter FormalParameterRests
    |
    ;

FormalParameter :
    Type IDENTIFIER
    ;

FormalParameterRests :
    FormalParamaterRest FormalParameterRests
    |
    ;

FormalParamaterRest :
    COMMA FormalParameter
    ;


Type :
    ArrayType
    | BooleanType
    | IntegerType
    | IDENTIFIER
    ;

ArrayType :
    INT SQUAREOPEN SQUARECLOSE
    ;

BooleanType :
    BOOLEAN
    ;

IntegerType :
    INT
    ;

Statements :
    Statement Statements
    |
    ;

Statement :
    Block
    | AssignmentStatement
    | ArrayAssignmentStatement
    | IfStatement
    | WhileStatement
    | PrintStatement
    | MacroStatement
    ;


Block :
    CURLYOPEN Statements CURLYCLOSE
    ;



AssignmentStatement :
    IDENTIFIER ASSIGN Expression SEMICOLON
    ;

ArrayAssignmentStatement :
    IDENTIFIER SQUAREOPEN Expression SQUARECLOSE ASSIGN Expression SEMICOLON
    ;

IfStatement :
    IfThenElseStatement
    | IfThenStatement
    ;

IfThenElseStatement :
    IF LEFTPAR Expression RIGHTPAR Statement ELSE Statement
    ; 

IfThenStatement :
    IF LEFTPAR Expression RIGHTPAR Statement
    ;

WhileStatement :
    WHILE LEFTPAR Expression RIGHTPAR Statement
    ;


MacroStatement :
    IDENTIFIER LEFTPAR ExpressionListOpt RIGHTPAR SEMICOLON
    ;



Expression :
    OrExpression
    | AndExpression
    | CompareExpression
    | neqExpression
    | AddExpression
    | MinusExpression
    | TimesExpression
    | DivExpression
    | Arraylookup
    | ArrayLength
    | MessageSend
    | MacroExpression
    | LambdaExpression
    | PrimaryExpression
    ;   




MacroExpression :
    IDENTIFIER LEFTPAR ExpressionListOpt RIGHTPAR
    
LambdaExpression :
    LEFTPAR IDENTIFIER RIGHTPAR ARROW Expression
    ;

AndExpression :
    PrimaryExpression ANDAND PrimaryExpression
    ;

OrExpression :
    PrimaryExpression OROR PrimaryExpression
    ;

CompareExpression :
    PrimaryExpression LESSEQUAL PrimaryExpression
    ;

neqExpression :
    PrimaryExpression NOTEQUAL PrimaryExpression
    ;

AddExpression :
    PrimaryExpression PLUS PrimaryExpression
    ;

MinusExpression :
    PrimaryExpression MINUS PrimaryExpression
    ;   

TimesExpression :
    PrimaryExpression MULTIPLY PrimaryExpression
    ;   

DivExpression :
    PrimaryExpression DIVIDE PrimaryExpression
    ;

Arraylookup :
    PrimaryExpression SQUAREOPEN PrimaryExpression SQUARECLOSE
    ;

ArrayLength :
    PrimaryExpression DOT LENGTH
    ;

MessageSend :
    PrimaryExpression DOT IDENTIFIER LEFTPAR ExpressionListOpt RIGHTPAR
    ;

ExpressionList :
    Expression ExpressionRests
    ;

ExpressionRests :
    ExpressionRest ExpressionRests
    | 
    ;

ExpressionRest :
    COMMA Expression
    ;

ExpressionListOpt :
    ExpressionList
    | 
    ;






    
PrimaryExpression :
    INTEGER_LITERAL
    | TrueLiteral
    | FalseLiteral
    | IDENTIFIER
    | ThisExpression
    | ArrayAllocationExpression
    | AllocationExpression
    | NotExpression
    | BracketExpression
    ;

TrueLiteral :
    TRUE_
    ;

FalseLiteral :
    FALSE_
    ;

ThisExpression :
    THIS
    ;

ArrayAllocationExpression :
    NEW INT SQUAREOPEN Expression SQUARECLOSE
    ;

AllocationExpression :
    NEW IDENTIFIER LEFTPAR RIGHTPAR
    ;

NotExpression :
    NOT Expression
    ;

BracketExpression :
    LEFTPAR Expression RIGHTPAR
    ;

Macrodefinition :
    MacroDefExpression
    | MacroDefStatement



MacroDefExpression :
    DEFINE IDENTIFIER LEFTPAR IdentifierListOpt RIGHTPAR Block
    ;

MacroDefStatement :
    DEFINE IDENTIFIER LEFTPAR IdentifierListOpt RIGHTPAR BracketExpression
    ;

IdentifierListOpt :
    IDENTIFIER IdentifierListRests
    | 
    ;

IdentifierListRests :
    IdentifierRest IdentifierListRests
    |
    ;

IdentifierRest :
    COMMA IDENTIFIER
    ;


    

    
%%


void yyerror(char *s) {
    fprintf(stderr, "Syntax error: %s\n", s);
    exit(1);
}

int main(void) {
    // if (yyparse() == 0) { 
    //     // cout << final_code << endl;
    // }
    return 0;
}
