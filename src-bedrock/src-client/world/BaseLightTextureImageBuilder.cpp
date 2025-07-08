#include "BaseLightTextureImageBuilder.hpp"
#include "../../../../../src-client/core/instance.hpp"

std::unique_ptr<BaseLightData> BaseLightTextureImageBuilder::createBaseLightTextureData_hk(void* clientInstance, const BaseLightData* base_light_data) {
    auto ofunc = selaura::trampolines::BaseLightTextureImageBuilder_createBaseLightTextureData;
    auto data = (this->*ofunc)(clientInstance, base_light_data);

    data->mNightvisionActive = true;
    data->mNightvisionScale = 1.0f;

    return data;
}


std::unique_ptr<BaseLightData> NetherLightTextureImageBuilder::createBaseLightTextureData_hk(void* clientInstance, const BaseLightData* base_light_data) {
    auto ofunc = selaura::trampolines::NetherLightTextureImageBuilder_createBaseLightTextureData;
    auto data = (this->*ofunc)(clientInstance, base_light_data);

    data->mNightvisionActive = true;
    data->mNightvisionScale = 1.0f;

    return data;
}
