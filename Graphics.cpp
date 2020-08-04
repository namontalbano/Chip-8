#include <time.h>
#include "Graphics.h"

Graphics::Graphics() {
    set_title("Chip-8 Emulator");
    set_size(1024, 512);
}

Graphics::~Graphics() { }


void Graphics::set_title(const char *title) {
    w_title_ = title;
}

void Graphics::set_size(int width, int height) {
     w_width_ = width;
     w_height_ = height;
}

void Graphics::set_draw_flag(bool draw_flag) {
    draw_flag_ = draw_flag;
}

void Graphics::init() {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        exit(1);
    }

    sdl_window_ = SDL_CreateWindow(w_title_,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            w_width_,
            w_height_,
            SDL_WINDOW_SHOWN);

    if (sdl_window_ == nullptr) {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        exit(2);
    }

    sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED);
    sdl_texture_ = SDL_CreateTexture(sdl_renderer_,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,64, 32);
}

void Graphics::draw() {
    srand(time(0));
    int r;
    int g;
    int b;
    r = rand() % 255 + 1;
    g = rand() % 255 + 1;
    b = rand() % 255 + 1;

    if (draw_flag_) {
        set_draw_flag(false);
        for (int i = 0; i < 2048; ++i) {
            pixel_ = graphics_[i];
            pixels_[i] = (0x00FcFFFFFu * pixel_) | 0xFF000000;
        }
        SDL_SetTextureColorMod(sdl_texture_, r, g, b);
        SDL_UpdateTexture(sdl_texture_, nullptr, pixels_, 64 * sizeof(Uint32));
    }
    render();
}


void Graphics::render() {
    SDL_RenderClear(sdl_renderer_);
    SDL_RenderCopy(sdl_renderer_, sdl_texture_, nullptr, nullptr);
    SDL_RenderPresent(sdl_renderer_);
}
