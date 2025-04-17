#include <stdio.h>
#include "ast.h"

extern int yyparse();
extern FILE* yyin;              // ✅ Declare yyin to redirect parser input
extern ASTNode* ast_root;

int main() {
    // Open input file
    yyin = fopen("input.c", "r");   // ✅ Open input.c for parsing
    if (!yyin) {
        perror("input.c");
        return 1;
    }

    // Open output file
    FILE* out = fopen("output.txt", "w");
    if (!out) {
        perror("output.txt");
        return 1;
    }

    // Run parser
    yyparse();

    // Print AST
    fprintf(out, "AST:\n");
    print_ast(ast_root, out, 0);

    fclose(yyin);
    fclose(out);

    printf("AST saved to output.txt\n");
    return 0;
}
