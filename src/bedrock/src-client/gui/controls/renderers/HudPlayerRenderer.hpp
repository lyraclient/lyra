#pragma once
#include <cstddef>

#include "../../renderer/screen/MinecraftUIRenderContext.hpp"

class HudPlayerRenderer : public MinecraftCustomUIRenderer {
    std::byte pad[16];
public:
    float mRenderTime;
    float tick;
};
