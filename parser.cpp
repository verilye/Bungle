#include "parser.h"

Expr & Parser::expression(){
    return equality();
}

Expr & Parser::equality(){
    // Evaluate equality and  
    Expr& expr = comparison();
    while(match(BANG_EQUAL, BANG_EQUAL)){
        // Operator is a keyword in C++, take care
        Token operatorSymbol = previous();
        Expr & right = comparison();
        Binary expression(expr, operatorSymbol,right);
        expr = expression;
    }

    return expr;
};

template<typename... TokenType>
bool Parser::match(const TokenType... types){
    // Check to make sure that the values match
    for(TokenType type : types){
        if(check(type)){
            advance();
            return true;
        }
    }

    return false;
};

bool Parser::check(TokenType type){
    if(isAtEnd()) return false;
    return peek().type == type;
};

Token Parser::advance(){
    if(!isAtEnd()) current++;
    return previous();
};

bool Parser::isAtEnd(){
    return peek().type == EOF;
};

Token Parser::peek(){
    return tokens[current];
};

Token Parser::previous(){
    return tokens[current-1];
};

Expr & comparison(){
    Expr & expr = term();

    while(match(GREATER, GREATER_EQUAL, LESS, LESS_EQUAL)){
        Token operatorSymbol = previous();
        Expr & right = term();
        Binary expression(expr, operatorSymbol, right);
        expr = expression;
    }

    return expr;
};

Expr & Parser::term(){
    Expr & expr = factor();
    while(match(MINUS, PLUS)){
        Token operatorSymbol = previous();
        Expr & right = factor();
        Binary expression(expr, operatorSymbol, right);
        expr = expression;
    }
    
    return expr;
 };

Expr Parser::factor(){
    Expr & expr = unary();

    while(match(SLASH, STAR)){
        Token operatorSymbol = previous();
        Expr & right = unary();
        Binary expression(expr, operatorSymbol, right);
        expr = expression;
    }

    return expr;
};

Expr & Parser::unary(){
    if(match(BANG, MINUS)){
        Token operatorSymbol = previous();
        Expr & right = unary();
        Unary expression(operatorSymbol, right);
        return expression;
    }

    return primary();
};

Expr & Parser::primary(){
    if(match(FALSE)) return Literal("false");
    if(match(TRUE)) return Literal("true");
    if(match(NIL)) return Literal(NULL);

    if(match(NUMBER, STRING)){
        return Literal(previous());
    }

    if(match(LEFT_PAREN)){
        Expr & expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression." );
        return Grouping(expr);
    }
};