%{
    #include "y.tab.h"
    #include <bits/stdc++.h>
    using namespace std;
    void yyerror(char *);
%}


%%

"//".*                { /* ignore single-line comments */ }
"/*"([^*]|\*[^/])*"*/"    { /* ignore multi-line comments */ }


"class"                 { return CLASS; }
"public"                { return PUBLIC; }
"static"                { return STATIC; }
"void"                  { return VOID; }
"main"                  { return MAIN; }
"String"                { return STRING; }
"extends"               { return EXTENDS; }
"return"                { return RETURN; }
"int"                   { return INT; }
"boolean"               { return BOOLEAN; }
"length"                { return LENGTH; }
"true"                  { return TRUE_; }
"false"                 { return FALSE_; }

"if"                    { return IF; }
"else"                  { return ELSE; }
"while"                 { return WHILE; }
"this"                  { return THIS; }
"new"                   { return NEW; }
"do"                    { return DO; }



"#define"               { return DEFINE; }


"System.out.println"    { return PRINT; }

"("                  { return LEFTPAR; }
")"                  { return RIGHTPAR; }
"{"                  { return CURLYOPEN; }
"}"                  { return CURLYCLOSE; }
"["                  { return SQUAREOPEN; }
"]"                  { return SQUARECLOSE; }
";"                  { return SEMICOLON; }
"+"                  { return PLUS; }
"-"                  { return MINUS; }
"*"                  { return MULTIPLY; }
"/"                  { return DIVIDE; }
"="                  { return ASSIGN; }
"=="                 { return EQUAL; }
"!="                 { return NOTEQUAL; }
"<"                  { return LESSTHAN; }
">"                  { return GREATERTHAN; }
"<="                 { return LESSEQUAL; }

"->"                 { return ARROW; }
"&&"                 { return ANDAND; }
"&"                  { return AND; }
"|"                  { return OR; }  
"||"                 { return OROR; }
"!"                  { return NOT; }
"."                  { return DOT; }
","                  { return COMMA; }


[0-9]+                  { yylval.val = atoi(yytext); return INTEGER_LITERAL; }
[a-zA-Z_][a-zA-Z0-9_]*   { yylval.str = strdup(yytext); return IDENTIFIER; }

[ \t\r\n]+               { /* ignore whitespace */ }
.                   { /* ignore any other character */ }

%%
int yywrap(void) {
    return 1;
}

    