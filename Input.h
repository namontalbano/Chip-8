#include "SDL2/SDL.h"

class Input {

public:
    Input();
    ~Input();

    void reset();
    void poll();

    bool pause_;
    bool reset_;
    uint8_t key_[16];
};


