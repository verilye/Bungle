#ifndef EXPR_H
#def EXPR_H

#include "Token.h"

//Convert this from Java conventions to C++

class Expr {
	virtual Expr left;
	virtual Token operatorToken;
	virtual Expr right;
};


class Binary : public Expr {

	Binary(Expr left, Token operatorToken, Expr right)
		:left(left), operatorToken(operatorToken), right(right)

};




#endif