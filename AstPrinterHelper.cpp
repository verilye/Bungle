#include "ExprGen.h"
#include <string>
#include <iostream>

// Implement the pure virtual functions defined in the 'Visitor interface' in ExprGen

template <typename T>
class AstVisitor : public ExprVisitor<T> {

public:
	// We want to print out the Abstract Syntax Tree
	// to check for errors and shi
	std::string print(Expr<T>& expr) {
		return expr.accept(*this);
	}

	T visitBinaryExprGen(Binary<T>& expression) {
		return parenthesize(expression->operatorToken->lexeme, 
					expression->left, expression->right);
	}

	T visitGroupingExprGen(Grouping<T>& expression) {
		return parenthesize("group", expression->expression);
	}

	T visitLiteralExprGen(Literal<T>& expression) {
		if (expression->value == NULL) return "nil";
		// Convert to string
		return std::to_string(expression->value);
	}

	T visitUnaryExprGen(Unary<T>& expression) {
		return parenthesize(expression->operatorToken->lexeme,
			expression->right);
	}

private:

	// Test method to try out the parenthesize function
	void TestMethod() {
		Expr* expression = new Binary(
			new Unary(
				new Token(MINUS, "-", NULL, 1),
				new Literal((std::string)"123")
			),
			new Token(STAR, '*', NULL, 1),
			new Grouping(
				new Literal((std::string)"45.67");
				)
		);

		std::cout << parenthesize(expression);
	}
 	
	std::string parenthesize(std::string name, Expr<T>* exprs[], int exprArrSize) {
		

		// TODO
		// REWRITE A BUNCH OF THE INHERTANCE SHIT IN THE EXPRGEN
		// I DONT THINK THE SUBCLASSES SHOULD BE INHERITING FROM EXPR<T>
		// WHEN T is SHOWN, it should represent a class of type EXPR, NOT EXPR<T>


		// Name of the AST
		std::string buildString = "(" + name;
		
		// Iterate through the abstract syntax tree, adding things to the string as we go 
		for (unsigned int i = 0; i < exprArrSize; i++) {

			// Throw call to the accept function on the Expression
			// The expression calls visit on the Visitor interface
			// Strings are printed out depending on the appropriate Expr type
			buildString.append(" ");
			buildString.append(exprs[i]->accept(this));
		}

		buildString.append(")");

		return buildString;
	}

};
