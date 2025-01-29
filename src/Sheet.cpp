#pragma once
#include "Sheet.hpp"
#include "Utils.hpp"

// Getters

std::shared_ptr<Cell> Sheet::get_cell(const std::string& key) {
    if (!is_address(key)) {
        throw std::invalid_argument("Invalid input");
    }
    return std::make_shared<Cell>(m_cells[key]);
}

// File I/O

void Sheet::save_to_file(const std::string& file_name) const {
    const std::string file_path = file_name_to_path(file_name);
    std::ofstream file(file_path);
    for ( const auto& cell : m_cells ) {
        file << cell.first << " " << cell.second.get() << std::endl;
    }
    file.close();
}
void Sheet::load_from_file(const std::string& file_name) {
    const std::string file_path = file_name_to_path(file_name);
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::out_of_range("Unable to open sheet");
    }
    std::string line, key, value_str;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        ss >> key; ss >> value_str;
        m_cells[key] = Cell(std::stod(value_str));
    }
    file.close();
}
void Sheet::sheet_input(const std::string& sheet_input) {
    if (sheet_input.empty()) {
        return;
    }

    std::string word;
    std::stringstream input(sheet_input);

    input >> word;
    if (!is_address(word)) {
        throw std::invalid_argument("First argument must be an address");
    }
    std::string key = sort_address(word);

    input >> word;
    if (!is_operator(word)) {
        throw std::invalid_argument("Second argument must be an operator");
    }
    const Operation op = string_to_operation(word);

    double current_value = 0;
    bool first_argument = true;

    while (input >> word) {
        try {
            current_value = std::stod(word);
        } catch (...) {
            current_value = get_cell(sort_address(word))->get();
        }

        if (first_argument) {
            m_cells[key] = Cell(current_value);
            first_argument = false;
        }
        else {
            switch (op) {
                case SET:
                    m_cells[key].set(current_value);
                break;
                case ADD:
                    m_cells[key].add(current_value);
                break;
                case SUB:
                    m_cells[key].sub(current_value);
                break;
                case MUL:
                    m_cells[key].mul(current_value);
                break;
                case DIV:
                    m_cells[key].div(current_value);
                break;
                default:
                    throw std::invalid_argument("Invalid operation");
            }
        }
    }
}

// Utility

std::string Sheet::file_name_to_path(const std::string& file_name) const {
    return std::string(FILE_DIR + file_name + FILE_EXT);
}
void Sheet::print_sheet_values() const {
    for (const auto& cell : m_cells) {
        std::cout<<cell.first<< " : " << cell.second.get() << std::endl;
    }
}
