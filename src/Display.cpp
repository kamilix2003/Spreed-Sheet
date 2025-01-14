
#include "Display.h"

#include <algorithm>

Display::Display() {
    while (true) {
        std::cout << "Enter sheet path: ";

        try {
            if (!std::getline(std::cin, sheet_path)) {
                throw std::invalid_argument("Invalid input");
            }

            if (sheet_path.empty()) {
                throw std::invalid_argument("Empty sheet path");
            }

            std::transform(sheet_path.begin(),
                sheet_path.end(),
                sheet_path.begin(),
              ::toupper);
            if (sheet_path == "EXIT") {
                throw std::exception();
            }

            current_sheet.load_from_file(sheet_path);

        } catch (std::out_of_range &e) {
            clear_screen();
            screen_home();
            print_error(e.what());
            continue;
        } catch (std::invalid_argument &e) {
            clear_screen();
            screen_home();
            print_error(e.what());
            continue;
        }
        break;
    }
}

void Display::print_instructions() {
    save_cursor();
    std::cout << "\nCommand sequence -> Address Operator arg0 ... argN";
    std::cout << "\nAvailable operators -> SET, ADD, SUB, MUL, DIV";
    std::cout << "\nType Exit to close the sheet";
    load_cursor();
}

void Display::loop() {
    clear_screen();
    screen_home();
    while (true) {
        current_sheet.print_sheet_values();
        std::cout << "Enter command: ";

        print_instructions();

        if (!std::getline(std::cin, user_input)) {
            throw std::invalid_argument("Invalid input");
        }

        std::transform(user_input.begin(),
                user_input.end(),
                user_input.begin(),
              ::toupper);
        if (user_input == "EXIT") {
            break;
        }

        clear_screen();
        screen_home();

        try {
            current_sheet.sheet_input(user_input);
        } catch(std::exception& e) {
            bell();
            print_error(e.what());
        }

    }

    clear_screen();
    screen_home();

    std::cout << "Save sheet? (Y/N)" << std::endl;
    std::cin >> user_input;
    std::transform(user_input.begin(),
                user_input.end(),
                user_input.begin(),
              ::toupper);
    if (user_input == "Y" || user_input == "y") {
        current_sheet.save_to_file(sheet_path);
    }
}
void Display::clear_screen() {
    std::cout << "\033[2J\r";
}

void Display::move_vertical(const int rows) {
    if (rows > 0) {
        std::cout << "\033["<<rows<<"A";
    }
    else {
        std::cout << "\033["<<rows<<"B";
    }
}

void Display::move_horizontal(int cols) {
    if (cols > 0) {
        std::cout << "\033["<<cols<<"C";
    }
    else {
        std::cout << "\033["<<cols<<"D";
    }
}

void Display::screen_home() {
    std::cout << "\033[H";
}

void Display::save_cursor() {
    std::cout << "\033[s";
}

void Display::load_cursor() {
    std::cout << "\033[u";
}

void Display::bell() {
    std::cout << "\a";
}

void Display::print_error(const std::string& error) {
    std::cout << "\033[1;31m" << error << "\033[0m\n";
}


