#include "Cell.hpp"

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

// Setters
void Cell::set(const double rhs) {
    m_value = rhs;
}

// Operations
void Cell::add(double rhs) {
    m_value += rhs;
}
void Cell::sub(double rhs) {
    m_value -= rhs;
}
void Cell::mul(double rhs) {
    m_value *= rhs;
}
void Cell::div(double rhs) {
    if (rhs == 0) {
        throw std::invalid_argument("Division by zero");
    }
    m_value /= rhs;
}
