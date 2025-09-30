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
    void set_x(float x);
    void set_y(float y);
    void set_width(float width);
    void set_height(float height);
    float get_x();
    float get_y();
    float get_width();
    float get_height();
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
