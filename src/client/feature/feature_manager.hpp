#pragma once
#include <tuple>
#include "impl/render/fullbright.hpp"

namespace selaura {
    struct feature_manager {
        using features_t = std::tuple<
            fullbright
        >;

        template <typename feature>
        constexpr auto& get() {
            return std::get<feature>(features);
        }

        template <typename Func>
        void for_each(Func&& func) {
            for_each_impl(std::forward<Func>(func), std::make_index_sequence<std::tuple_size_v<features_t>>{});
        }
    private:
        features_t features;

        template <typename Func, std::size_t... Is>
        void for_each_impl(Func&& func, std::index_sequence<Is...>) {
            (func(&std::get<Is>(features)), ...);
        }
    };
};