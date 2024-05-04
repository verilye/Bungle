#ifndef ERROR_H
#def ERROR_H

void error(int line, std::string message) {
	report(line, "", message);
}

void report(int line, std::string where, std::string message) {
	std::cout << "\033[1;31m [line " << line << "] Error" << where << ": " << message << "\033[0m" << std::endl;
	hadError = true;
}

#endif
