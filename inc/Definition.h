
enum Functions{
    plain_value = 0,
    add,
    subtract,
    multiply,
    divide,
};

class Definition{
private:
    Functions m_func;
    std::vector<Address> rel_args;
    std::vector<double> const_args;
public:
    Definition();
};
