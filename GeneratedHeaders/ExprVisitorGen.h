#ifndef EXPRVISITORGEN_H
#define EXPRVISITORGEN_H
#include "../token.h" 
#include <list> 
#include <string>

class Binary;
class Grouping;
class Literal;
class Unary;
class ExpressionStmt;
class PrintStmt;

class ExprVisitor { 
public:
	virtual std::string visitBinaryExprGen(const Binary* expression) = 0;
	virtual std::string visitGroupingExprGen(const Grouping* expression) = 0;
	virtual std::string visitLiteralExprGen(const Literal* expression) = 0;
	virtual std::string visitUnaryExprGen(const Unary* expression) = 0;
	virtual std::string visitExpressionStmtGen(const ExpressionStmt* expression) = 0;
	virtual std::string visitPrintStmtGen(const PrintStmt* expression) = 0;
};

#endif