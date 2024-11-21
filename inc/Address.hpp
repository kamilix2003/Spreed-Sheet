#include <string>

class Address{
    unsigned int m_col;
    unsigned int m_row;

    public:
    Address(std::string c, unsigned int r);
    Address(unsigned int c, unsigned int r);
    unsigned int get_row();
    unsigned int get_col();
    std::string get_col_string();
};