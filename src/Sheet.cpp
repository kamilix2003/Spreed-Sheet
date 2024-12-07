
#include "Sheet.hpp"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

// Setters
void Sheet::set_cell(const std::string& key, const Cell& cell) {
    m_cells[key] = cell;
}

void Sheet::set_sheet_input(const std::string &input) {
    m_sheet_input = input;
}


// Evaluation
void Sheet::evaluate_cell(const std::string &key) {
    Cell& cell = m_cells[key];
    switch (cell.get_definition()->get_operation()) {
        case none:

            break;
        case add:
            {
                const auto args_ptr = cell.get_definition()->get_args_vec();
                const auto consts_ptr = cell.get_definition()->get_const_vec();

                cell.set_value(0);

                for (const auto consts : *consts_ptr) {
                    // std::cout<<consts<<std::endl;
                    cell.add_value(consts);
                }

                for (const auto& arg : *args_ptr) {
                    Cell& arg_cell = m_cells[arg];
                    cell.add_value(arg_cell.get_value());
                    // std::cout<<arg<<std::endl;
                }
            }

            break;
        case mul:

        {
            const auto args_ptr = cell.get_definition()->get_args_vec();
            const auto consts_ptr = cell.get_definition()->get_const_vec();

            cell.set_value(1);

            for (const auto consts : *consts_ptr) {
                cell.mul_value(consts);
                // std::cout<<consts<<std::endl;
            }

            for (const auto& arg : *args_ptr) {
                Cell& arg_cell = m_cells[arg];
                cell.mul_value(arg_cell.get_value());
                // std::cout<<arg<<std::endl;
            }
        }

            break;

        default:

            break;
    }
}

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

Operation is_operation(const std::string& input) {
    for (size_t i = 0; i < OP_COUNT; i++) {
        if (op_str[i] == input)
            return static_cast<Operation>(i);
    }
    return none;
}

bool is_address(const std::string& input) {
    if ( std::any_of(input.begin(), input.end(), isupper) ) {
        return true;
    }
    return false;
}

/*
    Example input: AB12 AA1 BB3 1.2 11
    First element - output cell
    Second element - operation
                    plain value
                    reference to cell
    Other elements - inputs
*/
void Sheet::process_sheet_input() {
    const std::vector<std::string> input = split_sheet_input(m_sheet_input);
    std::vector<std::string> args;
    std::vector<double> consts;
    for (size_t i = 2; i < input.size(); i++) {
        if (is_address(input[i])) {
            args.push_back(input[i]);
        }
        else {
            consts.push_back(std::stod(input[i]));
        }
    }
    if (is_operation(input[1])) {
        Definition def(is_operation(input[1]), args, consts);
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

