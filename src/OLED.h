#ifndef TECO_FILAMENT_OLED_H
#define TECO_FILAMENT_OLED_H

#include "pins.h"
#include "DButton.h"
#include "Buzzer.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SH110X.h"

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

    void beep();
    void alarm();

private:
    Adafruit_SH1107 * display;
    Buzzer* buzzer;

    bool button_flag = false;

    static const int lines = 8;
    String show[lines];

    DButton ButtonA;
    DButton ButtonB;
    DButton ButtonC;
};


#endif //TECO_FILAMENT_OLED_H
