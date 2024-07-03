#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <iostream>
#include "token.h"
#include "RuntimeError.h"

extern bool hadError;
extern bool hadRuntimeError;

void report(int line, std::string where, std::string message);
void error(int line, std::string message);
void error(Token * token, std::string message);
void error(RuntimeError error);

#endif
