#include "Display.hpp"


int main() {
    try {
        Display display;
        display.loop();
    } catch(...) {
        return 0;
    }
}
