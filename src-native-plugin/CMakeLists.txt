cmake_minimum_required(VERSION 3.15)
project(selaura_native_plugin LANGUAGES CXX)

add_library(selaura_native_plugin SHARED
        ${SELAURA_BEDROCK_SOURCES}
        main.cpp
)
add_library(selaura::native_plugin ALIAS selaura_native_plugin)


target_include_directories(selaura_native_plugin PRIVATE
        ${SELAURA_BEDROCK_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/src-client
        selaura_client
)