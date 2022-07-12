#include "Buzzer.h"

Buzzer::Buzzer(int pin) : Waiter() {
    buzzer = pin;
    pinMode(buzzer, OUTPUT);
}

void Buzzer::beep() {
    time_set(duration_beep);
    start();
}

void Buzzer::alarm() {
    time_set(duration_alarm);
    start();
}

void Buzzer::update() {
    if (!active) {
        return;
    }

    if (time_check()) stop();
}

void Buzzer::start() {
    time_reset();
    tone(buzzer, freq);
    active = true;
}

void Buzzer::stop() {
    noTone(buzzer);
    active = false;
}
