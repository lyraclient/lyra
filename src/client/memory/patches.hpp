#pragma once

#include <unordered_map>
#include <spdlog/spdlog.h>
#include <libhat/access.hpp>
#include "../core/platform/all.hpp"
#include "patches.hpp"
#include "trampolines.hpp"

namespace selaura {

    struct patch_manager {
        void init();

        template <typename Callable>
        void register_hook(void* address, Callable&& detour_lambda, void** trampoline) {
            void* detour_ptr = get_address(std::forward<Callable>(detour_lambda));

            hook_install(address, detour_ptr, trampoline);
        }

        template <typename Callable>
        void register_hook(uintptr_t address, Callable&& detour_lambda, void** trampoline) {
            register_hook(reinterpret_cast<void*>(address), std::forward<Callable>(detour_lambda), trampoline);
        }
    };
};

#define REGISTER_HOOK(func_ptr, trampoline_ptr) \
register_hook(                             \
RESOLVE_SIG(func_ptr),                 \
func_ptr,                             \
reinterpret_cast<void**>(trampoline_ptr) \
)
