
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


// Setters
void Cell::set_parent_sheet(Sheet* sheet) {
    m_parent_sheet = sheet;
}

void Cell::set_definition(Definition definition) {
    m_definition = std::move(definition);
}


void Cell::set_value(const double value) {
    m_value = value;
}


// Evaluation
void Cell::evaluate() const {
    switch (m_definition.get_operation()) {
        case none:
            break;
        case add:
            for (auto constant : *m_definition.get_const_vec()) {
                std::cout << constant << "\n";
            }
            break;
        case mul:
            break;
        default:
            break;
    }
}

