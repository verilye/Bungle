#ifndef PARSER
#define PARSER

#include <list>
#include "token.h"
#include "ExprGen.h"

// Here we are using recursive descent to build the parser
// A simpler but still powerful alternative to a LALR parser

// The way this plays out is that expressions with a higher
// precedence are lower on the tree, so that they are 
// evaluated before their lower precedence parents

// A recursive descent parser is a literal translation of 
// the grammar rules into imperative code. Each rule
// becomes like a function

class Parser{

public:

    Parser(std::list<Token> tokens)
        :tokens(tokens){}

private:

    const std::list<Token> tokens;
    int current = 0;
    
    Expr & expression();
    Expr & equality();
    bool match(TokenType... types);
    bool check(TokenType type);
    Token advance();
    bool isAtEnd();
    Token peek();
    Token previous();
    Expr & comparison();
    Expr term();
    Expr factor();
    Expr unary();
    Expr primary();

    Token consume(TokenType type, std::string message);

};

#endif