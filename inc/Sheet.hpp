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

    // File I/O
    void save_to_file();
    void load_from_file();
    void save_to_bin();
    void load_from_bin();

    // Evaluation
    void evaluate_cell(const std::string& key);
    void evaluate_sheet();
    void process_sheet_input();

    // Utility
    bool cell_exist(const std::string& key);
    void print_cell(const std::string& key);
    void print_cell_value(const std::string& key);
    void print_sheet() const;
    void print_sheet_values() const;
};