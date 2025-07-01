#include "directx_hk.hpp"
#ifdef SELAURA_WINDOWS
#include "../../src-client/memory/trampolines.hpp"

HRESULT IDXGISwapChain_hk::Present(UINT SyncInterval, UINT Flags) {
    auto ofunc = selaura::trampolines::IDXGISwapChain_Present;

    static bool refreshed = false;
    if (!refreshed) {
        refreshed = true;
        // todo: hook createswapchainforcorewindow so i can handle vsync stuffs there
        return DXGI_ERROR_DEVICE_RESET;
    }

    return (this->*ofunc)(SyncInterval, Flags);
}
#endif