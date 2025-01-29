#pragma once

#include <iostream>
#include <memory>
#include <string>

class Cell{
private:
    double m_value;

public:
    // Constructors
    Cell();
    explicit Cell(double value);

    // Getters
    double get() const;

    // Setters
    void set(double value);

    // Operations
    void add(double rhs);
    void sub(double rhs);
    void mul(double rhs);
    void div(double rhs);
};
