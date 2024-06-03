#ifndef EXPRGEN_H
#define EXPRGEN_H
#include "Token.h" 
#include <list> 
#include <string> 

template <typename T> class Binary;
template <typename T> class Grouping;
template <typename T> class Literal;
template <typename T> class Unary;

template <typename T>
class ExprVisitor { 
	virtual T visitBinaryExprGen(Binary<T>& expression) = 0;
	virtual T visitGroupingExprGen(Grouping<T>& expression) = 0;
	virtual T visitLiteralExprGen(Literal<T>& expression) = 0;
	virtual T visitUnaryExprGen(Unary<T>& expression) = 0;
};

template <typename T>
class Expr { 
	virtual ~Expr() = default; 
	virtual const T accept(ExprVisitor<T> visitor) const = 0; 
};

template <typename T>
class Binary : public Expr<T> {
	const Expr<T>& left;
	 const Token& operatorToken;
	 const Expr<T>& right;
	Binary (const Expr<T>& left, const Token& operatorToken, const Expr<T>& right)
		:left(left),operatorToken(operatorToken),right(right){}

	virtual T accept(ExprVisitor<T>& visitor) override {
		return visitor.visit(*this);
	};
};

template <typename T>
class Grouping : public Expr<T> {
	const Expr<T>& expression;
	Grouping (const Expr<T>& expression)
		:expression(expression){}

	virtual T accept(ExprVisitor<T>& visitor) override {
		return visitor.visit(*this);
	};
};

template <typename T>
class Literal : public Expr<T> {

public:
	const std::string value;
	Literal (const std::string& value)
		:value(value){}

	virtual T accept(ExprVisitor<T>& visitor) override {
		return visitor.visit(*this);
	};
};

template <typename T>
class Unary : public Expr<T> {
	const Token& operatorToken;
	 const Expr<T>& right;
	Unary (const Token& operatorToken, const Expr<T>& right)
		:operatorToken(operatorToken),right(right){}

	virtual T accept(ExprVisitor<T>& visitor) override {
		return visitor.visit(*this);
	};
};

#endif