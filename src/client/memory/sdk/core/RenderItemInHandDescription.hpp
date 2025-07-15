#pragma once
#include <cstddef>
#include <glm/glm.hpp>

namespace mce::framebuilder {
    struct RenderItemInHandDescription {
        std::byte pad[0x8C];
        glm::vec3 mGlintColor;
        float mGlintAlpha;
        glm::vec3 mOverlayColor;
        float mOverlayAlpha;
        glm::vec3 mChangeColor;
        float mChangeAlpha;
        glm::vec3 mMultiplicativeTintColor;
        float mMultiplicativeTintColorAlpha;

        void RenderItemInHandDescription_ctor_hk(void* renderObject, void* itemFlags, void* material, void* glintTexture, void* worldMatrix, bool isDrawingUI, void* globalConstantBuffers, unsigned __int16 viewId, void* renderMetadata);
    };
};