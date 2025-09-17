#ifndef BUTTON_H
#define BUTTON_H

#include "impl/interface/button_observer.h"

#include <string>
#include <memory>

class Button {
public:
    Button(std::string label, std::shared_ptr<ButtonObserver> button_observer);
    std::shared_ptr<ButtonObserver> button_observer;
    std::string label;
    std::size_t offset_x;
    std::size_t offset_y;
    std::size_t displacement_x;
    std::size_t displacement_y;
};

#endif // BUTTON_H
