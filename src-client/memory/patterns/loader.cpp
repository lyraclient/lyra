#include "loader.hpp"
#include "../patterns.hpp"
#include "latest_windows.hpp"

namespace selaura {
    void resolve_signatures() {
        selaura::patterns::resolve_all_signatures_parallel({
            {"submit_hk_d3d11", [&] { return RESOLVE_SIG(&bgfx::d3d11::RendererContextD3D11::submit_hk); }},
            {"submit_hk_d3d12", [&] { return RESOLVE_SIG(&bgfx::d3d12::RendererContextD3D12::submit_hk); }},
            {"_onUri_hk", [&] { return RESOLVE_SIG(&GameArguments::_onUri_hk); }},
            {"setupAndRender_hk", [&] { return RESOLVE_SIG(&ScreenView::setupAndRender_hk); }},
        });
    }
}
