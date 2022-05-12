#include "Relay.h"

Relay::Relay() {
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN,0);
    off();
}

bool Relay::get_state() {
    return state;
}

void Relay::on() {
    state = 1;
    digitalWrite(RELAY_PIN,1);
}

void Relay::off() {
    state = 0;
    digitalWrite(RELAY_PIN,0);
}

void Relay::set(bool new_state) {
    if (new_state) on();
    else off();
}
