#ifndef TECO_FILAMENT_OLED_H
#define TECO_FILAMENT_OLED_H

#include "pins.h"
#include "DButton.h"
#include "Buzzer.h"

#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

class OLED {
public:
    OLED();
    void begin();
    void update();
    void print(String data, int line);
    void print_direct(String data, int line);
    void draw();
    void clear();
    bool pressed_A();
    bool pressed_B();
    bool pressed_C();
    bool any();
    void set_button_flag();
    void reset();

    void beep();
    void alarm();

private:
    U8G2_SH1106_128X64_NONAME_1_HW_I2C * display;
    Buzzer* buzzer;

    bool button_flag = false;

    static const int lines = 8;
    const int pix_count = 7;
    const int pix_separation = 2;

    String show[lines];

    DButton ButtonA;
    DButton ButtonB;
    DButton ButtonC;

    int line_to_pixel(int line);
};


#endif //TECO_FILAMENT_OLED_H
