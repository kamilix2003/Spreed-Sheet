
#include "Sheet.hpp"

#include <algorithm>
#include <assert.h>
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
    "NONE",
    "ADD",
    "MUL",
};

Operation is_operator(const std::string& input) {
    for (size_t i = 0; i < OP_COUNT; i++) {
        if (op_str[i] == input)
            return static_cast<Operation>(i);
    }
    return NONE;
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

// Setters
void Sheet::set_cell(const std::string& key, const Cell& cell) {
    m_cells[key] = cell;
}

void Sheet::set_sheet_input(const std::string &input) {
    if (is_address(input.substr(0, 4)) == false) {
        throw std::invalid_argument("Invalid input");
    }
    m_sheet_input = input;
}

// File I/O

void Sheet::save_to_file() {

}
void Sheet::load_from_file() {}
void Sheet::save_to_bin() {}
void Sheet::load_from_bin() {}

// Evaluation
void Sheet::evaluate_cell(const std::string &key) {
    Cell& cell = m_cells[key];
    switch (cell.get_definition()->get_operation()) {
        case NONE:
            try {
                cell.set_value(cell.get_definition()->get_first_const());
            } catch (...) {}
            try {
                const std::string temp = cell.get_definition()->get_first_arg();
                cell.set_value(m_cells[temp].get_value());
            } catch (...) {}
            break;
        case SUM:
            {
                const auto args_ptr = cell.get_definition()->get_args_vec();
                const auto consts_ptr = cell.get_definition()->get_const_vec();

                cell.set_value(0);

                for (const auto consts : *consts_ptr) {
                    cell.add_value(consts);
                }

                for (const auto& arg : *args_ptr) {
                    Cell& arg_cell = m_cells[arg];
                    cell.add_value(arg_cell.get_value());
                }
            }

            break;
        case PROD:

        {
            const auto args_ptr = cell.get_definition()->get_args_vec();
            const auto consts_ptr = cell.get_definition()->get_const_vec();

            cell.set_value(1);

            for (const auto consts : *consts_ptr) {
                cell.mul_value(consts);
            }

            for (const auto& arg : *args_ptr) {
                Cell& arg_cell = m_cells[arg];
                cell.mul_value(arg_cell.get_value());
            }
        }

            break;

        default:

            break;
    }
}

void Sheet::evaluate_sheet() {
    for (const auto& cell : m_cells) {
        evaluate_cell(cell.first);
    }
}


void Sheet::process_sheet_input() {
    const std::vector<std::string> input = split_sheet_input(m_sheet_input);
    std::vector<std::string> args;
    std::vector<double> consts;

    for (size_t i = 2; i < input.size(); i++) {
        if (is_address(input[i])) {
            args.push_back(input[i]);
        }
        else {
            try {
                consts.push_back(std::stod(input[i]));
            } catch(...) {
                continue;
            }
        }
    }

    if (is_operator(input[1])) {
        m_cells.emplace(input[0], Cell(Definition(is_operator(input[1]), args, consts)));
    }
    else if (is_address(input[1])) {
        m_cells.emplace(input[0], Cell(Definition(Operation::NONE, {input[1]}, {})));
    }
    else {
        try {
            m_cells.emplace(input[0], Cell(Definition(Operation::NONE, {}, {std::stod(input[1])})));
        } catch(...) {}
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
    m_cells[key].print_value();
}

void Sheet::print_sheet() const {
    for (const auto& cell : m_cells) {
        cell.second.print();
    }
}

void Sheet::print_sheet_values() const {
    for (const auto& cell : m_cells) {
        std::cout<<cell.first<< ": ";
        cell.second.print_value();
    }
}
