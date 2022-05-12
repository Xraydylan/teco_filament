#ifndef TECO_FILAMENT_OPERATING_H
#define TECO_FILAMENT_OPERATING_H

#include "preset.h"
#include "pins.h"
#include "Relay.h"
#include "Temperature.h"
#include "OLED.h"

/* Operating states:
 * 0: End
 * 1: Cancel
*/

#include "preset_struct.h"

class Operating {
public:
    Operating(OLED &display, Temperature &temp, Relay &relay_ext);
    static unsigned long int h_to_millis(float num);
protected:
    OLED* oled;
    Temperature* temp;
    Relay* relay;

    float margin = 1;
    int update_delay = 100;
    int state = 0;

    float target;
    float temperature;
    Preset * selected_preset;

    unsigned long int duration_ms = 0;
    unsigned long int start_time = 0;
    unsigned long int delta = 0;

    unsigned long int last = 0;

    void read_temp();
    int screen_cancel();
    int screen_end();
    void display_end(int end_type = 0);
    void display_cancel();
    void draw_stats();
    bool determine_end();
    bool determine_relay_state();
    void operation(bool stats = true);
    void check_cancel();
    bool check_update();
};


#endif //TECO_FILAMENT_OPERATING_H
