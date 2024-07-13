#include "ExprGen.h"
#include <string>
#include <sstream>

// Implement the pure virtual functions defined in the 'Visitor interface' in ExprGen
class AstVisitor : public ExprVisitor {

public:	
	std::string print(Expr* expr) {
		return expr->accept(this);
	}

	std::string visitBinaryExprGen(const Binary* expression) override {
		return parenthesize(expression->operatorToken->lexeme, 
					expression->left, expression->right);
	}

	std::string visitGroupingExprGen(const Grouping* expression) override {
		return parenthesize("group", expression->expression);
	}

	std::string visitLiteralExprGen(const Literal* expression) override {
		if (expression->value == " ") return "nil";
		// Convert to string
		return expression->value;
	}

	std::string visitUnaryExprGen(const Unary* expression) override {
		return parenthesize(expression->operatorToken->lexeme,
			expression->right);
	}

	// Test method to try out the parenthesize function
	// Using stack based shit to generate references instead of pointers
	void TestMethod() {
		// Create Tokens with automatic storage duration (stack-based)
		Token * minusToken = new Token(MINUS, "-", " ", 1);
		Token * starToken = new Token(STAR, "*", " ", 1);

		// Create Expressions with automatic storage duration (stack-based)
		Literal * literal123 = new Literal("123");
		Literal * literal4567 = new Literal("45.67");
		Grouping * groupingExpr = new Grouping(literal4567);
		Unary * unaryExpr = new Unary(minusToken, literal123);
		Binary * expression = new Binary(unaryExpr, starToken, groupingExpr);

		// Use the print method from the ASTVisitor base class
		std::cout << print(expression);
	}

private:

	// Using variadic template and a fold expression to take in uncertain amount of arguments
	template<typename... Exprs>
	std::string parenthesize(const std::string& name, const Exprs*... exprs) {
		// C++ resource on fold expressions incase I forget. Variadic templates and fold expressions
		//https://en.cppreference.com/w/cpp/language/fold 
		std::ostringstream oss;
		oss << "(" << name;
		(oss << ... << (" " + exprs->accept(*this)));
		oss << ")";
		return oss.str();
	}

};
