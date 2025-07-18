#pragma once
#include <vector>
#include <string>

#include "../../../renderer/screen/MinecraftUIRenderContext.hpp"

struct SplashTextRenderer {
    std::byte pad[0x20];
public:
    int mCurrentSplash;
private:
    std::byte pad2[0xC];
public:
    std::vector<std::string> mSplashes;
};