#include <map>
#include <memory>
#include "Cell.hpp"

class Sheet {
    private:
    std::map<std::string, Cell> m_cells;

    public:

    Cell get_cell(const std::string& key);
    void add_cell(const std::string& key, Cell& cell);

    void evaluate_cell(const std::string& key);
};