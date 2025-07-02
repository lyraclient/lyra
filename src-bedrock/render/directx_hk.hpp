#pragma once

#ifdef SELAURA_WINDOWS
#include <Windows.h>
#include <d3d11.h>
#include <d3d12.h>
#include <dxgi1_5.h>
#include <spdlog/spdlog.h>

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_dx11.h"
#include "imgui/backends/imgui_impl_dx12.h"

#include "../../src-client/memory/patterns.hpp"

HRESULT IDXGIFactory2_hk_CreateSwapChainForCoreWindow(IDXGIFactory2* _thisptr, IUnknown* pDevice, IUnknown* pWindow, const DXGI_SWAP_CHAIN_DESC1* pDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain);
HRESULT IDXGISwapChain_hk_Present(IDXGISwapChain3* _thisptr, UINT SyncInterval, UINT Flags);

#endif