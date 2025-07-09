#pragma once

#include <type_traits>
#include <cstddef>

#ifdef SELAURA_WINDOWS
#include <MinHook.h>
#else
#include <dobby.h>
#endif

namespace selaura {
    void hook_init();
    void hook_install(void* target, void* detour, void** original);

    template <typename T>
        requires std::is_pointer_v<T> && std::is_function_v<std::remove_pointer_t<T>>
    void* get_address(T fn_ptr) {
        return reinterpret_cast<void*>(fn_ptr);
    }

    template <typename T, typename R, typename... Args>
    void* get_address(R(T::*mpf)(Args...)) {
#if defined(_MSC_VER)
        return *reinterpret_cast<void**>(&mpf);
#elif defined(__clang__) || defined(__GNUC__)
        union {
            R(T::*mpf)(Args...);
            struct {
                void* addr;
                ptrdiff_t adj;
            } s;
        } caster{ .mpf = mpf };
        return caster.s.addr;
#else
#   error Unsupported compiler
#endif
    }

    template <typename T, typename R, typename... Args>
    void* get_address(R(T::*mpf)(Args...) const) {
#if defined(_MSC_VER)
        return *reinterpret_cast<void**>(&mpf);
#elif defined(__clang__) || defined(__GNUC__)
        union {
            R(T::*mpf)(Args...) const;
            struct {
                void* addr;
                ptrdiff_t adj;
            } s;
        } caster{ .mpf = mpf };
        return caster.s.addr;
#else
#   error Unsupported compiler
#endif
    }

    template <typename T>
    void* get_address(T) {
        static_assert(sizeof(T) == 0, "get_address() is not implemented for this type.");
        return nullptr;
    }
};