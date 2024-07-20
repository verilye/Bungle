#include "interpreter.h"

void Interpreter::interpret(std::list<std::shared_ptr<Stmt>> statements){
    try{
        for(std::shared_ptr<Stmt> statement : statements){
            execute(statement);
        }
    } catch(RuntimeError err){
        error(err);
    }
};

std::string Interpreter::visitBinaryExprGen(const Binary * expr){
    std::string left = evaluate(expr->left);
    std::string right = evaluate(expr->right);

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
                float addition = (std::stof(left) + std::stof(right));
                return std::to_string(addition);
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

std::string Interpreter::visitGroupingExprGen(const Grouping* expr){
    // a grouping node contains a reference to an inner node
    // To evaluate grouping expression, recursively evaluate sub expression and return it
    return evaluate(expr->expression);
};

// return a generic datatype but also the raw value for same behavior as Java
std::string Interpreter::visitLiteralExprGen(const Literal* expr){
    // In my current implementation, strings and numbers are identified in the scanner
    return expr->value;
}

std::string Interpreter::visitUnaryExprGen(const Unary* expr){
    // evaluate the value that the unary operator applies to 
    std::string right = evaluate(expr->right);

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

std::string Interpreter::visitExpressionStmtGen(const ExpressionStmt* stmt){
    evaluate(stmt->expression);;
    return "";
};

std::string Interpreter::visitPrintStmtGen(const PrintStmt* stmt){
    std::string value = evaluate(stmt->expression);
    std::cout<< stringify(value) <<std::endl;
    return "";
};

std::string Interpreter::evaluate(const Expr* expr){
    return expr->accept(this);
};

void Interpreter::execute(std::shared_ptr<Stmt> stmt){
    stmt->accept(this);
}

std::string Interpreter::stringify(std::string output){
    if(output == " "){
        return "nil";
    }

    return output;
};

bool Interpreter::isTruthy(std::string object){
    // False and nil are the only two falsey values 
    if(object == "nil"){return false;}
    if(object == "false") return false;

    return true;
};

bool Interpreter::checkIfNum(std::string num){

    bool decimalFound = false;
    for(int c = 0; c<num.size();c++){
        if(num[c] >= '0' && num[c] <= '9'){
            continue;
        }else if(num[c] == '.' && decimalFound == false){
            decimalFound = true;
            continue;
        }else{
            return false;
        }
    }
    return true;
};

bool Interpreter::isEqual(std::string a, std::string b){
    if(a == " " && b == " ") return true;
    if(a == " ") return false;

    return a == b;
};


void Interpreter::checkNumberOperand(const Token* operatorToken, std::string operand){
    //Check if operand is a double
    if(checkIfNum(operand)) return;
    // If not double throw error
    throw RuntimeError(operatorToken, "Operand must be a number");
};

void Interpreter::checkNumberOperands(const Token* operatorToken,  std::string left, std::string right){
    //Check left and right expresssions are both numbers
    if(checkIfNum(left) && checkIfNum(right)) return;
    // If not double throw error
    throw RuntimeError(operatorToken, "Operands must be numbers");
};

