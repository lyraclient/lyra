#include "SplashTextRenderer.hpp"
#include <spdlog/spdlog.h>
#include "../../../../../src-client/core/instance.hpp"

void SplashTextRenderer::render_hk(void* ctx, void* clientInstance, void* owner, int pass, void* renderAABB) {
    auto ofunc = selaura::trampolines::SplashTextRenderer_render;
    (this->*ofunc)(ctx, clientInstance, owner, pass, renderAABB);
}