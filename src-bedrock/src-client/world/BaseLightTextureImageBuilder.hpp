#pragma once
#include <memory>
#include <cstddef>
#include <cstdint>

#include "../../../src-client/memory/patterns.hpp"

struct BaseLightData {
    std::byte pad[0x24];
    bool mNightvisionActive;
    std::byte pad2[0x03];
    float mNightvisionScale;
};

struct BaseLightTextureImageBuilder {
    std::unique_ptr<BaseLightData> createBaseLightTextureData_hk(void* clientInstance, const BaseLightData& base_light_data);
};