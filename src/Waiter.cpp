#include "Waiter.h"

Waiter::Waiter() {

}

bool Waiter::time_check() {
    return millis() - last >= wait_time;
}

void Waiter::time_set(int time) {
    wait_time = time;
}

void Waiter::time_reset() {
    last = millis();
}
