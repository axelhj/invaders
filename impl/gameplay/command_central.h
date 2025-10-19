#ifndef COMMAND_CENTRAL_H
#define COMMAND_CENTRAL_H

#include <SDL3/SDL_events.h>
#include "impl/render/render_sprite.h"

#include <vector>

typedef enum Direction {
    L, R, U, D
} DIRECTION;

class CommandCentral {
public:
    CommandCentral(
        float width,
        float height,
        std::vector<RenderSprite*> units,
        float speed
    );
    void update(float time, float delta_time);
    void advance();
    void move_all(float x, float y);
    float max_x();
    float min_x();
    float max_y();
    float min_y();
    float speed;
    DIRECTION direction;
    float distance_for_direction;
    float offensive_distance;
    std::vector<DIRECTION> sequence;
private:
    float width;
    float height;
    std::size_t step_number;
    std::vector<RenderSprite*> units;
};

#endif // COMMAND_CENTRAL_H
