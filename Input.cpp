#include "Input.h"

void Input::reset() {
    _reset = false;
    memset(key_, 0, sizeof(key_));
}
void Input::poll() {
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0){
        if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)){
            exit(1);
        }
    }
    reset();
    const u_int8_t * key_down = SDL_GetKeyboardState(nullptr);
    if (key_down[SDL_SCANCODE_1])
        key_[1] = 0xFF;
    if (key_down[SDL_SCANCODE_2])
        key_[2] = 0xFF;
    if (key_down[SDL_SCANCODE_3])
        key_[3] = 0xFF;
    if (key_down[SDL_SCANCODE_4])
        key_[0xC] = 0xFF;
    if (key_down[SDL_SCANCODE_Q])
        key_[4] = 0xFF;
    if (key_down[SDL_SCANCODE_W])
        key_[5] = 0xFF;
    if (key_down[SDL_SCANCODE_E])
        key_[6] = 0xFF;
    if (key_down[SDL_SCANCODE_R])
        key_[0xD] = 0xFF;
    if (key_down[SDL_SCANCODE_A])
        key_[7] = 0xFF;
    if (key_down[SDL_SCANCODE_S])
        key_[8] = 0xFF;
    if (key_down[SDL_SCANCODE_D])
        key_[9] = 0xFF;
    if (key_down[SDL_SCANCODE_F])
        key_[0xE] = 0xFF;
    if (key_down[SDL_SCANCODE_Z])
        key_[0xA] = 0xFF;
    if (key_down[SDL_SCANCODE_X])
        key_[0] = 0xFF;
    if (key_down[SDL_SCANCODE_C])
        key_[0xB] = 0xFF;
    if (key_down[SDL_SCANCODE_V])
        key_[0xF] = 0xFF;
    if (key_down[SDL_SCANCODE_F1])
        _reset = true;
    if (key_down[SDL_SCANCODE_P])
        if (_pause) { _pause = false; }
        else if (!_pause) { _pause = true; }

}
