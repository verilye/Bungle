#ifndef INTERPRETER
#define INTERPRETER

#include <string>
#include "ExprGen.h"
#include "RuntimeError.h"
#include <iostream>
#include "error.h"

class Interpreter : public ExprVisitor{

public:
    Interpreter(){}
    void interpret(Expr* expression);
    // return a generic datatype but also the raw value for same behavior as Java
    std::string visitLiteralExprGen(const Literal* expr) override {
        // In my current implementation, strings and numbers are identified in the scanner
        return expr->value;
    }

    std::string visitGroupingExprGen(const Grouping* expr) override{
        // a grouping node contains a reference to an inner node
        // To evaluate grouping expression, recursively evaluate sub expression and return it
        return evaulate(expr->expression);
    };

    std::string visitUnaryExprGen(const Unary* expr) override{
        // evaluate the value that the unary operator applies to 
        std::string right = evaulate(expr->right);

        switch(expr->operatorToken->type){
            case BANG:
                // returns opposite of truthiness of value like in most languages
                return  std::to_string(!isTruthy(right));
            case MINUS:
                checkNumberOperand(expr->operatorToken, right);
                //if negative, cast as double and return the negative version of the number
                return  std::to_string(std::stof(right)*-1);
            default:
                std::cout<<"CASE NOT IMPLEMENTED - visitUnaryExprGen\n";
        }

        //Unreachable.
        return NULL;
    };

    std::string visitBinaryExprGen(const Binary * expr) override{
        std::string left = evaulate(expr->left);
        std::string right = evaulate(expr->right);

        switch(expr->operatorToken->type){
            case MINUS:
                checkNumberOperands(expr->operatorToken, left, right);
                return std::to_string(std::stof(left) - std::stof(right));
            case SLASH:
                checkNumberOperands(expr->operatorToken, left, right);
                return  std::to_string(std::stof(left) / std::stof(right));
            case STAR:
                checkNumberOperands(expr->operatorToken, left, right);
                return  std::to_string(std::stof(left) * std::stof(right));
            case PLUS:  
                // Can be used to concatenate two strings OR add 2 numbers
                if(checkIfNum(left) && checkIfNum(right)){
                    return std::to_string(std::stof(left) + std::stof(right));
                }

                // REMEMBER typeid FOR LATER, SHOULD HAVE BEEN USING IT THE WHOLE TIME
                if(typeid(left) == typeid(std::string) && typeid(right) == typeid(std::string)){
                    return left + right;
                }

                throw new RuntimeError(expr->operatorToken, "Operands must be two numbers or two strings");
            case GREATER:
                checkNumberOperands(expr->operatorToken, left, right);
                return std::to_string(std::stof(left) > std::stof(right));
            case GREATER_EQUAL:
                checkNumberOperands(expr->operatorToken, left, right);
                return std::to_string(std::stof(left) >= std::stof(right));
            case LESS:
                checkNumberOperands(expr->operatorToken, left, right);
                return std::to_string(std::stof(left) < std::stof(right));
            case LESS_EQUAL:
                checkNumberOperands(expr->operatorToken, left, right);
                return std::to_string(std::stof(left) <= std::stof(right));
            case BANG_EQUAL: 
                return std::to_string(!isEqual(left, right));
            case EQUAL_EQUAL: 
                return std::to_string(isEqual(left, right));
            default:
                std::cout<<"CASE NOT IMPLEMENTED - visitBinaryExprGen\n";
        }       

        // Unreachable
        return NULL;
        
    };

private:
    std::string evaulate(const Expr* expr);
    std::string stringify();
    bool isTruthy(std::string object);
    bool checkIfNum(std::string num);
    bool isEqual(std::string a, std::string b);
    void checkNumberOperand(const Token* operatorToken, std::string operand);
    void checkNumberOperands(const Token* operatorToken, std::string left, std::string right);

};

#endif