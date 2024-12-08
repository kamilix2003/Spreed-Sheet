
#include <iostream>
#include <utility>
#include "Cell.hpp"

// Constructors
Cell::Cell()
    : m_value(0), m_definition(NONE, {}, {}) {

}

Cell::Cell(const double value)
    : m_value(0), m_definition(NONE, {}, {value}) {

}

Cell::Cell(const std::string& address)
    : m_value(0), m_definition(NONE, {address}, {}) {

}

Cell::Cell(const Definition &definition)
    : m_value(0), m_definition(definition) {

}

// Getters
double Cell::get_value() const {
    return m_value;
}

std::shared_ptr<Definition> Cell::get_definition() const {
    return std::make_shared<Definition>(m_definition);
}


// Setters
void Cell::set_value(const double value) {
    m_value = value;
}

void Cell::add_value(double value) {
    m_value += value;
}

void Cell::mul_value(double value) {
    m_value *= value;
}

void Cell::set_definition(const Definition &definition) {
    m_definition = definition;
}

// Utility

void Cell::print_value() const {
    std::cout << m_value << std::endl;
}

void Cell::print() const {
    std::cout << "Value : " << m_value << std::endl;
    m_definition.print();
}
