#include "token.h"

void Token::printToken() {
	std::cout<< type <<std::endl;
	std::cout << lexeme << std::endl;
	if (strliteral == NULL) {
		std::cout << "NULL" << std::endl;
	}
	else {
		std::cout << strliteral << std::endl;
	}
	std::cout << line << std::endl;
	std::cout<<std::endl;
}
