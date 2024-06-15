#include "ExprGen.h"
#include <string>
#include <iostream>

// Implement the pure virtual functions defined in the 'Visitor interface' in ExprGen

// NOTE - reminder that all the generated classes are template classes
// Bad design? Only really going to find out when working on projects with others
// For pure functionality and performance so far I reckon whatever works is fine enough
// I can worry about best practices later

class AstVisitor : public ExprVisitor {

public:	
	void print(Expr& expr) {
		expr.accept(*this);
	}

	std::string visitBinaryExprGen(const Binary& expression) override {
		return parenthesize(expression.operatorToken.lexeme, 
					expression.left, expression.right);
	}

	std::string visitGroupingExprGen(const Grouping& expression) override {
		return parenthesize("group", expression->expression);
	}

	std::string visitLiteralExprGen(const Literal& expression) override {
		if (expression->value == NULL) return "nil";
		// Convert to string
		return std::to_string(expression->value);
	}

	std::string visitUnaryExprGen(const Unary& expression) override {
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

		// Print out AST example 
		std::cout << expression;
	}
 	
	template<typename... Expr>
	std::string parenthesize(std::string name, Expr... exprs) {
		// Create some example expressions and print them to test the printer

		// Name of the AST
		std::string buildString = "(" + name;

		// Iterate through the abstract syntax tree, adding things to the string as we go 
		for (const auto p : {exprs...}) {

			buildString.append(" ");
			
			// Parenthesize child expressions and add them inside the parent parentheses
			p->accept(*this);
		}

		buildString.append(")");

		return buildString;
	}

};
