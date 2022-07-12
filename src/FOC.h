#ifndef TECO_FILAMENT_FOC_H
#define TECO_FILAMENT_FOC_H

#include "preset_struct.h"

#include "OLED.h"
#include "Temperature.h"
#include "Start_Menu.h"
#include "Warmup.h"
#include "Drying.h"
#include "Heater.h"
#include "Waiter.h"

class FOC {
public:
    FOC();
    void begin();
    void update();
private:
    OLED* oled;
    Start_Menu* start_menu;
    Warmup* warmup;
    Drying* drying;

    Heater* heater;

    Temperature* temperature;

    int state = 0;
    Preset* selected;

    const int loop_delay = 10;
    unsigned long last = 0;

    void start_state();
    void warmup_state();
    void drying_state();
    void internal_delay();
};


#endif //TECO_FILAMENT_FOC_H
