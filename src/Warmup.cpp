#include "Warmup.h"


Warmup::Warmup(OLED &display, Temperature &temp, Heater &heaterExt) : Operating(display, temp, heaterExt) {

}

int Warmup::update() {
    int rst = 0;
    switch (state) {
        case 0:
            heater->off();
            return screen_exceed();
            break;
        case 1:
            rst = screen_cancel();
            oled->set_button_flag();
            if (rst == 1) {
                heater->off();
                return 2;
            }
            if (rst == 2) {
                if (warmup) display_warmup();
                else display_cooldown();
            }
            break;
        case 2:
            screen_warmup();
            break;
        case 3:
            screen_cooldown();
            break;
        case 4:
            return screen_ready();
            break;
        default:
            break;
    }
    return 0;
}

void Warmup::start(Preset &selected) {
    warmup = true;
    selected_preset = &selected;
    start_time = millis();
    duration_ms = h_to_millis(warmup_duration);
    target_real = selected_preset->temperature + pre_heat_offset;
    pre_heat_target = target_real + pre_heat_offset;
    target = pre_heat_target;

    display_warmup();
}

void Warmup::display_warmup() {
    state = 2;
    oled->clear();
    oled->print("Warmup in progress", 0);

    screen_warmup();
}

void Warmup::display_cooldown() {
    state = 3;
    oled->clear();
    oled->print("Cooling till target", 0);
    screen_cooldown();
}

void Warmup::display_ready() {
    state = 4;
    oled->clear();
    oled->print("Ready! Press Any Button!", 0);
    screen_ready();
}

void Warmup::screen_warmup() {
    operation();
    if (temperature >= pre_heat_target) {
        heater->off();
        warmup = false;
        target = target_real;
        display_cooldown();
    }
    check_cancel();
}

void Warmup::screen_cooldown() {
    operation();
    if (temperature <= target_real) {
        display_ready();
    }
    check_cancel();
}

int Warmup::screen_ready() {
    operation();
    return screen_end();
}

int Warmup::screen_exceed() {
    if (screen_end()) {
        return 2;
    }
}


