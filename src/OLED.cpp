#include "OLED.h"

OLED::OLED() {

}

void OLED::begin() {
    ButtonA.setup(ButtonPinA);
    ButtonB.setup(ButtonPinB);
    ButtonC.setup(ButtonPinC);

    buzzer = new Buzzer(Buzzer_Pin);

    display = new Adafruit_SH1107(64, 128, &Wire);
    delay(100);

    display->begin(0x3C, true);
    display->display();
    delay(500);
    display->clearDisplay();
    display->display();

    display->setRotation(1);
    display->setTextSize(1);
    display->setTextColor(SH110X_WHITE);
    display->setCursor(0,0);
}

void OLED::update() {
    button_flag = false;
    ButtonA.update();
    ButtonB.update();
    ButtonC.update();

    if (any()) {
        beep();
    }
    buzzer->update();
}

void OLED::print(String data, int line) {
    if (line >= lines) return;
    show[line] = data;
}

void OLED::print_direct(String data, int line) {
    if (line >= lines) return;
    show[line] = data;
    draw();
}

void OLED::clear() {
    for (auto & i : show) {
        i = "";
    }
    display->clearDisplay();
    display->display();
}

void OLED::draw() {
    display->clearDisplay();
    display->setCursor(0,0);
    for (const auto & i : show) {
        display->println(i);
    }
    display->display();
}

bool OLED::pressed_A() {
    if (button_flag) {
        return false;
    }
    return ButtonA.pressed();
}

bool OLED::pressed_B() {
    if (button_flag) {
        return false;
    }
    return ButtonB.pressed();
}

bool OLED::pressed_C() {
    if (button_flag) {
        return false;
    }
    return ButtonC.pressed();
}

bool OLED::any() {
    if (button_flag) {
        return false;
    }
    return pressed_A() || pressed_B() || pressed_C();
}

void OLED::set_button_flag() {
    button_flag = true;
}

void OLED::beep() {
    buzzer->beep();
}

void OLED::alarm() {
    buzzer->alarm();
}


