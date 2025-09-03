%{
    #include <bits/stdc++.h>
    using namespace std;
    void yyerror(char *);
    int yylex(void);
%}

%token CLASS PUBLIC RETURN IF ELSE WHILE DEFINE ARROW LENGTH
%token INT BOOLEAN VOID STRING
%token IDENTIFIER NUMBER TRUE_ FALSE_ THIS NEW NOT
%token ANDAND OROR LESSEQUAL NOTEQUAL PLUS MINUS MULTIPLY DIVIDE ASSIGN
%token CURLYOPEN CURLYCLOSE LEFTPAR RIGHTPAR SQUAREOPEN SQUARECLOSE SEMICOLON DOT

%nonassoc ELSE
%nonassoc IFX



%left OROR
%left ANDAND
%left LESSEQUAL NOTEQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE
%right NOT

%%

Goal : Macrodefinitions MainClass TypeDeclarations ;

MainClass : CLASS IDENTIFIER CURLYOPEN MethodDeclarations CURLYCLOSE ;

TypeDeclarations : /* empty */
                 | TypeDeclaration TypeDeclarations ;

TypeDeclaration : ClassDeclaration ;

ClassDeclaration : CLASS IDENTIFIER CURLYOPEN VariableDeclarations MethodDeclarations CURLYCLOSE ;

VariableDeclarations : /* empty */
                     | VariableDeclaration VariableDeclarations ;

VariableDeclaration : Type IDENTIFIER SEMICOLON ;

MethodDeclarations : /* empty */
                   | MethodDeclaration MethodDeclarations ;

MethodDeclaration : PUBLIC Type IDENTIFIER LEFTPAR FormalParamaterListOpt RIGHTPAR CURLYOPEN Statements RETURN Expression SEMICOLON CURLYCLOSE ;

FormalParamaterListOpt : /* empty */
                       | FormalParameterList ;

FormalParameterList : Type IDENTIFIER
                    | Type IDENTIFIER ',' FormalParameterList ;

Statements : /* empty */
           | Statement Statements ;

Statement : Block
          | IfStatement
          | WhileStatement
          | LocalDeclaration
          | AssignmentStatement
          | PrintStatement ;

Block : CURLYOPEN Statements CURLYCLOSE ;

IfStatement
    : IF LEFTPAR Expression RIGHTPAR Statement %prec IFX
    | IF LEFTPAR Expression RIGHTPAR Statement ELSE Statement
    ;

WhileStatement : WHILE LEFTPAR Expression RIGHTPAR Statement ;

LocalDeclaration : Type IDENTIFIER SEMICOLON ;

AssignmentStatement : IDENTIFIER ASSIGN Expression SEMICOLON ;

PrintStatement : IDENTIFIER DOT IDENTIFIER LEFTPAR Expression RIGHTPAR SEMICOLON ;

Type : INT
     | BOOLEAN
     | VOID
     | STRING
     | ClassType ;

ClassType : IDENTIFIER ;

Expression : Expression OROR Expression
           | Expression ANDAND Expression
           | Expression LESSEQUAL Expression
           | Expression NOTEQUAL Expression
           | Expression PLUS Expression
           | Expression MINUS Expression
           | Expression MULTIPLY Expression
           | Expression DIVIDE Expression
           | NOT Expression
           | PrimaryExpression ;

PrimaryExpression : IDENTIFIER
                  | NUMBER
                  | TRUE_
                  | FALSE_
                  | THIS
                  | NEW IDENTIFIER LEFTPAR RIGHTPAR
                  | LEFTPAR Expression RIGHTPAR
                  | PrimaryExpression SQUAREOPEN Expression SQUARECLOSE
                  | PrimaryExpression DOT LENGTH
                  | PrimaryExpression DOT IDENTIFIER LEFTPAR ExpressionListOpt RIGHTPAR ;

ExpressionListOpt : /* empty */
                  | ExpressionList ;

ExpressionList : Expression
               | Expression ',' ExpressionList ;

Macrodefinitions : /* empty */
                 | Macrodefinition Macrodefinitions ;

Macrodefinition : DEFINE IDENTIFIER LEFTPAR IdentifierListOpt RIGHTPAR BracketExpression ;

IdentifierListOpt : /* empty */
                  | IdentifierList ;

IdentifierList : IDENTIFIER
               | IDENTIFIER ',' IdentifierList ;

BracketExpression : LEFTPAR Expression RIGHTPAR ;

%%