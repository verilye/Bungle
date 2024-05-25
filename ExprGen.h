#ifndef EXPRGEN_H
#define EXPRGEN_H
#include "Expr.h" 
#include "Token.h" 
#include <list> 
  class Binary : public ExprGen {
    const Expr left;
    const  Token operatorToken;
    const  Expr right;
   Binary (Expr left, Token operatorToken, Expr right)

:left(left),operatorToken(operatorToken),right(right),{}
};
  class Grouping : public ExprGen {
    const Expr expression;
   Grouping (Expr expression)

:expression(expression),{}
};
  class Literal : public ExprGen {
    const strliteral value;
   Literal (strliteral value)

:value(value),{}
};
  class Unary : public ExprGen {
    const Token operatorToken;
    const  Expr right;
   Unary (Token operatorToken, Expr right)

:operatorToken(operatorToken),right(right),{}
};
#endif