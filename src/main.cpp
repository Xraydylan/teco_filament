#include <Arduino.h>
#include "Adafruit_I2CDevice.h"

#include "FOC.h"

FOC * app;

void setup() {
    app = new FOC();
    app->begin();
}

void loop() {
    app->update();
}





