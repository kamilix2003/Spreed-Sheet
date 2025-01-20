
#include "Display.h"

Display::Display() {
    greeting();
    clear_screen();
    set_cursor_home();
    while (true) {

        std::cout << "Enter sheet name: ";
        save_cursor();
        std::cout << "\nEnter only sheet name, not path"
                     "\nfile will appear in the same directory as executable";
        load_cursor();

        try {
            if (!std::getline(std::cin, sheet_name)) {
                throw std::invalid_argument("Invalid input");
            }

            if (sheet_name.empty()) {
                throw std::invalid_argument("Empty sheet name");
            }

            if (!verify_sheet_name(sheet_name)) {
                throw std::invalid_argument("Invalid sheet name, only alpha numerals allowed");
            }

            std::transform(sheet_name.begin(),
                sheet_name.end(),
                sheet_name.begin(),
              ::tolower);

            if (sheet_name == "exit") {
                throw std::exception();
            }

            current_sheet.load_from_file(sheet_name);

        } catch (std::out_of_range &e) {
            clear_screen();
            set_cursor_home();
            print_error(e.what());
            std::cout << "Creating new sheet: " << current_sheet.file_name_to_path(sheet_name);
            current_sheet.save_to_file(sheet_name);
            std::cout << "\npress enter to continue...";
            std::cin.get();
            break;
        } catch (std::invalid_argument &e) {
            clear_screen();
            set_cursor_home();
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
    set_cursor_home();

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
        set_cursor_home();

        try {
            current_sheet.sheet_input(user_input);
        } catch(std::exception& e) {
            bell();
            print_error(e.what());
        }
    }

    clear_screen();
    set_cursor_home();

    std::cout << "Save sheet? (Y/N)" << std::endl;
    std::cin >> user_input;
    std::transform(user_input.begin(),
                user_input.end(),
                user_input.begin(),
              ::toupper);
    if (user_input == "Y" || user_input == "y") {
        current_sheet.save_to_file(sheet_name);
    }
}

bool Display::verify_sheet_name(const std::string& input) {
    for (const char c : input) {
        if (!std::isalnum(c)) {
            return false;
        }
    }
    return true;
}
void Display::clear_screen() {
    std::cout << "\033[2J\r";
}

void Display::set_cursor_home() {
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

void Display::greeting() {
    std::cout << "Welcome to Spreed Sheet!\n"
                 "to exit application type exit in any command entry\n"
                 "commands are case-insensitive";
    std::cout << "\npress enter to continue...";
    std::cin.get();
}


