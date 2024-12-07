
#include "../inc/Definition.hpp"

#include <iostream>

const std::array<std::string, 3> op_names = {
    "Plain value",
    "Addition",
    "Multiplication",
};

// Constructors

Definition::Definition(const Operation op, const std::vector<std::string>& args, const std::vector<double>& consts)
    : m_op(op), m_args(args), m_consts(consts)
{

}

Definition::Definition(const Definition &definition)
    : m_op(definition.get_operation())
{
    const auto args = definition.get_args_vec();
    const auto consts = definition.get_const_vec();
    for (auto& arg : *args) {
        m_args.push_back(arg);
    }
    for (auto constant : *consts) {
        m_consts.push_back(constant);
    }
}

// Getters
Operation Definition::get_operation() const {
    return m_op;
}

std::shared_ptr<std::vector<std::string>> Definition::get_args_vec() const {
    return std::make_shared<std::vector<std::string>>(m_args);
}

std::shared_ptr<std::vector<double>> Definition::get_const_vec() const {
    return std::make_shared<std::vector<double>>(m_consts);
}

std::string Definition::get_first_arg() const {
    return m_args.at(0);
}

double Definition::get_first_const() const {
    return m_consts.at(0);
}



// Setters

void Definition::set_operation(const Operation op) {
    m_op = op;
}

void Definition::set_args_vec(const std::vector<std::string> &args) {
    m_args = args;
}

void Definition::set_const_vec(const std::vector<double> &consts) {
    m_consts = consts;
}



// Arguments operations
void Definition::append_args(const std::string& argument) {
    m_args.push_back(argument);
}

void Definition::append_const(const double constant) {
    m_consts.push_back(constant);
}

// Operators



// Utility
void Definition::print_const() const {
    for (const auto& arg : m_consts) {
        std::cout << arg << " ";
    }
}

void Definition::print() const {
    std::cout<<"Operation: "<<op_names[m_op]<<"\nArguments: ";
    for (const auto& arg : m_args) {
        std::cout<<arg<<" ";
    }
    std::cout<<"\nConstants: ";
    for (const auto& arg : m_consts) {
        std::cout<<arg<<" ";
    }
    std::cout<<std::endl;
}




