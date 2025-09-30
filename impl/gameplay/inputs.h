#ifndef INPUT_H
#define INPUT_H

#include <SDL3/SDL_events.h>

struct Inputs {
    Inputs();
    void update();
    void set_kc(SDL_Keycode code, bool status);
    bool l_down;
    bool r_down;
    bool u_down;
    bool d_down;
    bool a_down;
    bool c_down;
    bool s_down;
    bool l_tick;
    bool r_tick;
    bool u_tick;
    bool d_tick;
    bool a_tick;
    bool c_tick;
    bool s_tick;
};

#endif // INPUT_H
