
#include <map>
#include <memory>
#include <string>
#include <vector>


class Cell{
private:
    double m_value;

public:
    // Constructors
    Cell();
    explicit Cell(double value);
    explicit Cell(std::string key);

    // Getters
    double get() const;
    std::unique_ptr<double> get_ptr() const;

    // Setters
    void set(double value);
    void set(std::string key);

    // Operations
    void add(double rhs);
    void add(double lhs, double rhs);

    void sub(double rhs);
    void sub(double lhs, double rhs);

    void mul(double rhs);
    void mul(double lhs, double rhs);

    void div(double rhs);
    void div(double lhs, double rhs);

    // Utility
    void print() const;
};
