#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <iostream>

extern bool hadError;

void report(int line, std::string where, std::string message);
void error(int line, std::string message);

#endif
