
#include <iostream>
#include <utility>
#include "Cell.hpp"

// Constructors
Cell::Cell(const double value) : m_value(value), m_definition(none) {

}

// Getters
double Cell::get_value() const {
    return m_value;
}

std::shared_ptr<Definition> Cell::get_definition() const {
    return std::make_shared<Definition>(m_definition);
}


// Setters

