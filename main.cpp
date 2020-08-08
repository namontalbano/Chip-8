#include "CPU/CPU.h"
#include "Window.h"


int main(int argc, char* argv[]) {

//    Window window = Window(1024, 512, "Test");
//    window.init();
//
//    while (true) {
//        window.draw();
//        window.render();
//
//    }

    Input input = Input();
    Graphics graphics = Graphics();
    ROM rom = ROM();
    CPU cpu = CPU(&input, &graphics, &rom);

    while (cpu.isRunning()) {
        input.poll();
        if (!input.isPaused()) {
            cpu.cycle();
        }
        graphics.draw();
        std::this_thread::sleep_for(std::chrono::microseconds(2666));
    }
}


