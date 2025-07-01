set(SELAURA_BEDROCK_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
set(SELAURA_BEDROCK_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/render/directx_hk.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src-client/bgfx/bgfx.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src-client/gui/controls/renderers/SplashTextRenderer.cpp
    PARENT_SCOPE
)