#ifndef ROW_H
#define ROW_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <cstdlib>
#include <string>

class RenderRow {
public:
    RenderRow(SDL_Renderer* renderer, const char* font_path);
    ~RenderRow();
    bool render_text(
        SDL_Color c,
        const char *text,
        unsigned int width
    );
    bool prepare_text(
        const char* text,
        float x,
        float y,
        float w,
        bool has_cursor,
        std::size_t cursor_pos
    );
    bool draw();
    bool init_ok;
    bool is_prepared;
    bool has_cursor;
    bool cursor_pos;
private:
    SDL_Renderer* renderer;
    SDL_Rect rect;
    SDL_FRect target_rect;
    SDL_Texture* texture;
    TTF_Font* font;
    std::string text;
};

#endif // ROW_H
