#include <vector>
#include <tuple>
#include <memory>
#include "Address.hpp"
#include "Definition.h"

class Cell{
    private:
        double m_value;
        Definition m_def;
        unsigned int m_age;

    public:
        Cell(double value, Definition def);
};