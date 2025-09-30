#ifndef SPACE_WORLD_H
#define SPACE_WORLD_H

#include "impl/render/render_sprite.h"
#include "impl/gameplay/inputs.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <vector>

class SpaceWorld {
public:
    SpaceWorld(SDL_Renderer* renderer, Inputs* inputs);
    ~SpaceWorld();
    void update(float time, float delta_time);
    void draw();
    bool init_ok;
private:
    std::vector<RenderSprite*> render_sprites;
    SDL_Renderer* renderer;
    Inputs* inputs;
};

#endif // SPACE_WORLD_H
