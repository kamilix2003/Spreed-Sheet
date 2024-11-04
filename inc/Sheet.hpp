#include <iostream>
#include <memory>
#include "Cell.hpp"

class Sheet : Cell{
    private:
        const unsigned int m_rows;
        const unsigned int m_cols;
        std::shared_ptr<Cell> m_sheet;
        std::string input;
        
};