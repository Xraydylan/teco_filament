#ifndef TECO_FILAMENT_DBUTTON_H
#define TECO_FILAMENT_DBUTTON_H

#include "Bounce2.h"

class DButton {
public:
    DButton();
    DButton(int);
    void setup(int);
    void update();
    bool pressed();

private:
    Bounce2::Button button;
};


#endif //TECO_FILAMENT_DBUTTON_H
