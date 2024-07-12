#ifndef EXPRVISITORGEN_H
#define EXPRVISITORGEN_H
#include "token.h" 
#include <list> 
#include <string> 
#include "ExprGen.h" 
#include "StmtGen.h" 

class ExprVisitor { 
public:
	virtual std::string visitBinaryExprGen(const Binary* expression) = 0;
	virtual std::string visitGroupingExprGen(const Grouping* expression) = 0;
	virtual std::string visitLiteralExprGen(const Literal* expression) = 0;
	virtual std::string visitUnaryExprGen(const Unary* expression) = 0;
	virtual std::string visitExpressionStmtGen(const Expression* expression) = 0;
	virtual std::string visitPrintStmtGen(const Print* expression) = 0;
};

#endif