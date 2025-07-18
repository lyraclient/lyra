#include "MinecraftUIRenderContext.hpp"
#include "../../../patcher.hpp"
#include "../../../../client.hpp"
#include "../../../../event/event_types.hpp"

void MinecraftUIRenderContext::renderCustom_hk(gsl::not_null<CustomRenderComponent*> customRender, int pass, RectangleArea* renderAABB) {
    selaura::RenderCustom_event event{ customRender };
    auto& ev = selaura::get()->get<selaura::event_manager>();
    ev.dispatch<selaura::RenderCustom_event>(event);
    if (customRender->mOwner->name == "splash_text") {
        selaura::call_fn<&MinecraftUIRenderContext::renderCustom_hk>(this, customRender, pass, renderAABB);
        SplashTextRenderer* renderer = reinterpret_cast<SplashTextRenderer*>(customRender->renderer);

        renderer->mCurrentSplash = 0;
        renderer->mSplashes[0] = "\u00a76Selaura Client \u00a76on top!\u00a7r";
    }
    else if (customRender->mOwner->name == "vignette_rend") {
        selaura::call_fn<&MinecraftUIRenderContext::renderCustom_hk>(this, customRender, pass, renderAABB);
    }
    else {
        selaura::call_fn<&MinecraftUIRenderContext::renderCustom_hk>(this, customRender, pass, renderAABB);
    }
}