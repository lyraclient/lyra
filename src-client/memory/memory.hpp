#pragma once
#include <cstdint>
#include <string_view>

#include "../core/platform/all.hpp"

#include <libhat/fixed_string.hpp>
#include <libhat/scanner.hpp>
#include <libhat/signature.hpp>

namespace selaura::mem {
    template <hat::fixed_string pattern>
    inline std::optional<uintptr_t> find_pattern() {
        static auto platform = selaura::handle::resolve();
        if (auto result = hat::find_pattern(std::span{platform->bytes, platform->size}, hat::compile_signature<pattern>()).get()) {
            return reinterpret_cast<uintptr_t>(result);
        }
        return std::nullopt;
    }

    inline std::optional<uintptr_t> find_pattern(hat::signature_view signature) {
        static auto platform = selaura::handle::resolve();
        if (auto result = hat::find_pattern(std::span{platform->bytes, platform->size}, signature).get()) {
            return reinterpret_cast<uintptr_t>(result);
        }
        return std::nullopt;
    }
};