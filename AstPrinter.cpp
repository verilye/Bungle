#include "ExprGen.h"
#include <string>

// Implement the pure virtual functions defined in the 'Visitor interface' in ExprGen

template <typename T>
class AstVisitor : public ExprVisitor<T> {





public:
	// We want to print out the Abstract Syntax Tree
	// to check for errors and shi
	std::string print(Expr<T>& expr) {
		return expr.accept(*this)
	}

	T visitBinaryExprGen(Expr.Binary expression) {
		return parenthesize(expr.operator.lexeme, 
					expr.left, expr.right);
	}

	T visitGroupingExprGen(Expr.Grouping expression) {
		return parenthesize("group", expr.expression);
	}

	T visitLiteralExprGen(Expr.Literal expression) {
		if (expr.value == null) return "nil";
		return expr.value.toString();
	}

	T visitUnaryExprGen(Expr.Unary expression) {
		return parenthesize(expr.operator.lexeme,
			expr.right);
	}

private:

	std::string parenthesize(std::string, Expr<T>& [] exprs) {
		

		// Format ugly style to represent da tree
		
		
		return builder.toString();
	}

};