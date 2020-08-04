#include "Instructions.h"

void CPU::CLS_00E0() {
    memset(output->graphics_, 0, sizeof(output->graphics_));
    output->set_draw_flag(true);
    pc_ += 2;
}

void CPU::RET_00EE() {
    --sp_;
    pc_ = stack_[sp_];
    pc_ += 2;
}

void CPU::SYS_0NNN() {

}

void CPU::JMP_1NNN() {
    pc_ = op_code_ & 0x0FFF;
}

void CPU::CALL_2NNN() {
    stack_[sp_] = pc_;
    ++sp_;
    pc_ = op_code_ & 0x0FFF;
}

void CPU::SE_3XKK() {
    if(V_[(op_code_ & 0x0F00) >> 8] == (op_code_ & 0x00FF))
        pc_ += 4;
    else
        pc_ += 2;
}

void CPU::SNE_4XKK() {
    if(V_[(op_code_ & 0x0F00) >> 8] != (op_code_ & 0x00FF))
        pc_ += 4;
    else
        pc_ += 2;
}

void CPU::SE_5XY0() {
    if(V_[(op_code_ & 0x0F00) >> 8] == V_[(op_code_ & 0x00F0) >> 4])
        pc_ += 4;
    else
        pc_ += 2;
}

void CPU::LD_6XKK() {
    V_[(op_code_ & 0x0F00) >> 8] = op_code_ & 0x00FF;
    pc_ += 2;
}

void CPU::ADD_7XKK() {
    V_[(op_code_ & 0x0F00) >> 8] += op_code_ & 0x00FF;
    pc_ += 2;
}

void CPU::LD_8XY0() {
    V_[(op_code_ & 0x0F00) >> 8] = V_[(op_code_ & 0x00F0) >> 4];
    pc_ += 2;
}

void CPU::OR_8XY1() {
    V_[(op_code_ & 0x0F00) >> 8] |= V_[(op_code_ & 0x00F0) >> 4];
    pc_ += 2;
}

void CPU::AND_8XY2() {
    V_[(op_code_ & 0x0F00) >> 8] &= V_[(op_code_ & 0x00F0) >> 4];
    pc_ += 2;
}

void CPU::XOR_8XY3() {
    V_[(op_code_ & 0x0F00) >> 8] ^= V_[(op_code_ & 0x00F0) >> 4];
    pc_ += 2;
}

void CPU::ADD_8XY4() {
    if(V_[(op_code_ & 0x00F0) >> 4] > (0xFF - V_[(op_code_ & 0x0F00) >> 8]))
        V_[0xF] = 1;
    else
        V_[0xF] = 0;
    V_[(op_code_ & 0x0F00) >> 8] += V_[(op_code_ & 0x00F0) >> 4];
    pc_ += 2;
}

void CPU::SUB_8XY5() {
    if(V_[(op_code_ & 0x00F0) >> 4] > V_[(op_code_ & 0x0F00) >> 8])
        V_[0xF] = 0;
    else
        V_[0xF] = 1;
    V_[(op_code_ & 0x0F00) >> 8] -= V_[(op_code_ & 0x00F0) >> 4];
    pc_ += 2;
}

void CPU::SHR_8XY6() {
    V_[0xF] = V_[(op_code_ & 0x0F00) >> 8] & 0x1;
    V_[(op_code_ & 0x0F00) >> 8] >>= 1;
    pc_ += 2;}

void CPU::SUBN_8XY7() {
    if(V_[(op_code_ & 0x0F00) >> 8] > V_[(op_code_ & 0x00F0) >> 4])
        V_[0xF] = 0;
    else
        V_[0xF] = 1;
    V_[(op_code_ & 0x0F00) >> 8] = V_[(op_code_ & 0x00F0) >> 4] - V_[(op_code_ & 0x0F00) >> 8];
    pc_ += 2;
}

void CPU::SHL_8XYE() {
    V_[0xF] = V_[(op_code_ & 0x0F00) >> 8] >> 7;
    V_[(op_code_ & 0x0F00) >> 8] <<= 1;
    pc_ += 2;
}

void CPU::SNE_9XY0() {
    if(V_[(op_code_ & 0x0F00) >> 8] != V_[(op_code_ & 0x00F0) >> 4])
        pc_ += 4;
    else
        pc_ += 2;
}

void CPU::LD_ANNN() {
    I_ = op_code_ & 0x0FFF;
    pc_ += 2;
}

void CPU::JP_BNNN() {
    pc_ = (op_code_ & 0x0FFF) + V_[0];
}

void CPU::RND_CXKK() {
    V_[(op_code_ & 0x0F00) >> 8] = (rand() % 0xFF) & (op_code_ & 0x00FF);
    pc_ += 2;
}

void CPU::DRW_DXYN() {
    unsigned short x = V_[(op_code_ & 0x0F00) >> 8];
    unsigned short y = V_[(op_code_ & 0x00F0) >> 4];
    unsigned short n = op_code_ & 0x000F;
    unsigned short pixel;

    V_[0xF] = 0;
    for (int yline = 0; yline < n; yline++)
    {
        pixel = rom->memory_[I_ + yline];
        for(int xline = 0; xline < 8; xline++)
        {
            if((pixel & (0x80 >> xline)) != 0)
            {
                if(output->graphics_[(x + xline + ((y + yline) * 64))] == 1)
                {
                    V_[0xF] = 1;
                }
                output->graphics_[x + xline + ((y + yline) * 64)] ^= 1;
            }
        }
    }

    output->set_draw_flag(true);
    output->draw();
    pc_ += 2;
}

void CPU::SKP_EX9E() {
    if(input->key_[V_[(op_code_ & 0x0F00) >> 8]] != 0)
        pc_ += 4;
    else
        pc_ += 2;
}

void CPU::SKNP_EXA1() {
    if(input->key_[V_[(op_code_ & 0x0F00) >> 8]] == 0)
        pc_ += 4;
    else
        pc_ += 2;
}

void CPU::LD_FX07() {
    V_[(op_code_ & 0x0F00) >> 8] = delay_timer_;
    pc_ += 2;
}

void CPU::LD_FX0A() {
    bool keyPress = false;

    for(int i = 0; i < 16; ++i)
    {
        if(input->key_[i] != 0)
        {
            V_[(op_code_ & 0x0F00) >> 8] = i;
            keyPress = true;
        }
    }

    if(!keyPress)
        return;
    pc_ += 2;
}

void CPU::LD_FX15() {
    delay_timer_ = V_[(op_code_ & 0x0F00) >> 8];
    pc_ += 2;
}

void CPU::LD_FX18() {
    sound_timer_ = V_[(op_code_ & 0x0F00) >> 8];
    pc_ += 2;
}

void CPU::ADD_FX1E() {
    if(I_ + V_[(op_code_ & 0x0F00) >> 8] > 0xFFF)
        V_[0xF] = 1;
    else
        V_[0xF] = 0;
    I_ += V_[(op_code_ & 0x0F00) >> 8];
    pc_ += 2;
}

void CPU::LD_FX29() {
    I_ = V_[(op_code_ & 0x0F00) >> 8] * 0x5;
    pc_ += 2;
}

void CPU::LD_FX33() {
    rom->memory_[I_]     = V_[(op_code_ & 0x0F00) >> 8] / 100;
    rom->memory_[I_ + 1] = (V_[(op_code_ & 0x0F00) >> 8] / 10) % 10;
    rom->memory_[I_ + 2] = (V_[(op_code_ & 0x0F00) >> 8] % 100) % 10;
    pc_ += 2;
}

void CPU::LD_FX55() {
    for (int i = 0; i <= ((op_code_ & 0x0F00) >> 8); ++i)
        rom->memory_[I_ + i] = V_[i];

    I_ += ((op_code_ & 0x0F00) >> 8) + 1;
    pc_ += 2;}

void CPU::LD_FX65() {

    for (int i = 0; i <= ((op_code_ & 0x0F00) >> 8); ++i)
        V_[i] = rom->memory_[I_ + i];

    I_ += ((op_code_ & 0x0F00) >> 8) + 1;
    pc_ += 2;
}

void CPU::INV() {
    printf("\nUnknown op code: %.4X\n", op_code_);
    exit(3);
}