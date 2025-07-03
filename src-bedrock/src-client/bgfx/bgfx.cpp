#include "bgfx.hpp"
#include <spdlog/spdlog.h>

#include "../../../src-client/core/instance.hpp"

#ifdef SELAURA_WINDOWS
#include "../../../src-client/core/event/event_types.hpp"
#include "render/directx_hk.hpp"

void bgfx::d3d11::RendererContextD3D11::submit_hk(void *a1, void *a2, void *a3) {
    auto inst = selaura::get();
    static int fps = 0;

    {
        static int frameCount = 0;
        static auto lastTime = std::chrono::high_resolution_clock::now();

        frameCount++;
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTime);
        if (elapsed.count() >= 1000) {
            fps = frameCount;
            frameCount = 0;
            lastTime = now;
        }
    }

    std::once_flag vtable_hooking_flag;
    std::call_once(vtable_hooking_flag, [&](){
        IDXGISwapChain3* swapchain = reinterpret_cast<IDXGISwapChain3*>(this->swapChain());

        winrt::com_ptr<IDXGIFactory5> factory;
        if (FAILED(CreateDXGIFactory(IID_PPV_ARGS(factory.put())))) {
            spdlog::error("Factory not created!");
        }

        void** factory_vtable = *reinterpret_cast<void***>(factory.get());
        inst->get<selaura::patch_manager>().register_hook(
            factory_vtable[16],
            &IDXGIFactory2_hk_CreateSwapChainForCoreWindow,
            reinterpret_cast<void**>(&selaura::trampolines::IDXGIFactory2_CreateSwapChainForCoreWindow)
        );

        void** swapchain_vtable = *reinterpret_cast<void***>(swapchain);
        inst->get<selaura::patch_manager>().register_hook(
            swapchain_vtable[8],
            &IDXGISwapChain_hk_Present,
            reinterpret_cast<void**>(&selaura::trampolines::IDXGISwapChain_Present)
        );
    });

    selaura::frame_event ev {fps};
    inst->get<selaura::event_manager>().dispatch<selaura::frame_event>(ev);

    auto ofunc = selaura::trampolines::bgfx_d3d11_RendererContextD3D11_submit;
    (this->*ofunc)(a1, a2, a3);
}

void bgfx::d3d12::RendererContextD3D12::submit_hk(void *a1, void *a2, void *a3) {
    static int frameCount = 0;
    static auto lastTime = std::chrono::high_resolution_clock::now();

    frameCount++;
    auto now = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTime);
    if (elapsed.count() >= 1000) {
        spdlog::info("FPS: {}", frameCount);
        frameCount = 0;
        lastTime = now;
    }

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