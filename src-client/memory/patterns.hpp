#pragma once
#include <libhat/fixed_string.hpp>
#include <libhat/signature.hpp>

#include <format>
#include <vector>
#include <string_view>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <sstream>

#include "memory.hpp"
#include "member_at.hpp"

namespace selaura::patterns {
    template <auto func_ptr>
    struct signature_map {
        static_assert(sizeof(func_ptr) == 0, "Missing signature_map specialization for this function pointer");
        static inline constexpr auto value = hat::fixed_signature<0>{};
    };
}

#define DEFINE_SIG(func, sig_literal)                                                              \
template <>                                                                                        \
struct selaura::patterns::signature_map<func> {                                                    \
    static inline constexpr auto value = hat::compile_signature<sig_literal##>();                  \
                                                                                                   \
    static uintptr_t resolve() {                                                                   \
static auto result = selaura::mem::find_pattern(value);                                           \
if (!result || result.value() == 0) {                                                      \
spdlog::error("Signature not found for function: {}", #func);                           \
return 0;                                                                              \
} \
return result.value(); \
    }                                                                                              \
};

#define GET_SIG(func) selaura::patterns::signature_map<func>::value
#define RESOLVE_SIG(func) selaura::patterns::signature_map<func>::resolve()
