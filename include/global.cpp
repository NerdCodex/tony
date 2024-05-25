
#include "global.hpp"
#include <stdexcept>

std::map<std::string, valueType> STACK;

void GLOBAL_MEMORY::addInt(const std::string& key, int value) {
    STACK[key] = value;
}

void GLOBAL_MEMORY::addString(const std::string& key, const std::string& value) {
    STACK[key] = value;
}

valueType GLOBAL_MEMORY::getValue(const std::string& key) {
    auto it = STACK.find(key);
    valueType value = "\0";
    if (it != STACK.end()) {
        return it->second;
    }
    throw std::runtime_error("Unknown identifier: " + key);
    return value;
}
