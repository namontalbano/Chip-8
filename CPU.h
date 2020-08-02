#include <cstdint>
#include <string>

#include "Audio.h"
#include "Display.h"
#include "Keyboard.h"
#include "ROM.h"

class CPU {

public:

    CPU();
    ~CPU();

    void cycle();
    void reset();
    void input();
    void output();
    bool load_memory();

    Audio& audio();
    Display& display();
    Keyboard& keyboard();
    ROM& rom();

protected:

    Display _display;

    uint16_t pc_;
    uint16_t op_code_;
    uint16_t  I_;
    uint16_t  sp_;
    uint16_t stack_[16];
    uint16_t delay_timer_;

    uint8_t V_[16];
    uint8_t* memory_;
    uint8_t* key_;
    uint8_t graphics_[64 * 32];
    uint8_t sound_timer_;

private:
    bool running_;
    Audio _audio;
    Keyboard _keyboard;
    ROM _rom;

    virtual void CLS_00E0();  virtual void RET_00EE();  virtual void SYS_0NNN(); virtual void JMP_1NNN();
    virtual void CALL_2NNN(); virtual void SE_3XKK();   virtual void SNE_4XKK(); virtual void SE_5XY0();
    virtual void LD_6XKK();   virtual void ADD_7XKK();  virtual void LD_8XY0();  virtual void OR_8XY1();
    virtual void AND_8XY2();  virtual void XOR_8XY3();  virtual void ADD_8XY4(); virtual void SUB_8XY5();
    virtual void SHR_8XY6();  virtual void SUBN_8XY7(); virtual void SHL_8XYE(); virtual void SNE_9XY0();
    virtual void LD_ANNN();   virtual void JP_BNNN();   virtual void RND_CXKK(); virtual void DRW_DXYN();
    virtual void SKP_EX9E();  virtual void SKNP_EXA1(); virtual void LD_FX07();  virtual void LD_FX0A();
    virtual void LD_FX15();   virtual void LD_FX18();   virtual void ADD_FX1E(); virtual void LD_FX29();
    virtual void LD_FX33();   virtual void LD_FX55();   virtual void LD_FX65();  virtual void INV();
};
