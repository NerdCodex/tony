#include <iostream>
#include <fstream>
#include <sstream>
#include "include/lexer.hpp"
#include "include/parser.hpp"
#include "include/interpreter.hpp"

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    try {
        std::string filename = argv[1];
        std::string program = readFile(filename);

        Lexer lexer(program);
        Parser parser(lexer);
        Interpreter interpreter(parser);
        interpreter.interpret();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
