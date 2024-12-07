#include <iostream>
#include <Sheet.hpp>

/*
    Test inputs:
        AA11 3.14
        AA12 AA11
        AA13 ADD AA11 AA12 3.14
        AA14 MUL AA13 0.5
*/

int main() {
    std::string user_input;
    Sheet sheet;
    while (true) {
        std::cout << "Enter command: ";
        std::getline(std::cin, user_input);
        if (user_input == "exit" || user_input.empty()) {
            return 0;
        }
        sheet.set_sheet_input(user_input);
        sheet.process_sheet_input();
        sheet.print_sheet_values();

    }
}

/*int main(){

    Definition d1(Operation::add, {}, {});
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
    Cell c3(d3);
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

    s.set_sheet_input("AB12 MUL ADD 1.2 AA11 A1");
    s.process_sheet_input();

    // std::cout << (s.cell_exist("XX") ? "YES" : "NO") << std::endl;
    // std::cout << (s.cell_exist("A") ? "YES" : "NO") << std::endl;

    s.print_cell("AB12");
}*/
