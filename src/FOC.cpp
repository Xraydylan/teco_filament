#include "FOC.h"

FOC::FOC() {
    temperature = new Temperature();

    heater = new Heater(*temperature);

    oled = new OLED();
    start_menu = new Start_Menu(*oled);
    warmup = new Warmup(*oled, *temperature, *heater);
    drying = new Drying(*oled, *temperature, *heater);

    delay(50);
    oled->begin();
    temperature->begin();
}

void FOC::begin() {
    state = 1;
    start_menu->display();
    heater->begin();
}

void FOC::update() {
    oled->update();
    switch(state) {
        case 1:
            start_state();
            break;
        case 2:
            warmup_state();
            break;
        case 3:
            drying_state();
            break;
        default:
            break;
    }
    temperature->update();
    heater->update();
    internal_delay();
}

void FOC::start_state() {
    int rst = start_menu->update();

    if (rst) {
        selected = start_menu->get_selected();
        warmup->start(*selected);
        state = 2;
    }
}

// Needs testing?
void FOC::internal_delay() {
    int delta = (int)(millis() - last);
    delay(loop_delay - constrain(delta, 0, loop_delay));
    last = millis();
}

void FOC::warmup_state() {
    int rst = warmup->update();

    if (rst == 1) {
        drying->start(*selected);
        state = 3;
    } else if (rst == 2) {
        begin();
    }
}

void FOC::drying_state() {
    int rst = drying->update();

    if (rst) {
        oled->alarm();
        begin();
    }
}
