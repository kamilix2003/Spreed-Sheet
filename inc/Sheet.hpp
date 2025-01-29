#pragma once

#include <map>
#include <fstream>
#include <sstream>
#include <string>

#include "Cell.hpp"

class Sheet {
    private:
    std::map<std::string, Cell> m_cells;

    public:

    std::shared_ptr<Cell> get_cell(const std::string& key);

    // File I/O
    void save_to_file(const std::string& file_name) const;
    void load_from_file(const std::string& file_name);

    // Evaluation
    void sheet_input(const std::string& sheet_input);

    // Utility
    std::string file_name_to_path(const std::string& file_name) const;
    void print_sheet_values() const;
};