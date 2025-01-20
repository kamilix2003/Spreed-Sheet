#pragma once
#include <Sheet.hpp>
#include <algorithm>

class Display {
private:
    Sheet current_sheet;
    std::string user_input;
    std::string sheet_name;

public:
    Display();

    void loop();

    static bool verify_sheet_name(const std::string& input);
    static void print_error(const std::string& error);

    static void greeting();
    static void print_instructions();

    // Terminal escape codes wrappers
    static void clear_screen();
    static void set_cursor_home();
    static void save_cursor();
    static void load_cursor();
    static void bell();
};
