#pragma once
#include <string>

struct DimensionHeightRange {
    __int16 mMin;
    __int16 mMax;
};


struct Dimension {
    float getTimeOfDay_hk(int time, float a);
};

void Dimension_ctor_hk(Dimension* thisptr, void* level, void* dimId, DimensionHeightRange heightRange, void* callbackContext, std::string* name);