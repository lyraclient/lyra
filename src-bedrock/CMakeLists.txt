set(SELAURA_BEDROCK_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

FILE(GLOB_RECURSE IMGUI_FILES "${CMAKE_CURRENT_SOURCE_DIR}/render/imgui/*.cpp")

set(SELAURA_BEDROCK_SOURCES
    ${IMGUI_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/render/directx_hk.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src-client/bgfx/bgfx.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src-client/gui/ScreenView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src-client/renderer/screen/MinecraftUIRenderContext.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src-client/uri/GameArguments.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src-client/world/BaseLightTextureImageBuilder.cpp
    PARENT_SCOPE
)