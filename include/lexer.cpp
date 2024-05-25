
#include "lexer.hpp"

Lexer::Lexer(std::string src) : pos(0) {
    this->source = src;
    slen = src.length();
    current_char = source[pos];
}

void Lexer::advance() {
    pos += 1;
    if (pos > slen) current_char = '\0';
    else current_char = source[pos];
}

void Lexer::skipWhiteSpaces() {
    while(current_char != '\0' && isspace(current_char)) {
        advance();
    }
}

void Lexer::skipComment() {
    advance();
    while (current_char != '\n' && current_char != '\0') {
        advance();
    }
}

std::string Lexer::getInteger() {
    std::string number = "";
    while(current_char != '\0' && isdigit(current_char)) {
        number += current_char;
        advance();
    }
    return number;
}

char Lexer::peek() {
    int peek_pos = pos + 1;
    if (peek_pos > slen) return '\0';
    else return source[peek_pos];
}

Token Lexer::getIdentifier() {
    std::string idf = "";
    while ((current_char != '\0' && isalnum(current_char)) || current_char == '_') {
        idf += current_char;
        advance();
    }
    if (RESERVED_KEYWORD.find(idf) != RESERVED_KEYWORD.end()) {
        return RESERVED_KEYWORD[idf];
    }
    return Token(IDENTIFIER, idf);
}

Token Lexer::getStringLiteral() {
    std::string stringliteral = "";
    advance();
    while(current_char != '\0' || current_char == ' ') {
        stringliteral += current_char;
        advance();
        if (current_char == '"') {
            advance();
            break;
        }
    } return Token(STRING, stringliteral);
}

Token Lexer::peekToken() {
    int peek_pos = pos;
    char peek_char = current_char;

    while( peek_char != '\0') {
        if (peek_char == ' ') {
            while(peek_char != '\0' && peek_char == ' ') {
                peek_pos++;
                if (peek_pos >= slen) {
                    peek_char = '\0';
                } else {
                    peek_char = source[peek_pos];
                }
            }
        }

        else if (peek_char == '+') {
            return Token(PLUS, "+");
        }

        else if (peek_char == '-') {
            return Token(MINUS, "-");
        }

        else if (peek_char == '*') {
            return Token(MULTIPLY, "*");
        }

        else if (peek_char == '/') {
            return Token(DIVIDE, "/");
        }

        else if (peek_char == ':' && source[peek_pos+1] == '=') {
            return Token(ASSIGNMENT, ":=");
        }

        else if (peek_char == '(') {
            return Token(LPAREN, "(");
        }

        else if (peek_char == ')') {
            return Token(RPAREN, ")");
        }

        else if (peek_char == '=') {
            return Token(EQUAL, "=");
        }

        else if (peek_char == '!' && source[peek_pos+1] == '=') {
            return Token(NOTEQUAL, "!=");
        }

        else {
            std::cout << "UnKnown Character: " << current_char << std::endl;
            exit(1);
        }
    } return Token(EOFF, "\0");
}

Token Lexer::next() {
    while (current_char != '\0') {
        if (isspace(current_char)) skipWhiteSpaces();

        else if (current_char == '$') {
            skipComment();
        }

        else if (isdigit(current_char)) {
            return Token(INT, getInteger());
        }

        else if (isalnum(current_char)) {
            return getIdentifier();
        }

        else if (current_char == '+') {
            advance();
            return Token(PLUS, "+");
        }

        else if (current_char == '-') {
            advance();
            return Token(MINUS, "-");
        }

        else if (current_char == '*') {
            advance();
            return Token(MULTIPLY, "*");
        }

        else if (current_char == '/') {
            advance();
            return Token(DIVIDE, "/");
        }

        else if (current_char == ':' && peek() == '=') {
            advance();
            advance();
            return Token(ASSIGNMENT, ":=");
        }

        else if (current_char == '=') {
            advance();
            return Token(EQUAL, "=");
        }

        else if (current_char == '!' && peek() == '=') {
            advance();
            return Token(NOTEQUAL, "!=");
        }

        else if (current_char == '(') {
            advance();
            return Token(LPAREN, "(");
        }

        else if (current_char == '"') {
            return getStringLiteral();
        }

        else if (current_char == ')') {
            advance();
            return Token(RPAREN, ")");
        }

        else if (current_char == '{') {
            advance();
            return Token(LBRACKET, "{");
        }

        else if (current_char == '}') {
            advance();
            return Token(RBRACKET, "}");
        }

        else if (current_char == ';') {
            advance();
            return Token(SEMICOLON, ";");
        }

        else if (current_char == '<') {
            if (peek() == '=') {
                advance();
                advance();
                return Token(LESSTHANOREQUAL, "<=");
            }
            advance();
            return Token(LESSTHAN, "<");
        }

        else if (current_char == '>') {
            if (peek() == '=') {
                advance();
                advance();
                return Token(GREATERTHANOREQUAL, ">=");
            }
            advance();
            return Token(GREATERTHAN, ">");
        }

        else if (current_char == '%') {
            advance();
            return Token(MODULUS, "%");
        }

        else {
            std::cout << "UnKnown Character: " << current_char;
            exit(1);
        }
    } return Token(EOFF, "\0");
}
