#include "bgfx.hpp"
#include <spdlog/spdlog.h>

#include "../../../src-client/core/instance.hpp"

#ifdef SELAURA_WINDOWS
#include "render/directx_hk.hpp"

void bgfx::d3d11::RendererContextD3D11::submit_hk(void *a1, void *a2, void *a3) {

    IDXGISwapChain* swapchain = this->swapChain();
    static bool hooked = false;

    if (swapchain && !hooked) {
        void** vtable = *reinterpret_cast<void***>(swapchain);

        selaura::get()->get<selaura::patch_manager>().register_hook(
            vtable[8],
            &IDXGISwapChain_hk::Present,
            reinterpret_cast<void**>(&selaura::trampolines::IDXGISwapChain_Present)
        );

        hooked = true;
    }

    auto ofunc = selaura::trampolines::bgfx_d3d11_RendererContextD3D11_submit;
    (this->*ofunc)(a1, a2, a3);
}

void bgfx::d3d12::RendererContextD3D12::submit_hk(void *a1, void *a2, void *a3) {

    IDXGISwapChain* swapchain = this->swapChain();
    static bool hooked = false;

    if (swapchain && !hooked) {
        void** vtable = *reinterpret_cast<void***>(swapchain);

        selaura::get()->get<selaura::patch_manager>().register_hook(
            vtable[140],
            &IDXGISwapChain_hk::Present,
            reinterpret_cast<void**>(&selaura::trampolines::IDXGISwapChain_Present)
        );

        hooked = true;
    }

    auto ofunc = selaura::trampolines::bgfx_d3d12_RendererContextD3D12_submit;
    (this->*ofunc)(a1, a2, a3);
}
#endif