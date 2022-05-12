#ifndef TECO_FILAMENT_FOC_H
#define TECO_FILAMENT_FOC_H

#include "preset_struct.h"

#include "OLED.h"
#include "Relay.h"
#include "Temperature.h"
#include "Start_Menu.h"
#include "Warmup.h"
#include "Drying.h"

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

    Temperature* temperature;
    Relay* relay;

    int state = 0;
    Preset* selected;

    const int loop_delay = 5;
    unsigned long int last = 0;

    void start_state();
    void warmup_state();
    void drying_state();
    void internal_delay();
};


#endif //TECO_FILAMENT_FOC_H
