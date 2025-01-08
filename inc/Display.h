
#include <iostream>
#include <Sheet.hpp>

class Display {
private:
    Sheet current_sheet;
    std::string user_input;
    std::string sheet_path;
    bool stop_loop = false;

public:
    Display() {
        std::cout << "Enter sheet path: ";
        std::cin >> sheet_path;
        try {
            current_sheet.load_from_file(sheet_path);
        } catch (...) {
            std::cout << "Creating new sheet: " << sheet_path << std::endl;
            current_sheet.save_to_file(sheet_path);
        }
    }
    void loop() {
        bool clear = true;
        while (!stop_loop) {
            std::cout << "Enter command: ";
            std::cin >> user_input;
            if (user_input == "exit" || user_input.empty()) {
                stop_loop = true;
            }
            try {
                current_sheet.set_sheet_input(user_input);
                current_sheet.process_sheet_input();
            } catch(std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }
        std::cout << "Save sheet? (Y/N)" << std::endl;
        std::cin >> user_input;
        if (user_input == "Y" || user_input == "y") {
            current_sheet.save_to_file(sheet_path);
        }
    }
    void clear_screen() {
        std::cout << "\033[2J";
    }
    void move_down(int rows) {
        std::cout << "\033["<<rows<<"H";
    }
};
