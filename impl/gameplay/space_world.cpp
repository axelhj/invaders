#include "impl/gameplay/space_world.h"
#include "impl/gameplay/inputs.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_properties.h>
#include <SDL3_ttf/SDL_ttf.h>

#define BASE_SPEED 90.0f
#define MAX_SPEED 115.0f

SpaceWorld::SpaceWorld(
    SDL_Renderer* renderer,
    Inputs* inputs,
    int width,
    int height
) : init_ok(false),
    render_sprites(),
    renderer(renderer),
    inputs(inputs),
    width(width),
    height(height)
{
    render_sprites.emplace_back(
        new RenderSprite(renderer, "../asset/ship.png")
    );
    render_rows.emplace_back(
        new RenderRow(renderer, "./FreeSans.ttf")
    );
    render_rows[0]->prepare_text(
        "Space Invaders",
        200,
        200,
        100,
        false,
        0
    );
    auto render_sprite = render_sprites[0];
    auto ship_width = 80;
    auto ship_height = 80;
    render_sprite->width = ship_width;
    render_sprite->height = ship_height;
    render_sprite->x = (float)(width - ship_width) / 2;
    render_sprite->y = height - ship_height;
    init_ok = true;
}

void SpaceWorld::update(
    float time,
    float delta_time
) {
    auto render_sprite = render_sprites[0];
    if (inputs->a_tick) {
        // Fire space-cannon.
    }
    if (inputs->l_tick) {
        render_sprite->x =
            render_sprite->x - (BASE_SPEED * delta_time);
    } else if (inputs->r_tick) {
        render_sprite->x =
            render_sprite->x + (BASE_SPEED * delta_time);
    }
    if (inputs->u_tick) {
        render_sprite->y =
            render_sprite->y - (BASE_SPEED * delta_time);
    } else if (inputs->d_tick) {
        render_sprite->y =
            render_sprite->y + (BASE_SPEED * delta_time);
    }
}

void SpaceWorld::draw() {
    for (auto &render_sprite : render_sprites) {
        render_sprite->draw();
    }
    for (auto &render_row : render_rows) {
        render_row->draw();
    }
}

SpaceWorld::~SpaceWorld() {
}
