#include "impl/render/render_row.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_properties.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <cstdlib>
#include <cstdio>
#include <string>

RenderRow::RenderRow(SDL_Renderer* renderer, const char* font_path)
    : init_ok(false),
    renderer(renderer),
    rect(),
    texture(nullptr),
    font(nullptr) {
    /* Initialize the TTF library */
    if (TTF_Init() < 0) {
        SDL_LogError(1, "TTF_Init() failed: %s\n", TTF_GetError());
        return;
    }
    font = TTF_OpenFont(font_path, 24);
    if (font == NULL) {
        SDL_LogError(1, "Couldn't initialize TT-font: %s\n", TTF_GetError());
        return;
    }
    if (TTF_SetFontSize(font, 24) != 0) {
        SDL_LogError(1, "Couldn't set font-size with TTF: %s\n", TTF_GetError());
        return;
    }
    init_ok = true;
}

bool RenderRow::render_text(
    SDL_Color textColor,
    const char *text,
    unsigned int width
) {
    SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(font, text, textColor, width);
    if (surface == nullptr) {
        SDL_LogError(1, "TTF_RenderUTF8_Solid_Wrapped() failed: %s\n", TTF_GetError());
        return false;
    }
    // Continuous creation and destrution of surface causes a small memory leak.
    // Similar to as described here https://github.com/libsdl-org/SDL/issues/3453
    // In which case it might be caused by a hardware driver program.
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect.w = surface->w;
    rect.h = surface->h;
    SDL_DestroySurface(surface);
    return true;
}

bool RenderRow::draw(
    const char* text,
    float x,
    float y,
    float w,
    bool has_cursor,
    std::size_t cursor_pos
) {
    SDL_FRect tRect = {};
    TTF_SetFontOutline(font, 0);
    int result = 0;
    if (text[0] == '\0') {
        rect.w = 8;
        rect.h = 32;
    } else {
        // auto hashed = str_hasher(text);
        // auto entry = lru.find(hashed);
        // if (entry == nullptr) {
            SDL_Color cursor_color = {200, 200, 200, 0};
            result = render_text(cursor_color, text, w);
        //     lru.append(hashed, texture);
        // } else {
            auto prop = SDL_GetTextureProperties(texture);
            rect.w = SDL_GetNumberProperty(prop, SDL_PROP_TEXTURE_WIDTH_NUMBER, 0);
            rect.h = SDL_GetNumberProperty(prop, SDL_PROP_TEXTURE_HEIGHT_NUMBER, 0);
        // }
    }
    if (rect.w == 0 || rect.h == 0 || result != 0) {
        return false;
    }
    tRect.x = x;
    tRect.y = y;
    tRect.w = rect.w;
    tRect.h = rect.h;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(renderer, &tRect);
    if (has_cursor) {
        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 0);
        int precedingWidth = 0;
        int precedingHeight = 0;
        auto until_cursor = std::string(text).substr(0, cursor_pos);
        int precedingStringResult = TTF_SizeUTF8(font, until_cursor.c_str(), &precedingWidth, &precedingHeight);
        int charWidth = 0;
        int charHeight = 0;
        auto from_cursor = std::string(text).substr(cursor_pos, 1);
        int charResult = TTF_SizeUTF8(font, from_cursor.c_str(), &charWidth, &charHeight);
        if (precedingStringResult == 0 && charResult == 0) {
            tRect.x = x + precedingWidth;
            // No char width indicates end of row.
            if (charWidth == 0) {
                tRect.y = precedingHeight + y - charHeight / 2.f;
                tRect.w = 12;
                tRect.h = charHeight / 2.f;
            } else {
                tRect.y = precedingHeight + y - charHeight;
                tRect.w = charWidth;
                tRect.h = charHeight;
            }
        }
        SDL_RenderFillRect(renderer, &tRect);
    }
    tRect.x = x;
    tRect.y = y;
    tRect.w = rect.w;
    tRect.h = rect.h;
    if (text[0] != '\0') {
        SDL_RenderTexture(renderer, texture, NULL, &tRect);
    }
    return true;
}

RenderRow::~RenderRow() {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
    }
    if (font != NULL) {
        TTF_CloseFont(font);
    }
    /* De-init TTF. */
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
    }
    /* De-init TTF. */
    if (init_ok) {
        TTF_Quit();
    }
}
