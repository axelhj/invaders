#ifndef WINDOW_H
#define WINDOW_H

#include "impl/render/render_sprite.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <vector>
#include <memory>

class Window {
public:
    Window(std::shared_ptr<RenderSprite> render);
    bool draw();
    bool init_ok;
    std::shared_ptr<RenderSprite> render;
    std::size_t offset_x;
    std::size_t offset_y;
    std::size_t displacement_x;
    std::size_t displacement_y;
};

#endif // WINDOW_H
