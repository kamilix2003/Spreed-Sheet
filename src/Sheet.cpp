
#include "Sheet.hpp"

#include <string>

Cell Sheet::get_cell(const std::string& key) {
    return m_cells[key];
}



void Sheet::add_cell(const std::string &key, Cell &cell) {
    cell.set_parent_sheet(this);
    m_cells[key] = cell;
}
