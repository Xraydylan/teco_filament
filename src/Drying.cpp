#include "Drying.h"

Drying::Drying(OLED &display, Temperature &temp, Heater &heaterExt) : Operating(display, temp, heaterExt) {

}

void Drying::start(Preset & selected) {
    selected_preset = &selected;
    start_time = millis();
    duration_ms = (unsigned long int)(selected_preset->duration * 60 * 60 * 1000);
    set_new_target(selected_preset->temperature);
    display_drying();
}

int Drying::update() {
    int rst = 0;
    switch (state) {
        case 0:
            return screen_end();
            break;
        case 1:
            rst = screen_cancel();
            oled->set_button_flag();
            if (rst == 1) return 1;
            if (rst == 2) display_drying();
            break;
        case 2:
            screen_drying();
            break;
        default:
            break;
    }
    return 0;
}

void Drying::display_drying() {
    state = 2;
    oled->clear();
    oled->print("Drying in progress", 0);
    screen_drying();
}

void Drying::screen_drying() {
    operation();
}


