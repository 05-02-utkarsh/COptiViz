#include <stdio.h>

extern int yylex();  // Declare the lexer function

int main() {
   
    yylex();    // Start scanning input
   
    return 0;
}
