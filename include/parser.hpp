#ifndef PARSER_HEADER
#define PARSER_HEADER

#include "lexer.hpp"
#include "token.hpp"
#include "ast.hpp"

class Parser {
private:
    Lexer lexer;
    void eat(TokenType);
    Node* factor();
    Node* term();
    Node* expr();
    Node* compound_statement();
    Node* statement();
    Node* assignment_statement();
    Node* variable();
    Node* stringLiteral();
    Node* print_statement();
    Node* scanInt_statement();
    Node* scanStr_statement();
    Node* int_to_str();
    Node* if_statement();
public:
    Parser(Lexer&);
    Token current_token;
    Node* parse();
};



#endif
