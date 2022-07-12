//
// Created by Dylan Ray Roodt on 10.07.2022.
//

#include "Heater.h"


Heater::Heater() : Waiter() {
    relay = new Relay();
}

void Heater::begin() {
    relay->off();
    heating = false;
    state = false;
    time_reset();
}

void Heater::update() {
    if (!state) {
        relay->off();
        return;
    }

    if (!time_check()) {
        return;
    }
    time_reset();

    if (heating) {
        time_set(cooling_time * 1000);
    } else {
        time_set(heating_time * 1000);
    }
    heating = !heating;
    relay->set(heating);
}

void Heater::on() {
    set(true);
}

void Heater::off() {
    set(false);
    heating = false;
}

void Heater::set(bool new_state) {
    state = new_state;
};

bool Heater::get_state() {
    return state;
}