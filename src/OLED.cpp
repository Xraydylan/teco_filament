#include "OLED.h"

OLED::OLED() {

}

void OLED::begin() {
    pinMode(OLED_RESET, OUTPUT);

    ButtonA.setup(ButtonPinA);
    ButtonB.setup(ButtonPinB);
    ButtonC.setup(ButtonPinC);

    buzzer = new Buzzer(Buzzer_Pin);

    reset();
    display = new U8G2_SH1106_128X64_NONAME_1_HW_I2C(U8G2_R0);
    display->begin();
    delay(50);

}

void OLED::reset() {
    digitalWrite(OLED_RESET, LOW);
    delay(200);
    digitalWrite(OLED_RESET, HIGH);
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
}

void OLED::draw() {
    display->firstPage();

    do {
        display->setFont(u8g2_font_profont11_mr);

        for (int i = 0; i < lines; i++) {
            display->drawStr(0, line_to_pixel(i), show[i].c_str());
        }
    } while ( display->nextPage() );
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
    bool flag = pressed_A() || pressed_B() || pressed_C();
    if (flag) buzzer->stop_alarm();
    return flag;
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

int OLED::line_to_pixel(int line) {
    return (1+line) * (pix_count + pix_separation);
}
