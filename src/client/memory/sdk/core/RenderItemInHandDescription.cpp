#include "RenderItemInHandDescription.hpp"

#include "../../patcher.hpp"

namespace mce::framebuilder {
    void RenderItemInHandDescription::RenderItemInHandDescription_ctor_hk(void* renderObject, void* itemFlags, void* material, void* glintTexture, void* worldMatrix, bool isDrawingUI, void* globalConstantBuffers, unsigned __int16 viewId, void* renderMetadata) {
        selaura::call_fn<&RenderItemInHandDescription::RenderItemInHandDescription_ctor_hk>(this, renderObject, itemFlags, material, glintTexture, worldMatrix, isDrawingUI, globalConstantBuffers, viewId, renderMetadata);

        this->mGlintColor = glm::vec3{0.f, 0.f, 0.3f};
        this->mGlintAlpha = 0.25f;
    }
}
