#include "Heater.h"


Heater::Heater(Temperature &temp_ext) : Waiter() {
    relay = new Relay();
    temp = &temp_ext;
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
    check_temp_delta();

    if (heating) {
        time_set(cooling_time);
    } else {
        time_set(heating_time);
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

void Heater::set_pwm(int p, float dc) {
    period = p;
    duty_cycle = dc;
    calculate_times();
}

void Heater::calculate_times() {
    heating_time = int(period * duty_cycle * 1000);
    cooling_time = int(period * (1 - duty_cycle) * 1000);
}

void Heater::check_temp_delta() {
    float delta = target - temp->get_temperature();
    if (delta < 0) {
        delta = 0;
    }

    for (auto element : preset_heater.list) {
        if (delta >= element.delta) {
            set_pwm(element.period, element.duty_cycle);
            return;
        }
    }
}

void Heater::set_new_target(float new_target) {
    target = new_target;
}
