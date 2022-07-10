#include "DButton.h"

DButton::DButton() {

}

DButton::DButton(int pin) {
    setup(pin);
}

void DButton::setup(int pin) {
    button.attach(pin, INPUT_PULLUP);
    button.interval(15);
    //button.setPressedState(LOW);
    button.setPressedState(HIGH);
}

void DButton::update() {
    button.update();
}

bool DButton::pressed() {
    return button.pressed();
}


