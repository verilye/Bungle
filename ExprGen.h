#ifndef EXPRGEN_H
#define EXPRGEN_H
#include "Expr.h" 
#include "Token.h" 
#include <list> 
template <typename T>
class ExprVisitor { 
	virtual T visitBinaryExprGen(Binary expression);
	virtual T visitGroupingExprGen(Grouping expression);
	virtual T visitLiteralExprGen(Literal expression);
	virtual T visitUnaryExprGen(Unary expression);
};

template <typename T>
class Binary : public Expr {
	const Expr left;
	const  Token operatorToken;
	const  Expr right;
	Binary (Expr left, Token operatorToken, Expr right)
		:left(left),operatorToken(operatorToken),right(right),{}

	virtual T accept(ExprVisitor<T> visitor) override {
		return visitor.visit(*this);
	};
};

template <typename T>
class Grouping : public Expr {
	const Expr expression;
	Grouping (Expr expression)
		:expression(expression),{}

	virtual T accept(ExprVisitor<T> visitor) override {
		return visitor.visit(*this);
	};
};

template <typename T>
class Literal : public Expr {
	const strliteral value;
	Literal (strliteral value)
		:value(value),{}

	virtual T accept(ExprVisitor<T> visitor) override {
		return visitor.visit(*this);
	};
};

template <typename T>
class Unary : public Expr {
	const Token operatorToken;
	const  Expr right;
	Unary (Token operatorToken, Expr right)
		:operatorToken(operatorToken),right(right),{}

	virtual T accept(ExprVisitor<T> visitor) override {
		return visitor.visit(*this);
	};
};

#endif