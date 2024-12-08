#include <iostream>
#include <Sheet.hpp>

/*
    Test inputs:
        AA11 3.14
        AA12 AA11
        AA13 ADD AA11 AA12 3.14
        AA14 MUL AA13 0.5
*/


/*
    Example input: AB12 AA1 BB3 1.2 11
    First element - output cell
    Second element - operator
                    plain value
                    reference to cell
    Other elements - inputs
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
        try {
            sheet.set_sheet_input(user_input);
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            continue;
        }
        sheet.process_sheet_input();
        sheet.evaluate_sheet();
        sheet.print_sheet_values();
    }
}