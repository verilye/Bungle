#ifndef INTERPRETER
#define INTERPRETER

#include <string>
#include "ExprGen.h"
#include <iostream>

class Interpreter : public ExprVisitor{

public:
    Interpreter(){}
    std::string visitLiteralExprGen(Literal* expr);
    std::string visitGroupingExprGen(Grouping* expr);
    std::string visitUnaryExprGen(Unary* expr);
    std::string visitBinaryExprGen(Binary * expr);

private:
    std::string evaulate(const Expr* expr);
    bool isTruthy(std::string object);
    bool checkIfNum(std::string num);
    bool isEqual(std::string a, std::string b);

};


#endif