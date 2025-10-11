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
    void draw();
    float x;
    float y;
    float width;
    float height;
    bool init_ok;
private:
    SDL_Renderer* renderer;
    SDL_FRect rect;
    SDL_Texture* texture;
    stbi_uc* image;
    int image_width;
    int image_height;
    int image_channels;
};

#endif // RENDER_SPRITE_H
