#ifndef INTERPRETER_HEADER
#define INTERPRETER_HEADER

#include "parser.hpp"
#include "visitor.hpp"
#include "global.hpp"
#include <variant>
#include <stdexcept>
#include <iostream>
#include <string>

class Interpreter : public NodeVisitor {
private:
    Parser parser;
    GLOBAL_MEMORY globalMemory;
    std::variant<int, std::string> result;

public:
    Interpreter(Parser p);

    void visit(NumberNode* node) override;
    void visit(StringNode* node) override;
    void visit(BinaryNode* node) override;
    void visit(UnaryNode* node) override;
    void visit(AssignmentNode* node) override;
    void visit(VariableNode* node) override;
    void visit(PrintNode* node) override;
    void visit(ScanIntNode* node) override;
    void visit(ScanStrNode* node) override;
    void visit(StrNode* node) override;
    void visit(IfNode* node) override;
    void visit(EmptyNode* node) override;
    void visit(CompoundNode* node) override;

    void interpret();
};

#endif // INTERPRETER_HEADER
