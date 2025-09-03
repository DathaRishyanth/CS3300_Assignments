%{
    #include <bits/stdc++.h>
    using namespace std;
    void yyerror(char *);
    int yylex(void);
%}

%union {
    string* str;
    int val;
    vector<string>* strlist;
}


%token<str> IDENTIFIER
%token<val> INTEGER_LITERAL
%token CLASS PUBLIC STATIC VOID MAIN STRING EXTENDS RETURN INT BOOLEAN IF ELSE WHILE THIS NEW FOR DEFINE
        PRINT LEFTPAR RIGHTPAR CURLYOPEN CURLYCLOSE SQUAREOPEN SQUARECLOSE SEMICOLON PLUS MINUS MULTIPLY DIVIDE ASSIGN EQUAL NOTEQUAL
        LESSTHAN GREATERTHAN LESSEQUAL GREATEREQUAL ARROW AND OR NOT DOT COMMA ANDAND OROR LENGTH DO TRUE_ FALSE_

%type<str> Goal MainClass TypeDeclarations TypeDeclaration MethodDeclarations MethodDeclaration
%type<str> Statements Statement Expression PrimaryExpression Type VariableDeclarations VariableDeclaration
%type<strlist>  ExpressionListOpt ExpressionListInBrackets

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

Macrodefinitions :
    Macrodefinition Macrodefinitions
    | 
    ;

MainClass :
    CLASS IDENTIFIER CURLYOPEN PUBLIC STATIC VOID MAIN LEFTPAR STRING SQUAREOPEN SQUARECLOSE IDENTIFIER RIGHTPAR CURLYOPEN PrintStatement CURLYCLOSE CURLYCLOSE
    ;

PrintStatement :
    PRINT LEFTPAR Expression RIGHTPAR SEMICOLON
    ;

TypeDeclarations :
    TypeDeclaration TypeDeclarations
    | 
    ;

TypeDeclaration :
    ClassDeclaration
    | ClassExtendsDeclaration
    ;

ClassDeclaration :
    CLASS IDENTIFIER CURLYOPEN VariableDeclarations MethodDeclarations CURLYCLOSE
    ;

ClassExtendsDeclaration :
    CLASS IDENTIFIER EXTENDS IDENTIFIER CURLYOPEN VariableDeclarations MethodDeclarations CURLYCLOSE
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



VariableDeclarations :
    VariableDeclaration VariableDeclarations
    | 
    ;
VariableDeclaration :
    Type IDENTIFIER SEMICOLON
    ;



Macrodefinition :
    MacroDefExpression
    | MacroDefStatement



  




Statements :
    Statement Statements
    | Statement
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
    IDENTIFIER EQUAL Expression SEMICOLON
    ;

ArrayAssignmentStatement :
    IDENTIFIER SQUAREOPEN Expression SQUARECLOSE EQUAL Expression SEMICOLON
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

PrintStatement :
    PRINT LEFTPAR Expression RIGHTPAR SEMICOLON
    ;

MacroStatement :
    IDENTIFIER LEFTPAR ExpressionListOpt RIGHTPAR SEMICOLON
    ;





ExpressionListOpt :
    Expression ExpressionListInBrackets
    |
    ;

ExpressionListInBrackets :
    COMMA Expression ExpressionListInBrackets
    |
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

MacroDefinition :
    MacroDefExpression
    | MacroDefStatement
    ;

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
