#include <vector>
#include <tuple>
#include <memory>

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
         * @brief Function describing the cell
         * 
         */
        Funcs m_function;
        /**
         * @brief Arguments 
         * 
         */
        std::vector<std::tuple<int, int>> arguments;
    public:
        Cell();

        void set_value(double val);
        void set_function(Funcs func);
        void set_arguments(std::vector<std::tuple<int, int>> args);

        double get_value();
        Funcs get_function();
        std::shared_ptr<std::vector<std::tuple<int, int>>> get_arguments();
};