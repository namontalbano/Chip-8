#include <chrono>
#include <thread>
#include "CPU.h"

int main(int argc, char* argv[]) {
    CPU cpu = CPU();


    while (true) {
        cpu.cycle();
        cpu.input();
        cpu.output();
        std::this_thread::sleep_for(std::chrono::microseconds(1666));
    }
}
