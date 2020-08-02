#include "Keyboard.h"

Keyboard::Keyboard() {}
Keyboard::~Keyboard() {}

void Keyboard::init() {
    memset(key, 0, sizeof(key));
    reset = false;
    pause = false;
}


u_int8_t* Keyboard::poll() {
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0){
        if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)){
            exit(1);
        }
    }
    memset(key, 0, sizeof(key));
    const u_int8_t * key_down = SDL_GetKeyboardState(0);

    if (key_down[SDL_SCANCODE_1])
        key[1] = 0xFF;
    if (key_down[SDL_SCANCODE_2])
        key[2] = 0xFF;
    if (key_down[SDL_SCANCODE_3])
        key[3] = 0xFF;
    if (key_down[SDL_SCANCODE_4])
        key[0xC] = 0xFF;
    if (key_down[SDL_SCANCODE_Q])
        key[4] = 0xFF;
    if (key_down[SDL_SCANCODE_W])
        key[5] = 0xFF;
    if (key_down[SDL_SCANCODE_E])
        key[6] = 0xFF;
    if (key_down[SDL_SCANCODE_R])
        key[0xD] = 0xFF;
    if (key_down[SDL_SCANCODE_A])
        key[7] = 0xFF;
    if (key_down[SDL_SCANCODE_S])
        key[8] = 0xFF;
    if (key_down[SDL_SCANCODE_D])
        key[9] = 0xFF;
    if (key_down[SDL_SCANCODE_F])
        key[0xE] = 0xFF;
    if (key_down[SDL_SCANCODE_Z])
        key[0xA] = 0xFF;
    if (key_down[SDL_SCANCODE_X])
        key[0] = 0xFF;
    if (key_down[SDL_SCANCODE_C])
        key[0xB] = 0xFF;
    if (key_down[SDL_SCANCODE_V])
        key[0xF] = 0xFF;
    if (key_down[SDL_SCANCODE_F1])
        Keyboard::reset = true;

    return key;
}
