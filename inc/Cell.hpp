#include <vector>
#include <tuple>

enum Funcs{
    plain_value = 0,
    add,
    subtract,
    multiply,
    divide,    
};

class Cell{
    private:
        /**
         * @brief Calcualted or stored numeric value
         * 
         */
        double m_value;
        /**
         * @brief Function describing value of the cell
         * 
         */
        Funcs m_function;
        /**
         * @brief Arguments 
         * 
         */
        std::vector<std::tuple<int, int>> arguments;
};