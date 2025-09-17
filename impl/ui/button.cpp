#include "impl/ui/button.h"
#include "impl/interface/button_observer.h"

#include <memory>

Button::Button(std::string label, std::shared_ptr<ButtonObserver> button_observer)
    : button_observer(button_observer), label(label) {
}
