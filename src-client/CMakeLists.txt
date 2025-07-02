cmake_minimum_required(VERSION 3.15)
project(selaura_client LANGUAGES CXX)

FILE(GLOB IMGUI_SOURCES "${imgui_SOURCE_DIR}/*.cpp")

add_library(selaura_client SHARED
    ${SELAURA_BEDROCK_SOURCES}
    ${IMGUI_SOURCES}
    main.cpp
    core/instance.cpp
    core/builder.cpp
    memory/memory.cpp
    memory/patterns.cpp
    memory/patches.cpp
    core/platform/handle.cpp
    core/platform/version.cpp
    core/platform/title.cpp
    core/platform/console.cpp
    core/platform/data_folder.cpp
    core/platform/hook.cpp
)
add_library(selaura::client ALIAS selaura_client)


target_include_directories(selaura_client PRIVATE
    ${SELAURA_BEDROCK_INCLUDE_DIR}
    fmt
    EnTT
    spdlog
    libhat
    gsl
)

target_link_libraries(selaura_client PRIVATE
    EnTT::EnTT
    spdlog
    libhat
    Microsoft.GSL::GSL
)

if (MSVC)
    target_link_libraries(selaura_client PRIVATE
        minhook dxgi
    )
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
else()
    target_link_libraries(selaura_client PRIVATE
        dobby_static
    )
endif()
