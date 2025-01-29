#pragma once

#include <string>
#include <array>
#include "Sheet.hpp"

#define  OP_COUNT 5
#define  FILE_EXT ".txt"
#define  FILE_DIR "./"

enum Operation {
    SET = 0,
    ADD,
    SUB,
    MUL,
    DIV,
};

std::string sort_address(std::string& input);                   // Sorts address characters A1B1 -> AB11
bool is_address(const std::string& input);
Operation string_to_operation(const std::string& input);        // Casts operation keyword string to Operation enum
bool is_operator(const std::string& input);
