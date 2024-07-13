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

std::string Interpreter::visitExpressionStmtGen(ExpressionStmt* stmt){
    return evaluate(stmt->expression);;
};

std::string Interpreter::visitPrintStmtGen(PrintStmt* stmt){
    std::string value = evaluate(stmt->expression);
    std::cout<< stringify(value) <<std::endl;
    return value;

};

std::string Interpreter::evaluate(const Expr* expr){
    return expr->accept(this);
};

void Interpreter::execute(std::shared_ptr<Stmt> stmt){
    stmt->accept(this);
}

std::string stringify(std::string output){
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

    for(int c = 0; c<num.size();c++){
        if(c >= '0' && c <= '9'){
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

