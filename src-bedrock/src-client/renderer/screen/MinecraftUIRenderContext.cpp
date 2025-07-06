#include "MinecraftUIRenderContext.hpp"
#include "../../../../../src-client/core/instance.hpp"
#include "src-client/gui/controls/renderers/HudPlayerRenderer.hpp"

void MinecraftUIRenderContext::renderCustom_hk(gsl::not_null<CustomRenderComponent*> customRender, int pass, RectangleArea* renderAABB) {
    auto ofunc = selaura::trampolines::MinecraftUIRenderContext_renderCustom;
    (this->*ofunc)(customRender, pass, renderAABB);

    if (customRender->mOwner->name == "splash_text") {
        SplashTextRenderer* renderer = reinterpret_cast<SplashTextRenderer*>(customRender->renderer);

        std::vector<std::string> splashes = { "\u00a76Selaura Client \u00a76on top!\u00a7r" };
        renderer->mCurrentSplash = 0;
        renderer->mSplashes = std::move(splashes);
    }

    if (customRender->mOwner->name == "hud_player") {
        HudPlayerRenderer* renderer = reinterpret_cast<HudPlayerRenderer*>(customRender->renderer);

        //renderer->timeToClose = 1.0f; makes paperdoll never go away
    }
}
