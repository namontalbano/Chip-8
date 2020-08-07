#include "CPU.h"

CPU::CPU(Input *input, Graphics *graphics, ROM *rom) :
_rom(rom), _input(input), _output(graphics)
{
    _rom->setFilePath("..//ROMS//CAVE");
    _output->init();
    CPU::reset();
}

void CPU::reset() {
    _input->reset();
    _rom->setReloaded(false);

    _pc = 0x200;
    _I = 0;
    _sp = 0;
    _op_code = 0;
    _sound_timer = 0;
    _delay_timer = 0;

    memset(_V, 0, sizeof(_V));
    memset(_stack, 0, sizeof(_stack));
    memset(_output->_graphics, 0, sizeof(_output->_graphics));

    _output->set_draw_flag(false);
}

void CPU::cycle() {
    _op_code = _rom->getMemory()[_pc] << 8 | _rom->getMemory()[_pc + 1];
    switch (_op_code & 0xF000) {
        case 0x0000:
            switch (_op_code & 0x000F) {
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
            switch (_op_code & 0x000F) {
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
            switch (_op_code & 0x00FF) {
                case 0x009E: SKP_EX9E(); break;
                case 0x00A1: SKNP_EXA1(); break;
                default: INV();
            }
            break;
        case 0xF000:
            switch (_op_code & 0x00FF) {
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

    if (_input->isReset())  CPU::reset();
    if (_rom->isReloaded()) CPU::reset();
    if (_delay_timer > 0) --_delay_timer;
    if (_sound_timer > 0) --_sound_timer;
}

