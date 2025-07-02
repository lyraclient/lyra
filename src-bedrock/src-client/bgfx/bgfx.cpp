#include "bgfx.hpp"
#include <spdlog/spdlog.h>

#include "../../../src-client/core/instance.hpp"

#ifdef SELAURA_WINDOWS
#include "render/directx_hk.hpp"

void bgfx::d3d11::RendererContextD3D11::submit_hk(void *a1, void *a2, void *a3) {

    IDXGISwapChain3* swapchain = reinterpret_cast<IDXGISwapChain3*>(this->swapChain());
    static bool hooked = false;

    if (swapchain && !hooked) {
        IDXGIFactory2* factory = NULL;
        CreateDXGIFactory(IID_PPV_ARGS(&factory));
        if (!factory) {
            spdlog::error("Factory not created!");
        }

        void** factory_vtable = *reinterpret_cast<void***>(factory);
        selaura::get()->get<selaura::patch_manager>().register_hook(
            factory_vtable[16],
            &IDXGIFactory2_hk_CreateSwapChainForCoreWindow,
            reinterpret_cast<void**>(&selaura::trampolines::IDXGIFactory2_CreateSwapChainForCoreWindow)
        );

        void** swapchain_vtable = *reinterpret_cast<void***>(swapchain);
        selaura::get()->get<selaura::patch_manager>().register_hook(
            swapchain_vtable[8],
            &IDXGISwapChain_hk_Present,
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
            &IDXGISwapChain_hk_Present,
            reinterpret_cast<void**>(&selaura::trampolines::IDXGISwapChain_Present)
        );

        hooked = true;
    }

    auto ofunc = selaura::trampolines::bgfx_d3d12_RendererContextD3D12_submit;
    (this->*ofunc)(a1, a2, a3);
}
#endif