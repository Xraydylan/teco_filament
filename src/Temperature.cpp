#include "Temperature.h"

Temperature::Temperature() {
    ds = new DS18B20(WIRE_PIN);
}

void Temperature::begin() {
    // Setup resolution
    // Resolution: 9, 10, 11, or 12 bit corresponding to increments of 0.5°C, 0.25°C, 0.125°C, 0.0625°C
    // Delay 93.75, 187.5, 375, 750 ms
    ds->setResolution(resolution);
    pause = get_delay();
}

void Temperature::update() {
    if (reading) check_end_reading();
    else start_reading();
}


float Temperature::get_temperature() {
    return temperature;
}

int Temperature::get_delay() {
    switch (ds->getResolution()) {
        case RES_9_BIT:
            return CONV_TIME_9_BIT;
        case RES_10_BIT:
            return CONV_TIME_10_BIT;
        case RES_11_BIT:
            return CONV_TIME_11_BIT;
        case RES_12_BIT:
            return CONV_TIME_12_BIT;
    }
    return 0;
}

void Temperature::start_reading() {
    ds->selectNext();
    ds->start_getTempC();
    reading = true;
    last = millis();
}

void Temperature::check_end_reading() {
    if (ds->getPowerMode()) {
        if (ds->check_power_mode()) {
            // This has no use
            // calc_temp();
            // reading = false;
        }
    } else {
        if  (millis() - last >= pause) {
            calc_temp();
            reading = false;
        }
    }
}

void Temperature::calc_temp() {
    temp_array[slot] = ds->stop_get_TempC();
    if (slot) {
        temperature = (temp_array[0] + temp_array[1]) / 2;
    }
    slot = !slot;
}
