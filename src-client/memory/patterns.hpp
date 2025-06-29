#pragma once
#include <libhat/fixed_string.hpp>
#include <libhat/signature.hpp>

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
}

#define GET_SIG(func) selaura::patterns::signature_map<func>::value