#include "ast.hpp"

#include <iostream>
#include <string>


ASTNodePtr astRoot = nullptr;


static void printIndent(int indent) {
    for (int i = 0; i < indent; ++i)
        std::cout << "  ";
}

void Program::addFunction(ASTNodePtr func) {
    functions.push_back(func);
}

void Program::print(int indent) const {
    printIndent(indent);
    std::cout << "Program\n";
    for (auto& func : functions)
        func->print(indent + 1);
}

FunctionDecl::FunctionDecl(const std::string& retType, const std::string& name, ASTNodePtr body)
    : returnType(retType), name(name), body(body) {}

void FunctionDecl::print(int indent) const {
    printIndent(indent);
    std::cout << "FunctionDecl: " << returnType << " " << name << "\n";
    if (body) body->print(indent + 1);
}

void CompoundStmt::addStatement(ASTNodePtr stmt) {
    statements.push_back(stmt);
}

void CompoundStmt::print(int indent) const {
    printIndent(indent);
    std::cout << "CompoundStmt\n";
    for (auto& stmt : statements)
        stmt->print(indent + 1);
}

IfStmt::IfStmt(ASTNodePtr cond, ASTNodePtr thenBr, ASTNodePtr elseBr)
    : condition(cond), thenBranch(thenBr), elseBranch(elseBr) {}

void IfStmt::print(int indent) const {
    printIndent(indent);
    std::cout << "IfStmt\n";
    condition->print(indent + 1);
    thenBranch->print(indent + 1);
    if (elseBranch) {
        printIndent(indent);
        std::cout << "ElseBranch\n";
        elseBranch->print(indent + 1);
    }
}

WhileStmt::WhileStmt(ASTNodePtr cond, ASTNodePtr body) : condition(cond), body(body) {}

void WhileStmt::print(int indent) const {
    printIndent(indent);
    std::cout << "WhileStmt\n";
    condition->print(indent + 1);
    body->print(indent + 1);
}

ForStmt::ForStmt(ASTNodePtr init, ASTNodePtr cond, ASTNodePtr upd, ASTNodePtr body)
    : init(init), condition(cond), update(upd), body(body) {}

void ForStmt::print(int indent) const {
    printIndent(indent);
    std::cout << "ForStmt\n";
    if (init) init->print(indent + 1);
    if (condition) condition->print(indent + 1);
    if (update) update->print(indent + 1);
    body->print(indent + 1);
}

ReturnStmt::ReturnStmt(ASTNodePtr expr) : expr(expr) {}

void ReturnStmt::print(int indent) const {
    printIndent(indent);
    std::cout << "ReturnStmt\n";
    expr->print(indent + 1);
}

BinaryExpr::BinaryExpr(const std::string& op, ASTNodePtr left, ASTNodePtr right)
    : op(op), left(left), right(right) {}

void BinaryExpr::print(int indent) const {
    printIndent(indent);
    std::cout << "BinaryExpr: " << op << "\n";
    left->print(indent + 1);
    right->print(indent + 1);
}

Literal::Literal(const std::string& value) : value(value) {}

void Literal::print(int indent) const {
    printIndent(indent);
    std::cout << "Literal: " << value << "\n";
}

Variable::Variable(const std::string& name) : name(name) {}

void Variable::print(int indent) const {
    printIndent(indent);
    std::cout << "Variable: " << name << "\n";
}

Assignment::Assignment(const std::string& varName, ASTNodePtr expr)
    : varName(varName), expr(expr) {}

void Assignment::print(int indent) const {
    printIndent(indent);
    std::cout << "Assignment to " << varName << "\n";
    expr->print(indent + 1);
}
void FunctionDecl::print(int indent) const {
    printIndent(indent);
    std::cout << "FunctionDecl: " << returnType << " " << name << "\n";
    if (body) body->print(indent + 1);
}

void CompoundStmt::addStatement(ASTNodePtr stmt) {
    statements.push_back(stmt);
}

void CompoundStmt::print(int indent) const {
    printIndent(indent);
    std::cout << "CompoundStmt\n";
    for (auto& stmt : statements)
        stmt->print(indent + 1);
}

IfStmt::IfStmt(ASTNodePtr cond, ASTNodePtr thenBr, ASTNodePtr elseBr)
    : condition(cond), thenBranch(thenBr), elseBranch(elseBr) {}

void IfStmt::print(int indent) const {
    printIndent(indent);
    std::cout << "IfStmt\n";
    if (condition) {
        printIndent(indent + 1);
        std::cout << "Condition:\n";
        condition->print(indent + 2);
    }
    if (thenBranch) {
        printIndent(indent + 1);
        std::cout << "Then:\n";
        thenBranch->print(indent + 2);
    }
    if (elseBranch) {
        printIndent(indent + 1);
        std::cout << "Else:\n";
        elseBranch->print(indent + 2);
    }
}

WhileStmt::WhileStmt(ASTNodePtr cond, ASTNodePtr body)
    : condition(cond), body(body) {}

void WhileStmt::print(int indent) const {
    printIndent(indent);
    std::cout << "WhileStmt\n";
    if (condition) {
        printIndent(indent + 1);
        std::cout << "Condition:\n";
        condition->print(indent + 2);
    }
    if (body) {
        printIndent(indent + 1);
        std::cout << "Body:\n";
        body->print(indent + 2);
    }
}

ForStmt::ForStmt(ASTNodePtr init, ASTNodePtr cond, ASTNodePtr upd, ASTNodePtr body)
    : init(init), condition(cond), update(upd), body(body) {}

void ForStmt::print(int indent) const {
    printIndent(indent);
    std::cout << "ForStmt\n";
    if (init) {
        printIndent(indent + 1);
        std::cout << "Init:\n";
        init->print(indent + 2);
    }
    if (condition) {
        printIndent(indent + 1);
        std::cout << "Condition:\n";
        condition->print(indent + 2);
    }
    if (update) {
        printIndent(indent + 1);
        std::cout << "Update:\n";
        update->print(indent + 2);
    }
    if (body) {
        printIndent(indent + 1);
        std::cout << "Body:\n";
        body->print(indent + 2);
    }
}

ReturnStmt::ReturnStmt(ASTNodePtr expr)
    : expr(expr) {}

void ReturnStmt::print(int indent) const {
    printIndent(indent);
    std::cout << "ReturnStmt\n";
    if (expr)
        expr->print(indent + 1);
}

BinaryExpr::BinaryExpr(const std::string& op, ASTNodePtr left, ASTNodePtr right)
    : op(op), left(left), right(right) {}

void BinaryExpr::print(int indent) const {
    printIndent(indent);
    std::cout << "BinaryExpr: " << op << "\n";
    if (left) left->print(indent + 1);
    if (right) right->print(indent + 1);
}

Literal::Literal(const std::string& value)
    : value(value) {}

void Literal::print(int indent) const {
    printIndent(indent);
    std::cout << "Literal: " << value << "\n";
}

Variable::Variable(const std::string& name)
    : name(name) {}

void Variable::print(int indent) const {
    printIndent(indent);
    std::cout << "Variable: " << name << "\n";
}

Assignment::Assignment(const std::string& varName, ASTNodePtr expr)
    : varName(varName), expr(expr) {}

void Assignment::print(int indent) const {
    printIndent(indent);
    std::cout << "Assignment to: " << varName << "\n";
    if (expr)
        expr->print(indent + 1);
}
