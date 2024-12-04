
#include <map>
#include <string>
#include <vector>
#include "Definition.hpp"

class Sheet;

class Cell{
private:
    double m_value;
    Definition m_definition;
    std::shared_ptr<std::map<std::string, Cell>> m_sheet_map;

public:
    // Constructors
    explicit Cell(double value = 0);

    // Getters
    double get_value() const;

    // Setters
    void set_value(double value);
    void set_definition(Definition definition);
    void set_map_ptr(const std::shared_ptr<std::map<std::string, Cell>>& map_ptr);

    // Evaluation
    void evaluate();

};
