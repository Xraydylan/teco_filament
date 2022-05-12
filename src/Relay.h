#ifndef TECO_FILAMENT_RELAY_H
#define TECO_FILAMENT_RELAY_H

#include "Arduino.h"
#include "pins.h"

class Relay {
public:
    Relay();
    bool get_state();
    void on();
    void off();
    void set(bool new_state);
private:
    int state = 0;
};


#endif //TECO_FILAMENT_RELAY_H
