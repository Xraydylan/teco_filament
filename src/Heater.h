#ifndef TECO_FILAMENT_HEATER_H
#define TECO_FILAMENT_HEATER_H

#include "Waiter.h"
#include "Relay.h"

class Heater : public Waiter {
public:
    Heater();
    void begin();
    void update();
    void on();
    void off();
    void set(bool new_state);
    bool get_state();

private:
    // Times in seconds
    int heating_time = 10;
    int cooling_time = 20;

    bool heating = false;
    bool state = false;

    Relay* relay;

};


#endif //TECO_FILAMENT_HEATER_H
