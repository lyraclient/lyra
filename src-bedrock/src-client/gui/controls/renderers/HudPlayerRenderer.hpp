#pragma once
#include <cstddef>

#include "src-client/renderer/screen/MinecraftUIRenderContext.hpp"

class HudPlayerRenderer : public MinecraftCustomUIRenderer {
    std::byte pad[16];
public:
    float mRenderTime;
    float tick;
};
