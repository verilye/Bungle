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

class Expression : public Stmt {
public:
	const Expr* expression;
	Expression (const Expr* expression)
		:expression(expression){}

	virtual std::string accept(ExprVisitor* visitor) const override {
		return visitor->visitExpressionStmtGen(this);
	};
};

class Print : public Stmt {
public:
	const Expr* expression;
	Print (const Expr* expression)
		:expression(expression){}

	virtual std::string accept(ExprVisitor* visitor) const override {
		return visitor->visitPrintStmtGen(this);
	};
};

#endif