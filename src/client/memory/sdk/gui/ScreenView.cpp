#include "ScreenView.hpp"
#include "../../patcher.hpp"
#include "../renderer/screen/MinecraftUIRenderContext.hpp"

void ScreenView::setupAndRender_hk(void* renderContext) {
    static bool once = false;
    if (!once && renderContext) {
        void** mcuirc_vtable = *reinterpret_cast<void***>(renderContext);

        selaura::patch_fn<&MinecraftUIRenderContext::renderCustom_hk>(mcuirc_vtable[26]);
        once = true;
    }

    selaura::call_fn<&ScreenView::setupAndRender_hk>(this, renderContext);
}
