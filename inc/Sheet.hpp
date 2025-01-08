#include <map>
#include <memory>

#include "Cell.hpp"

const unsigned int OP_COUNT = 7;

enum Operation {
    SET = 0,
    ADD,
    SUB,
    MUL,
    DIV,
    SUM,
    PROD,
};

class Sheet {
    private:
    std::map<std::string, Cell> m_cells;
    std::string m_sheet_input;

    public:
    // Constructors


    // Getters
    std::shared_ptr<Cell> get_cell(const std::string& key);
    double get_value(const std::string& key);
    std::unique_ptr<double> get_value_ptr(const std::string& key);

    // Setters
    void set_cell(const std::string& key, const Cell& cell);
    void set_cell(const std::string& key, double value);
    void set_cell(const std::string& key, const std::string& key_ref);
    void set_sheet_input(const std::string& input);

    // File I/O
    void save_to_file(const std::string& file_name);
    void load_from_file(const std::string& file_name);

    // Evaluation
    void process_sheet_input();

    // Utility
    bool cell_exist(const std::string& key);
    void print_cell(const std::string& key);
    void print_cell_value(const std::string& key);
    void print_sheet() const;
    void print_sheet_values() const;
};