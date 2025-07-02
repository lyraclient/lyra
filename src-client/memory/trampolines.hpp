#pragma once

#include "render/directx_hk.hpp"
#include "src-client/bgfx/bgfx.hpp"

namespace selaura::trampolines {
    inline decltype(&bgfx::d3d11::RendererContextD3D11::submit_hk) bgfx_d3d11_RendererContextD3D11_submit = 0;
    inline decltype(&bgfx::d3d12::RendererContextD3D12::submit_hk) bgfx_d3d12_RendererContextD3D12_submit = 0;
    inline uintptr_t SplashTextRenderer_render = 0;

#ifdef SELAURA_WINDOWS
    inline decltype(&IDXGIFactory2_hk_CreateSwapChainForCoreWindow) IDXGIFactory2_CreateSwapChainForCoreWindow = 0;
    inline decltype(&IDXGISwapChain_hk_Present) IDXGISwapChain_Present = 0;
#endif
};