#ifndef LEXER_HEADER
#define LEXER_HEADER

#include "token.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

class Lexer {
private:
    int pos, slen;
    std::string source;
    char current_char;
    void advance();
    void skipWhiteSpaces();
    std::string getInteger();
    char peek();
    Token getIdentifier();
    Token getStringLiteral();
    void skipComment();
public:
    Lexer(std::string);
    Token next();
    Token peekToken();
};


#endif
