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
        static uintptr_t cached = 0;                                                               \
        static bool initialized = false;                                                           \
        if (initialized) return cached;                                                            \
        initialized = true;                                                                        \
                                                                                                   \
        namespace fs = std::filesystem;                                                            \
        const fs::path cache_path = selaura::get_data_folder() / "cached_memory.txt";              \
        std::unordered_map<std::string, uintptr_t> cache;                                          \
                                                                                                   \
        if (fs::exists(cache_path)) {                                                              \
            std::ifstream file(cache_path);                                                        \
            std::string line;                                                                      \
            while (std::getline(file, line)) {                                                     \
                std::istringstream iss(line);                                                      \
                std::string key, value_str;                                                        \
                if (iss >> key >> value_str) {                                                     \
                    try {                                                                          \
                        uintptr_t value = std::stoull(value_str, nullptr, 16);                     \
                        cache[key] = value;                                                        \
                    } catch (...) {}                                                               \
                }                                                                                  \
            }                                                                                      \
        }                                                                                          \
                                                                                                   \
        const std::string name = #func;                                                            \
        if (auto it = cache.find(name); it != cache.end()) {                                       \
            cached = it->second;                                                                   \
            return cached;                                                                         \
        }                                                                                          \
                                                                                                   \
        auto result = selaura::mem::find_pattern(value);                                           \
        if (!result || result.value() == 0) {                                                      \
            spdlog::error("Signature not found for function: {}", name);                           \
            return 0;                                                                              \
        }                                                                                          \
                                                                                                   \
        cached = result.value();                                                                   \
        cache[name] = cached;                                                                      \
                                                                                                   \
        std::ofstream out(cache_path, std::ios::trunc);                                            \
        for (const auto& [k, v] : cache)                                                           \
            out << k << " 0x" << std::uppercase << std::hex << v << '\n';                          \
                                                                                                   \
        return cached;                                                                             \
    }                                                                                              \
};

#define GET_SIG(func) selaura::patterns::signature_map<func>::value
#define RESOLVE_SIG(func) selaura::patterns::signature_map<func>::resolve()
