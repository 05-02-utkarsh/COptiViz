
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "y.tab.h"
#include "tokens.h"



// Declaring yylval because we are using Bison and want to pass values (e.g., identifiers, numbers)
//extern YYSTYPE yylval;

/*niche kis 12 se 19 tak filhaal ke liye jodi hai*/
typedef union {
    int ival;
    float fval;
    char* str;
} YYSTYPE;

extern YYSTYPE yylval;
YYSTYPE yylval;



#define PRINT_TOKEN(tok) do { printf(#tok); } while(0)
#define PRINT_TOKEN_VAL(tok, val) do { printf(#tok "(%s)\n", val); } while(0)
#define PRINT_TOKEN_INT(tok, val) do { printf(#tok "(%d)\n", val); } while(0)
#define PRINT_TOKEN_FLOAT(tok, val) do { printf(#tok "(%lf)\n", (double)(val)); } while(0)

%}

/* Regex definitions */
DIGIT        [0-9]
LETTER       [a-zA-Z_]
ID           {LETTER}({LETTER}|{DIGIT})*
INT_CONST    {DIGIT}+
FLOAT_CONST  ({DIGIT}+"."{DIGIT}*|"."{DIGIT}+)

%%

 /* Keywords */  
                
"auto"          { PRINT_TOKEN(TOK_AUTO); printf("\n"); return TOK_AUTO; }
"break"         { PRINT_TOKEN(TOK_BREAK); printf("\n"); return TOK_BREAK; }
"case"          { PRINT_TOKEN(TOK_CASE); printf("\n"); return TOK_CASE; }
"char"          { PRINT_TOKEN(TOK_CHAR); printf("\n"); return TOK_CHAR; }
"const"         { PRINT_TOKEN(TOK_CONST); printf("\n"); return TOK_CONST; }
"continue"      { PRINT_TOKEN(TOK_CONTINUE); printf("\n"); return TOK_CONTINUE; }
"default"       { PRINT_TOKEN(TOK_DEFAULT); printf("\n"); return TOK_DEFAULT; }
"do"            { PRINT_TOKEN(TOK_DO); printf("\n"); return TOK_DO; }
"double"        { PRINT_TOKEN(TOK_DOUBLE); printf("\n"); return TOK_DOUBLE; }
"else"          { PRINT_TOKEN(TOK_ELSE); printf("\n"); return TOK_ELSE; }
"enum"          { PRINT_TOKEN(TOK_ENUM); printf("\n"); return TOK_ENUM; }
"extern"        { PRINT_TOKEN(TOK_EXTERN); printf("\n"); return TOK_EXTERN; }
"float"         { PRINT_TOKEN(TOK_FLOAT); printf("\n"); return TOK_FLOAT; }
"for"           { PRINT_TOKEN(TOK_FOR); printf("\n"); return TOK_FOR; }
"goto"          { PRINT_TOKEN(TOK_GOTO); printf("\n"); return TOK_GOTO; }
"if"            { PRINT_TOKEN(TOK_IF); printf("\n"); return TOK_IF; }
"int"           { PRINT_TOKEN(TOK_INT); printf("\n"); return TOK_INT; }
"long"          { PRINT_TOKEN(TOK_LONG); printf("\n"); return TOK_LONG; }
"register"      { PRINT_TOKEN(TOK_REGISTER); printf("\n"); return TOK_REGISTER; }
"return"        { PRINT_TOKEN(TOK_RETURN); printf("\n"); return TOK_RETURN; }
"short"         { PRINT_TOKEN(TOK_SHORT); printf("\n"); return TOK_SHORT; }
"signed"        { PRINT_TOKEN(TOK_SIGNED); printf("\n"); return TOK_SIGNED; }
"sizeof"        { PRINT_TOKEN(TOK_SIZEOF); printf("\n"); return TOK_SIZEOF; }
"static"        { PRINT_TOKEN(TOK_STATIC); printf("\n"); return TOK_STATIC; }
"struct"        { PRINT_TOKEN(TOK_STRUCT); printf("\n"); return TOK_STRUCT; }
"switch"        { PRINT_TOKEN(TOK_SWITCH); printf("\n"); return TOK_SWITCH; }
"typedef"       { PRINT_TOKEN(TOK_TYPEDEF); printf("\n"); return TOK_TYPEDEF; }
"union"         { PRINT_TOKEN(TOK_UNION); printf("\n"); return TOK_UNION; }
"unsigned"      { PRINT_TOKEN(TOK_UNSIGNED); printf("\n"); return TOK_UNSIGNED; }
"void"          { PRINT_TOKEN(TOK_VOID); printf("\n"); return TOK_VOID; }
"volatile"      { PRINT_TOKEN(TOK_VOLATILE); printf("\n"); return TOK_VOLATILE; }
"while"         { PRINT_TOKEN(TOK_WHILE); printf("\n"); return TOK_WHILE; }

 /* Operators and symbols */
"=="            { PRINT_TOKEN(TOK_EQ); printf("\n"); return TOK_EQ; }
"!="            { PRINT_TOKEN(TOK_NEQ); printf("\n"); return TOK_NEQ; }
"<="            { PRINT_TOKEN(TOK_LE); printf("\n"); return TOK_LE; }
">="            { PRINT_TOKEN(TOK_GE); printf("\n"); return TOK_GE; }
"="             { PRINT_TOKEN(TOK_ASSIGN); printf("\n"); return TOK_ASSIGN; }
"<"             { PRINT_TOKEN(TOK_LT); printf("\n"); return TOK_LT; }
">"             { PRINT_TOKEN(TOK_GT); printf("\n"); return TOK_GT; }
"++"            { PRINT_TOKEN(TOK_INC); printf("\n"); return TOK_INC; }
"--"            { PRINT_TOKEN(TOK_DEC); printf("\n"); return TOK_DEC; }
"+"             { PRINT_TOKEN(TOK_PLUS); printf("\n"); return TOK_PLUS; }
"-"             { PRINT_TOKEN(TOK_MINUS); printf("\n"); return TOK_MINUS; }
"*"             { PRINT_TOKEN(TOK_MULT); printf("\n"); return TOK_MULT; }
"/"             { PRINT_TOKEN(TOK_DIV); printf("\n"); return TOK_DIV; }
"%"             { PRINT_TOKEN(TOK_MOD); printf("\n"); return TOK_MOD; }
"&&"            { PRINT_TOKEN(TOK_AND); printf("\n"); return TOK_AND; }
"||"            { PRINT_TOKEN(TOK_OR); printf("\n"); return TOK_OR; }
"!"             { PRINT_TOKEN(TOK_NOT); printf("\n"); return TOK_NOT; }
"&"             { PRINT_TOKEN(TOK_BITAND); printf("\n"); return TOK_BITAND; }
"|"             { PRINT_TOKEN(TOK_BITOR); printf("\n"); return TOK_BITOR; }
"^"             { PRINT_TOKEN(TOK_BITXOR); printf("\n"); return TOK_BITXOR; }
"~"             { PRINT_TOKEN(TOK_BITNOT); printf("\n"); return TOK_BITNOT; }
"<<"            { PRINT_TOKEN(TOK_SHL); printf("\n"); return TOK_SHL; }
">>"            { PRINT_TOKEN(TOK_SHR); printf("\n"); return TOK_SHR; }
"+="            { PRINT_TOKEN(TOK_PLUSEQ); printf("\n"); return TOK_PLUSEQ; }
"-="            { PRINT_TOKEN(TOK_MINUSEQ); printf("\n"); return TOK_MINUSEQ; }
"*="            { PRINT_TOKEN(TOK_MULTEQ); printf("\n"); return TOK_MULTEQ; }
"/="            { PRINT_TOKEN(TOK_DIVEQ); printf("\n"); return TOK_DIVEQ; }
"%="            { PRINT_TOKEN(TOK_MODEQ); printf("\n"); return TOK_MODEQ; }

 /* Punctuation */
";"             { PRINT_TOKEN(TOK_SEMICOLON); printf("\n"); return TOK_SEMICOLON; }
","             { PRINT_TOKEN(TOK_COMMA); printf("\n"); return TOK_COMMA; }
"."             { PRINT_TOKEN(TOK_DOT); printf("\n"); return TOK_DOT; }
"->"            { PRINT_TOKEN(TOK_ARROW); printf("\n"); return TOK_ARROW; }
"("             { PRINT_TOKEN(TOK_LPAREN); printf("\n"); return TOK_LPAREN; }
")"             { PRINT_TOKEN(TOK_RPAREN); printf("\n"); return TOK_RPAREN; }
"{"             { PRINT_TOKEN(TOK_LBRACE); printf("\n"); return TOK_LBRACE; }
"}"             { PRINT_TOKEN(TOK_RBRACE); printf("\n"); return TOK_RBRACE; }
"["             { PRINT_TOKEN(TOK_LBRACKET); printf("\n"); return TOK_LBRACKET; }
"]"             { PRINT_TOKEN(TOK_RBRACKET); printf("\n"); return TOK_RBRACKET; }
":"             { PRINT_TOKEN(TOK_COLON); printf("\n"); return TOK_COLON; }
"?"             { PRINT_TOKEN(TOK_QUESTION); printf("\n"); return TOK_QUESTION; }

 /* Identifiers */
{ID}            { yylval.str = strdup(yytext); PRINT_TOKEN_VAL(TOK_IDENTIFIER, yytext); return TOK_IDENTIFIER; }

 /* Literals */
{FLOAT_CONST}   { yylval.fval = atof(yytext); PRINT_TOKEN_FLOAT(TOK_FLOAT_LITERAL, yylval.fval); return TOK_FLOAT_LITERAL; }
{INT_CONST}     { yylval.ival = atoi(yytext); PRINT_TOKEN_INT(TOK_INT_LITERAL, yylval.ival); return TOK_INT_LITERAL; }


 /*Micellaneous*/  
\"          { /* double quote character */ 
                PRINT_TOKEN(TOK_DQUOTE);
                printf("\n");
                return TOK_DQUOTE;
            }

\'          { /* single quote character */ 
                PRINT_TOKEN(TOK_SQUOTE);
                printf("\n");
                return TOK_SQUOTE;
            }

\\          { /* backslash character */ 
                PRINT_TOKEN(TOK_BACKSLASH);
                printf("\n");
                return TOK_BACKSLASH;
            }



 /* Comments */
"//".*                      ;   // Ignore single-line comments
"/*"([^*]|\*[^/])*"\*/"     ;   // Ignore multi-line comments

 /* Whitespace (ignore) */
[ \t\r\n]+       ;

 /* Unknown characters(Error Handling) */
.                { printf("Unknown token: %s\n", yytext); return TOK_ERROR; }
 /*For non-printable characters, %s might show garbage.  we can use this if some problem comes.
 .               { printf("Unknown token: 0x%02x\n", yytext[0]); return TOK_ERROR; }

 */

%%

int yywrap(void) {
    return 1;
}



iuqrw

