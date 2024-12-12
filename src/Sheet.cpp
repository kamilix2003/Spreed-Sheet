
#include "Sheet.hpp"

#include <algorithm>
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
    "NONE",
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

void Sheet::save_to_file(const std::string& file_name) {
    if (file_name.empty()) {
        throw std::invalid_argument("Empty file name");
    }
    std::ofstream file(file_name);
    if (!file.is_open()) {
        throw std::invalid_argument("Cannot open file");
    }
    for ( const auto& cell : m_cells ) {

        file << cell.first << "{";

        auto& current_cell = cell.second;
        auto current_def = current_cell.get_definition();
        file << op_str[current_def->get_operation()] << "";

        auto arg_vec = *current_def->get_args_vec();
        file << "[";
        for (const auto& a : arg_vec) {
            file << a << ",";
        }
        file << "]";

        auto const_vec = *current_def->get_const_vec();
        file << "[";
        for (const auto& c : const_vec) {
            file << c << ",";
        }
        file << "]";

    file << "}\n";
    }
    file.close();
}
void Sheet::load_from_file(const std::string& file_name) {

    struct Current_cell {
        std::string name;
        std::string op;
        std::vector<std::string> args;
        std::vector<double> consts;
    };

    m_cells.clear();
    std::ifstream file(file_name);
    if (!file.is_open()) {
        throw std::invalid_argument("File does not exist");
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string cell_line;
    while (std::getline(buffer, cell_line, '\n')) {
        Current_cell cell{};
        if (!is_address(cell_line.substr(0, 4))) {
            throw std::invalid_argument("Invalid input");
        }
        cell.name = cell_line.substr(0, 4);
        cell.op = cell_line.substr(
            cell_line.find_first_of('{') + 1,
            cell_line.find_first_of('[') - cell_line.find_first_of('{') - 1);
        std::stringstream args_stream(cell_line.substr(
            cell_line.find_first_of('[') + 1,
            cell_line.find_first_of(']') - cell_line.find_first_of('[') - 1));
        std::string token;
        while (std::getline(args_stream, token, ',')) {
            cell.args.push_back(token);
        }
        std::stringstream consts_stream(cell_line.substr(
            cell_line.find_last_of('[') + 1,
            cell_line.find_last_of(']') - cell_line.find_last_of('[') - 1));
        while (std::getline(consts_stream, token, ',')) {
            cell.consts.push_back(std::stod(token));
        }

        m_cells[cell.name] = Cell(
            Definition(
                is_operator(cell.op),
                cell.args,
                cell.consts
                )
            );
    }
    file.close();
}


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
