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
#include <iostream>

RenderSprite::RenderSprite(SDL_Renderer* renderer, const char* asset_path) :
    x(),
    y(),
    width(),
    height(),
    init_ok(false),
    renderer(renderer),
    texture(nullptr),
    image(nullptr),
    image_width(0),
    image_height(0),
    image_channels(0)
{
    if ((image = stbi_load(
        asset_path,
        &image_width,
        &image_height,
        &image_channels,
        4
    )) == nullptr) {
        SDL_LogError(
            1,
            "Couldn't load asset: %s (%s)\n",
            stbi_failure_reason(),
            asset_path
        );
        return;
    }
}

void RenderSprite::draw() {
    if (texture == nullptr) {
        texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGBA32,
            SDL_TEXTUREACCESS_STREAMING,
            image_width,
            image_height
        );
        // Alternative method for setting pixel data:
        // int pitch = 128 * 4;
        // SDL_UpdateTexture(texture, NULL, image, pitch);
        // Pitch is changed to 512 after locking.
        void* pixels = NULL;
        int pitch = 0;
        SDL_LockTexture(texture, NULL, &pixels, &pitch);
        memcpy(pixels, image, image_width * image_height * 4);
        SDL_UnlockTexture(texture);
        SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    }
    SDL_FRect destinationRect { x, y, width, height };
    SDL_RenderTexture(renderer, texture, NULL, &destinationRect);
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
