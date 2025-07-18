cmake_minimum_required(VERSION 3.28)
project(selaura LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CLIENT_VERSION "0.40")

if (WIN32)
    add_compile_definitions(SELAURA_WINDOWS)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        if (CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC")
            message(STATUS "Selaura: Clang-cl detected (beware there may be issues using this, as it is not tested).")
        else()
            message(FATAL_ERROR "Selaura: Native Clang is not supported on Windows. Use MSVC or Clang-cl.")
        endif ()
    elseif (NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        message(FATAL_ERROR "Selaura: Only MSVC or Clang-cl are supported on Windows.")
    endif ()

    add_compile_options(/await)
elseif (UNIX)
    add_compile_definitions(SELAURA_LINUX)
    if (NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        message(FATAL_ERROR "Selaura: Clang is required on Linux.")
    endif ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -fPIC" CACHE STRING "" FORCE)
else()
    message(FATAL_ERROR "Selaura: ${CMAKE_SYSTEM_NAME} (${CMAKE_SYSTEM_PROCESSOR}) is not supported")
endif ()

if (MSVC AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
    set(CMAKE_CXX_FLAGS_DEBUG "/MDd /Zi /Od" CACHE STRING "" FORCE)

    add_compile_definitions(
            _ITERATOR_DEBUG_LEVEL=0
            _HAS_ITERATOR_DEBUGGING=0
            _SECURE_SCL=0
    )
endif()

add_compile_definitions(
        CLIENT_VERSION=\"${CLIENT_VERSION}\"
)

add_subdirectory(include)
add_subdirectory(src/client)

if (MSVC)
    add_compile_options(/W4 /permissive- /wd4201 /wd4324)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-gnu-zero-variadic-macro-arguments)
endif ()