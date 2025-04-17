#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

ASTNode* make_int_node(int value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_INT;
    node->int_val = value;
    return node;
}

ASTNode* make_var_node(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_VAR;
    node->var_name = strdup(name);
    return node;
}

ASTNode* make_binop_node(char op, ASTNode* left, ASTNode* right) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_BINOP;
    node->binop.op = op;
    node->binop.left = left;
    node->binop.right = right;
    return node;
}

ASTNode* make_assign_node(char* lhs, ASTNode* rhs) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ASSIGN;
    node->assign.lhs = strdup(lhs);
    node->assign.rhs = rhs;
    return node;
}

void print_ast(ASTNode* root, FILE* fp, int indent) {
    for (int i = 0; i < indent; i++) fprintf(fp, "  ");
    if (!root) {
        fprintf(fp, "(null)\n");
        return;
    }
    switch (root->type) {
        case NODE_INT:
            fprintf(fp, "INT: %d\n", root->int_val);
            break;
        case NODE_VAR:
            fprintf(fp, "VAR: %s\n", root->var_name);
            break;
        case NODE_BINOP:
            fprintf(fp, "BINOP: %c\n", root->binop.op);
            print_ast(root->binop.left, fp, indent + 1);
            print_ast(root->binop.right, fp, indent + 1);
            break;
        case NODE_ASSIGN:
            fprintf(fp, "ASSIGN: %s =\n", root->assign.lhs);
            print_ast(root->assign.rhs, fp, indent + 1);
            break;
    }
}
