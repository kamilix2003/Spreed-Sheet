
#include <iostream>
#include <utility>
#include "Cell.hpp"

#include <memory>

// Constructors
Cell::Cell()
    : m_value(0){

}

Cell::Cell(const double value)
    : m_value(value) {

}


// Getters
double Cell::get() const {
    return m_value;
}

std::unique_ptr<double> Cell::get_ptr() const {
    return std::make_unique<double>(m_value);
}

// Setters
void Cell::set(const double rhs) {
    m_value = rhs;
}

// Operations
void Cell::add(double rhs) {
    m_value += rhs;
}
void Cell::add(double rhs, double lhs) {
    m_value = rhs + lhs;
}
void Cell::sub(double rhs) {
    m_value -= rhs;
}
void Cell::sub(double rhs, double lhs) {
    m_value = rhs - lhs;
}
void Cell::mul(double rhs) {
    m_value *= rhs;
}
void Cell::mul(double rhs, double lhs) {
    m_value = rhs * lhs;
}
void Cell::div(double rhs) {
    m_value /= rhs;
}
void Cell::div(double lhs, double rhs) {
    m_value = lhs / rhs;
}

// Utility

void Cell::print() const {
    std::cout << "Value : " << m_value << std::endl;
}
