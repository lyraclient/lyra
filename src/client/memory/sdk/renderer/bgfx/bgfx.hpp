#pragma once
#ifdef SELAURA_WINDOWS
#include <Windows.h>
#include <d3d11.h>
#include <d3d12.h>
#include <dxgi1_5.h>
#endif

#include <cstddef>

namespace bgfx {
#ifdef SELAURA_WINDOWS
    namespace d3d11 {
        struct RendererContextD3D11 {
            std::byte pad[0x228];
            IDXGISwapChain* swapChain;

            void submit_hk(void* a1, void* a2, void* a3);
        };
    };
    namespace d3d12 {
        struct RendererContextD3D12 {
            std::byte pad[0x152];
            IDXGISwapChain* swapChain;

            void submit_hk(void* a1, void* a2, void* a3);
        };
    };
#endif
};