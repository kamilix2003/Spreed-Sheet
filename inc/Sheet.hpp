#pragma once
#include <map>
#include <memory>

#include "Cell.hpp"

# define OP_COUNT 5

enum Operation {
    SET = 0,
    ADD,
    SUB,
    MUL,
    DIV,
};

class Sheet {
    private:
    std::map<std::string, Cell> m_cells;

    public:
    // Constructors

    // Destructors

    // Getters

    std::shared_ptr<Cell> get_cell(const std::string& key);

    // Setters

    // File I/O
    void save_to_file(const std::string& file_name) const;
    void load_from_file(const std::string& file_name);

    // Evaluation
    void sheet_input(const std::string& sheet_input);

    // Utility
    bool cell_exist(const std::string& key) const;
    void print_sheet_values() const;
};