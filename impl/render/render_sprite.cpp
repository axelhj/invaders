#include "impl/render/render_sprite.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_properties.h>
#include <SDL3_ttf/SDL_ttf.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <cstdlib>
#include <cstdio>
#include <format>

RenderSprite::RenderSprite(SDL_Renderer* renderer, const char* asset_path)
    : init_ok(false),
    renderer(renderer),
    rect(),
    texture(nullptr),
    image(nullptr),
    width(0),
    height(0),
    channels(0)
{
    if ((image = stbi_load(asset_path, &width, &height, &channels, 4)) == nullptr) {
        SDL_LogError(
            1,
            "Couldn't load asset: %s (%s)\n",
            stbi_failure_reason(),
            asset_path
        );
        return;
    }
}

void RenderSprite::set_x(unsigned int x) {
    rect.x = x;
}

void RenderSprite::set_y(unsigned int y) {
    rect.y = y;
}

void RenderSprite::set_width(
    unsigned int width
) {
    rect.w = width;
}

void RenderSprite::set_height(
    unsigned int height
) {
    rect.h = height;
}

int RenderSprite::get_x() {
    return rect.x;
}

int RenderSprite::get_y() {
    return rect.y;
}

int RenderSprite::get_width() {
    return rect.w;
}

int RenderSprite::get_height() {
    return rect.h;
}

void RenderSprite::draw() {
    if (texture == nullptr) {
        texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGBA32,
            SDL_TEXTUREACCESS_STREAMING,
            width,
            height
        );
        // Alternative method for setting pixel data:
        // int pitch = 128 * 4;
        // SDL_UpdateTexture(texture, NULL, image, pitch);
        // Pitch is changed to 512 after locking.
        void* pixels = NULL;
        int pitch = 0;
        SDL_LockTexture(texture, NULL, &pixels, &pitch);
        memcpy(pixels, image, width * height * 4);
        SDL_UnlockTexture(texture);
    }
    SDL_RenderTexture(renderer, texture, NULL, &rect);
}

RenderSprite::~RenderSprite() {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
    if (image != NULL) {
        stbi_image_free(image);
        image = NULL;
    }
}
