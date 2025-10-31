#include "impl/gameplay/space_world.h"
#include "impl/gameplay/inputs.h"
#include "impl/gameplay/command_central.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_properties.h>
#include <SDL3_ttf/SDL_ttf.h>

#define BASE_SPEED 175.0f
#define MAX_SPEED 320.0f
#define ENEMY_INITIAL_SPEED 135.0f

SpaceWorld::SpaceWorld(
    SDL_Renderer* renderer,
    Inputs* inputs,
    int width,
    int height
) : init_ok(false),
    render_sprites(),
    render_rows(),
    command_central(
        width,
        height,
        std::vector<RenderSprite*>(),
        ENEMY_INITIAL_SPEED
    ),
    renderer(renderer),
    inputs(inputs),
    width(width),
    height(height)
{
    render_sprites.emplace_back(
        new RenderSprite(renderer, "../asset/ship.png")
    );
    render_sprites.emplace_back(
        new RenderSprite(renderer, "../asset/blip.png")
    );
    render_rows.emplace_back(
        new RenderRow(renderer, "./FreeSans.ttf")
    );
    render_rows[0]->prepare_text(
        "Space Invaders",
        70,
        70,
        130,
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
    render_sprite = render_sprites[1];
    // auto blip_width = 40;
    // auto blip_height = 40;
    auto ship_count = 5;
    auto padding = 60;
    auto enemy_width = 80;
    auto enemy_height = 80;
    render_sprite->x = 50;
    render_sprite->y = 200;
    std::vector<RenderSprite*> commanded_sprites {};
    for (int i = 0; i < ship_count; ++i) {
        render_sprites.emplace_back((render_sprite = new RenderSprite(renderer, "../asset/alien.png")));
        render_sprite->x = (int)(padding + ((width - padding) / ship_count) * i + enemy_width / 2);
        render_sprite->y = (int)(height / ship_count - (enemy_height / 2));
        render_sprite->width = enemy_width;
        render_sprite->height = enemy_height;
        commanded_sprites.push_back(render_sprite);
    }
    command_central = CommandCentral(
        width,
        height,
        commanded_sprites,
        ENEMY_INITIAL_SPEED
    );
    command_central.sequence = std::vector<DIRECTION> {
        DIRECTION::R,
        DIRECTION::D,
        DIRECTION::L,
        DIRECTION::D,
    };
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
    const auto tick_speed = (inputs->sh_down ? MAX_SPEED : BASE_SPEED) *
        delta_time;
    if (inputs->l_down) {
        render_sprite->x = render_sprite->x - tick_speed;
    } else if (inputs->r_down) {
        render_sprite->x = render_sprite->x + tick_speed;
    }
    if (inputs->u_down) {
        render_sprite->y = render_sprite->y - tick_speed;
    } else if (inputs->d_down) {
        render_sprite->y = render_sprite->y + tick_speed;
    }
    command_central.update(time, delta_time);
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
    for (auto &render_sprite : render_sprites) {
        delete render_sprite;
    }
    for (auto &render_row : render_rows) {
        delete render_row;
    }
}
