
#include "parser.hpp"

Parser::Parser(Lexer& lex) : lexer(lex) {
    current_token = lexer.next();
}

void Parser::eat(TokenType token_type) {
    if (current_token.type == token_type) {
        current_token = lexer.next();
    } else {
        std::cout << current_token.value << ":" << token_type << std::endl;
        throw std::runtime_error("Unexpected token type");
    }
}

Node* Parser::compound_statement() {
    std::vector<Node*> statements;
    if (current_token.type == LBRACKET) eat(LBRACKET);
    if (current_token.type == BEGIN) eat(BEGIN);
    while (current_token.type != END && current_token.type != RBRACKET) {
        if (current_token.type == SEMICOLON) {
            eat(SEMICOLON);
        } else {
            statements.push_back(statement());
        }
    }
    if (current_token.type == RBRACKET) eat(RBRACKET);
    if (current_token.type == END) eat(END);
    if (statements.size() == 1) return statements[0];
    else return new CompoundNode(statements);
}

Node* Parser::statement() {
    Node* node = new EmptyNode();
    if (current_token.type == IDENTIFIER) {
        if (lexer.peekToken().type == ASSIGNMENT) {
            node = assignment_statement();
        } else {
            node = expr();
        }
    } else if (current_token.type == PRINT) {
        node = print_statement();
    } else if (current_token.type == SCANINT) {
        node = scanInt_statement();
    } else if (current_token.type == SCANSTR) {
        node = scanStr_statement();
    } else if (current_token.type == IF) {
        node = if_statement();
    } else node = expr();

    return node;
}

Node* Parser::if_statement() {
    eat(IF);
    eat(LPAREN);
    Node* condition = expr();
    eat(RPAREN);
    Node* if_branch = compound_statement();
    Node* else_branch = nullptr;

    if (current_token.type == ELSE) {
        eat(ELSE);
        else_branch = compound_statement();
    }

    return new IfNode(condition, if_branch, else_branch);
}

Node* Parser::assignment_statement() {
    VariableNode* left = (VariableNode*) variable();
    Token token = current_token;
    Node* right = new EmptyNode();
    eat(ASSIGNMENT);
    if (current_token.type == SCANINT) {
        right = scanInt_statement();
    } else if (current_token.type == SCANSTR){
        right = scanStr_statement();
    } else {
        right = expr();
    }
    Node* node = new AssignmentNode(left, token, right);
    return node;
}

Node* Parser::print_statement() {
    eat(PRINT);
    eat(LPAREN);
    Node* expression = expr();
    eat(RPAREN);
    return new PrintNode(expression);
}

Node* Parser::scanInt_statement() {
    eat(SCANINT);
    eat(LPAREN);
    Node* expression = expr();
    eat(RPAREN);
    return new ScanIntNode(expression);
}

Node* Parser::int_to_str() {
    eat(STR);
    eat(LPAREN);
    Node* expression = expr();
    eat(RPAREN);
    return new StrNode(expression);
}

Node* Parser::scanStr_statement() {
    eat(SCANSTR);
    eat(LPAREN);
    Node* expression = expr();
    eat(RPAREN);
    return new ScanStrNode(expression);
}

Node* Parser::variable() {
    Node* node = new VariableNode(current_token);
    eat(IDENTIFIER);
    return node;
}

Node* Parser::stringLiteral() {
    Token token = current_token;
    eat(STRING);
    return new StringNode(token);
}

Node* Parser::factor() {
    Token token = current_token;
    Node* node = new EmptyNode();
    if (token.type == INT) {
        eat(INT);
        node = new NumberNode(token);
    } else if (token.type == STR) {
        node = int_to_str();
    } else if (token.type == STRING) {
        node = stringLiteral();
    } else if (token.type == LPAREN) {
        eat(LPAREN);
        node = expr();
        eat(RPAREN);
    } else if (token.type == PLUS) {
        eat(PLUS);
        node = new UnaryNode(token, factor());
    } else if (token.type == MINUS) {
        eat(MINUS);
        node = new UnaryNode(token, factor());
    } else {
        node = variable();
    }
    return node;
}

Node* Parser::term() {
    Node* node = factor();
    Token token = current_token;
    while(token.type == MULTIPLY || token.type == DIVIDE || token.type == MODULUS) {
        if (token.type == MULTIPLY) eat(MULTIPLY);
        else if (token.type == DIVIDE) eat(DIVIDE);
        else if (token.type == MODULUS) eat(MODULUS);
        node = new BinaryNode(node, token, factor());
        token = current_token;
    }
    return node;
}


Node* Parser::expr() {
    Node* node = term();
    Token token = current_token;
    while (token.type == PLUS || token.type == MINUS || token.type == EQUAL || token.type == NOTEQUAL || token.type == LESSTHAN
            || token.type == LESSTHANOREQUAL || token.type == GREATERTHAN || token.type == GREATERTHANOREQUAL || token.type == STR || token.type == MODULUS) {
        if (token.type == PLUS) eat(PLUS);
        else if (token.type == EQUAL) eat(EQUAL);
        else if (token.type == NOTEQUAL) eat(NOTEQUAL);
        else if (token.type == LESSTHAN) eat(LESSTHAN);
        else if (token.type == LESSTHANOREQUAL) eat(LESSTHANOREQUAL);
        else if (token.type == GREATERTHAN) eat(GREATERTHAN);
        else if (token.type == GREATERTHANOREQUAL) eat(GREATERTHANOREQUAL);
        else if (token.type == MINUS) eat(MINUS);
        else if (token.type == MODULUS) eat(MODULUS);
        node = new BinaryNode(node, token, term());
        token = current_token;
    }
    return node;
}

Node* Parser::parse() {
    Node* node = compound_statement();
    if (current_token.type != EOFF) {
        throw std::runtime_error("NOT END OF FILE (EOF).");
    }
    return node;
}
