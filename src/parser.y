%code requires {
    #include "ast.h"
}

%{
#include <stdio.h>
#include "ast.h"

extern int yylex();
void yyerror(const char* s) { fprintf(stderr, "Parse error: %s\n", s); }

ASTNode* ast_root;
%}

%union {
    int ival;
    char* str;
    ASTNode* node;
}

%token <ival> NUMBER
%token <str> IDENTIFIER
%type <node> stmt expr
%left '+' '-' 
%left '*' '/' 
%token '=' ';'

%%

stmt:
    IDENTIFIER '=' expr ';'     { ast_root = make_assign_node($1, $3); }
;

expr:
    expr '+' expr               { $$ = make_binop_node('+', $1, $3); }
  | expr '-' expr               { $$ = make_binop_node('-', $1, $3); }
  | expr '*' expr               { $$ = make_binop_node('*', $1, $3); }
  | expr '/' expr               { $$ = make_binop_node('/', $1, $3); }
  | NUMBER                      { $$ = make_int_node($1); }
  | IDENTIFIER                  { $$ = make_var_node($1); }
;

%%
