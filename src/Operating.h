#ifndef TECO_FILAMENT_OPERATING_H
#define TECO_FILAMENT_OPERATING_H

#include "preset.h"
#include "pins.h"
#include "Heater.h"
#include "Temperature.h"
#include "OLED.h"

/* Operating states:
 * 0: End
 * 1: Cancel
*/

#include "Waiter.h"
#include "preset_struct.h"

class Operating : public Waiter {
public:
    Operating(OLED &display, Temperature &temp, Heater &heater_ext);
    static unsigned long int h_to_millis(float num);
protected:
    OLED* oled;
    Temperature* temp;
    Heater* heater;

    float margin = 1;
    int update_delay = 100;
    int state = 0;

    float target;
    float temperature;
    Preset * selected_preset;

    unsigned long int duration_ms = 0;
    unsigned long int start_time = 0;
    unsigned long int delta = 0;

    void read_temp();
    int screen_cancel();
    int screen_end();
    void display_end(int end_type = 0);
    void display_cancel();
    void draw_stats();
    bool determine_end();
    bool determine_heater_state();
    void operation(bool stats = true);
    void check_cancel();

    void set_new_target(float new_target);
};


#endif //TECO_FILAMENT_OPERATING_H
