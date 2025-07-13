#include "BaseLightTextureImageBuilder.hpp"
#include "../../patcher.hpp"

std::unique_ptr<BaseLightData> BaseLightTextureImageBuilder::createBaseLightTextureData_hk(void* clientInstance, const BaseLightData* base_light_data) {
    auto data = selaura::call_fn<&BaseLightTextureImageBuilder::createBaseLightTextureData_hk>(this, clientInstance, base_light_data);

    data->mNightvisionActive = true;
    data->mNightvisionScale = 1.0f;

    return data;
}

std::unique_ptr<BaseLightData> NetherLightTextureImageBuilder::createBaseLightTextureData_hk(void* clientInstance, const BaseLightData* base_light_data) {
    auto data = selaura::call_fn<&NetherLightTextureImageBuilder::createBaseLightTextureData_hk>(this, clientInstance, base_light_data);

    data->mNightvisionActive = true;
    data->mNightvisionScale = 1.0f;

    return data;
}