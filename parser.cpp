#include "parser.h"

std::list<std::shared_ptr<Stmt>> Parser::parse(){
   std::list<std::shared_ptr<Stmt>> statements;
   while(!isAtEnd){
        statements.push_back(statement());
   }

    return statements;
}

Expr * Parser::expression(){
    return equality();
}

std::shared_ptr<Stmt> Parser::statement(){
    if(match(PRINT)) return printStatement();

    return expressionStatement();
};

std::shared_ptr<PrintStmt> Parser::printStatement(){
    Expr * value = expression();
    consume(SEMICOLON, "Expect ';' after value.");
    return std::shared_ptr<PrintStmt> (new PrintStmt(value));
};

std::shared_ptr<ExpressionStmt> Parser::expressionStatement(){
    Expr * expr = expression();
    consume(SEMICOLON, "Expect ';' after value.");
    return std::shared_ptr<ExpressionStmt> (new ExpressionStmt(expr));

};

Expr * Parser::equality(){
    // Evaluate equality 
    Expr * expr = comparison();
    while(match(BANG_EQUAL, BANG_EQUAL)){
        // Operator is a keyword in C++, take care
        Token * operatorSymbol = previous();
        Expr * right = comparison();
        Binary * expression = new Binary(expr, operatorSymbol,right);
        expr = expression;
    }

    return expr;
};

template<typename... TokenType>
bool Parser::match(const TokenType... types){
    // Check if the token matches the types
    for(const auto type : {types...}){
        if(check(type)){
            advance();
            return true;
        }
    }

    return false;
};

bool Parser::check(TokenType type){
    if(isAtEnd()) return false;
    return peek()->type == type;
};

Token * Parser::advance(){
    if(!isAtEnd()) current++;
    return previous();
};

bool Parser::isAtEnd(){
    return peek()->type == ENDOFILE;
};

Token * Parser::peek(){
    return tokens[current];
};

Token * Parser::previous(){
    return tokens[current-1];
};

Expr * Parser::comparison(){
    Expr * expr = term();

    while(match(GREATER, GREATER_EQUAL, LESS, LESS_EQUAL)){
        Token * operatorSymbol = previous();
        Expr * right = term();
        Binary * expression = new Binary(expr, operatorSymbol, right);
        expr = expression;
    }

    return expr;
};

Expr * Parser::term(){
    Expr * expr = factor();
    while(match(MINUS, PLUS)){
        Token * operatorSymbol = previous();
        Expr * right = factor();
        Binary * expression = new Binary(expr, operatorSymbol, right);
        expr = expression;
    }
    
    return expr;
 };

Expr * Parser::factor(){
    Expr * expr = unary();

    while(match(SLASH, STAR)){
        Token * operatorSymbol = previous();
        Expr * right = unary();
        Binary * expression = new Binary(expr, operatorSymbol, right);
        expr = expression;
    }

    return expr;
};

Expr * Parser::unary(){

    if(match(BANG, MINUS)){
        Token * operatorSymbol = previous();
        Expr * right = unary();
        Unary * expression = new Unary(operatorSymbol, right);
        return expression;
    }

    return primary();
};

Expr * Parser::primary(){
    if(match(FALSE)) return new Literal("false");
    if(match(TRUE)) return new Literal("true");
    if(match(NIL)) return new Literal(NULL);

    if(match(NUMBER, STRING)){
        //Pass what the token says as the argument
        return new Literal(previous()->strliteral);
    }

    if(match(LEFT_PAREN)){
        Expr * expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression." );
        return new Grouping(expr);
    }

    throw reportError(peek(), "Expect expression");
};


Token * Parser::consume(TokenType type, std::string message){
    if(check(type)) return advance();

    // We want to throw here because exceptions contain
    // more details and we want to describe the problem verbosely
    // if we fail to consume a close parenthesis, throw error
    throw reportError(peek(), message);
};

Parser::ParseError Parser::reportError(Token * token, std::string message){
    error(token, message);

    // throw an error, synchronise the parser
    return ParseError();
};

void Parser::synchronise(){

    // We want to abandon the current statement boundary and go to the next
    // Forget all errors after the first inside the bounds and carry on
    // for brevity and speed
    advance();

    while(!isAtEnd()){
        if(previous()->type == SEMICOLON) return;

        switch(peek()->type){
            case CLASS:
            case FUN:
            case VAR:
            case FOR:
            case IF:
            case WHILE:
            case PRINT:
            case RETURN:
            default:
                return;
        }

        advance();
    }
}

