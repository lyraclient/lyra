cmake_minimum_required(VERSION 3.15)
project(selaura LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CLIENT_VERSION "0.30")

if (WIN32)

    add_compile_definitions(SELAURA_WINDOWS)
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

elseif (ANDROID)

    add_compile_definitions(SELAURA_ANDROID)
    message(STATUS "Selaura: Building for Android (${CMAKE_SYSTEM_NAME} - ${CMAKE_SYSTEM_PROCESSOR})")
    if (NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        message(FATAL_ERROR "Selaura: Clang is required for Android.")
    endif ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++" CACHE STRING "" FORCE)

elseif (UNIX)

    add_compile_definitions(SELAURA_LINUX)
    if (NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        message(FATAL_ERROR "Selaura: Clang is required on Linux.")
    endif ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -fPIC" CACHE STRING "" FORCE)

else()
    message(FATAL_ERROR "Selaura: ${CMAKE_SYSTEM_NAME} (${CMAKE_SYSTEM_PROCESSOR}) is not supported")
endif ()

add_compile_definitions(
        CLIENT_VERSION=\"${CLIENT_VERSION}\"
)

add_subdirectory(include)
add_subdirectory(src-bedrock)
add_subdirectory(src-client)
add_subdirectory(src-native-plugin)