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



}
