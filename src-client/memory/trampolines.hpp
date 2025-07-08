#pragma once

#include "render/directx_hk.hpp"
#include "src-client/bgfx/bgfx.hpp"
#include "src-client/gui/ScreenView.hpp"
#include "src-client/gui/controls/renderers/SplashTextRenderer.hpp"
#include "src-client/uri/GameArguments.hpp"
#include "src-client/world/BaseLightTextureImageBuilder.hpp"

namespace selaura::trampolines {
    inline decltype(&bgfx::d3d11::RendererContextD3D11::submit_hk) bgfx_d3d11_RendererContextD3D11_submit = 0;
    inline decltype(&bgfx::d3d12::RendererContextD3D12::submit_hk) bgfx_d3d12_RendererContextD3D12_submit = 0;
    inline decltype(&GameArguments::_onUri_hk) GameArguments_onUri = 0;
    inline decltype(&ScreenView::setupAndRender_hk) ScreenView_setupAndRender = 0;
    inline decltype(&MinecraftUIRenderContext::renderCustom_hk) MinecraftUIRenderContext_renderCustom = 0;
    inline decltype(&BaseLightTextureImageBuilder::createBaseLightTextureData_hk) BaseLightTextureImageBuilder_createBaseLightTextureData = 0;
    inline decltype(&NetherLightTextureImageBuilder::createBaseLightTextureData_hk) NetherLightTextureImageBuilder_createBaseLightTextureData = 0;

#ifdef SELAURA_WINDOWS
    inline decltype(&IDXGIFactory2_hk_CreateSwapChainForCoreWindow) IDXGIFactory2_CreateSwapChainForCoreWindow = 0;
    inline decltype(&IDXGISwapChain_hk_Present) IDXGISwapChain_Present = 0;
#endif
};