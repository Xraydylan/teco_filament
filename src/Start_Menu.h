#ifndef TECO_FILAMENT_START_MENU_H
#define TECO_FILAMENT_START_MENU_H

#include "preset.h"
#include "preset_struct.h"
#include "OLED.h"

class Start_Menu {
public:
    Start_Menu(OLED &display);
    void display();
    int update();
    Preset * get_selected();
private:
    OLED* oled;
    int index = 0;
    int state = 0;

    Preset_data preset;

    Preset * selected;

    void start_screen();
    int selected_screen();
    void display_selection();
    void draw_preset_name();
};


#endif //TECO_FILAMENT_START_MENU_H
