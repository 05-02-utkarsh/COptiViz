%{
#include <iostream>
#include <memory>
#include "ast.hpp"

extern int yylex();
void yyerror(const char *s);

std::shared_ptr<ASTNode> astRoot;
%}

%union {
    int intval;
    char* strval;
    ASTNodePtr node;
}

%token <strval> IDENTIFIER
%token <strval> NUMBER
%token IF ELSE WHILE FOR RETURN INT VOID
%token EQ NEQ LEQ GEQ
%token AND OR
%token PLUS MINUS MUL DIV
%token ASSIGN
%token SEMICOLON COMMA
%token LPAREN RPAREN LBRACE RBRACE
%token LT GT

%type <node> program function_decl compound_stmt stmt expr

%%

program
    : function_decl { astRoot = $1; }
    ;

function_decl
    : INT IDENTIFIER LPAREN RPAREN compound_stmt {
        $$ = std::make_shared<FunctionDecl>("int", $2, $5);
    }
    ;

compound_stmt
    : LBRACE stmt_list RBRACE {
        $$ = std::make_shared<CompoundStmt>();
        for (auto& stmt : *$2) {
            std::dynamic_pointer_cast<CompoundStmt>($$)->addStatement(stmt);
        }
    }
    ;

stmt_list
    : stmt_list stmt {
        $$ = $1;
        $$->push_back($2);
    }
    | /* empty */ {
        $$ = new std::vector<ASTNodePtr>();
    }
    ;

stmt
    : expr SEMICOLON {
        $$ = $1;
    }
    | RETURN expr SEMICOLON {
        $$ = std::make_shared<ReturnStmt>($2);
    }
    | IF LPAREN expr RPAREN stmt ELSE stmt {
        $$ = std::make_shared<IfStmt>($3, $5, $7);
    }
    | IF LPAREN expr RPAREN stmt {
        $$ = std::make_shared<IfStmt>($3, $5, nullptr);
    }
    | WHILE LPAREN expr RPAREN stmt {
        $$ = std::make_shared<WhileStmt>($3, $5);
    }
    | FOR LPAREN expr SEMICOLON expr SEMICOLON expr RPAREN stmt {
        $$ = std::make_shared<ForStmt>($3, $5, $7, $9);
    }
    | compound_stmt {
        $$ = $1;
    }
    ;

expr
    : IDENTIFIER ASSIGN expr {
        $$ = std::make_shared<Assignment>($1, $3);
    }
    | expr PLUS expr {
        $$ = std::make_shared<BinaryExpr>("+", $1, $3);
    }
    | expr MINUS expr {
        $$ = std::make_shared<BinaryExpr>("-", $1, $3);
    }
    | expr MUL expr {
        $$ = std::make_shared<BinaryExpr>("*", $1, $3);
    }
    | expr DIV expr {
        $$ = std::make_shared<BinaryExpr>("/", $1, $3);
    }
    | LPAREN expr RPAREN {
        $$ = $2;
    }
    | IDENTIFIER {
        $$ = std::make_shared<Variable>($1);
    }
    | NUMBER {
        $$ = std::make_shared<Literal>($1);
    }
    ;

%%

void yyerror(const char *s) {
    std::cerr << "Parse error: " << s << std::endl;
}
