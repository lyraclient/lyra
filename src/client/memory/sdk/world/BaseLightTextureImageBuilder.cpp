#include "BaseLightTextureImageBuilder.hpp"
#include "../../patcher.hpp"
#include "../../../client.hpp"
#include "../../../event/event_types.hpp"

std::unique_ptr<BaseLightData> BaseLightTextureImageBuilder::createBaseLightTextureData_hk(void* clientInstance, const BaseLightData* base_light_data) {
    auto data = selaura::call_fn<&BaseLightTextureImageBuilder::createBaseLightTextureData_hk>(this, clientInstance, base_light_data);

    selaura::BaseLightTextureImageBuilder_event event{ data->mNightvisionActive, data->mNightvisionScale };
    auto& ev = selaura::get()->get<selaura::event_manager>();
    ev.dispatch<selaura::BaseLightTextureImageBuilder_event>(event);

    data->mNightvisionActive = event.mNightvisionActive;
    data->mNightvisionScale = event.mNightvisionScale;

    return std::move(data);
}

std::unique_ptr<BaseLightData> NetherLightTextureImageBuilder::createBaseLightTextureData_hk(void* clientInstance, const BaseLightData* base_light_data) {
    auto data = selaura::call_fn<&NetherLightTextureImageBuilder::createBaseLightTextureData_hk>(this, clientInstance, base_light_data);

    selaura::BaseLightTextureImageBuilder_event event{ data->mNightvisionActive, data->mNightvisionScale };
    auto& ev = selaura::get()->get<selaura::event_manager>();
    ev.dispatch<selaura::BaseLightTextureImageBuilder_event>(event);

    data->mNightvisionActive = event.mNightvisionActive;
    data->mNightvisionScale = event.mNightvisionScale;

    return std::move(data);
}