#include "parser.h"

Expr & Parser::expression(){
    return equality();
}

Expr & Parser::equality(){
    // Evaluate equality and  
    Expr& expr = comparison();
    while(match(BANG_EQUAL, BANG_EQUAL)){
        Token operator = previous();
        Expr right = comparison();
        expr = new Expr.Binary(expr, operator, right);
    }

    return expr;
};

bool Parser::match(TokenType... types){

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
    return tokens.get(current);
};

Token Parser::previous(){
    return tokens.get(current-1);
};

Expr & comparison(){
    Expr& expr = term();

    while(match(GREATER, GREATER_EQUAL, LESS, LESS_EQUAL)){
        Token operator = previous();
        Expr right = term();
        expr = new Expr.Binary(expr, operator, right);
    }

    return expr;
};

 Expr Parser::term(){
    Expr expr = factor();
    while(match(MINUS, PLUS)){
        Token operator = previous();
        Expr right = factor();
        expr = new Expr.Binary(expr, operator, right);
    }
    
    return expr
 };

Expr Parser::factor(){
    Expr expr = unary();

    while(match(SLASH, STAR)){
        Token operator = previous();
        Expr right = unary();
        expr = new Expr.Binary(expr, operator, right);
    }

    return expr;
};

Expr Parser::unary(){
    if(match(BANG, MINUS)){
        Token operator = previous();
        Expr right = unary();
        return new Expr.Unary(operator, right);
    }

    return primary;
};

Expr Parser::primary(){
    if(match(FALSE)) return new Expr.Literal(false);
    if(match(TRUE)) return new Expr.Literal(true);
    if(match(NIL)) return new Expr.Literal(NULL);

    if(match(NUMBER, STRING)){
        return new Expr.Literal(previous().literal);
    }

    if(match(LEFT_PAREN){
        Expr expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression." );
        return new Expr.Grouping(expr);
    }
};