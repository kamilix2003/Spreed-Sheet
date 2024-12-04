#include <iostream>
#include <Sheet.hpp>

int main(){

    Definition d1(Operation::add);
    d1.append_const(1.5);
    d1.append_const(3.14);
    d1.append_args("B");
    d1.append_args("C");

    Cell c1(1);
    Cell c2(2);
    Cell c3(3);

    Sheet s;
    s.add_cell("A", c1);
    s.add_cell("B", c2);
    s.add_cell("C", c3);

    c1.set_definition(d1);
    c1.evaluate();
    std::cout<<s.get_cell("A").get_value()<<std::endl;

}
