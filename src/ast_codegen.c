#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDREN 10
#define MAX_LINE 512

typedef enum {
    NODE_FUNCTION_DEF, NODE_SEQUENCE, NODE_DECLARATION,
    NODE_INT, NODE_VAR, NODE_STRING,
    NODE_BINARY_EXPR, NODE_UNARY_EXPR,
    NODE_IF_STMT, NODE_FOR_STMT, NODE_FUNCTION_CALL,
    NODE_EXPR_LIST, NODE_RETURN_STMT,
    NODE_UNKNOWN
} NodeType;

typedef struct ASTNode {
    NodeType type;
    char name[64];              // For VAR, FUNC names
    char string_value[128];     // For STRING ("...")
    int int_value;              // For INT (n)
    struct ASTNode *children[MAX_CHILDREN];
    int child_count;
    int indent;
} ASTNode;

// Helper to detect node type
NodeType get_node_type(const char *line) {
    if (strstr(line, "FUNCTION_DEF")) return NODE_FUNCTION_DEF;
    if (strstr(line, "SEQUENCE")) return NODE_SEQUENCE;
    if (strstr(line, "DECLARATION")) return NODE_DECLARATION;
    if (strstr(line, "INT (")) return NODE_INT;
    if (strstr(line, "VAR (")) return NODE_VAR;
    if (strstr(line, "STRING (")) return NODE_STRING;
    if (strstr(line, "BINARY_EXPR")) return NODE_BINARY_EXPR;
    if (strstr(line, "UNARY_EXPR")) return NODE_UNARY_EXPR;
    if (strstr(line, "IF_STMT")) return NODE_IF_STMT;
    if (strstr(line, "FOR_STMT")) return NODE_FOR_STMT;
    if (strstr(line, "FUNCTION_CALL")) return NODE_FUNCTION_CALL;
    if (strstr(line, "EXPR_LIST")) return NODE_EXPR_LIST;
    if (strstr(line, "RETURN_STMT")) return NODE_RETURN_STMT;
    return NODE_UNKNOWN;
}

int count_indent(const char *line) {
    int spaces = 0;
    while (*line == ' ') {
        spaces++;
        line++;
    }
    return spaces / 2; // assuming 2 spaces per level
}

ASTNode *create_node(const char *line) {
    ASTNode *node = malloc(sizeof(ASTNode));
    memset(node, 0, sizeof(ASTNode));
    node->indent = count_indent(line);
    node->type = get_node_type(line);

    const char *p = strchr(line, '(');
    if (p) {
        if (node->type == NODE_DECLARATION || node->type == NODE_FUNCTION_DEF ||
            node->type == NODE_FUNCTION_CALL || node->type == NODE_VAR) {
            sscanf(p + 1, "%[^)]", node->name);
        } else if (node->type == NODE_STRING) {
            sscanf(p + 1, " \"%[^\"]", node->string_value);
        } else if (node->type == NODE_INT) {
            sscanf(p + 1, "%d", &node->int_value);
        }
    }

    return node;
}

void add_child(ASTNode *parent, ASTNode *child) {
    if (parent && parent->child_count < MAX_CHILDREN) {
        parent->children[parent->child_count++] = child;
    }
}

ASTNode *parse_ast(FILE *fp) {
    char line[MAX_LINE];
    ASTNode *stack[100];
    int top = -1;

    int in_optimized_ast = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (!in_optimized_ast) {
            if (strstr(line, "Optimized AST:")) {
                in_optimized_ast = 1;
            }
            continue;
        }

        if (strlen(line) < 2) continue; // skip blank lines

        ASTNode *node = create_node(line);

        while (top >= 0 && node->indent <= stack[top]->indent)
            top--;

        if (top >= 0)
            add_child(stack[top], node);

        stack[++top] = node;
    }

    return (top >= 0) ? stack[0] : NULL;
}

// Utility for indentation
void print_indent(int level) {
    for (int i = 0; i < level; ++i)
        printf("    ");
}

// Expression printer
void print_expr(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case NODE_INT:
            printf("%d", node->int_value);
            break;
        case NODE_VAR:
            printf("%s", node->name);
            break;
        case NODE_STRING:
            printf("\"%s\"", node->string_value);
            break;
        case NODE_BINARY_EXPR:
            printf("(");
            print_expr(node->children[0]);
            printf(" + "); // simplified
            print_expr(node->children[1]);
            printf(")");
            break;
        case NODE_UNARY_EXPR:
            printf("++");
            print_expr(node->children[0]);
            break;
        case NODE_EXPR_LIST:
            for (int i = 0; i < node->child_count; ++i) {
                print_expr(node->children[i]);
                if (i < node->child_count - 1)
                    printf(", ");
            }
            break;
        default:
            break;
    }
}

// Code generator
void generate_code(ASTNode *node, int indent) {
    if (!node) return;

    switch (node->type) {
        case NODE_FUNCTION_DEF:
            printf("int %s() {\n", node->name);
            for (int i = 0; i < node->child_count; ++i)
                generate_code(node->children[i], indent + 1);
            printf("}\n");
            break;

        case NODE_SEQUENCE:
            for (int i = 0; i < node->child_count; ++i)
                generate_code(node->children[i], indent);
            break;

        case NODE_DECLARATION:
            print_indent(indent);
            printf("int %s = ", node->name);
            print_expr(node->children[0]);
            printf(";\n");
            break;

        case NODE_FUNCTION_CALL:
            print_indent(indent);
            printf("%s(", node->name);
            if (node->child_count > 0)
                print_expr(node->children[0]);
            printf(");\n");
            break;

        case NODE_RETURN_STMT:
            print_indent(indent);
            printf("return ");
            print_expr(node->children[0]);
            printf(";\n");
            break;

        default:
            break;
    }
}

// Main
int main() {
    FILE *fp = fopen("output.txt", "r");
    if (!fp) {
        perror("File open failed");
        return 1;
    }

    ASTNode *root = parse_ast(fp);
    fclose(fp);

    if (!root) {
        printf("Failed to parse AST.\n");
        return 1;
    }

    generate_code(root, 0);
    return 0;
}
