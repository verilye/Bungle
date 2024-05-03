#include "token.h"

void Token::printToken() {
	std::cout<< type <<std::endl;
	std::cout << lexeme << std::endl;
	std::cout << strliteral << std::endl;
	std::cout << line << std::endl;
}