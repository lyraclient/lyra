#pragma once
#include "api.hpp"
#include "../../../../../src-client/memory/patterns.hpp"

#include <vector>
#include <string>

class SplashTextRenderer {
public:
    MEMBER_AT(0x10, mCurrentSplash, int);
    MEMBER_AT(0x28, mSplashes, std::vector<std::string>);

    void render_hk(void* ctx, void* clientInstance, void* owner, int pass, void* renderAABB);
};