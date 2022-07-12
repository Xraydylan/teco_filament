#include "Operating.h"

Operating::Operating(OLED &oled_ext, Temperature &temp_ext, Heater &heater_ext) : Waiter() {
    oled = &oled_ext;
    temp = &temp_ext;
    heater = &heater_ext;

    time_set(update_delay);
}

void Operating::draw_stats() {
    int h = (int)((duration_ms-delta) / 1000 / 3600);
    int min = (int)((duration_ms-delta) / 1000 / 60 % 60);
    oled->print("Material: " + String(selected_preset->name), 2);
    oled->print("Temperature: " + String(temperature, 2) + "C", 3);
    oled->print("Target: " + String(target, 2) + "C", 4);
    oled->print("Remaining: " + String(h) + "h " + String(min) + "min", 6);

    oled->draw();
}

void Operating::read_temp() {
    temperature = temp->get_temperature();
}

bool Operating::determine_relay_state() {
    if (heater->get_state()) {
        return (temperature <= target + margin);
    }
    return temperature <= target - margin;
}

bool Operating::determine_end() {
    delta = millis() - start_time;
    return delta >= duration_ms;
}


void Operating::display_cancel() {
    state = 1;
    oled->clear();
    oled->print_direct("Cancel?", 1);
}

void Operating::display_end(int end_type) {
    state = 0;
    heater->off();
    oled->clear();
    switch (end_type) {
        case 0:
            oled->print("Drying complete!", 0);
            oled->print("Remove Filament", 1);
            oled->print("(press any button)", 5);
            break;
        case 1:
            oled->print("Preheating time exceeded!", 1);
            oled->print("(press any button)", 5);
            break;
        default:
            break;
    }
    oled->draw();
}

int Operating::screen_cancel() {
    if (oled->pressed_A()) {
        return 1;
    }
    if (oled->pressed_C()) {
        return 2;
    }
    return 0;
}

int Operating::screen_end() {
    return oled->any();
}

unsigned long int Operating::h_to_millis(float num) {
    return (unsigned long int)(num * 60 * 60) * 1000;
}

void Operating::check_cancel() {
    if (oled->pressed_C()) {
        display_cancel();
    }
}

void Operating::operation(bool stats) {
    if (!time_check()) {
        return;
    }
    time_reset();
    if (determine_end()) {
        display_end();
        return;
    }
    read_temp();
    bool relay_state = determine_relay_state();
    heater->set(relay_state);
    if (stats) {
        draw_stats();
    }
    check_cancel();
}
