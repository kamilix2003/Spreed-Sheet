
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
    Cell();
    explicit Cell(double value);
    explicit Cell(const std::string& address);
    explicit Cell(const Definition& definition);

    // Getters
    double get_value() const;
    std::shared_ptr<Definition> get_definition() const;

    // Setters
    void set_value(double value);
    void add_value(double value);
    void mul_value(double value);
    void set_definition(const Definition& definition);

    // Utility
    void print_value() const;
    void print() const;

};
