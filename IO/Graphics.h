#include "SDL2/SDL.h"
#include <ctime>

class Graphics {

public:

    Graphics();
    ~Graphics();

    void set_title(const char* title);
    void set_size(int width, int height);
    void set_draw_flag(bool draw_flag);
    void set_rgb(int red, int green, int blue);
    void set_rand_rgb();

    void init();
    void draw();
    void render();
    void drawPixel(const int x, const int y);

    uint8_t _graphics [2048];

private:

    int _r;
    int _g;
    int _b;
    int _width;
    int _height;
    uint32_t _pixels[2048];
    uint8_t _pixel;
    bool _drawFlag;
    bool _randRGB = true;
    const char* _title;

    SDL_Window* _window;
    SDL_Renderer* _renderer;
    SDL_Texture* _texture;

    void random_colors();
};


