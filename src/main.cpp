#include <iostream>
#include <Sheet.hpp>

int main(){

    Definition d1(Operation::add);
    d1.set_args_vec({"A", "B"});
    d1.set_const_vec({2, 1});
    d1.append_const(3.14);
    d1.append_args("C");
    // d1.print();

    Definition d2(d1);

    Definition d3(mul, {"A", "B"}, {3.14, 3});


    Cell c1(1);
    // c1.print();
    Cell c2(1);
    c2.set_definition(d1);
    // c2.print();
    Cell c3(2, d3);
    // c3.print();

    Sheet s;
    s.set_cell("A", c1);
    s.set_cell("B", c2);
    s.set_cell("C", c3);

    s.evaluate_cell("A");
    s.evaluate_cell("B");
    s.evaluate_cell("C");

    s.print_cell("A");
    s.print_cell("B");
    s.print_cell("C");

}
