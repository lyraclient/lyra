#pragma once
#include <cstddef>

struct HudPlayerRenderer {
    std::byte pad[16];
public:
    float mRenderTime;
    float mTick;
};