#include "Dimension.hpp"
#include "../../patcher.hpp"

float Dimension::getTimeOfDay_hk(int a1, float a2) {
    auto time = selaura::call_fn<&Dimension::getTimeOfDay_hk>(this, a1, a2);
    return time;
}