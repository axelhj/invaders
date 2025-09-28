#ifndef SPACE_WORLD_H
#define SPACE_WORLD_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <cstdlib>

class SpaceWorld {
public:
    SpaceWorld(SDL_Renderer* renderer, const char* asset_path, const char* font_path);
    ~SpaceWorld();
    bool render_text(
        SDL_Color c,
        const char *text,
        unsigned int width
    );
    bool draw(
        const char* text,
        float x,
        float y,
        float w,
        bool has_cursor,
        std::size_t cursor_pos
    );
    bool init_ok;
private:
    SDL_Renderer* renderer;
    SDL_Rect rect;
    SDL_Texture* texture;
    TTF_Font* font;
    unsigned char* image;
    int width;
    int height;
    int channels;
};

#endif // SPACE_WORLD_H
