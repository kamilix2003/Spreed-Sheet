
#include "Sheet.hpp"

#include <string>

Cell Sheet::get_cell(const std::string& key) {
    return m_cells[key];
}

void Sheet::add_cell(const std::string &key, Cell &cell) {
    cell.set_map_ptr(std::make_shared<std::map<std::string, Cell>>(m_cells));
    m_cells[key] = cell;
}
