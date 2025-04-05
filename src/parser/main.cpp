#include <iostream>
#include <memory>
#include "ast.hpp"

extern int yyparse();
extern std::shared_ptr<ASTNode> astRoot;

int main() {
    if (yyparse() == 0) {
        if (astRoot) {
            astRoot->print();
        } else {
            std::cerr << "AST root is null!" << std::endl;
        }
    } else {
        std::cerr << "Parsing failed!" << std::endl;
    }
    return 0;
}


// This main.cpp will:

// Call yyparse()

// If parsing succeeds, print the AST by calling astRoot->print().

