#pragma once
#include "api.hpp"
#include "../../../../../src-client/memory/patterns.hpp"

#include <vector>
#include <string>

#include "src-client/renderer/screen/MinecraftUIRenderContext.hpp"

class SplashTextRenderer : public MinecraftCustomUIRenderer {
    std::byte pad[0x20];
public:
    int mCurrentSplash;
private:
    std::byte pad2[0xC];
public:
    std::vector<std::string> mSplashes;
};