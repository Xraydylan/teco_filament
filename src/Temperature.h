#ifndef TECO_FILAMENT_TEMPERATURE_H
#define TECO_FILAMENT_TEMPERATURE_H

#include "pins.h"
#include "DS18B20.h"

#define CONNECTION_ERROR_CODE 85
#define INIT_TEMP 999

class Temperature {
public:
    Temperature();
    void begin();
    void update();
    void set_resolution();
    float get_temperature();
private:
    DS18B20* ds;

    // select fitting resolution
    int resolution = 11;
    bool reading = false;
    bool slot = false;
    unsigned long int last;
    int pause;
    float temperature = INIT_TEMP;
    float temp_array[2];

    float temp_jump_delta = 10;
    bool error_check[2] = {false, false};

    void check_end_reading();
    void start_reading();
    int get_delay();
    void calc_temp();
    bool single_error_detection(float temperature);
};


#endif //TECO_FILAMENT_TEMPERATURE_H
