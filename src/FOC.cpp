#include "FOC.h"

FOC::FOC() {
    temperature = new Temperature();
    relay = new Relay();
    oled = new OLED();
    start_menu = new Start_Menu(*oled);
    warmup = new Warmup(*oled, *temperature, *relay);
    drying = new Drying(*oled, *temperature, *relay);

    oled->begin();
}

void FOC::begin() {
    state = 1;
    start_menu->display();
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

void FOC::internal_delay() {
    int delta = -1 * (int)(millis() - last);
    delay(loop_delay - constrain(delta, -loop_delay, 0));
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
        begin();
    }
}
