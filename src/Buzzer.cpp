#include "Buzzer.h"

Buzzer::Buzzer(int pin) {
    buzzer = pin;
    pinMode(buzzer, OUTPUT);
}

void Buzzer::beep() {
    wait_time = duration_beep;
    start();
}

void Buzzer::alarm() {
    wait_time = duration_alarm;
    start();
}

void Buzzer::update() {
    if (millis() - last >= wait_time) stop();
}

void Buzzer::start() {
    last = millis();
    tone(buzzer, freq);
}

void Buzzer::stop() {
    noTone(buzzer);
}
