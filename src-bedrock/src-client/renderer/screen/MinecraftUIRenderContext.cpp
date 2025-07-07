#include "MinecraftUIRenderContext.hpp"
#include "../../../../../src-client/core/instance.hpp"
#include "src-client/gui/controls/renderers/HudPlayerRenderer.hpp"

void MinecraftUIRenderContext::renderCustom_hk(gsl::not_null<CustomRenderComponent*> customRender, int pass, RectangleArea* renderAABB) {
    auto ofunc = selaura::trampolines::MinecraftUIRenderContext_renderCustom;

    if (customRender->mOwner->name == "splash_text") {
        (this->*ofunc)(customRender, pass, renderAABB);
        SplashTextRenderer* renderer = reinterpret_cast<SplashTextRenderer*>(customRender->renderer);

        std::vector<std::string> splashes = { "\u00a76Selaura Client \u00a76on top!\u00a7r" };
        renderer->mCurrentSplash = 0;
        renderer->mSplashes = std::move(splashes);
    }
    else if (customRender->mOwner->name == "hud_player") {
        (this->*ofunc)(customRender, pass, renderAABB);
        HudPlayerRenderer* renderer = reinterpret_cast<HudPlayerRenderer*>(customRender->renderer);

        renderer->mRenderTime = 1.0f;
    }
    else if (customRender->mOwner->name == "vignette_rend") {
        (this->*ofunc)(customRender, pass, renderAABB);
    }
    else {
        (this->*ofunc)(customRender, pass, renderAABB);
    }
}
