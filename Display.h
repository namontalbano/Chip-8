#include "SDL2/SDL.h"

class Display {

public:

    Display();
    ~Display();

    void set_title(const char* title);
    void set_size(int width, int height);
    void set_draw_flag(bool draw_flag);

    void init();
    void draw(const uint8_t* graphics);
    void render();

private:

    int w_width_;
    int w_height_;
    u_int32_t pixels_ [2048];
    u_int8_t pixel_;
    bool draw_flag_;
    const char* w_title_;

    SDL_Window* sdl_window_;
    SDL_Renderer* sdl_renderer_;
    SDL_Texture* sdl_texture_;

};


