#include <map>
#include <memory>
#include "Cell.hpp"

class Sheet {
    private:
    std::map<std::string, Cell> m_cells;

    public:
    // Constructors


    // Getters
    Cell get_cell(const std::string& key);

    // Setters
    void set_cell(const std::string& key, const Cell& cell);

    // Evaluation
    void evaluate_cell(const std::string& key);

    // Utility
    void print_cell(const std::string& key);
};