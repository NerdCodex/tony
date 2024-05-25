#ifndef AST_HEADER
#define AST_HEADER

#include "visitor.hpp"
#include "token.hpp"
#include <vector>
#include <string>

class Node {
public:
    virtual ~Node() = default;
    virtual void accept(NodeVisitor* visitor) = 0;
};

class CompoundNode : public Node {
public:
    std::vector<Node*> statements;
    CompoundNode(std::vector<Node*>& stmts);
    ~CompoundNode();
    void accept(NodeVisitor*);
};

class BinaryNode: public Node {
public:
    Node* leftNode;
    Token op;
    Node* rightNode;
    BinaryNode(Node* left, Token op, Node* right);
    void accept(NodeVisitor* visitor) override;
};


class NumberNode: public Node {
public:
    TokenType type;
    std::string value;
    NumberNode(Token);
    void accept(NodeVisitor* visitor) override;
};

class StringNode: public Node {
public:
    std::string value;
    StringNode(Token tok);
    void accept(NodeVisitor* visitor) override;
};

class UnaryNode: public Node {
public:
    Token op;
    Node* expr;
    UnaryNode(Token tok, Node* expr);
    void accept(NodeVisitor * visitor) override;
};

class AssignmentNode: public Node {
public:
    VariableNode* leftNode;
    Token op;
    Node* rightNode;
    AssignmentNode(VariableNode* left, Token op, Node* right);
    void accept(NodeVisitor* visitor) override;
};

class VariableNode: public Node {
public:
    Token token;
    VariableNode(Token);
    void accept(NodeVisitor* visitor) override;
};

class EmptyNode: public Node {
public:
    EmptyNode();
    void accept(NodeVisitor* visitor) override;
};

class PrintNode: public Node {
public:
    Node* expression;
    PrintNode(Node*);
    void accept(NodeVisitor* visitor);
};

class ScanIntNode: public Node {
public:
    Node* expression;
    ScanIntNode(Node*);
    void accept(NodeVisitor*);
};

class ScanStrNode: public Node {
public:
    Node* expression;
    ScanStrNode(Node*);
    void accept(NodeVisitor*);
};

class StrNode: public Node {
public:
    Node* expression;
    StrNode(Node*);
    void accept(NodeVisitor*);
};

class IfNode: public Node {
public:
    Node* condition;
    Node* true_branch;
    Node* false_branch;
    IfNode(Node*, Node*, Node*);
    void accept(NodeVisitor*);
};

// Constrcutors


#endif
