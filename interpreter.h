#ifndef INTERPRETER
#define INTERPRETER

#include <string>
#include "genHeaders.h"
#include "RuntimeError.h"
#include <iostream>
#include "error.h"
#include <memory>

class Interpreter : public ExprVisitor{

public:

    Interpreter(){}
    void interpret(std::list<std::shared_ptr<Stmt>> statements);
    
    virtual std::string visitBinaryExprGen(const Binary * expression) override;
    virtual std::string visitGroupingExprGen(const Grouping* expression) override;
    virtual std::string visitLiteralExprGen(const Literal* expression) override;
    virtual std::string visitUnaryExprGen(const Unary* expression) override;
    virtual std::string visitExpressionStmtGen(const ExpressionStmt* expression) override;
    virtual std::string visitPrintStmtGen(const PrintStmt* expression) override;

private:
    std::string evaluate(const Expr* expr);
    void execute(std::shared_ptr<Stmt> stmt);
    std::string stringify(std::string output);
    bool isTruthy(std::string object);
    bool checkIfNum(std::string num);
    bool isEqual(std::string a, std::string b);
    void checkNumberOperand(const Token* operatorToken, std::string operand);
    void checkNumberOperands(const Token* operatorToken, std::string left, std::string right);

};

#endif