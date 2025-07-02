#include "directx_hk.hpp"
#ifdef SELAURA_WINDOWS
#include "../../src-client/core/instance.hpp"
#include "../../src-client/memory/trampolines.hpp"

bool vsync = false;

static bool DirectX_TearingSupport() {
    static bool resolved = false;
    bool result = false;
    winrt::com_ptr<IDXGIFactory5> factory;
    if (!resolved && SUCCEEDED(CreateDXGIFactory1(IID_PPV_ARGS(&factory)))) {
        if (SUCCEEDED(factory->CheckFeatureSupport(
            DXGI_FEATURE_PRESENT_ALLOW_TEARING,
            &result,
            sizeof(result)))) {
            resolved = true;
            return result;
        }
    }

    resolved = true;
    return result;
}

HRESULT IDXGIFactory2_hk_CreateSwapChainForCoreWindow(IDXGIFactory2* _thisptr, IUnknown* pDevice, IUnknown* pWindow, const DXGI_SWAP_CHAIN_DESC1* pDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain) {

    DXGI_SWAP_CHAIN_DESC1 desc = *pDesc;

    if (!vsync && DirectX_TearingSupport()) {
        desc.Flags |= DXGI_PRESENT_ALLOW_TEARING;
    }

    spdlog::debug("DirectX Tearing Support: {}", DirectX_TearingSupport());

    auto ofunc = selaura::trampolines::IDXGIFactory2_CreateSwapChainForCoreWindow;
    return ofunc(_thisptr, pDevice, pWindow, &desc, pRestrictToOutput, ppSwapChain);
}

HRESULT IDXGISwapChain_hk_Present(IDXGISwapChain3* _thisptr, UINT SyncInterval, UINT Flags) {
    auto ofunc = selaura::trampolines::IDXGISwapChain_Present;

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

    UINT presentFlags = Flags;
    if (!vsync && DirectX_TearingSupport()) {
        SyncInterval = 0;
        presentFlags |= DXGI_PRESENT_ALLOW_TEARING;
    }

    static bool refreshed = false;
    if (!refreshed) {
        refreshed = true;
        return DXGI_ERROR_DEVICE_RESET;
    }

    return ofunc(_thisptr, SyncInterval, presentFlags);
}

#endif