#include "error.h"

// Initialise with no errors
bool hadError = false;

void report(int line, std::string where, std::string message) {

	std::cout << "\033[1;31m [line " << line << "] Error" << where << ": " << message << "\033[0m" << std::endl;

	// need to change the state of the variable in the main class
	hadError = true;
}

void error(int line, std::string message) {
	report(line, "", message);
}