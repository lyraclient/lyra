#pragma once
#include <span>
#include <string_view>

#ifdef SELAURA_WINDOWS
#include <Windows.h>
#include <Psapi.h>
#else
#include <dlfcn.h>
#include <link.h>
#endif

namespace selaura {
    struct dynamic_module {
        void* native_handle = nullptr;
        std::span<std::byte> memory_view{};
        std::uintptr_t base_address;
        std::size_t size;

        constexpr bool valid() const noexcept {
            return native_handle != nullptr;
        }

        template<typename T>
        constexpr T& at(std::ptrdiff_t offset) const noexcept {
            static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");
            return *reinterpret_cast<T*>(base_address + offset);
        }
    };

    dynamic_module& get_dynamic_module(std::string_view name);
    dynamic_module& get_dynamic_module();
};