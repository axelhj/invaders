#include "impl/ui/window.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <memory>
#include <vector>
#include <sstream>

static std::shared_ptr<std::vector<std::string>> make_parts(std::string source, std::string delimiter);

Window::Window(std::shared_ptr<RenderSprite> render)
    : init_ok(false),
    render(render),
    offset_x(0),
    offset_y(0),
    displacement_x(0),
    displacement_y(0)
{
    init_ok = render->init_ok;
}

bool Window::draw() {
    std::size_t i = 0;
    auto parts = make_parts("", "\r");
    std::size_t row_start = 0;
    for (auto part : *parts) {
        auto cursor_position = 0;
        auto has_cursor = false;
        if (cursor_position >= row_start && cursor_position <= row_start + part.length()) {
            has_cursor = true;
            cursor_position -= row_start;
        }
        auto result = render->draw(part.c_str(), offset_x, offset_y + 26.f * i, displacement_x, has_cursor, cursor_position);
        if (result != true) {
            return false;
        }
        ++i;
        row_start += part.length() + 1;
    }
    return true;
}

static std::shared_ptr<std::vector<std::string>> make_parts(std::string source, std::string delimiter) {
    auto result = std::make_shared<std::vector<std::string>>();
    std::stringstream stream(source);
    std::string intermediate;
    if (delimiter.length() < 1) {
        return result;
    }
    while (std::getline(stream, intermediate, delimiter.c_str()[0])) {
        result->push_back(intermediate);
    }
    return result;
}
