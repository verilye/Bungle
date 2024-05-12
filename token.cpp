#include "token.h"

void Token::printToken() {
	std::cout << "  Type:";
	std::cout << type;
	std::cout << "  Lexeme:";
	std::cout << lexeme;
	std::cout << "  Literal:";
	std::cout << strliteral;
	std::cout << "  Line:";
	std::cout << line;
	std::cout<<std::endl;
}
