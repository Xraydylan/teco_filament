#ifndef TECO_FILAMENT_PRESET_STRUCT_H
#define TECO_FILAMENT_PRESET_STRUCT_H

struct Preset {
    char name[10];
    float duration;
    float temperature;
};

struct Heating {
    int period;
    float duty_cycle;
    int delta;
};

#endif //TECO_FILAMENT_PRESET_STRUCT_H
