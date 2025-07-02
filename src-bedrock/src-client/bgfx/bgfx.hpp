#pragma once
#ifdef SELAURA_WINDOWS
#include <Windows.h>
#include <d3d11.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#endif

#include <cstddef>

#include "../../../src-client/memory/patterns.hpp"

namespace bgfx {
#ifdef SELAURA_WINDOWS
    namespace d3d11 {
        struct RendererContextD3D11 {
            MEMBER_AT(552, swapChain, IDXGISwapChain*);
            void submit_hk(void* a1, void* a2, void* a3);
        };
    };
    namespace d3d12 {
        struct RendererContextD3D12 {
            MEMBER_AT(338, swapChain, IDXGISwapChain*);
            void submit_hk(void* a1, void* a2, void* a3);
        };
    };
#endif
};