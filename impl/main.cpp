#include "impl/gameplay/space_world.h"
#include "impl/constant/constants.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_render.h>

#include <cstdlib>
#include <iostream>

int main(int argc, char **argv) {
    SDL_Event event;
    SDL_Window* window;
    SDL_Renderer* renderer;
    /* Init SDL. */
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO)) {
        SDL_LogError(1, "SDL_Init() failed: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    /* Create a window */
    if (SDL_CreateWindowAndRenderer("invaders", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) < 0) {
        SDL_LogError(1, "SDL_CreateWindowAndRenderer() failed: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    auto world = SpaceWorld(renderer);
    bool should_quit = false;
    float accumulator = 0;
    while (!should_quit) {
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 0);
        SDL_RenderClear(renderer);
        world.update(accumulator, 0.16);
        accumulator += 0.16;
        world.draw();
        SDL_RenderPresent(renderer);
        if (SDL_PollEvent(&event) == SDL_TRUE) {
            std::cout << event.type << std::endl;
            if (event.type == SDL_EVENT_QUIT) {
                should_quit = true;
            } else if (event.type == SDL_EVENT_KEY_DOWN) {
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
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
