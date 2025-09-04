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
struct Macro {
    bool isExpression;               // true for expression macros
    vector<string> params; // parameter names
    string body;                // the macro body as text
};
map<string, Macro> macroTable;
static inline string trim(const string& s){
    size_t i=0, j=s.size();
    while(i<j && isspace((unsigned char)s[i])) ++i;
    while(j>i && isspace((unsigned char)s[j-1])) --j;
    return s.substr(i, j-i);
}

static vector<string> parseArgs(const string& s) {
    vector<string> out;
    string cur;
    int depth = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (c == '(' || c == '[' || c == '{') { depth++; cur.push_back(c); }
        else if (c == ')' || c == ']' || c == '}') { depth--; cur.push_back(c); }
        else if (c == ',' && depth == 0) { out.push_back(trim(cur)); cur.clear(); }
        else { cur.push_back(c); }
    }
    if (!cur.empty()) out.push_back(trim(cur));
    if (out.size() == 1 && out[0].empty()) out.clear(); // handle empty arg list
    return out;
}

#include <regex>

static string substituteParams(
    const string& body,
    const vector<string>& params,
    const vector<string>& args
) {
    string res = body;
    for (size_t i = 0; i < params.size(); ++i) {
        const string& p = params[i];
        const string& a = args[i];
        // \b doesn’t match inside identifiers; IDENTIFIERs are [A-Za-z_][A-Za-z0-9_]*
        regex re("\\b" + p + "\\b");
        res = regex_replace(res, re, a);
    }
    return res;
}



// Global table to store macro definitions
int indent = 0;
string indentation(int indent) {
    string ind = "";
    for (int i = 0; i < indent; i++) {
        ind += "    ";
    }
    return ind;
}


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
%type<val> Statements Statement UnmatchedStatement Block ClassType
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
    |{$$ = strdup("");}
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
    | ClassType{string s = string($1) + " "; $$ = strdup(s.c_str()); free($1);}
    | '(' Type ARROW Type ')'
    ;


ClassType
    : IDENTIFIER{ $$ = $1; }
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
        cout<<indentation(indent)<<$$;
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
        { $$ = strdup((string($1) + ".length").c_str()); free($1); }
    | Expression '.' IDENTIFIER '(' OptExprs ')'
        { $$ = strdup((string($1) + "." + string($3) + "(" + string($5) + ")").c_str()); free($1); free($3); }
    | NEW INT '[' Expression ']'
        { $$ = strdup(("new int[" + string($4) + "]").c_str()); free($4); }
    | NEW IDENTIFIER '(' ')'
        { $$ = strdup(("new " + string($2) + "()").c_str()); free($2); }
    | Expression '[' Expression ']'
        { $$ = strdup((string($1) + "[" + string($3) + "]").c_str()); free($1); free($3); }
    | '!' Expression
        { $$ = strdup(("!" + string($2)).c_str()); free($2); }
    | Expression '*' Expression
        { $$ = strdup((string($1) + " * " + string($3)).c_str()); free($1); free($3); }
    | Expression '/' Expression
        { $$ = strdup((string($1) + " / " + string($3)).c_str()); free($1); free($3); }
    | Expression '+' Expression
        { $$ = strdup((string($1) + " + " + string($3)).c_str()); free($1); free($3); }
    | Expression '-' Expression
        { $$ = strdup((string($1) + " - " + string($3)).c_str()); free($1); free($3); }
    | Expression LEQ Expression
        { $$ = strdup((string($1) + " <= " + string($3)).c_str()); free($1); free($3); }
    | Expression NEQ Expression
        { $$ = strdup((string($1) + " != " + string($3)).c_str()); free($1); free($3); }
    | Expression AND Expression
        { $$ = strdup((string($1) + " && " + string($3)).c_str()); free($1); free($3); }
    | Expression OR Expression
        { $$ = strdup((string($1) + " || " + string($3)).c_str()); free($1); free($3); }
    | IDENTIFIER '(' OptExprs ')'
    {
        string name($1 ? $1 : "");
        string argsStr($3 ? $3 : "");

        // 1) Look up macro
        auto it = macroTable.find(name);
        if (it == macroTable.end()) {
            yyerror(("Unknown macro: " + name).c_str());
            if ($1) free($1);
            if ($3) free($3);
            YYERROR; // or exit(1);
        }
        const Macro& macro = it->second;
        if (!macro.isExpression) {
            yyerror(("Macro is not an expression macro: " + name).c_str());
            if ($1) free($1);
            if ($3) free($3);
            YYERROR;
        }

        // 2) Parse args robustly
        vector<string> args = parseArgs(argsStr);

        // 3) Arity check
        if (args.size() != macro.params.size()) {
            ostringstream oss;
            oss << "Macro '" << name << "' expects " << macro.params.size()
                << " arg(s), got " << args.size();
            yyerror(oss.str().c_str());
            if ($1) free($1);
            if ($3) free($3);
            YYERROR;
        }

        // 4) Substitute with word-boundary safety
        string expanded = substituteParams(macro.body, macro.params, args);

        // (Optional) recursive expansion: if your spec allows macros inside macro bodies,
        // you can feed 'expanded' back through a small expander loop before returning.

        // 5) Set semantic value (as char*)
        $$ = strdup(expanded.c_str());

        if ($1) free($1);
        if ($3) free($3);
    }   

    | '(' Expression ')'
        { $$ = strdup(("(" + string($2) + ")").c_str()); free($2); }
    | Expression ARROW Expression
        { $$ = strdup((string($1) + " -> " + string($3)).c_str()); free($1); free($3); }
    | Expression '.' APPLY '(' Expression ')'
        { $$ = strdup((string($1) + ".apply(" + string($5) + ")").c_str()); free($1); free($5); }
    ;

MacroDefinition :
    MacroDefExpression
    | MacroDefStatement
    ;

MacroDefExpression
    : DEFINE IDENTIFIER '(' OptIdList ')' '(' Expression ')'
    {
        string name = string($2);
        string paramsStr = string($4);
        vector<string> params;
        string temp = "";
        if (paramsStr != "") {
            for(int i=0;i<paramsStr.size();i++){
                if(paramsStr[i]==','){
                    params.push_back(temp);
                    temp="";
                }
                else if(paramsStr[i]!=' '){
                    temp+=paramsStr[i];
                }
            }
            params.push_back(temp);
        }
        string body = string($7);

        Macro macro;
        macro.isExpression = true;
        macro.params = params;
        macro.body = body;

        macroTable[name] = macro;

        

        
    }
    ;

MacroDefStatement
    : DEFINE IDENTIFIER '(' OptIdList ')' '{' Statements '}'
    ;

OptIdList :
    IdList{$$ = $1; free($1);}
    |{ $$ = strdup(""); }
    ;

IdList :
    IDENTIFIER IdRests{$$ = strdup((string($1) + string($2)).c_str()); free($2); free($1);}
    ;

IdRests :
    IdRest IdRests{$$ = strdup((string($1) + string($2)).c_str()); free($2);}
    |{ $$ = strdup(""); }
    ;

IdRest :
    ',' IDENTIFIER
    {
        $$ = strdup((string(", ") + string($2)).c_str());
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
}

int main(void) {
    return yyparse();
}