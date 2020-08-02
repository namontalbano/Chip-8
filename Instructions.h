#include "CPU.h"

class Instructions: protected CPU {

private:

    void CLS_00E0();  void RET_00EE(); void SYS_0NNN();  void JMP_1NNN(); void CALL_2NNN();
    void SE_3XKK();   void SNE_4XKK(); void SE_5XY0();   void LD_6XKK();  void ADD_7XKK();
    void LD_8XY0();   void OR_8XY1();  void AND_8XY2();  void XOR_8XY3(); void ADD_8XY4();
    void SUB_8XY5();  void SHR_8XY6(); void SUBN_8XY7(); void SHL_8XYE(); void SNE_9XY0();
    void LD_ANNN();   void JP_BNNN();  void RND_CXKK();  void DRW_DXYN(); void SKP_EX9E();
    void SKNP_EXA1(); void LD_FX07();  void LD_FX0A();   void LD_FX15();  void LD_FX18();
    void ADD_FX1E();  void LD_FX29();  void LD_FX33();   void LD_FX55();  void LD_FX65();
    void INV();
};

