#ifndef RENDER_SPRITE_H
#define RENDER_SPRITE_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "stb_image.h"

class RenderSprite {
public:
    RenderSprite(SDL_Renderer* renderer, const char* asset_path);
    ~RenderSprite();
    void set_x(unsigned int x);
    void set_y(unsigned int y);
    void set_width(unsigned int width);
    void set_height(unsigned int height);
    int get_x();
    int get_y();
    int get_width();
    int get_height();
    void draw();
    bool init_ok;
private:
    SDL_Renderer* renderer;
    SDL_FRect rect;
    SDL_Texture* texture;
    stbi_uc* image;
    int width;
    int height;
    int channels;
};

#endif // RENDER_SPRITE_H
