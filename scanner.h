#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include "token.h"
#include "error.h"

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
	
	
	bool isAtEnd();
	char peek();
	void scanToken();
	char advance();
	void string();
	void addToken(TokenType type);
	void addToken(TokenType type, char* strliteral);
	bool isDigit(char c);
	void number();
	char peekNext();
	void identifier();
	bool isAlpha(char c);
	bool isAlphaNumeric(char c);
};

#endif