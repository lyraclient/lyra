#pragma once
#include <libhat/fixed_string.hpp>
#include <libhat/signature.hpp>

#include "memory.hpp"

namespace selaura::patterns {
    template <auto func_ptr>
    struct signature_map {
        static_assert(sizeof(func_ptr) == 0, "Missing signature_map specialization for this function pointer");
        static inline constexpr auto value = hat::fixed_signature<0>{};
    };
}

#define DEFINE_SIG(func, sig_literal)                                             \
template <>                                                                   \
struct selaura::patterns::signature_map<func> {                               \
static inline constexpr auto value = hat::compile_signature<sig_literal##>(); \
static uintptr_t resolve() {                                               \
auto pattern_result = selaura::mem::find_pattern(value);               \
if (!pattern_result || pattern_result == 0) {                                                 \
spdlog::error("Signature not found for function: {}", #func);      \
return 0;                              \
}                                                                     \
return pattern_result.value();                                        \
}                                                                         \
}

#define GET_SIG(func) selaura::patterns::signature_map<func>::value
#define RESOLVE_SIG(func) selaura::patterns::signature_map<func>::resolve()
