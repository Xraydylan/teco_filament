#ifndef TECO_FILAMENT_PRESET_H
#define TECO_FILAMENT_PRESET_H

#include "preset_struct.h"

class Preset_data {
public:
    // Duration is in Hours
    Preset PLA = {"PLA", 5, 45};
    Preset ABS = {"ABS", 5, 80};
    Preset Nylon = {"Nylon", 2, 80};

    Preset Test = {"Test", 0.06, 40};

    static const int count = 4;
    Preset list[count] = {PLA, ABS, Nylon, Test};
};




//struct Preset presets[preset_count] = {PLA, ABS, Nylon};
//struct Preset *presets[preset_count] = {&PLA, &ABS, &Nylon};


#endif //TECO_FILAMENT_PRESET_H
