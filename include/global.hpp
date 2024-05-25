#ifndef GLOBAL_SCOPE_HEADER
#define GLOBAL_SCOPE_HEADER

#include <map>
#include <variant>
#include <vector>
#include <string>


using valueType = std::variant<int, std::string>;
extern std::map<std::string, valueType> STACK;

class GLOBAL_MEMORY {
public:
    void addInt(const std::string& key, int value);
    void addString(const std::string& key, const std::string& value);
    valueType getValue(const std::string& key);
};



#endif
