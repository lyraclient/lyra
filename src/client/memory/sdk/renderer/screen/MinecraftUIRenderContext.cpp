#include "MinecraftUIRenderContext.hpp"
#include "../../../patcher.hpp"

void MinecraftUIRenderContext::renderCustom_hk(gsl::not_null<CustomRenderComponent*> customRender, int pass, RectangleArea* renderAABB) {
    if (customRender->mOwner->name == "splash_text") {
        selaura::call_fn<&MinecraftUIRenderContext::renderCustom_hk>(this, customRender, pass, renderAABB);
        SplashTextRenderer* renderer = reinterpret_cast<SplashTextRenderer*>(customRender->renderer);

        renderer->mCurrentSplash = 0;
        renderer->mSplashes[0] = "\u00a76Selaura Client \u00a76on top!\u00a7r";
    }
    else if (customRender->mOwner->name == "hud_player") {
        selaura::call_fn<&MinecraftUIRenderContext::renderCustom_hk>(this, customRender, pass, renderAABB);
        HudPlayerRenderer* renderer = reinterpret_cast<HudPlayerRenderer*>(customRender->renderer);

        renderer->mRenderTime = 1.0f;
    }
    else if (customRender->mOwner->name == "vignette_rend") {
        selaura::call_fn<&MinecraftUIRenderContext::renderCustom_hk>(this, customRender, pass, renderAABB);
    }
    else {
        selaura::call_fn<&MinecraftUIRenderContext::renderCustom_hk>(this, customRender, pass, renderAABB);
    }
}