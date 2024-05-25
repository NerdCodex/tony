
#include "ast.hpp"

CompoundNode::CompoundNode(std::vector<Node*>& stmts): statements(stmts) {}

CompoundNode::~CompoundNode() {
    for (auto stmt : statements) {
            delete stmt; // Clean up memory for individual statements
    }
}

IfNode::IfNode(Node* con, Node* trueb, Node* falseb)
    : condition(con), true_branch(trueb), false_branch(falseb) {}

BinaryNode::BinaryNode(Node* left, Token op, Node* right)
    : leftNode(left), op(op), rightNode(right) {}

NumberNode::NumberNode(Token tok)
    : type(tok.type), value(tok.value) {}

UnaryNode::UnaryNode(Token tok, Node* expr)
    : op(tok), expr(expr) {}

AssignmentNode::AssignmentNode(VariableNode* left, Token op, Node* right)
    : leftNode(left), op(op), rightNode(right) {}

VariableNode::VariableNode(Token tok)
    : token(tok) {}

StringNode::StringNode(Token tok)
    : value(tok.value) {}

EmptyNode::EmptyNode() {}

PrintNode::PrintNode(Node* expr)
    :expression(expr) {}

ScanIntNode::ScanIntNode(Node* expr)
    :expression(expr) {}

ScanStrNode::ScanStrNode(Node* expr)
    :expression(expr) {}

StrNode::StrNode(Node* expr)
    :expression(expr) {}

// Accept methods for visitor pattern

void CompoundNode::accept(NodeVisitor* visitor) {
    visitor->visit(this);
}

void BinaryNode::accept(NodeVisitor* visitor) {
    visitor->visit(this);
}

void NumberNode::accept(NodeVisitor* visitor) {
    visitor->visit(this);
}

void UnaryNode::accept(NodeVisitor* visitor) {
    visitor->visit(this);
}

void AssignmentNode::accept(NodeVisitor* visitor) {
    visitor->visit(this);
}

void VariableNode::accept(NodeVisitor* visitor) {
    visitor->visit(this);
}

void EmptyNode::accept(NodeVisitor* visitor) {
    visitor->visit(this);
}

void StringNode::accept(NodeVisitor* visitor) {
    visitor->visit(this);
}

void PrintNode::accept(NodeVisitor* visitor) {
    visitor->visit(this);
}

void ScanIntNode::accept(NodeVisitor* visitor) {
    visitor->visit(this);
}

void ScanStrNode::accept(NodeVisitor* visitor) {
    visitor->visit(this);
}

void IfNode::accept(NodeVisitor* visitor) {
    visitor->visit(this);
}

void StrNode::accept(NodeVisitor* visitor) {
    visitor->visit(this);
}
