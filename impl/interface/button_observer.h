#ifndef BUTTON_OBSERVER_H
#define BUTTON_OBSERVER_H

#include <string>

class ButtonObserver {
public:
    virtual void on_press(
        std::string name
    ) = 0;
};

#endif // BUTTON_OBSERVER_H
