#ifndef LAYOUT_H
#define LAYOUT_H
#include <vector>

#include "impl/ui/window.h"

class Layout {
public:
    Layout();
public:
    std::vector<Window> windows;
    bool horizontal_direction;
    std::size_t offset_x;
    std::size_t offset_y;
    std::size_t displacement_x;
    std::size_t displacement_y;
};

#endif // LAYOUT_H
