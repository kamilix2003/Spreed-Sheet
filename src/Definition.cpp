
#include "../inc/Definition.hpp"

#include <iostream>

// Constructors
Definition::Definition(const Operation op = none) : m_op(op) {

}


// Getters
Operation Definition::get_operation() const {
    return m_op;
}

std::shared_ptr<std::vector<std::string>> Definition::get_args_vec() const {
    return std::make_shared<std::vector<std::string>>(m_args);
}

std::shared_ptr<std::vector<double>> Definition::get_const_vec() const {
    return std::make_shared<std::vector<double>>(m_const);
}

// Setters


// Arguments operations
void Definition::append_args(const std::string& argument) {
    m_args.push_back(argument);
}

void Definition::append_const(const double constant) {
    m_const.push_back(constant);
}

// Utility
void Definition::print_const() const {
    for (const auto& arg : m_const) {
        std::cout << arg << " ";
    }
}

void Definition::print() const {
    std::cout<<m_op<<"\nArguments:\n";
    for (const auto& arg : m_args) {
        std::cout<<arg<<"\n";
    }
    std::cout<<"Constants:\n";
    for (const auto& arg : m_const) {
        std::cout<<arg<<"\n";
    }
}




