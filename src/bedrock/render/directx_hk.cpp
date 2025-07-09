#include "directx_hk.hpp"
#ifdef SELAURA_WINDOWS
#include "../../client/core/instance.hpp"
#include "../../client/memory/trampolines.hpp"

HRESULT IDXGIFactory2_hk_CreateSwapChainForCoreWindow(IDXGIFactory2* _thisptr, IUnknown* pDevice, IUnknown* pWindow, const DXGI_SWAP_CHAIN_DESC1* pDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain) {
    winrt::com_ptr<IDXGIFactory5> factory;
    if (SUCCEEDED(CreateDXGIFactory1(IID_PPV_ARGS(factory.put())))) {
        if (SUCCEEDED(factory->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &selaura::options::tearing_feature_enabled,sizeof(selaura::options::tearing_feature_enabled)))) {
            selaura::options::tearing_feature_enabled = true;
        }
    }

    spdlog::debug("DirectX Tearing Support: {}", selaura::options::tearing_feature_enabled);

    DXGI_SWAP_CHAIN_DESC1 desc = *pDesc;
    if (!selaura::options::vsync && selaura::options::tearing_feature_enabled) {
        desc.Flags |= DXGI_PRESENT_ALLOW_TEARING;
    }

    auto ofunc = selaura::trampolines::IDXGIFactory2_CreateSwapChainForCoreWindow;
    return ofunc(_thisptr, pDevice, pWindow, &desc, pRestrictToOutput, ppSwapChain);
}

HRESULT IDXGISwapChain_hk_Present(IDXGISwapChain3* _thisptr, UINT SyncInterval, UINT Flags) {
    auto ofunc = selaura::trampolines::IDXGISwapChain_Present;

    static bool refreshed = false;
    if (!refreshed) {
        refreshed = true;
        return DXGI_ERROR_DEVICE_RESET;
    }

    return ofunc(_thisptr, SyncInterval, Flags);
}

#endif