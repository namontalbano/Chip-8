#include "SDL2/SDL.h"

class Input {

public:
    void reset();
    void poll();

    bool isReset() { return _reset; }
    bool isPaused() { return _pause; }

    uint8_t key_[16];

private:
    bool _pause;
    bool _reset;
};


