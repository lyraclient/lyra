#include "Dimension.hpp"
#include "../../patcher.hpp"

void Dimension::Dimension_ctor_hk(void *level, void *dimId, DimensionHeightRange heightRange, void *callbackContext, std::string *name) {
    if (heightRange.mMax == 128) {
        heightRange.mMax = 256; // nether roof fix
    }

    selaura::call_fn<&Dimension::Dimension_ctor_hk>(this, level, dimId, heightRange, callbackContext, name);
}


float Dimension::getTimeOfDay_hk(int time, float a) {
    // i need to make it so you can speed up time by pressing a key or setting in mod menu
    // just do time the first int * the speed
    return selaura::call_fn<&Dimension::getTimeOfDay_hk>(this, time, a);
}
