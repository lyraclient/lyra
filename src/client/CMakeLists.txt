cmake_minimum_required(VERSION 3.15)
project(selaura_client LANGUAGES CXX)

add_library(selaura_client SHARED
    main.cpp
    client.cpp
    platform/platform.cpp
    memory/sdk/gui/ScreenView.cpp
    memory/sdk/world/BaseLightTextureImageBuilder.cpp
    memory/sdk/world/Dimension.cpp
    memory/sdk/game/uri/GameArguments.cpp
    memory/sdk/renderer/screen/MinecraftUIRenderContext.cpp
    memory/sdk/renderer/bgfx/bgfx.cpp
    command/impl/Help.cpp
)

target_include_directories(selaura_client PRIVATE
    fmt
    EnTT
    spdlog
    libhat
    gsl
    glm
    safetyhook
)

target_link_libraries(selaura_client PRIVATE
    EnTT::EnTT
    spdlog
    libhat
    Microsoft.GSL::GSL
    glm
    safetyhook::safetyhook
)