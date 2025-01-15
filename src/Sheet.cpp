
#include "Sheet.hpp"

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

/*
std::pair<std::string, int> address_to_pair(const std::string& input) {
    std::pair<std::string, int> result = {"", 0};
    for (const char i : input) {
        if (std::isdigit(i)) {
            result.second = result.second * 10 + (i - '0');
        }
        else if (std::isalpha(i)) {
            result.first.append(1, i);
        }
        else {
            throw std::invalid_argument("Invalid input");
        }
    }
    return result;
}
*/

// Destructors

// Getters

std::shared_ptr<Cell> Sheet::get_cell(const std::string& key) {
    if (!is_address(key)) {
        throw std::invalid_argument("Invalid input");
    }
    return std::make_shared<Cell>(m_cells[key]);
}

// Setters

// File I/O

void Sheet::save_to_file(const std::string& file_name) const {
    std::ofstream file(file_name);
    if (!file.is_open()) {
        throw std::out_of_range("Could not open file");
    }
    for ( const auto& cell : m_cells ) {
        file << cell.first << " " << cell.second.get() << std::endl;
    }
    file.close();
}
void Sheet::load_from_file(const std::string& file_name) {
    std::ifstream file(file_name);
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
    std::string key = word;

    input >> word;
    if (!is_operator(word)) {
        throw std::invalid_argument("Second argument must be an operator");
    }
    Operation op = string_to_operation(word);

    double current_value = 0;

    while (input >> word) {
        try {
            current_value = std::stod(word);
        } catch (...) {
            current_value = get_cell(word)->get();
        }

        switch (op) {
            case SET:
                m_cells[key] = Cell(current_value);
                break;
            case ADD:
                m_cells[key].add(current_value);
                break;
            case SUB:
                m_cells[key].sub(current_value);
                break;
            case MUL:
                if (!cell_exist(key)) {
                    m_cells[key] = Cell(1);
                }
                m_cells[key].mul(current_value);
                break;
            case DIV:
                if (!cell_exist(key)) {
                    m_cells[key] = Cell(1);
                }
                m_cells[key].div(current_value);
                break;
            default:
                throw std::invalid_argument("Invalid operation");
        }
    }
}



// Utility

bool Sheet::cell_exist(const std::string &key) const {
    if (m_cells.count(key) > 0) {
        return true;
    }
    return false;
}


void Sheet::print_sheet_values() const {
    for (const auto& cell : m_cells) {
        std::cout<<cell.first<< " : " << cell.second.get() << std::endl;
    }
}
