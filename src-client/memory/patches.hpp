#pragma once
#include <tuple>
#include <unordered_map>
#include <spdlog/spdlog.h>

#include "../core/platform/all.hpp"
#include "patches.hpp"

namespace selaura {
    struct patch_manager {
        std::unordered_map<void*, void*> original_map;

        template <typename Callable, typename MPF>
        void register_hook(uintptr_t address, Callable&& detour_lambda, MPF abi_reference) {
            void* target = reinterpret_cast<void*>(address);
            void* detour_ptr = reinterpret_cast<void*>(+detour_lambda);
            void** original_ptr = reinterpret_cast<void**>(&original_map[target]);

            selaura::hook_install(target, detour_ptr, original_ptr);
        }

        template <typename R, typename... Args>
        void register_hook(R(*original)(Args...), R(*detour)(Args...)) {
            void* target = reinterpret_cast<void*>(original);
            void* detour_ptr = reinterpret_cast<void*>(detour);
            void** original_ptr = reinterpret_cast<void**>(&original_map[target]);
            selaura::hook_install(target, detour_ptr, original_ptr);
        }

        template <typename Callable, typename MPF>
        void register_hook(Callable&& detour_lambda, MPF target_mfp) {
            void* target = selaura::get_address(target_mfp);
            void* detour_ptr = reinterpret_cast<void*>(+detour_lambda);
            void** original_ptr = reinterpret_cast<void**>(&original_map[target]);
            selaura::hook_install(target, detour_ptr, original_ptr);
        }

        template <typename T, typename R, typename... Args>
        void register_hook(R(T::*mpf)(Args...), R(*detour)(Args...)) {
            void* target = selaura::get_address(mpf);
            void** original_ptr = reinterpret_cast<void**>(&original_map[target]);
            selaura::hook_install(target, reinterpret_cast<void*>(detour), original_ptr);
        }

        template <typename T, typename R, typename... Args>
        void register_hook(R(T::*mpf)(Args...) const, R(*detour)(Args...)) {
            void* target = selaura::get_address(mpf);
            void** original_ptr = reinterpret_cast<void**>(&original_map[target]);
            selaura::hook_install(target, reinterpret_cast<void*>(detour), original_ptr);
        }

        template <typename Callable>
        void register_hook(uintptr_t address, Callable&& detour_lambda) {
            void* target = reinterpret_cast<void*>(address);
            void* detour_ptr = selaura::get_address(std::forward<Callable>(detour_lambda));
            void** original_ptr = reinterpret_cast<void**>(&original_map[target]);

            selaura::hook_install(target, detour_ptr, original_ptr);
        }
    };
}
