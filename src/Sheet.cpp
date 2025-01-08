
#include "Sheet.hpp"

#include <algorithm>
#include <array>
#include <assert.h>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

std::vector<std::string> split_sheet_input(const std::string &input) {
    std::vector<std::string> output;
    std::istringstream iss(input);
    std::string token;
    while (iss >> token) {
        output.push_back(token);
    }
    return output;
}

const std::array<std::string, OP_COUNT> op_str = {
    "SET",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "SUM",
    "PROD",
};

Operation is_operator(const std::string& input) {
    for (size_t i = 0; i < OP_COUNT; i++) {
        if (op_str[i] == input)
            return static_cast<Operation>(i);
    }
    return SET;
}

bool is_address(const std::string& input) {
    if ( input.size() != 4) {
        return false;
    }
    if ( std::any_of(input.begin(), input.begin()+1, isupper) == false ) {
        return false;
    }
    if ( std::any_of(input.end()-1, input.end(), isdigit) == false ) {
        return false;
    }
    if (is_operator(input)) {
        return false;
    }
    return true;
}

// Getters

std::shared_ptr<Cell> Sheet::get_cell(const std::string& key) {
    if (!is_address(key)) {
        throw std::invalid_argument("Invalid address");
    }
    return std::make_shared<Cell>(m_cells[key]);
}

double Sheet::get_value(const std::string &key) {
    if (!is_address(key)) {
        throw std::invalid_argument("Invalid address");
    }
    return m_cells.at(key).get();
}

std::unique_ptr<double> Sheet::get_value_ptr(const std::string &key) {
    if (!is_address(key)) {
        throw std::invalid_argument("Invalid address");
    }
    return m_cells.at(key).get_ptr();
}

// Setters
void Sheet::set_cell(const std::string& key, const Cell& cell) {
    m_cells[key] = cell;
}

void Sheet::set_cell(const std::string &key, double value) {
    m_cells[key] = Cell(value);
}

void Sheet::set_cell(const std::string &key, const std::string &key_ref) {
    m_cells[key] = *get_cell(key_ref);
}


void Sheet::set_sheet_input(const std::string &input) {
    if (is_address(input.substr(0, 4)) == false) {
        throw std::invalid_argument("Invalid input");
    }
    m_sheet_input = input;
}

// File I/O

void Sheet::save_to_file(const std::string& file_name) {
    std::ofstream file(file_name);
    for ( const auto& cell : m_cells ) {

        file << cell.first << " " << cell.second.get() << std::endl;

    }
    file.close();
}
void Sheet::load_from_file(const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        throw std::invalid_argument("Unable to open sheet");
    }
    std::string line, key, value_str;
    double value;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        ss >> key; ss >> value_str;
        m_cells[key] = Cell(std::stod(value_str));
    }
    file.close();
}



void Sheet::process_sheet_input() {
    if (m_sheet_input.empty()) {
        return;
    }

    std::string word;
    std::stringstream input(m_sheet_input);

    input >> word;
    if (!is_address(word)) {
        throw std::invalid_argument("First argument must be an address");
    }
    std::string key = word;

    input >> word;
    if (!is_operator(word)) {
        throw std::invalid_argument("Second argument must be an operator");
    }
    Operation op = is_operator(word);

    bool first_arg = true;
    double current_value = 0;

    while (input >> word) {
        try {
            current_value = std::stod(word);
        } catch (...) {
            current_value = get_cell(word)->get();
        }

        if (first_arg) {
            first_arg = false;
            set_cell(key, current_value);
        }

        switch (op) {
            case SET:
                input.clear();
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



// Utility
bool Sheet::cell_exist(const std::string &key) {
    return m_cells.find(key) != m_cells.end();
}


void Sheet::print_cell(const std::string& key) {
    std::cout<<"Cell: "<<key<<std::endl;
    m_cells[key].print();
}

void Sheet::print_cell_value(const std::string& key) {
    std::cout<<"Cell: "<<key<<std::endl;
    m_cells[key].print();
}

void Sheet::print_sheet() const {
    for (const auto& cell : m_cells) {
        cell.second.print();
    }
}

void Sheet::print_sheet_values() const {
    for (const auto& cell : m_cells) {
        std::cout<<cell.first<< ": ";
        cell.second.print();
    }
}
