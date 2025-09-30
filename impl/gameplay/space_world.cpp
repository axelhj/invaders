#include "impl/gameplay/space_world.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_properties.h>
#include <SDL3_ttf/SDL_ttf.h>

SpaceWorld::SpaceWorld(SDL_Renderer* renderer)
    : init_ok(false),
    render_sprites(),
    renderer(renderer)
{
    render_sprites.emplace_back(
        // new RenderSprite(renderer, "../asset/ship.png")
        new RenderSprite(renderer, "../asset/square.png")
    );
    init_ok = true;
}

void SpaceWorld::update(
    float time,
    float delta_time
) {
    auto render_sprite = render_sprites[0];
    render_sprite->set_width(400);
    render_sprite->set_height(400);
}

void SpaceWorld::draw() {
    for (auto &render_sprite : render_sprites) {
        render_sprite->draw();
    }
}

SpaceWorld::~SpaceWorld() {
}
