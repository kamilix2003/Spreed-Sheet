#include <map>
#include <memory>
#include "Cell.hpp"

class Sheet {
    private:
    std::map<std::string, Cell> m_cells;
    std::string m_sheet_input;

    public:
    // Constructors


    // Getters
    Cell get_cell(const std::string& key);

    // Setters
    void set_cell(const std::string& key, const Cell& cell);
    void set_sheet_input(const std::string& input);

    // Evaluation
    void evaluate_cell(const std::string& key);
    void evaluate_sheet();
    void process_sheet_input();

    // Utility
    bool cell_exist(const std::string& key);
    void print_cell(const std::string& key);
};