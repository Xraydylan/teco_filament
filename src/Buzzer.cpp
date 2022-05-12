#include "Buzzer.h"

Buzzer::Buzzer(int pin) {
    buzzer = pin;
    pinMode(buzzer, OUTPUT);
}

void Buzzer::beep() {
    tone(buzzer, freq);
    delay(duration);
    noTone(buzzer);
}
