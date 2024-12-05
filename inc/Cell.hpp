
#include <map>
#include <string>
#include <vector>
#include "Definition.hpp"

class Sheet;

class Cell{
private:
    double m_value;
    Definition m_definition;

public:
    // Constructors
    explicit Cell(double value = 0);

    // Getters
    double get_value() const;
    std::shared_ptr<Definition> get_definition() const;

    // Setters
    void set_value(double value);
    void set_definition(Definition definition);

};
