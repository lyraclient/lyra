#include "Dimension.hpp"
#include "../../patcher.hpp"
#include "../../../client.hpp"
#include "../../../event/event_types.hpp"

void Dimension::Dimension_ctor_hk(void *level, void *dimId, DimensionHeightRange heightRange, void *callbackContext, std::string *name) {
    if (heightRange.mMax == 128) {
        heightRange.mMax = 256; // nether roof fix
    }

    selaura::call_fn<&Dimension::Dimension_ctor_hk>(this, level, dimId, heightRange, callbackContext, name);
}


float Dimension::getTimeOfDay_hk(int time, float a) {
    selaura::getTimeOfDay_event event{ time, -1 };
    auto& ev = selaura::get()->get<selaura::event_manager>();
    ev.dispatch<selaura::getTimeOfDay_event>(event);

    if (event.overriden_time != -1) {
        return event.overriden_time;
    } else {
        return selaura::call_fn<&Dimension::getTimeOfDay_hk>(this, event.time, a);
    }
}
