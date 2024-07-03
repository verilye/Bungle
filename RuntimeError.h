#ifndef RUNTIME_ERROR
#define RUNTIME_ERROR

#include "token.h"
#include <string>

class RuntimeError: public std::exception{

public:
    const Token* token;
    std::string message;

    RuntimeError(const Token* token, std::string message){
        this->token = token;
        this->message = message;
    }
};


#endif