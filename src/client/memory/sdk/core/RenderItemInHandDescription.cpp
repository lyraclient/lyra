#include "RenderItemInHandDescription.hpp"
#include "../../patcher.hpp"
#include "../../../client.hpp"
#include "../../../event/event_types.hpp"

namespace mce::framebuilder {
    void RenderItemInHandDescription::RenderItemInHandDescription_ctor_hk(void* renderObject, void* itemFlags, void* material, void* glintTexture, void* worldMatrix, bool isDrawingUI, void* globalConstantBuffers, unsigned __int16 viewId, void* renderMetadata) {
        selaura::call_fn<&RenderItemInHandDescription::RenderItemInHandDescription_ctor_hk>(this, renderObject, itemFlags, material, glintTexture, worldMatrix, isDrawingUI, globalConstantBuffers, viewId, renderMetadata);

        selaura::RenderItemInHandDescription_event event{ this->mGlintColor, this->mGlintAlpha };
        auto& ev = selaura::get()->get<selaura::event_manager>();
        ev.dispatch<selaura::RenderItemInHandDescription_event>(event);

        this->mGlintColor = event.color;
        this->mGlintAlpha = event.alpha;
    }
}
