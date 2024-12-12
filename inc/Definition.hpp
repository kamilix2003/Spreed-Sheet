#include <memory>
#include <vector>
#include <array>
#include <string>

#define OP_COUNT 7

enum Operation {
    NONE = 0,
    ADD,
    SUB,
    MUL,
    DIV,
    SUM,
    PROD,
};

class Definition {
private:
    Operation m_op = NONE;
    std::vector<std::string> m_args{};
    std::vector<double> m_consts{};

public:
    // Constructors
    Definition(Operation op, const std::vector<std::string>& args, const std::vector<double>& consts);
    Definition(const Definition& definition);

    // Getters
    Operation get_operation() const;
    std::shared_ptr<std::vector<std::string>> get_args_vec() const;
    std::shared_ptr<std::vector<double>> get_const_vec() const;
    std::string get_first_arg() const;
    double get_first_const() const;

    // Setters
    void set_operation(Operation op);
    void set_args_vec(const std::vector<std::string> &args);
    void set_const_vec(const std::vector<double> &consts);

    // Arguments operations
    void append_args(const std::string& argument);
    void append_const(double constant);

    // Utility
    void print_const() const;
    void print() const;
};

