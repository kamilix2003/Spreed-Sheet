
#include "Utils.hpp"

// Look-up table for operation keywords
const std::array<std::string, OP_COUNT> op_str = {
    "SET",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
};

bool is_operator(const std::string& input) {
    for (size_t i = 0; i < OP_COUNT; i++) {
        if (op_str[i] == input)
            return true;
    }
    return false;
}
Operation string_to_operation(const std::string& input) {
    for (size_t i = 0; i < OP_COUNT; i++) {
        if (op_str[i] == input)
            return static_cast<Operation>(i);
    }
    throw std::invalid_argument("Invalid operation");
}
bool is_address(const std::string& input) {
    bool letter = false;
    bool number = false;
    for (const char c : input) {
        if (std::isdigit(c)) {
            number = true;
        }
        else if (std::isalpha(c)) {
            letter = true;
        }
    }
    return letter && number;
}

std::string sort_address(std::string& input) {
    std::string digits, letters;
    for (const char c : input) {
        if (std::isdigit(c)) {
            digits += c;
        }
        else if (std::isalpha(c)) {
            letters += c;
        }
    }
    return letters + digits;
}