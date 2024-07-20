#ifndef PARSER
#define PARSER

#include <iostream>
#include <string>
#include <vector>
#include "token.h"
#include "genHeaders.h"
#include "error.h"
#include <memory>

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

    Parser(std::vector<Token*> tokens)
        :tokens(tokens){}

   std::list<std::shared_ptr<Stmt>> parse();

private:

    // Go into panic mode when error is found, go back up the tree and
    // cut off everything after the error

    // "Sentinel" class to describe Parser errors
    class ParseError : public std::exception{};
    // Where using a vector for easy access to the indicies
    const std::vector<Token*> tokens;
    int current = 0;

    template<typename... TokenType> bool match(const TokenType... types);
    bool check(TokenType type);
    bool isAtEnd();
    Token * advance();
    Token * peek();
    Token * previous();
    Token * consume(TokenType type, std::string message);
    Expr * expression();
    Expr * equality();
    Expr * comparison();
    Expr * term();
    Expr * factor();
    Expr * unary();
    Expr * primary();

    std::shared_ptr<Stmt> statement();

    std::shared_ptr<PrintStmt> printStatement();
    std::shared_ptr<ExpressionStmt> expressionStatement();
    std::shared_ptr<Stmt> declaration();
    std::shared_ptr<VarStmt> varDeclaration();

    void synchronise();

    // An error is thrown thus allowing the stack to synchronise
    ParseError reportError(Token * token, std::string message);

    

};

// Detect and report errors
// Avoid crashing or hanging
// Fast
// Rerport as many distinct errors as there are
// Minimise Cascaded errors
// We want super fast Error Recovery

#endif