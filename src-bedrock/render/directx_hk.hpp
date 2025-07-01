#pragma once

#ifdef SELAURA_WINDOWS
#include <Windows.h>
#include <d3d11.h>
#include <d3d12.h>
#include <spdlog/spdlog.h>

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_dx11.h"
#include "imgui/backends/imgui_impl_dx12.h"

#include "../../src-client/memory/patterns.hpp"

struct IDXGISwapChain_hk {
    HRESULT Present(UINT SyncInterval, UINT Flags);
};
#endif