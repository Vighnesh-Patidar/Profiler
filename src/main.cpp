#include "cpu.hpp"
#include <chrono>
#include <thread>
#include <iostream>
#include <cstdlib>

void clear_screen() {
    // ANSI escape codes to clear screen and move cursor to top-left
    std::cout << "\033[2J\033[1;1H";
}

int main() {
    while (true) {
        system("clear");
        
        std::cout << "------------------------------------------ CPU Statistics -------------------------------------------\n";
        std::cout << "Process Name            |           Process_ID               |             CPU_Usage\n";
        CPU_Usage cpu;
        clear_screen();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}
