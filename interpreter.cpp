#include "interpreter.h"


// return a generic datatype but also the raw value for same behavior as Java
std::string Interpreter::visitLiteralExprGen(Literal* expr){
    // In my current implementation, strings and numbers are identified in the scanner
    return expr->value;
}

std::string Interpreter::visitGroupingExprGen(Grouping* expr){
    // a grouping node contains a reference to an inner node
    // To evaluate grouping expression, recursively evaluate sub expression and return it
    return evaulate(expr->expression);
};

std::string Interpreter::visitUnaryExprGen(Unary* expr){
    // evaluate the value that the unary operator applies to 
    std::string right = evaulate(expr->right);

    switch(expr->operatorToken->type){
        case BANG:
            // returns opposite of truthiness of value like in most languages
            return  std::to_string(!isTruthy(right));
        case MINUS:
            //if negative, cast as double and return the negative version of the number
            return  std::to_string(std::stof(right)*-1);
    }

    //Unreachable.
    return NULL;
};

std::string Interpreter::visitBinaryExprGen(Binary * expr){
    std::string left = evaulate(expr->left);
    std::string right = evaulate(expr->right);

    switch(expr->operatorToken->type){
        case MINUS:
            return std::to_string(std::stof(left) - std::stof(right));
        case SLASH:
            return  std::to_string(std::stof(left) / std::stof(right));
        case STAR:
            return  std::to_string(std::stof(left) * std::stof(right));
        case PLUS:  
            // Can be used to concatenate two strings OR add 2 numbers
            if(checkIfNum(left) && checkIfNum(right)){
                return  std::to_string(std::stof(left) + std::stof(right));
            }
            return left + right;
        case GREATER:
             return std::to_string(std::stof(left) > std::stof(right));
        case GREATER_EQUAL:
            return std::to_string(std::stof(left) >= std::stof(right));
        case LESS:
            return std::to_string(std::stof(left) < std::stof(right));
        case LESS_EQUAL:
            return std::to_string(std::stof(left) <= std::stof(right));
        case BANG_EQUAL: 
            return std::to_string(!isEqual(left, right));
        case EQUAL_EQUAL: 
            return std::to_string(isEqual(left, right));
    }       

    // Unreachable
    return NULL;
    
};

std::string Interpreter::evaulate(const Expr* expr){
    return expr->accept(*this);
};

bool isTruthy(std::string object){
    // False and nil are the only two falsey values 
    if(object == "nil"){return false;}
    if(object == "false") return false;

    return true;
};

bool Interpreter::checkIfNum(std::string num){

    for(int c = 0; c<num.size();c++){
        if(c >= '0' && c <= '9'){
            continue;
        }else{
            return false;
        }
    }
    return true;
};

bool isEqual(std::string a, std::string b){
    if(a == " " && b == " ") return true;
    if(a == " ") return false;

    return a == b;
};