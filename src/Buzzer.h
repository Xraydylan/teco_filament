#ifndef TECO_FILAMENT_BUZZER_H
#define TECO_FILAMENT_BUZZER_H

#include <Arduino.h>
#include "Waiter.h"

class Buzzer : public Waiter {
public:
    Buzzer(int);
    void beep();
    void alarm();
    void update();
    void stop_alarm();
private:
    int duration_beep = 50;
    int duration_alarm = 1000;
    int freq = 1000;
    int buzzer;

    bool active = false;
    bool alarm_on = false;

    void start();
    void stop();
};


#endif //TECO_FILAMENT_BUZZER_H
