
#include <string>
#include <vector>
#include "Definition.h"



class Sheet;

class Cell{
private:
    double m_value;
    Definition m_definition;
    Sheet* m_parent_sheet = nullptr;

public:
    // Constructors
    explicit Cell(double value = 0);

    // Getters
    double get_value() const;

    // Setters
    void set_value(double value);
    void set_definition(Definition definition);
    void set_parent_sheet(Sheet* sheet);

    // Evaluation
    void evaluate() const;
};
