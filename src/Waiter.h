#ifndef TECO_FILAMENT_WAITER_H
#define TECO_FILAMENT_WAITER_H

#include <Arduino.h>

class Waiter {
public:
    Waiter();
    bool time_check();
    void time_set(int time);
    void time_reset();
private:
    int wait_time = 0;
    unsigned long last = 0;
};


#endif //TECO_FILAMENT_WAITER_H
