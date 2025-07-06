#include "ScreenView.hpp"
#include "../../../../../src-client/core/instance.hpp"

void ScreenView::setupAndRender_hk(MinecraftUIRenderContext* ctx) {
    auto inst = selaura::get();
    auto ofunc = selaura::trampolines::ScreenView_setupAndRender;

    static bool once = false;
    if (!once && ctx) {
        void** mcuirc_vtable = *reinterpret_cast<void***>(ctx);

        inst->get<selaura::patch_manager>().register_hook(
            mcuirc_vtable[26],
            &MinecraftUIRenderContext::renderCustom_hk,
            reinterpret_cast<void**>(&selaura::trampolines::MinecraftUIRenderContext_renderCustom)
        );
    }

    (this->*ofunc)(ctx);
}
