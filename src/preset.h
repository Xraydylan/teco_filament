#ifndef TECO_FILAMENT_PRESET_H
#define TECO_FILAMENT_PRESET_H

#include "preset_struct.h"

class Preset_data {
public:
    // Duration is in Hours
    Preset PLA = {"PLA", 5, 45};
    Preset ABS = {"ABS", 5, 80};
    Preset PVA = {"PVA", 5, 45};
    Preset TPU = {"TPU", 4, 60};
    Preset PETG = {"PETG", 5, 65};
    Preset Nylon = {"Nylon", 2, 80};

    Preset Test = {"Test", 0.06, 40};

    static const int count = 7;
    Preset list[count] = {PLA, ABS, PVA, TPU, PETG, Nylon, Test};
};

class Preset_heater {
public:
    Heating D5 = {30, 0.5, 20};
    Heating D4 = {30, 0.4, 15};
    Heating D3 = {20, 0.33, 10};
    Heating D2 = {20, 0.25, 5};
    Heating D1 = {10, 0.2, 1};
    Heating D0 = {10, 0.1, 0};

    static const int count = 6;
    Heating list[count] = {D5,D4,D3, D2, D1, D0};
};


#endif //TECO_FILAMENT_PRESET_H
