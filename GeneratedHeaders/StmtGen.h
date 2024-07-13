#ifndef STMTGEN_H
#define STMSGEN_H
#include "token.h" 
#include <list> 
#include <string> 
#include "ExprVisitorGen.h" 

class Stmt{ 
public:
	virtual ~Stmt() = default; 
	virtual std::string accept(ExprVisitor* visitor) const = 0; 
};

class ExpressionStmt : public Stmt {
public:
	const Expr* expression;
	ExpressionStmt (const Expr* expression)
		:expression(expression){}

	virtual std::string accept(ExprVisitor* visitor) const override {
		return visitor->visitExpressionStmtGen(this);
	};
};

class PrintStmt : public Stmt {
public:
	const Expr* expression;
	PrintStmt (const Expr* expression)
		:expression(expression){}

	virtual std::string accept(ExprVisitor* visitor) const override {
		return visitor->visitPrintStmtGen(this);
	};
};

#endif