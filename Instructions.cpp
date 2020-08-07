#include "Instructions.h"

void CPU::CLS_00E0() {
    memset(_output->_graphics, 0, sizeof(_output->_graphics));
    _output->set_draw_flag(true);
    _pc += 2;
}

void CPU::RET_00EE() {
    --_sp;
    _pc = _stack[_sp];
    _pc += 2;
}

void CPU::SYS_0NNN() {

}

void CPU::JMP_1NNN() {
    _pc = _op_code & 0x0FFF;
}

void CPU::CALL_2NNN() {
    _stack[_sp] = _pc;
    ++_sp;
    _pc = _op_code & 0x0FFF;
}

void CPU::SE_3XKK() {
    if(_V[(_op_code & 0x0F00) >> 8] == (_op_code & 0x00FF))
        _pc += 4;
    else
        _pc += 2;
}

void CPU::SNE_4XKK() {
    if(_V[(_op_code & 0x0F00) >> 8] != (_op_code & 0x00FF))
        _pc += 4;
    else
        _pc += 2;
}

void CPU::SE_5XY0() {
    if(_V[(_op_code & 0x0F00) >> 8] == _V[(_op_code & 0x00F0) >> 4])
        _pc += 4;
    else
        _pc += 2;
}

void CPU::LD_6XKK() {
    _V[(_op_code & 0x0F00) >> 8] = _op_code & 0x00FF;
    _pc += 2;
}

void CPU::ADD_7XKK() {
    _V[(_op_code & 0x0F00) >> 8] += _op_code & 0x00FF;
    _pc += 2;
}

void CPU::LD_8XY0() {
    _V[(_op_code & 0x0F00) >> 8] = _V[(_op_code & 0x00F0) >> 4];
    _pc += 2;
}

void CPU::OR_8XY1() {
    _V[(_op_code & 0x0F00) >> 8] |= _V[(_op_code & 0x00F0) >> 4];
    _pc += 2;
}

void CPU::AND_8XY2() {
    _V[(_op_code & 0x0F00) >> 8] &= _V[(_op_code & 0x00F0) >> 4];
    _pc += 2;
}

void CPU::XOR_8XY3() {
    _V[(_op_code & 0x0F00) >> 8] ^= _V[(_op_code & 0x00F0) >> 4];
    _pc += 2;
}

void CPU::ADD_8XY4() {
    if(_V[(_op_code & 0x00F0) >> 4] > (0xFF - _V[(_op_code & 0x0F00) >> 8]))
        _V[0xF] = 1;
    else
        _V[0xF] = 0;
    _V[(_op_code & 0x0F00) >> 8] += _V[(_op_code & 0x00F0) >> 4];
    _pc += 2;
}

void CPU::SUB_8XY5() {
    if(_V[(_op_code & 0x00F0) >> 4] > _V[(_op_code & 0x0F00) >> 8])
        _V[0xF] = 0;
    else
        _V[0xF] = 1;
    _V[(_op_code & 0x0F00) >> 8] -= _V[(_op_code & 0x00F0) >> 4];
    _pc += 2;
}

void CPU::SHR_8XY6() {
    _V[0xF] = _V[(_op_code & 0x0F00) >> 8] & 0x1;
    _V[(_op_code & 0x0F00) >> 8] >>= 1;
    _pc += 2;}

void CPU::SUBN_8XY7() {
    if(_V[(_op_code & 0x0F00) >> 8] > _V[(_op_code & 0x00F0) >> 4])
        _V[0xF] = 0;
    else
        _V[0xF] = 1;
    _V[(_op_code & 0x0F00) >> 8] = _V[(_op_code & 0x00F0) >> 4] - _V[(_op_code & 0x0F00) >> 8];
    _pc += 2;
}

void CPU::SHL_8XYE() {
    _V[0xF] = _V[(_op_code & 0x0F00) >> 8] >> 7;
    _V[(_op_code & 0x0F00) >> 8] <<= 1;
    _pc += 2;
}

void CPU::SNE_9XY0() {
    if(_V[(_op_code & 0x0F00) >> 8] != _V[(_op_code & 0x00F0) >> 4])
        _pc += 4;
    else
        _pc += 2;
}

void CPU::LD_ANNN() {
    _I = _op_code & 0x0FFF;
    _pc += 2;
}

void CPU::JP_BNNN() {
    _pc = (_op_code & 0x0FFF) + _V[0];
}

void CPU::RND_CXKK() {
    _V[(_op_code & 0x0F00) >> 8] = (rand() % 0xFF) & (_op_code & 0x00FF);
    _pc += 2;
}

void CPU::DRW_DXYN() {
    unsigned short x = _V[(_op_code & 0x0F00) >> 8];
    unsigned short y = _V[(_op_code & 0x00F0) >> 4];
    unsigned short n = _op_code & 0x000F;
    unsigned short pixel;

    _V[0xF] = 0;
    for (int yline = 0; yline < n; yline++)
    {
        pixel = _rom->getMemory()[_I + yline];
        for(int xline = 0; xline < 8; xline++)
        {
            if((pixel & (0x80 >> xline)) != 0)
            {
                if(_output->_graphics[(x + xline + ((y + yline) * 64))] == 1)
                {
                    _V[0xF] = 1;
                }
                _output->_graphics[x + xline + ((y + yline) * 64)] ^= 1;
            }
        }
    }

    _output->set_draw_flag(true);
    _pc += 2;
}

void CPU::SKP_EX9E() {
    if(_input->key_[_V[(_op_code & 0x0F00) >> 8]] != 0)
        _pc += 4;
    else
        _pc += 2;
}

void CPU::SKNP_EXA1() {
    if(_input->key_[_V[(_op_code & 0x0F00) >> 8]] == 0)
        _pc += 4;
    else
        _pc += 2;
}

void CPU::LD_FX07() {
    _V[(_op_code & 0x0F00) >> 8] = _delay_timer;
    _pc += 2;
}

void CPU::LD_FX0A() {
    bool keyPress = false;

    for(int i = 0; i < 16; ++i)
    {
        if(_input->key_[i] != 0)
        {
            _V[(_op_code & 0x0F00) >> 8] = i;
            keyPress = true;
        }
    }

    if(!keyPress)
        return;
    _pc += 2;
}

void CPU::LD_FX15() {
    _delay_timer = _V[(_op_code & 0x0F00) >> 8];
    _pc += 2;
}

void CPU::LD_FX18() {
    _sound_timer = _V[(_op_code & 0x0F00) >> 8];
    _pc += 2;
}

void CPU::ADD_FX1E() {
    if(_I + _V[(_op_code & 0x0F00) >> 8] > 0xFFF)
        _V[0xF] = 1;
    else
        _V[0xF] = 0;
    _I += _V[(_op_code & 0x0F00) >> 8];
    _pc += 2;
}

void CPU::LD_FX29() {
    _I = _V[(_op_code & 0x0F00) >> 8] * 0x5;
    _pc += 2;
}

void CPU::LD_FX33() {
    _rom->getMemory()[_I]     = _V[(_op_code & 0x0F00) >> 8] / 100;
    _rom->getMemory()[_I + 1] = (_V[(_op_code & 0x0F00) >> 8] / 10) % 10;
    _rom->getMemory()[_I + 2] = (_V[(_op_code & 0x0F00) >> 8] % 100) % 10;
    _pc += 2;
}

void CPU::LD_FX55() {
    for (int i = 0; i <= ((_op_code & 0x0F00) >> 8); ++i)
        _rom->getMemory()[_I + i] = _V[i];

    _I += ((_op_code & 0x0F00) >> 8) + 1;
    _pc += 2;}

void CPU::LD_FX65() {

    for (int i = 0; i <= ((_op_code & 0x0F00) >> 8); ++i)
        _V[i] = _rom->getMemory()[_I + i];

    _I += ((_op_code & 0x0F00) >> 8) + 1;
    _pc += 2;
}

void CPU::INV() {
    printf("\nUnknown op code: %.4X\n", _op_code);
    exit(3);
}