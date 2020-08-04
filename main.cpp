#include "CPU.h"

int main(int argc, char* argv[]) {

    Input input = Input();
    Graphics graphics = Graphics();
    ROM rom = ROM();

    CPU cpu = CPU(&input, &graphics, &rom);

    while (cpu.running_) {
        input.poll();
        if (!input.pause_) {
            cpu.cycle();
        }
        std::this_thread::sleep_for(std::chrono::microseconds(2666));
    }
}
