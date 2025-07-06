#include "patches.hpp"

#include <future>

#include "src-client/gui/controls/renderers/SplashTextRenderer.hpp"
#include "patterns/latest_windows.hpp"

namespace selaura {
    void patch_manager::init() {
        std::async(std::launch::deferred, [&] {
            REGISTER_HOOK(
                &bgfx::d3d11::RendererContextD3D11::submit_hk,
                reinterpret_cast<void**>(&selaura::trampolines::bgfx_d3d11_RendererContextD3D11_submit)
            );

            REGISTER_HOOK(
                &bgfx::d3d12::RendererContextD3D12::submit_hk,
                reinterpret_cast<void**>(&selaura::trampolines::bgfx_d3d12_RendererContextD3D12_submit)
            );

            REGISTER_HOOK(
                &ScreenView::setupAndRender_hk,
                reinterpret_cast<void**>(&selaura::trampolines::ScreenView_setupAndRender)
            );

            REGISTER_HOOK(
                &GameArguments::_onUri_hk,
                reinterpret_cast<void**>(&selaura::trampolines::GameArguments_onUri)
            );
        }).get();
    }
};
