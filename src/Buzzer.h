#ifndef TECO_FILAMENT_BUZZER_H
#define TECO_FILAMENT_BUZZER_H

#include <Arduino.h>

class Buzzer {
public:
    Buzzer(int);
    void beep();
private:
    int duration = 50;
    int freq = 1000;
    int buzzer;
};


#endif //TECO_FILAMENT_BUZZER_H
