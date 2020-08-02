#include "CPU.h"

CPU::CPU() {
    _rom.set_file_path("..//ROMS//BRIX");
    reset();
}

 CPU::~CPU() {}

void CPU::reset() {
    _display.init();
    _keyboard.init();

    pc_ = 0x200;
    I_ = 0;
    sp_ = 0;
    op_code_ = 0;
    sound_timer_ = 0;
    delay_timer_ = 0;

    memset(V_, 0, sizeof(V_));
    memset(stack_, 0, sizeof(stack_));
    memset(graphics_, 0, sizeof(graphics_));


    CPU::load_memory();
    _display.set_draw_flag(false);
}

bool CPU::load_memory(){
    memory_ = _rom.load();
    return memory_ != nullptr;
}


void CPU::input() {
    key_ = _keyboard.poll();

    if (_keyboard.reset) {
        reset();
    }
}

void CPU::output() {
    _display.draw(graphics_);
}

Display& CPU::display() {
    return _display;
}

Keyboard& CPU::keyboard() {
    return _keyboard;
}

ROM& CPU::rom() {
    return _rom;
}

Audio& CPU::audio() {
    return _audio;
}

void CPU::cycle() {

    op_code_ = memory_[pc_] << 8 | memory_[pc_ + 1];

    switch (op_code_ & 0xF000) {

        case 0x0000:
            switch (op_code_ & 0x000F) {
                case 0x0000: CLS_00E0(); break;
                case 0x000E: RET_00EE(); break;
                default: INV();
            }
            break;
        case 0x1000: JMP_1NNN(); break;
        case 0x2000: CALL_2NNN(); break;
        case 0x3000: SE_3XKK(); break;
        case 0x4000: SNE_4XKK(); break;
        case 0x5000: SE_5XY0(); break;
        case 0x6000: LD_6XKK(); break;
        case 0x7000: ADD_7XKK(); break;
        case 0x8000:
            switch (op_code_ & 0x000F) {
                case 0x0000: LD_8XY0(); break;
                case 0x0001: OR_8XY1(); break;
                case 0x0002: AND_8XY2(); break;
                case 0x0003: XOR_8XY3(); break;
                case 0x0004: ADD_8XY4(); break;
                case 0x0005: SUB_8XY5(); break;
                case 0x0006: SHR_8XY6(); break;
                case 0x0007: SUBN_8XY7(); break;
                case 0x000E: SHL_8XYE(); break;
                default: INV();
            }
            break;
        case 0x9000: SNE_9XY0(); break;
        case 0xA000: LD_ANNN(); break;
        case 0xB000: JP_BNNN(); break;
        case 0xC000: RND_CXKK(); break;
        case 0xD000: DRW_DXYN(); break;
        case 0xE000:
            switch (op_code_ & 0x00FF) {
                case 0x009E: SKP_EX9E(); break;
                case 0x00A1: SKNP_EXA1(); break;
                default: INV();
            }
            break;
        case 0xF000:
            switch (op_code_ & 0x00FF) {
                case 0x0007: LD_FX07(); break;
                case 0x000A: LD_FX0A(); break;
                case 0x0015: LD_FX15(); break;
                case 0x0018: LD_FX18(); break;
                case 0x001E: ADD_FX1E(); break;
                case 0x0029: LD_FX29(); break;
                case 0x0033: LD_FX33(); break;
                case 0x0055: LD_FX55(); break;
                case 0x0065: LD_FX65(); break;
                default: INV();
            }
            break;
        default: INV();
    }

    if (delay_timer_ > 0)
        --delay_timer_;

    if (sound_timer_ > 0)
        --sound_timer_;

}