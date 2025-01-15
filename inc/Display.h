#pragma once
#include <Sheet.hpp>
#include <algorithm>

class Display {
private:
    Sheet current_sheet;
    std::string user_input;
    std::string sheet_path;

public:
    Display();

    static void print_instructions();

    void loop();
    static void clear_screen();
    static void move_vertical(int rows);
    static void move_horizontal(int cols);
    static void screen_home();
    static void save_cursor();
    static void load_cursor();
    static void bell();
    static void print_error(const std::string& error);
};
