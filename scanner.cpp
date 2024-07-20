#include "scanner.h"

// Consume current value and step forward one
char Scanner::advance() {
	current++;
	return source[current-1];
}

void Scanner::addToken(TokenType type) {
	addToken(type, " ");
}

void Scanner::addToken(TokenType type, std::string strliteral) {
	std::string text = source.substr(start,(current-start));
	Token * token = new Token(type, text, strliteral, line);
	tokens.push_back(token);
	counter++;
}

// Decide the type of the value in the scanner and handle it
void Scanner::scanToken() {
	// This is currently the only area where I'm returning a value from advance
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
		case '!': 
			addToken(match('=') ? BANG_EQUAL : BANG);
			break;
		case '=':
			addToken(match('=') ? EQUAL_EQUAL : EQUAL);
		case '<':
			addToken(match('=') ? LESS_EQUAL : LESS);
		case '>':
			addToken(match('=') ? GREATER_EQUAL : GREATER);
			break;
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
			break;
		case '\r':
			break;
		case '\t':
			//Ignore whitespace
			break;
		case '\n':
			line++;
			break;
		case '"': string(); break;
			// Conside the concept of maximal munch
			// The case which matches the most characters wins when 2 lexical grammar rules match a chunk
		case 'o':
			if (peek() == 'r') {
				addToken(OR);
			}
			break;

		default:

			if (isDigit(c)) {
				number();
			}
			else if (isAlpha(c)) {
				identifier();
			}
			else {
				std::string err = "Unexpected character - ";
				error(line, err += c);
			}
			break;
	}

}

void Scanner::string() {
	while (peek() != '"' && !isAtEnd()) {
		if (peek() == '\n') {
			line++;
		}
		advance();
	}
	if (isAtEnd()) {
		error(line, "Unterminated string.");
		return;
	}
	std::string value = source.substr(start+1, ((current - start)-1));

	// The closing "
	advance();
	addToken(STRING, value);
}

bool Scanner::isAtEnd() {
	return current >= source.size();
}

// Checks the current char loaded in the scanner
char Scanner::peek() {
	if (isAtEnd()) return '\0';
	return source[current];
}

std::vector<Token*> Scanner::scanTokens() {
	while (!isAtEnd()) {

		start = current;
		scanToken();
	}
	Token* ptr = new Token(ENDOFILE," "," ", line);
	tokens.push_back(ptr);
	return tokens;

}

bool Scanner::isDigit(char c) {
	return c >= '0' && c <= '9';
}

void Scanner::number() {
	while (isDigit(peek())) advance();

	//Look for a fractional part;
	if (peek() == '.' && isDigit(peekNext())) {
		// Consume the .
		advance();

		while (isDigit(peek())) advance();
	}

	// Double.parseDouble() Java method in the example
	addToken(NUMBER, (source.substr(start, (current - start))));

	// A number needs to be followed by a mathematical operator, a space or semicolon

}

// Convert chars to the proper datatype
char Scanner::peekNext() {
	if (current + 1 >= source.length()) return '\0';
	return source[current + 1];
}

void Scanner::identifier() {
	while (isAlphaNumeric(peek())) advance();

	std::string text = source.substr(start, ((current - start)));

	TokenType type;

	auto iterator = keywords.find(text);
	if (iterator != keywords.end()) {
		type = iterator->second;
	}
	else {
		type = IDENTIFIER;
	}
	addToken(type);

}

bool Scanner::isAlpha(char c) {
	return (c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		c == '_';
}

bool Scanner::isAlphaNumeric(char c) {
	return isAlpha(c) || isDigit(c);
}

bool Scanner::match(char expected) {
	if (isAtEnd()) return false;
	if (source[current] != expected) return false;
	current++;
	return true;
}