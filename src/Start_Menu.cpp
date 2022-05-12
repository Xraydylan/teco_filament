#include "Start_Menu.h"

// Later: add adjustable options

Start_Menu::Start_Menu(OLED &display) {
    oled = &display;
}

void Start_Menu::display() {
    state = 0;
    oled->clear();
    oled->print("Filament Dryer select", 0);
    draw_preset_name();
}

int Start_Menu::update() {
    switch (state) {
        case 0:
            start_screen();
            break;
        case 1:
            return selected_screen();
            break;
        default:
            break;
    }
    return 0;
}

Preset * Start_Menu::get_selected() {
    return selected;
}

void Start_Menu::start_screen() {
    if (oled->pressed_A()) {
        display_selection();
    }
    if (oled->pressed_B()) {
        index++;
        if (index >= Preset_data::count) index = 0;
        draw_preset_name();
    }
    if (oled->pressed_C()) {
        index--;
        if (index < 0) index = Preset_data::count - 1;
        draw_preset_name();
    }
}

int Start_Menu::selected_screen() {
    if (oled->pressed_A()) {
        selected = &preset.list[index];
        state = 0;
        return 1;
    }
    if (oled->pressed_B()) {
        // Maybe change options
    }
    if (oled->pressed_C()) {
        display();
    }

    return 0;
}

void Start_Menu::display_selection() {
    state = 1;
    Preset *select = &preset.list[index];
    oled->clear();
    oled->print("Selected:",0);
    oled->print("Material: " + String(select->name),2);
    oled->print("Temperature: " + String(select->temperature,2) + "C",3);
    oled->print("Duration: " + String(select->duration,2) + "h",4);
    oled->draw();
}


void Start_Menu::draw_preset_name() {
    oled->print(preset.list[index].name, 3);
    oled->print("(A = Select; B = Up; C = Down/Cancel)", 6);
    oled->draw();
}

