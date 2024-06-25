#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <iostream>
#include "token.h"

extern bool hadError;

void report(int line, std::string where, std::string message);
void error(int line, std::string message);
void error(Token token, std::string message);

#endif
