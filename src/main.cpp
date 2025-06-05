#include "cpu.hpp"
#include "memory.hpp"
#include <chrono>
#include <thread>
#include <iostream>
#include <cstdlib>
#include <iomanip>



int main() {
    while (true) {
        std::cout << "\033[2J\033[1;1H"; // Clear screen
        system("clear");
        CPU_Usage cpu;  // this prints both CPU and memory usage
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    return 0;
}

