#include "scanner.h"

char Scanner::advance() {
	current++;
	return source[current - 1];
}

void Scanner::addToken(TokenType type) {
	addToken(type, NULL);
}

void Scanner::addToken(TokenType type, char* strliteral) {
	std::string text = source.substr(start,(current-start));
	Token* token = new Token(type, text, strliteral, line);
	tokens.push_back(token);
}

void Scanner::scanToken() {
	char c = advance();
	switch (c) {
		case '(': addToken(LEFT_PAREN); break;
		case ')': addToken(RIGHT_PAREN); break;
		case '{': addToken(LEFT_BRACE); break;
		case '}': addToken(RIGHT_BRACE); break;
		case ',': addToken(COMMA); break;
		case '.': addToken(DOT); break;
		case '-': addToken(MINUS); break;
		case '+': addToken(PLUS); break;
		case ';': addToken(SEMICOLON); break;
		case '*': addToken(STAR); break;
		default:
			std::string err = "Unexpected character - ";
			error(line, err+=c);
			break;
	}
}

bool Scanner::isAtEnd() {
	return current >= source.size();
}

std::vector<Token*> Scanner::scanTokens() {

	while (!isAtEnd()) {

		start = current;
		scanToken();

	}
	tokens.push_back((new Token(ENDOFILE, "", NULL, line)));
	return tokens;

}
