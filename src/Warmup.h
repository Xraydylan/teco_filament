#ifndef TECO_FILAMENT_WARMUP_H
#define TECO_FILAMENT_WARMUP_H

#include "preset_struct.h"
#include "Operating.h"

/* States
 * 2: Heatup
 * 3: Cooldown
*/

class Warmup : public Operating {
public:
    Warmup(OLED &display, Temperature &temp, Relay &relayExt);
    void start(Preset &selected);
    int update();
private:
    const float pre_heat_offset = 5; // set to 5!!!!!
    const float warmup_duration = 0.5; // ca. 30 min

    int warmup = true;

    float pre_heat_target;
    float target_real;

    void display_warmup();
    void display_cooldown();
    void display_ready();
    void screen_warmup();
    void screen_cooldown();
    int screen_ready();
    int screen_exceed();
};


#endif //TECO_FILAMENT_WARMUP_H
