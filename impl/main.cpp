#include "impl/gameplay/space_world.h"
#include "impl/gameplay/inputs.h"
#include "impl/constant/constants.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_render.h>

#include <cstdlib>
#include <iostream>

#define FRAME_TIME_TARGET_MS 16.66f

int main(int argc, char **argv) {
    SDL_Event event;
    SDL_Window* window;
    SDL_Renderer* renderer;
    /* Init SDL. */
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(1, "SDL_Init() failed: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    /* Create a window */
    if (!SDL_CreateWindowAndRenderer("invaders", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
        SDL_LogError(1, "SDL_CreateWindowAndRenderer() failed: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    auto inputs = Inputs();
    auto world = SpaceWorld(renderer, &inputs, WINDOW_WIDTH, WINDOW_HEIGHT);
    bool should_quit = false;
    float accumulator = 0;
    while (!should_quit) {
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 0);
        SDL_RenderClear(renderer);
        world.update(accumulator, FRAME_TIME_TARGET_MS / 1000.0f);
        accumulator += FRAME_TIME_TARGET_MS / 1000.0f;
        world.draw();
        inputs.update();
        SDL_Delay((int)FRAME_TIME_TARGET_MS);
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                should_quit = true;
            } else if (event.type == SDL_EVENT_KEY_DOWN) {
                inputs.set_kc(event.key.key, true);
                switch (event.key.key) {
                case SDLK_BACKSPACE:
                    break;
                case SDLK_ESCAPE:
                    should_quit = true;
                    break;
                case SDLK_RETURN:
                    break;
                case SDLK_TAB:
                    break;
                }
            } else if (event.type == SDL_EVENT_KEY_UP) {
                inputs.set_kc(event.key.key, false);
            } else {
                std::cout << event.type << std::endl;
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
