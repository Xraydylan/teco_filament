#ifndef TECO_FILAMENT_BUZZER_H
#define TECO_FILAMENT_BUZZER_H

#include <Arduino.h>

class Buzzer {
public:
    Buzzer(int);
    void beep();
    void alarm();
    void update();
private:
    int duration_beep = 50;
    int duration_alarm = 1000;
    int freq = 1000;
    int buzzer;

    int wait_time = 0;
    unsigned long int last = 0;

    void start();
    void stop();
};


#endif //TECO_FILAMENT_BUZZER_H
