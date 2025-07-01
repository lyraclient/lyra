#include "patches.hpp"

#include "src-client/gui/controls/renderers/SplashTextRenderer.hpp"
#include "patterns/latest_windows.hpp"

namespace selaura {
    void patch_manager::init() {
        register_hook(
        RESOLVE_SIG(&bgfx::d3d11::RendererContextD3D11::submit_hk),
            &bgfx::d3d11::RendererContextD3D11::submit_hk,
            reinterpret_cast<void**>(&selaura::trampolines::bgfx_d3d11_RendererContextD3D11_submit)
        );

        register_hook(
            RESOLVE_SIG(&bgfx::d3d12::RendererContextD3D12::submit_hk),
            &bgfx::d3d12::RendererContextD3D12::submit_hk,
            reinterpret_cast<void**>(&selaura::trampolines::bgfx_d3d12_RendererContextD3D12_submit)
        );

        register_hook(
            RESOLVE_SIG(&SplashTextRenderer::render_hk),
            &SplashTextRenderer::render_hk,
            reinterpret_cast<void**>(&selaura::trampolines::SplashTextRenderer_render)
        );
    }
};
