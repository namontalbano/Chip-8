#include "SDL2/SDL.h"

class Graphics {

public:

    Graphics();
    ~Graphics();

    void set_title(const char* title);
    void set_size(int width, int height);
    void set_draw_flag(bool draw_flag);
    void set_rgb(int red, int blue, int green);
    void init();
    void draw();
    void render();

    uint8_t graphics_ [2048];

private:
    int r_;
    int g_;
    int b_;
    int w_width_;
    int w_height_;
    uint32_t pixels_ [2048];
    uint8_t pixel_;
    bool draw_flag_;
    const char* w_title_;

    SDL_Window* sdl_window_;
    SDL_Renderer* sdl_renderer_;
    SDL_Texture* sdl_texture_;

};


