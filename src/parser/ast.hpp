#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <memory>

dnk.wbqcakjbm
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void print(int indent = 0) const = 0;
};

using ASTNodePtr = std::shared_ptr<ASTNode>;

class Program : public ASTNode {
public:
    std::vector<ASTNodePtr> functions;
    void addFunction(ASTNodePtr func);
    void print(int indent = 0) const override;
};

class FunctionDecl : public ASTNode {
public:
    std::string returnType;
    std::string name;
    ASTNodePtr body;
    FunctionDecl(const std::string& retType, const std::string& name, ASTNodePtr body);
    void print(int indent = 0) const override;
};

class CompoundStmt : public ASTNode {
public:
    std::vector<ASTNodePtr> statements;
    void addStatement(ASTNodePtr stmt);
    void print(int indent = 0) const override;
};

class IfStmt : public ASTNode {
public:
    ASTNodePtr condition;
    ASTNodePtr thenBranch;
    ASTNodePtr elseBranch;
    IfStmt(ASTNodePtr cond, ASTNodePtr thenBr, ASTNodePtr elseBr = nullptr);
    void print(int indent = 0) const override;
};

class WhileStmt : public ASTNode {
public:
    ASTNodePtr condition;
    ASTNodePtr body;
    WhileStmt(ASTNodePtr cond, ASTNodePtr body);
    void print(int indent = 0) const override;
};

class ForStmt : public ASTNode {
public:
    ASTNodePtr init;
    ASTNodePtr condition;
    ASTNodePtr update;
    ASTNodePtr body;
    ForStmt(ASTNodePtr init, ASTNodePtr cond, ASTNodePtr upd, ASTNodePtr body);
    void print(int indent = 0) const override;
};

class ReturnStmt : public ASTNode {
public:
    ASTNodePtr expr;
    ReturnStmt(ASTNodePtr expr);
    void print(int indent = 0) const override;
};

class BinaryExpr : public ASTNode {
public:
    std::string op;
    ASTNodePtr left;
    ASTNodePtr right;
    BinaryExpr(const std::string& op, ASTNodePtr left, ASTNodePtr right);
    void print(int indent = 0) const override;
};

class Literal : public ASTNode {
public:
    std::string value;
    Literal(const std::string& value);
    void print(int indent = 0) const override;
};

class Variable : public ASTNode {
public:
    std::string name;
    Variable(const std::string& name);
    void print(int indent = 0) const override;
};

class Assignment : public ASTNode {
public:
    std::string varName;
    ASTNodePtr expr;
    Assignment(const std::string& varName, ASTNodePtr expr);
    void print(int indent = 0) const override;
};
extern ASTNodePtr astRoot;

#endif // AST_H
