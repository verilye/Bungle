#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <iostream>

// Types of tokens that will be recognised by the interpreter
enum TokenType {
	// Single character tokens
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
	COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

	// One or two character tokens.
	BANG, BANG_EQUAL,
	EQUAL, EQUAL_EQUAL,
	GREATER, GREATER_EQUAL,
	LESS, LESS_EQUAL,

	// Literals
	IDENTIFIER, STRING, NUMBER,

	// Keywords
	AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
	PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

	ENDOFILE
};

class Token {
	
public:
	const TokenType type;
	const std::string lexeme;
	const std::string strliteral;
	const int line;

	Token(TokenType type, std::string lexeme, std::string strliteral, int line)
		:type(type), lexeme(lexeme), strliteral(strliteral), line(line){}

	void printToken();

private:


};

#endif