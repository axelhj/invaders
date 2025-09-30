#include "impl/gameplay/inputs.h"

#include <SDL3/SDL_keycode.h>

Inputs::Inputs() :
    l_down(false),
    r_down(false),
    u_down(false),
    d_down(false),
    a_down(false),
    c_down(false),
    s_down(false),
    l_tick(false),
    r_tick(false),
    u_tick(false),
    d_tick(false),
    a_tick(false),
    c_tick(false),
    s_tick(false) {
}

void Inputs::update() {
    // l_tick = r_tick = u_tick =
    // d_tick = a_tick = c_tick = s_tick = false;
}

void Inputs::set_kc(SDL_Keycode code, bool status) {
    switch (code) {
    case SDLK_LEFT:
        l_down = l_tick = status;
        break;
    case SDLK_RIGHT:
        r_down = r_tick = status;
        break;
    case SDLK_UP:
        u_down = u_tick = status;
        break;
    case SDLK_DOWN:
        d_down = d_tick = status;
        break;
    case SDLK_SPACE:
        s_down = s_tick = status;
        break;
    case SDLK_LCTRL:
    case SDLK_RCTRL:
        c_down = c_tick = status;
        break;
    case SDLK_A:
        a_down = a_tick = status;
        break;
    default: return;
    }
}
