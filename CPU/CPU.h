#include <cstdint>
#include <string>
#include <chrono>
#include <thread>

#include "../IO/Audio.h"
#include "../IO/Graphics.h"
#include "../IO/Input.h"
#include "../Memory/ROM.h"

class CPU {

public:

    CPU(Input *input, Graphics *graphics, ROM *rom);

    void cycle();
    void reset();

    bool isRunning() { return _running; };

protected:

    uint16_t _pc;
    uint16_t _op_code;
    uint16_t _I;
    uint16_t _sp;
    uint16_t _stack[16];
    uint16_t _delay_timer;

    uint8_t _V[16];
    uint8_t _sound_timer;

private:
    ROM *_rom;
    Input *_input;
    Graphics *_output;

    bool _paused = false;
    bool _running = true;

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
