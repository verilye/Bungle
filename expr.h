#ifndef EXPR_H
#def EXPR_H

#include "Token.h"

template <typename T>
class Expr {
	virtual Expr left;
	virtual Token operatorToken;
	virtual Expr right;
	virtual T accept(ExprVisitor<T> visitor);
};

#endif