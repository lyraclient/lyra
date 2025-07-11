#pragma once
#include <future>
#include <vector>
#include <unordered_map>
#include <typeindex>

#include <libhat/scanner.hpp>
#include <libhat/signature.hpp>

#include "../platform/platform.hpp"

namespace selaura {
    template <auto fn>
    struct signature {
        static_assert(sizeof(fn) == 0, "signature must be specialized for this tag type");
    };

    /*template <>
    struct selaura::signature<&ScreenView::setupAndRender> {
        static constexpr auto value = hat::compile_signature<"48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 98 FD">();
    };
    */

    template <auto fn>
    constexpr auto get_signature = signature<fn>::value;

    template <auto fn, typename T = std::uintptr_t>
    T resolve_signature(std::string_view module_name = {}) {
        static T addr = [&] {
            static auto& handle = module_name.empty()
                ? get_dynamic_module()
                : get_dynamic_module(module_name);

            return reinterpret_cast<T>(
                hat::find_pattern(handle.memory_view, signature<fn>::value).get()
            );
        }();
        return addr;
    }

    template <auto... tags>
    void prewarm_signatures(std::string_view module_name = {}) {
        std::vector<std::future<void>> futures;

        (futures.emplace_back(std::async(std::launch::async, [module_name]() {
            (void)resolve_signature<tags, std::uintptr_t>(module_name);
        })), ...);

        for (auto& fut : futures) {
            fut.get();
        }
    }

};
