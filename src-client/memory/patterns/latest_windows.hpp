#pragma once
#include "src-client/bgfx/bgfx.hpp"
#include "src-client/gui/ScreenView.hpp"
#include "src-client/uri/GameArguments.hpp"
#include "src-client/world/BaseLightTextureImageBuilder.hpp"

DEFINE_SIG(&bgfx::d3d11::RendererContextD3D11::submit_hk, "48 8B C4 55 53 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ?");
DEFINE_SIG(&bgfx::d3d12::RendererContextD3D12::submit_hk, "40 55 53 56 57 41 54 41 55 41 56 41 57 B8");
DEFINE_SIG(&GameArguments::_onUri_hk, "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA 48 8B F1");
DEFINE_SIG(&ScreenView::setupAndRender_hk, "48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 98 FD");
DEFINE_SIG(&BaseLightTextureImageBuilder::createBaseLightTextureData_hk, "48 89 5C 24 ? 48 89 54 24 ? 55 56 57 41 56 41 57 48 83 EC 40 4D 8B F1");