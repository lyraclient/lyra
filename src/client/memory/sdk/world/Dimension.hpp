#pragma once
#include <string>

struct DimensionHeightRange {
    __int16 mMin;
    __int16 mMax;
};


struct Dimension {
    void Dimension_ctor_hk(void* level, void* dimId, DimensionHeightRange heightRange, void* callbackContext, std::string* name);
    float getTimeOfDay_hk(int time, float a);
};