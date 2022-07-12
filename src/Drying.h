//
// Created by Dylan Ray Roodt on 08.05.2022.
//

#ifndef TECO_FILAMENT_DRYING_H
#define TECO_FILAMENT_DRYING_H

#include "preset_struct.h"
#include "Operating.h"

/* States
 * 2: Operation
*/

class Drying : public Operating {
public:
    Drying(OLED &display, Temperature &temp, Heater &heaterExt);
    void start(Preset & selected);
    int update();
private:
    void screen_drying();

    void display_drying();
};


#endif //TECO_FILAMENT_DRYING_H
