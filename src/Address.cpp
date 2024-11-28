#include "../inc/Address.hpp"

Address::Address(unsigned int c, unsigned int r) : m_col(c), m_row(r)
{
}

Address::Address(std::string c, unsigned int r) : m_row(r), m_col_str(c)
{
    m_col = 0;
    for(char i : c) {
        m_col += (unsigned int)(i - 'A');
    }
}

unsigned int Address::get_row() const {
    return m_row;
}

unsigned int Address::get_col() const {
    return m_col;
}

std::string Address::get_col_string() {
    return m_col_str;
}
