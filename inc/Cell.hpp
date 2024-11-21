#include <vector>
#include <tuple>
#include <memory>
#include "Address.hpp"

enum Functions{
    plain_value = 0,
    add,
    subtract,
    multiply,
    divide,    
};

class Definition{
    private:
        Functions m_func;
        std::vector<Address> rel_args;
        std::vector<double> const_args;

};

class Cell{
    private:
        double m_value;
        Definition m_def;
        unsigned int m_age;
};