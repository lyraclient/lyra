#include "ScreenView.hpp"
#include "../../patcher.hpp"
#include "../renderer/screen/MinecraftUIRenderContext.hpp"

void ScreenView::setupAndRender_hk(void* renderContext) {
    static bool once = false;
    if (!once && renderContext) {
        selaura::patch_vtable_fn<&MinecraftUIRenderContext::renderCustom_hk>(renderContext, 26);
        once = true;
    }

    selaura::call_fn<&ScreenView::setupAndRender_hk>(this, renderContext);
}
