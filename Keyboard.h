#include "SDL2/SDL.h"

class Keyboard {

public:

    Keyboard();
    ~Keyboard();
    void init();
     u_int8_t* poll();
     u_int8_t key[16];
     bool reset;
     bool pause;
};


