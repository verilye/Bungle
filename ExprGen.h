#ifndef EXPRGEN_H
#define EXPRGEN_H
#include "Token.h" 
#include <list> 
#include <string> 

class Binary;
class Grouping;
class Literal;
class Unary;

class ExprVisitor { 
public:
	virtual std::string visitBinaryExprGen(const Binary& expression) = 0;
	virtual std::string visitGroupingExprGen(const Grouping& expression) = 0;
	virtual std::string visitLiteralExprGen(const Literal& expression) = 0;
	virtual std::string visitUnaryExprGen(const Unary& expression) = 0;
};

class Expr { 
public:
	virtual ~Expr() = default; 
	virtual std::string accept(ExprVisitor& visitor) const = 0; 
};

class Binary : public Expr {
public:
	const Expr& left;
	 const Token& operatorToken;
	 const Expr& right;
	Binary (const Expr& left, const Token& operatorToken, const Expr& right)
		:left(left),operatorToken(operatorToken),right(right){}

	virtual std::string accept(ExprVisitor& visitor) const override {
		return visitor.visitBinaryExprGen(*this);
	};
};

class Grouping : public Expr {
public:
	const Expr& expression;
	Grouping (const Expr& expression)
		:expression(expression){}

	virtual std::string accept(ExprVisitor& visitor) const override {
		return visitor.visitGroupingExprGen(*this);
	};
};

class Literal : public Expr {
public:
	const std::string& value;
	Literal (const std::string& value)
		:value(value){}

	virtual std::string accept(ExprVisitor& visitor) const override {
		return visitor.visitLiteralExprGen(*this);
	};
};

class Unary : public Expr {
public:
	const Token& operatorToken;
	 const Expr& right;
	Unary (const Token& operatorToken, const Expr& right)
		:operatorToken(operatorToken),right(right){}

	virtual std::string accept(ExprVisitor& visitor) const override {
		return visitor.visitUnaryExprGen(*this);
	};
};

#endif