
#include "interpreter.hpp"

Interpreter::Interpreter(Parser p) : parser(p), result(0) {}

void Interpreter::visit(NumberNode* node) {
    result = std::stoi(node->value);
}

void Interpreter::visit(StringNode* node) {
    result = node->value;
}

void Interpreter::visit(BinaryNode* node) {
    node->leftNode->accept(this);
    auto left = result;

    node->rightNode->accept(this);
    auto right = result;

    if (std::holds_alternative<int>(left) && std::holds_alternative<int>(right)) {
        int leftValue = std::get<int>(left);
        int rightValue = std::get<int>(right);

        switch (node->op.type) {
            case PLUS:
                result = leftValue + rightValue;
                break;
            case MINUS:
                result = leftValue - rightValue;
                break;
            case MULTIPLY:
                result = leftValue * rightValue;
                break;
            case DIVIDE:
                if (rightValue == 0) {
                    throw std::runtime_error("Division by zero");
                }
                result = leftValue / rightValue;
                break;
            case EQUAL:
                result = (left == right) ? "true" : "false";
                break;
            case NOTEQUAL:
                result = (left != right) ? "true" : "false";
                break;
            case LESSTHAN:
                result = (left < right) ? "true" : "false";
                break;
            case LESSTHANOREQUAL:
                result = (left <= right) ? "true" : "false";
                break;
            case GREATERTHANOREQUAL:
                result = (left >= right) ? "true" : "false";
                break;
            case GREATERTHAN:
                result = (left > right) ? "true" : "false";
                break;
            case MODULUS:
                if (rightValue == 0) {
                    throw std::runtime_error("Division by zero");
                }
                result = leftValue % rightValue;
                break;
            default:
                throw std::runtime_error("Unknown operator");
        }
    } else if (std::holds_alternative<std::string>(left) && std::holds_alternative<std::string>(right)) {
        if (node->op.type == PLUS) {
            result = std::get<std::string>(left) + std::get<std::string>(right);
        } else if (node->op.type == EQUAL) {
            result = (left == right) ? "true" : "false";
        } else if (node->op.type == NOTEQUAL) {
            result = (left != right) ? "true" : "false";
        } else {
            throw std::runtime_error("Unsupported string operation");
        }
    } else {
        throw std::runtime_error("Type mismatch in binary operation");
    }
}

void Interpreter::visit(UnaryNode* node) {
    node->expr->accept(this);
    TokenType op = node->op.type;
    if (op == PLUS) {
        // No action needed
    } else if (op == MINUS) {
        result = -(std::get<int>(result));
    }
}

void Interpreter::visit(AssignmentNode* node) {
    std::string var_name = node->leftNode->token.value;
    node->rightNode->accept(this);
    if (std::holds_alternative<int>(result)) {
        globalMemory.addInt(var_name, std::get<int>(result));
    } else {
        globalMemory.addString(var_name, std::get<std::string>(result));
    }
}

void Interpreter::visit(VariableNode* node) {
    std::string var_name = node->token.value;
    try {
        result = globalMemory.getValue(var_name);
    } catch (const std::runtime_error& e) {
        throw std::runtime_error("Unknown identifier: " + var_name);
    }
}

void Interpreter::visit(PrintNode* node) {
    node->expression->accept(this);
    if (std::holds_alternative<int>(result)) {
        std::cout << std::get<int>(result) << std::endl;
    } else {
        std::cout << std::get<std::string>(result) << std::endl;
    }
}

void Interpreter::visit(ScanIntNode* node) {
    std::string input;
    node->expression->accept(this);
    if (std::holds_alternative<int>(result)) {
        std::cout << std::get<int>(result);
    } else {
        std::cout << std::get<std::string>(result);
    }
    std::getline(std::cin, input);
    try {
        result = std::stoi(input);
    } catch(const std::invalid_argument&) {
        throw std::runtime_error("Invalid Input. Expected an Integer.");
    }
}

void Interpreter::visit(ScanStrNode* node) {
    std::string input;
    node->expression->accept(this);
    if (std::holds_alternative<int>(result)) {
        std::cout << std::get<int>(result);
    } else {
        std::cout << std::get<std::string>(result);
    }
    std::getline(std::cin, input);
    result = input;
}

void Interpreter::visit(StrNode* node) {
    node->expression->accept(this);
    if (std::holds_alternative<int>(result)) {
        result = std::to_string(std::get<int>(result));
    } else {
        result = std::get<std::string>(result);
    }
}

void Interpreter::visit(IfNode* node) {
    node->condition->accept(this);
    std::string condition_result = std::get<std::string>(result);

    if (condition_result == "true") {
        node->true_branch->accept(this);
    } else {
        node->false_branch->accept(this);
    }
}

void Interpreter::visit(EmptyNode* node) {
    // No action needed for empty nodes
}

void Interpreter::visit(CompoundNode* node) {
    for (auto statement : node->statements) {
        statement->accept(this);
    }
}

void Interpreter::interpret() {
    Node* program = parser.parse();
    if (!program) {
        throw std::runtime_error("Parse error: no syntax tree");
    }

    program->accept(this);

    delete program; // Clean up memory
}
