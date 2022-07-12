#ifndef TECO_FILAMENT_HEATER_H
#define TECO_FILAMENT_HEATER_H

#include "Waiter.h"
#include "Relay.h"
#include "Temperature.h"
#include "preset.h"
#include "preset_struct.h"

class Heater : public Waiter {
public:
    Heater(Temperature &temp);
    void begin();
    void update();
    void on();
    void off();
    void set(bool new_state);
    bool get_state();
    void set_pwm(int p, float dc);
    void set_new_target(float new_target);

private:
    float duty_cycle;
    int period;
    int heating_time;
    int cooling_time;
    float target;

    Preset_heater preset_heater;

    bool heating = false;
    bool state = false;

    Relay* relay;
    Temperature* temp;

    void check_temp_delta();
    void calculate_times();
};


#endif //TECO_FILAMENT_HEATER_H
