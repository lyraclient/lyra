#pragma once
#include "api.hpp"
#include "../../../../../src-client/memory/patterns.hpp"

#include <vector>
#include <string>

struct SplashTextRenderer {
    std::byte pad[0x10];
    int mCurrentSplash;
    std::byte pad2[0x28 - 0x10];
    std::vector<std::string> mSplashes;

    void render_hk(void* ctx, void* clientInstance, void* owner, int pass, void* renderAABB);
};