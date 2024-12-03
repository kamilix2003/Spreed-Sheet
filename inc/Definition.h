#include <memory>
#include <vector>
#include <string>

enum Operation {
    none = 0,
    add = 1,
    mul = 2,
};

class Definition {
private:
    Operation m_op;
    std::vector<std::string> m_args{};
    std::vector<double> m_const{};

public:
    // Constructors
    explicit Definition(Operation op);

    // Getters
    Operation get_operation() const;
    std::shared_ptr<std::vector<std::string>> get_args_vec() const;
    std::shared_ptr<std::vector<double>> get_const_vec() const;

    // Setters

    // Arguments operations
    void append_args(const std::string& argument);
    void append_const(double constant);

    // Utility
    void print_const() const;
    void print() const;
};