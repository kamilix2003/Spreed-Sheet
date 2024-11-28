#include <string>

class Address{
    unsigned int m_col;
    unsigned int m_row;
    std::string m_col_str;

    public:
    Address(std::string c, unsigned int r);
    Address(unsigned int c, unsigned int r);
    unsigned int get_row() const;
    unsigned int get_col() const;
    std::string get_col_string();
};