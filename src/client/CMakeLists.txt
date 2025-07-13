cmake_minimum_required(VERSION 3.15)
project(selaura_client LANGUAGES CXX)

add_library(selaura_client SHARED
    main.cpp
    client.cpp
    platform/platform.cpp
    memory/patches/render/ScreenView.cpp
    memory/patches/world/BaseLightTextureImageBuilder.cpp
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