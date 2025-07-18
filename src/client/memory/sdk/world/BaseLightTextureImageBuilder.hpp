#pragma once
#include <memory>

#include "../core/math/Color.hpp"

struct BaseLightData {
    mce::Color mSunriseColor;
    float mGamma;
    float mSkyDarken;
    int mDimensionType;
    float mDarkenWorldAmount;
    float mPreviousDarkenWorldAmount;
    bool mNightvisionActive;
    float mNightvisionScale;
    bool mUnderwaterVision;
    float mUnderwaterScale;
    float mSkyFlashTime;
};

struct BaseLightTextureImageBuilder {
    std::unique_ptr<BaseLightData> createBaseLightTextureData_hk(void* clientInstance, const BaseLightData* base_light_data);
};

struct NetherLightTextureImageBuilder {
    std::unique_ptr<BaseLightData> createBaseLightTextureData_hk(void* clientInstance, const BaseLightData* base_light_data);
};