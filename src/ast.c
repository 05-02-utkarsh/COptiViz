#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* Create a new AST node - using your approach */
ASTNode* create_node(NodeType type, const char* value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    node->type = type;
    node->value = value ? strdup(value) : NULL;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    
    return node;
}

/* Add a child node to a parent node */
void add_child(ASTNode* parent, ASTNode* child) {
    if (!parent || !child) return;
    
    if (!parent->left) {
        parent->left = child;
    } else if (!parent->right) {
        parent->right = child;
    } else {
        /* If both children exist, add as sibling to right child */
        add_sibling(parent->right, child);
    }
}

/* Add a sibling node */
void add_sibling(ASTNode* node, ASTNode* sibling) {
    if (!node || !sibling) return;
    
    ASTNode* current = node;
    while (current->next) {
        current = current->next;
    }
    current->next = sibling;
}

/* Helper function to convert an integer to a string */
static char* int_to_str(int value) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%d", value);
    return strdup(buffer);
}

/* Helper function for string conversion */
static char* char_to_str(char c) {
    char buffer[2] = {c, '\0'};
    return strdup(buffer);
}

/* Create an integer literal node */
ASTNode* make_int_node(int value) {
    char* val_str = int_to_str(value);
    ASTNode* node = create_node(NODE_INT, val_str);
    free(val_str);
    return node;
}

/* Create a string literal node */
ASTNode* make_string_node(char* value) {
    return create_node(NODE_STRING, value);
}

/* Create a variable reference node */
ASTNode* make_var_node(char* name) {
    return create_node(NODE_VAR, name);
}

/* Create a binary operation node */
ASTNode* make_binop_node(char op, ASTNode* left, ASTNode* right) {
    char* op_str = char_to_str(op);
    ASTNode* node = create_node(NODE_BINOP, op_str);
    free(op_str);
    
    node->left = left;
    node->right = right;
    
    return node;
}

/* Create a unary operation node */
ASTNode* make_unary_node(char* op, ASTNode* expr) {
    ASTNode* node = create_node(NODE_UNARY, op);
    node->left = expr;
    return node;
}

/* Create a variable declaration node */
ASTNode* make_decl_node(char* name, ASTNode* init_expr) {
    ASTNode* node = create_node(NODE_DECL, name);
    node->left = init_expr;  /* Init expression is the left child */
    return node;
}

/* Create a function call node */
ASTNode* make_func_call_node(char* name, ASTNode* args) {
    ASTNode* node = create_node(NODE_FUNC_CALL, name);
    node->left = args;  /* Arguments are stored as left child */
    return node;
}

/* Create a function definition node */
ASTNode* make_function_node(char* name, ASTNode* body) {
    ASTNode* node = create_node(NODE_FUNC_DEF, name);
    node->left = body;  /* Body is stored as left child */
    return node;
}

/* Create an if statement node */
ASTNode* make_if_node(ASTNode* condition, ASTNode* then_body) {
    ASTNode* node = create_node(NODE_IF, NULL);
    node->left = condition;   /* Condition is stored as left child */
    node->right = then_body;  /* Then body is stored as right child */
    return node;
}

/* Create a for statement node */
ASTNode* make_for_node(ASTNode* init, ASTNode* condition, ASTNode* update, ASTNode* body) {
    ASTNode* node = create_node(NODE_FOR, NULL);
    
    /* Store init as left child */
    node->left = init;
    
    /* Store condition as right child */
    node->right = condition;
    
    /* Add update and body as siblings of condition */
    if (condition) {
        add_sibling(condition, update);
        if (update) {
            add_sibling(update, body);
        }
    }
    
    return node;
}

/* Create a return statement node */
ASTNode* make_return_node(ASTNode* expr) {
    ASTNode* node = create_node(NODE_RETURN, NULL);
    node->left = expr;  /* Expression is stored as left child */
    return node;
}

/* Create an expression list node */
ASTNode* make_expr_list_node(ASTNode* expr, ASTNode* next) {
    ASTNode* node = create_node(NODE_EXPR_LIST, NULL);
    node->left = expr;  /* Current expression is stored as left child */
    node->next = next;  /* Next expression is stored as next sibling */
    return node;
}

/* Create a sequence node */
ASTNode* make_seq_node(ASTNode* first, ASTNode* second) {
    ASTNode* node = create_node(NODE_SEQ, NULL);
    node->left = first;   /* First statement is stored as left child */
    node->right = second; /* Second statement is stored as right child */
    return node;
}

/* Create a type node */
ASTNode* make_type_node(char* type_name) {
    return create_node(NODE_TYPE, type_name);
}

/* Get node type as string for printing */
const char* get_node_type_str(NodeType type) {
    switch (type) {
        case NODE_INT: return "INT";
        case NODE_STRING: return "STRING";
        case NODE_VAR: return "VAR";
        case NODE_DECL: return "DECLARATION";
        case NODE_BINOP: return "BINARY_EXPR";
        case NODE_UNARY: return "UNARY_EXPR";
        case NODE_FUNC_CALL: return "FUNCTION_CALL";
        case NODE_FUNC_DEF: return "FUNCTION_DEF";
        case NODE_IF: return "IF_STMT";
        case NODE_FOR: return "FOR_STMT";
        case NODE_RETURN: return "RETURN_STMT";
        case NODE_EXPR_LIST: return "EXPR_LIST";
        case NODE_SEQ: return "SEQUENCE";
        case NODE_TYPE: return "TYPE";
        default: return "UNKNOWN";
    }
}

/* Print the AST */
void print_ast(ASTNode* node, FILE* output, int indent) {
    if (!node) return;
    
    /* Print indentation */
    for (int i = 0; i < indent; i++) {
        fprintf(output, "  ");
    }
    
    /* Print node info */
    fprintf(output, "%s", get_node_type_str(node->type));
    if (node->value) {
        fprintf(output, " (%s)", node->value);
    }
    fprintf(output, "\n");
    
    /* Print children */
    if (node->left) {
        print_ast(node->left, output, indent + 1);
    }
    
    if (node->right) {
        print_ast(node->right, output, indent + 1);
    }
    
    /* Print siblings */
    if (node->next) {
        print_ast(node->next, output, indent);
    }
}

/* Free AST memory */
void free_ast(ASTNode* node) {
    if (!node) return;
    
    if (node->value) {
        free(node->value);
    }
    
    if (node->left) {
        free_ast(node->left);
    }
    
    if (node->right) {
        free_ast(node->right);
    }
    
    if (node->next) {
        free_ast(node->next);
    }
    
    free(node);
}