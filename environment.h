#ifndef ENVIRONMENT_CPP
#define ENVIRONMENT_CPP

#include <string>
#include <map>
#include "error.h"
#include "RuntimeError.h"
#include <memory>

class Environment{

public:
    void define(std::string name, std::unique_ptr<Token> value){
        environmentMap.emplace(name, value);
    }


    // NOTE - due to the way unique ptr works if we didnt copy it with make_unique
    // when returning it from the map it would be replaced with a nullptr. This 
    // is due to RAII
    std::unique_ptr<Token> get(std::unique_ptr<Token> name){
        std::map<std::string, std::unique_ptr<Token>>::iterator it = environmentMap.find(name->lexeme);
        if(it != environmentMap.end()){
            return std::make_unique<Token>(it->second);
        }
        std::string msg = "Undefined variable '" + name->lexeme + "'.";
        throw new RuntimeError(name.get(), msg);
    }

private:
    std::map<std::string, std::unique_ptr<Token>> environmentMap;
};

#endif