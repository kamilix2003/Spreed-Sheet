#include <iostream>
#include "../inc/Address.hpp"

int main(){
    Address add1(3, 5);
    Address add2("AA", 5);

    std::cout << "add1: " << add1.get_col() << ", " << add1.get_row() << "\n";
    std::cout << "add2: " << add2.get_col() << ", " << add2.get_row() << "\n";
}