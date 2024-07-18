#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include "token.h"
#include "error.h"
#include <map>

class Scanner {

public:
	
	Scanner(std::string source) : source(source) {};
	std::vector<Token*> scanTokens();

private:
	const std::string source;
	std::vector<Token*> tokens;

	// Points to the first character in the lexeme
	int start = 0;
	// Points to the character currently being considered
	int current = 0;
	// Tracks line that the lexeme is on so we can track its location (for errors etc)
	int line = 1;

	int counter = 0;
	
	bool isAtEnd();
	char peek();
	void scanToken();
	char advance();
	void string();
	void addToken(TokenType type);
	void addToken(TokenType type, std::string strliteral);
	bool isDigit(char c);
	void number();
	char peekNext();
	void identifier();
	bool isAlpha(char c);
	bool isAlphaNumeric(char c);
	bool match(char expected);

	std::map<std::string, TokenType> keywords = {
		{"and", AND},
		{ "class", CLASS},
		{ "else", ELSE},
		{ "false", FALSE },
		{ "for", FOR },
		{ "fun", FUN },
		{ "if", IF },
		{ "nil", NIL },
		{ "or", OR },
		{ "print", PRINT },
		{ "return", RETURN },
		{ "super", SUPER },
		{ "this", THIS },
		{ "true", TRUE },
		{ "var", VAR },
		{ "while", WHILE },
	};
};

#endif