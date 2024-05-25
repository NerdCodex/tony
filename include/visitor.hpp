#ifndef VISITOR_HEADER
#define VISITOR_HEADER

#include <stdexcept>
#include "ast.hpp"

class Node;
class CompoundNode;
class NumberNode;
class BinaryNode;
class UnaryNode;
class AssignmentNode;
class VariableNode;
class EmptyNode;
class StringNode;
class PrintNode;
class ScanIntNode;
class ScanStrNode;
class IfNode;
class StrNode;

class NodeVisitor {
public:
    virtual void visit(NumberNode* node) = 0;
    virtual void visit(BinaryNode* node) = 0;
    virtual void visit(UnaryNode* node) = 0;
    virtual void visit(AssignmentNode* node) = 0;
    virtual void visit(VariableNode* node) = 0;
    virtual void visit(EmptyNode* node) = 0;
    virtual void visit(StringNode* node) = 0;
    virtual void visit(PrintNode* node) = 0;
    virtual void visit(ScanIntNode* node) = 0;
    virtual void visit(ScanStrNode* node) = 0;
    virtual void visit(CompoundNode* node) = 0;
    virtual void visit(IfNode* node) = 0;
    virtual void visit(StrNode* node) = 0;

    void visit(Node* node) {
        if (auto numberNode = (NumberNode*) node) {
            visit(numberNode);
        } else if (auto binaryNode = (BinaryNode*) node) {
            visit(binaryNode);
        } else if (auto unaryNode = (UnaryNode*) node) {
            visit(unaryNode);
        } else if (auto assignNode = (AssignmentNode*) node) {
            visit(assignNode);
        } else if (auto varNode = (VariableNode*) node) {
            visit(varNode);
        } else if (auto emptyNode = (EmptyNode*) node) {
            visit(emptyNode);
        } else if (auto stringNode = (StringNode*) node) {
            visit(stringNode);
        } else if (auto printNode = (PrintNode*) node) {
            visit(printNode);
        } else if (auto scanIntNode = (ScanIntNode*) node) {
            visit(scanIntNode);
        } else if (auto scanStrNode = (ScanStrNode*) node) {
            visit(scanStrNode);
        } else if (auto compoundNode = (CompoundNode*) node) {
            visit(compoundNode);
        } else if (auto strNode = (StrNode*) node) {
            visit(strNode);
        } else if (auto ifNode = (IfNode*) node) {
            visit(ifNode);
        } else {
            throw std::runtime_error("No visit method for node type");
        }
    }
};

#endif
