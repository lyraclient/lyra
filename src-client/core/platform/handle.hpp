#pragma once
#include <cstddef>
#include <memory>
#include <string_view>
#include <stdexcept>

#ifdef SELAURA_WINDOWS
#include <Windows.h>
#include <Psapi.h>
#else
#include <dlfcn.h>
#include <link.h>
#endif

namespace selaura {
    struct handle {
        void* native_handle;

        std::byte* bytes;
        std::size_t size;

        static std::unique_ptr<selaura::handle> resolve(const std::string_view& name);
        static std::unique_ptr<selaura::handle> resolve();
    };
};