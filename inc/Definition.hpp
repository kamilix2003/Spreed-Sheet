#include <memory>
#include <vector>
#include <array>
#include <string>

#define OP_COUNT 3

enum Operation {
    none = 0,
    add = 1,
    mul = 2,
};

class Definition {
private:
    Operation m_op = none;
    std::vector<std::string> m_args{};
    std::vector<double> m_consts{};

public:
    // Constructors
    explicit Definition(Operation op);
    Definition(Operation op, const std::vector<std::string>& args, const std::vector<double>& consts);
    Definition(const Definition& definition);

    // Getters
    Operation get_operation() const;
    std::shared_ptr<std::vector<std::string>> get_args_vec() const;
    std::shared_ptr<std::vector<double>> get_const_vec() const;

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

