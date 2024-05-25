
#include "token.hpp"

Token::Token() {}
Token::Token(TokenType tp, std::string v): value(v), type(tp) {}

std::map<std::string, Token> RESERVED_KEYWORD = {
    {"print", Token(PRINT, "PRINT")},
    {"scanInt", Token(SCANINT, "SCANINT")},
    {"scanStr", Token(SCANSTR, "SCANSTR")},
    {"BEGIN", Token(BEGIN, "BEGIN")},
    {"END", Token(END, "END")},
    {"if", Token(IF, "IF")},
    {"else", Token(ELSE, "ELSE")},
    {"str", Token(STR, "STR")}
};
