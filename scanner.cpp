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
		case '/':
			if (match('/')) {
				// A comment goes until the end of the line
				while (peek() != '\n' && !isAtEnd()) advance();
			}
			else {
				addToken(SLASH);
			}
			break;
		case ' ':
		case '\r':
		case '\t':
			//Ignore whitespace
		case '\n';
			line++;
			break;
		case '"': string(); break;


		default:
			std::string err = "Unexpected character - ";
			error(line, err+=c);
			break;
	}
}

void Scanner::string() {
	while (peek() != '"' && !isAtEnd()) {
		if (peek() == '\n') line++;
		advance();
	}

	if (isAtEnd()) {
		error(line, "Unterminated string.");
		return;
	}

	// The closing "
	advance();

	std::string value = source.substr(start+1, ((current - start)-1));
	addToken(STRING, value);
}

bool Scanner::isAtEnd() {
	return current >= source.size();
}

// lookahead function. Check the character ahead of it without 'consuming' it
// important concept within interpreters
char Scanner::peek() {
	if (isAtEnd()) return '\0';
	return source[current];
}

std::vector<Token*> Scanner::scanTokens() {

	while (!isAtEnd()) {

		start = current;
		scanToken();

	}
	tokens.push_back((new Token(ENDOFILE, "", NULL, line)));
	return tokens;

}
