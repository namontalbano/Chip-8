#include "Graphics.h"

Graphics::Graphics() {
    set_title("Chip-8 Emulator");
    set_size(1024, 512);
    set_rgb(0, 255, 0);
}

Graphics::~Graphics() { }

void Graphics::set_title(const char *title) {
    _title = title;
}

void Graphics::set_size(int width, int height) {
     _width = width;
     _height = height;
}

void Graphics::set_rgb(int red, int green, int blue) {
    _r = red;
    _g = green;
    _b = blue;
}

void Graphics::set_draw_flag(bool draw_flag) {
    _drawFlag = draw_flag;
}

void Graphics::random_colors() {
    srand(time(nullptr));
    _r = rand() % 255 + 0;
    _g = rand() % 255 + 0;
    _b = rand() % 255 + 0;
}

void Graphics::init() {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        exit(1);
    }

    _window = SDL_CreateWindow(_title,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            _width,
            _height,
            SDL_WINDOW_SHOWN);

    if (_window == nullptr) {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        exit(2);
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    _texture = SDL_CreateTexture(_renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,64, 32);
}

void Graphics::draw() {
    if (_randRGB) { random_colors(); }

    if (_drawFlag) {
        set_draw_flag(false);
        for (int i = 0; i < 2048; ++i) {
            _pixel = _graphics[i];
            _pixels[i] = (0x00FcFFFFFu * _pixel) | 0xFF000000;
        }
        SDL_SetTextureColorMod(_texture, _r, _g, _b);
        SDL_UpdateTexture(_texture, nullptr, _pixels, 64 * sizeof(Uint32));
    }
    render();

//    for(int i = 0; i < 64*32; i++)
//    {
//        if(_graphics[i] == 1)
//        {
//            drawPixel(i%64, i/64);
//        }
//    }
}

void Graphics::render() {
    SDL_RenderClear(_renderer);
    SDL_RenderCopy(_renderer, _texture, nullptr, nullptr);
    SDL_RenderPresent(_renderer);
}

void Graphics::drawPixel(const int x, const int y) {
    int onePixelX = (int)(1024 - 0) / 64;
    int onePixelY = (int)(512 - 0) / 32;
    int scaledX = onePixelX * x;
    int scaledY = onePixelY * y;

    float vertices[] = {
            (float)scaledX, (float)scaledY, //Top Left
            (float)scaledX + onePixelX, (float)scaledY, //Top Right
            (float)scaledX + onePixelX, (float)scaledY + onePixelY, // Bottom Right
            (float)scaledX, (float)scaledY + onePixelY // Bottom Left
    };
    unsigned int indices[] = {
            0, 1, 2,
            0, 3, 2
    };
}
