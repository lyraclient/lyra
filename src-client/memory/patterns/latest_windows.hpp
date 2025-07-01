#pragma once
#include "../patterns.hpp"
#include "src-client/bgfx/bgfx.hpp"
#include "src-client/gui/controls/renderers/SplashTextRenderer.hpp"

DEFINE_SIG(&SplashTextRenderer::render_hk, "48 89 5C 24 18 55 56 57 48 8D AC 24 50 FC FF FF 48 81 EC B0 04 00 00 48 8B FA");
DEFINE_SIG(&bgfx::d3d11::RendererContextD3D11::submit_hk, "48 8B C4 55 53 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ?");
DEFINE_SIG(&bgfx::d3d12::RendererContextD3D12::submit_hk, "40 55 53 56 57 41 54 41 55 41 56 41 57 B8");