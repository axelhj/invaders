#include "impl/gameplay/command_central.h"

#include <SDL3/SDL_keycode.h>

#include <limits>

CommandCentral::CommandCentral(
    float width,
    float height,
    std::vector<RenderSprite*> units,
    float speed
) :
    speed(speed),
    direction(DIRECTION::L),
    distance_for_direction(0),
    offensive_distance(1),
    sequence(),
    width(width),
    height(height),
    step_number(0),
    units(units) {
}

void CommandCentral::update(float time, float delta_time) {
    if (step_number < sequence.size()) {
        direction = sequence[step_number];
    }
    if (direction == DIRECTION::L) {
        move_all(-speed * delta_time, 0);
    } else if (direction == DIRECTION::R) {
        move_all(speed * delta_time, 0);
    } else if (direction == DIRECTION::D) {
        move_all(0, speed * delta_time * 0.3f);
    } else if (direction == DIRECTION::U) {
        move_all(0, -speed * delta_time);
    }
    if (
        (direction == DIRECTION::L && min_x() < 40) ||
        (direction == DIRECTION::R && max_x() > (width - 40)) ||
        (
            direction == DIRECTION::D &&
            distance_for_direction >= speed * offensive_distance
        ) ||
        (direction == DIRECTION::D && max_y() > height)
    ) {
        distance_for_direction = 0.0f;
        advance();
    }
}

void CommandCentral::advance() {
    ++step_number;
    if (step_number >= sequence.size()) {
        step_number = 0;
    }
    direction = sequence[step_number];
}

void CommandCentral::move_all(float x, float y) {
    for (auto& unit : units) {
        distance_for_direction += std::max(x, y);
        unit->x += x;
        unit->y += y;
    }
}

float CommandCentral::max_x() {
    auto max = std::numeric_limits<float>::min();
    for (auto& unit : units) {
        if (unit->x + unit->width > max) {
            max = unit->x + unit->width;
        }
    }
    return max;
}

float CommandCentral::min_x() {
    auto min = std::numeric_limits<float>::max();
    for (auto& unit : units) {
        if (unit->x < min) {
            min = unit->x;
        }
    }
    return min;
}

float CommandCentral::max_y() {
    auto max = std::numeric_limits<float>::min();
    for (auto& unit : units) {
        if (unit->y + unit->height > max) {
            max = unit->y + unit->height;
        }
    }
    return max;
}

float CommandCentral::min_y() {
    auto min = std::numeric_limits<float>::max();
    for (auto& unit : units) {
        if (unit->y < min) {
            min = unit->y;
        }
    }
    return min;
}
