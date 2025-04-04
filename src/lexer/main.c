#include <stdio.h>

extern int yylex();  // Declare the lexer function

int main() {
    return yylex();  // Call the lexer
}
