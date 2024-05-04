#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include "token.h"
#include "error.h"

class Bungle;

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
	void scanToken();
	char advance();
	void addToken(TokenType type);
	void addToken(TokenType type, std::string strliteral);

	// Declare Bunge::error as a friend function
	//friend void Bungle::error(int line, std::string message);

};

#endif