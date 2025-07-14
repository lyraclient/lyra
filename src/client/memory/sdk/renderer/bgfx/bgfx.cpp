#include "bgfx.hpp"
#include "../../../patcher.hpp"
#include <spdlog/spdlog.h>

#ifdef SELAURA_WINDOWS
void bgfx::d3d11::RendererContextD3D11::submit_hk(void *a1, void *a2, void *a3) {
    selaura::call_fn<&bgfx::d3d11::RendererContextD3D11::submit_hk>(this, a1, a2, a3);
}

void bgfx::d3d12::RendererContextD3D12::submit_hk(void *a1, void *a2, void *a3) {
    selaura::call_fn<&bgfx::d3d12::RendererContextD3D12::submit_hk>(this, a1, a2, a3);
}
#endif