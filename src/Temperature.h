#ifndef TECO_FILAMENT_TEMPERATURE_H
#define TECO_FILAMENT_TEMPERATURE_H

#include "pins.h"
#include "DS18B20.h"

class Temperature {
public:
    Temperature();
    void begin();
    void update();
    float get_temperature();
private:
    DS18B20* ds;

    // select fitting resolution
    int resolution = 11;
    bool reading = false;
    bool slot = false;
    unsigned long int last;
    int pause;
    float temperature = 999;
    float temp_array[2];

    void check_end_reading();
    void start_reading();
    int get_delay();
    void calc_temp();
};


#endif //TECO_FILAMENT_TEMPERATURE_H
