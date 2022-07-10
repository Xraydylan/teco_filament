#include "Temperature.h"

Temperature::Temperature() {
    delay(250);
    ds = new DS18B20(WIRE_PIN);
}

void Temperature::begin() {
    // Setup resolution
    // Resolution: 9, 10, 11, or 12 bit corresponding to increments of 0.5°C, 0.25°C, 0.125°C, 0.0625°C
    // Delay 93.75, 187.5, 375, 750 ms
    set_resolution();
    pause = get_delay();
}

void Temperature::update() {
    if (reading) check_end_reading();
    else start_reading();
}

void Temperature::set_resolution() {
    while (ds->selectNext()) {
        ds->setResolution(resolution);
    }
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
            // I am a fucking idiot
            calc_temp();
            reading = false;
        }
    } else {
        if  (millis() - last >= pause) {
            calc_temp();
            reading = false;
        }
    }
}

void Temperature::calc_temp() {
    float temp = ds->stop_get_TempC();

    if (single_error_detection(temp)) {
        return;
    }
    error_check[slot] = false;

    temp_array[slot] = temp;
    if (slot) {
        temperature = (temp_array[0] + temp_array[1]) / 2;
    }
    slot = !slot;

}

bool Temperature::single_error_detection(float temp) {
    float previous = temp_array[slot];
    float delta = abs(temp - previous);

    // Check for init temperature
    if (temperature == INIT_TEMP) {
        return false;
    }

    // Check for small jump in temperature
    if (delta < temp_jump_delta) {
        return false;
    }

    // Check for not error code
    if (temperature != CONNECTION_ERROR_CODE) {
        return false;
    }

    // Check if last value was also error
    if (error_check[slot]) {
        return false;
    }

    error_check[slot] = true;
    return true;
}