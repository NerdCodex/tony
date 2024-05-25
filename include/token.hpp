#ifndef TOKEN_HEADER
#define TOKEN_HEADER

#include <string>
#include <map>

enum TokenType {
    BEGIN,
    END,
    INT,
    STRING,
    IDENTIFIER,
    ASSIGNMENT,
    LPAREN,
    RPAREN,
    LBRACKET,
    RBRACKET,
    PLUS,
    MINUS,
    DIVIDE,
    MULTIPLY,
    MODULUS,
    LESSTHAN,
    LESSTHANOREQUAL,
    GREATERTHAN,
    GREATERTHANOREQUAL,
    EOFF,
    PRINT,
    SCANINT,
    SCANSTR,
    STR,
    IF,
    ELSE,
    EQUAL,
    NOTEQUAL,
    SEMICOLON
};

struct Token {
    std::string value;
    TokenType type;
    Token();
    Token(TokenType tp, std::string v);
};

extern std::map<std::string, Token> RESERVED_KEYWORD;

#endif
