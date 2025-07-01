cmake_minimum_required(VERSION 3.15)
project(selaura LANGUAGES CXX)

if(NOT CPM_SOURCE_CACHE)
    set(CPM_SOURCE_CACHE "${CMAKE_BINARY_DIR}/.cpmcache")
endif()

if(NOT EXISTS "${CMAKE_BINARY_DIR}/cmake/CPM.cmake")
    file(DOWNLOAD
            https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/CPM.cmake
            "${CMAKE_BINARY_DIR}/cmake/CPM.cmake"
            TLS_VERIFY ON)
endif()
include("${CMAKE_BINARY_DIR}/cmake/CPM.cmake")

CPMAddPackage(
        NAME fmt
        GITHUB_REPOSITORY fmtlib/fmt
        GIT_TAG master
)

CPMAddPackage(
        NAME entt
        GITHUB_REPOSITORY skypjack/entt
        GIT_TAG d4014c74dc3793aba95ae354d6e23a026c2796db
)

CPMAddPackage(
        NAME libhat
        GITHUB_REPOSITORY BasedInc/libhat
        GIT_TAG master
)

CPMAddPackage(
        NAME spdlog
        GITHUB_REPOSITORY gabime/spdlog
        GIT_TAG v1.x
)

CPMAddPackage(
        NAME gsl
        GITHUB_REPOSITORY microsoft/GSL
        GIT_TAG v4.0.0
)

if(MSVC)
    CPMAddPackage(
            NAME minhook
            GITHUB_REPOSITORY TsudaKageyu/minhook
            GIT_TAG master
    )
else()
    CPMAddPackage(
            NAME dobby
            GITHUB_REPOSITORY selauraclient/Dobby
            GIT_TAG master
    )
endif()

set(DOBBY_DEBUG OFF CACHE BOOL "Dobby debug mode")
set(DOBBY_GENERATE_SHARED OFF CACHE BOOL "Dobby generate shared library")

add_library(selaura INTERFACE)
add_library(selaura::selaura ALIAS selaura)

target_include_directories(selaura INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

if(MSVC)
    target_link_libraries(selaura INTERFACE minhook)
else()
    target_link_libraries(selaura INTERFACE dobby)
endif()

target_link_libraries(selaura INTERFACE
        fmt
        EnTT::EnTT
        libhat
        spdlog::spdlog
        GSL::gsl
)
