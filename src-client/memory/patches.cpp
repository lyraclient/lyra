#include "patches.hpp"

#include <future>

#include "patterns/latest_windows.hpp"

namespace selaura {
    void patch_manager::init() {
        std::vector<std::future<void>> tasks;

        tasks.push_back(std::async(std::launch::async, [&] {
            REGISTER_HOOK(&bgfx::d3d11::RendererContextD3D11::submit_hk,
                          reinterpret_cast<void**>( &selaura::trampolines::bgfx_d3d11_RendererContextD3D11_submit));
        }));

        tasks.push_back(std::async(std::launch::async, [&] {
            REGISTER_HOOK(&bgfx::d3d12::RendererContextD3D12::submit_hk,
                          reinterpret_cast<void**>(&selaura::trampolines::bgfx_d3d12_RendererContextD3D12_submit));
        }));

        tasks.push_back(std::async(std::launch::async, [&] {
            REGISTER_HOOK(&ScreenView::setupAndRender_hk,
                          reinterpret_cast<void**>(&selaura::trampolines::ScreenView_setupAndRender));
        }));

        tasks.push_back(std::async(std::launch::async, [&] {
            REGISTER_HOOK(&GameArguments::_onUri_hk,
                          reinterpret_cast<void**>(&selaura::trampolines::GameArguments_onUri));
        }));

        tasks.push_back(std::async(std::launch::async, [&] {
            REGISTER_HOOK(&BaseLightTextureImageBuilder::createBaseLightTextureData_hk,
                          reinterpret_cast<void**>(&selaura::trampolines::BaseLightTextureImageBuilder_createBaseLightTextureData));
        }));

        tasks.push_back(std::async(std::launch::async, [&] {
            REGISTER_HOOK(&NetherLightTextureImageBuilder::createBaseLightTextureData_hk,
                          reinterpret_cast<void**>(&selaura::trampolines::NetherLightTextureImageBuilder_createBaseLightTextureData));
        });

        for (auto& task : tasks) task.get();
    }
};
