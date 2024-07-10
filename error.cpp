#include "error.h"

// Initialise with no errors
bool hadError = false;
bool hadRuntimeError = false;

void report(int line, std::string where, std::string message) {

	std::cout << "\033[1;31m [line " << line << "] Error" << where << ": " << message << "\033[0m" << std::endl;

	// need to change the state of the variable in the main class
	hadError = true;
}

// Report errors in the written code
void error(int line, std::string message) {
	report(line, "", message);
}

// report error detected from the parser
void error(Token * token, std::string message){
	if(token->type == ENDOFILE){
		report(token->line, " at end", message);
	} else{
		report(token->line, " at '" + token->lexeme + "'", message);
	}
}


// report error detected from the interpreter most of the time
void error(RuntimeError error){
	std::cout<<"\n"<< error.message << "\n [line " << error.token->line << "]";
	hadRuntimeError = true;
}