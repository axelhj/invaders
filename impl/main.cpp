#include "impl/render/render_sprite.h"
#include "impl/ui/window.h"
#include "impl/constant/constants.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <vector>
#include <cctype>
#include <cstdlib>
#include <string>
#include <memory>

int main(int argc, char **argv) {
    SDL_Event event;
    SDL_Window* window;
    SDL_Renderer* renderer;
    /* Init TTF. */
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
    auto render_sprite = std::make_shared<RenderSprite>(renderer, "FreeSans.ttf");
    auto render_windows = std::vector<Window>();
    render_windows.emplace_back(Window(render_sprite));
    // if (SDL_StartTextInput(window) != 0) {
    // }
    bool should_quit = false;
    while (!should_quit) {
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 0);
        SDL_RenderClear(renderer);
        if (!render_windows[0].draw()) {
            should_quit = true;
        }
        SDL_RenderPresent(renderer);
        if (SDL_PollEvent(&event) == SDL_TRUE) {
            if (event.type == SDL_EVENT_QUIT) {
                should_quit = true;
            // } else if (event.type == SDL_EVENT_TEXT_INPUT) {
                // interpreter->on_input(event.text.text);
            } else if (event.type == SDL_EVENT_KEY_DOWN) {
                switch (event.key.key) {
                case SDLK_BACKSPACE:
                    // interpreter->on_input(std::string("\b"));
                    break;
                case SDLK_ESCAPE:
                    // interpreter->on_input(std::string("\e"));
                    should_quit = true;
                    break;
                case SDLK_RETURN:
                    // interpreter->on_input(std::string("\r"));
                    break;
                case SDLK_TAB:
                    // interpreter->on_input(std::string("\t"));
                    break;
                }
            }
        }
    }
    SDL_StopTextInput(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
