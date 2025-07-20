#pragma once
#include <tuple>
#include <memory>
#include <utility>
#include <type_traits>

#include "impl/render/fullbright.hpp"
#include "impl/render/paperdoll.hpp"
#include "impl/render/enchant_glint.hpp"
#include "impl/render/environment.hpp"

namespace selaura {
    using feature_types = std::tuple<
        fullbright,
        paperdoll,
        enchant_glint,
        environment
    >;

    template <typename Tuple, std::size_t... Is>
    auto make_features_impl(std::index_sequence<Is...>) {
        return std::make_tuple(std::make_shared<std::tuple_element_t<Is, Tuple>>()...);
    }

    template <typename Tuple>
    auto make_features() {
        constexpr auto size = std::tuple_size_v<Tuple>;
        return make_features_impl<Tuple>(std::make_index_sequence<size>{});
    }

    class feature_manager {
    public:
        using features_t = decltype(make_features<feature_types>());

        feature_manager()
            : features(make_features<feature_types>())
        {}

        template <typename T>
        void enable() {
            if (auto f = get<T>()) {
                f->set_enabled(true);
            }
        }

        template <typename T>
        void disable() {
            if (auto f = get<T>()) {
                f->set_enabled(false);
            }
        }

        template <typename T>
        std::shared_ptr<T> get() {
            return std::get<std::shared_ptr<T>>(features);
        }

        template <typename Func>
        void for_each(Func&& func) {
            std::apply([&](auto&&... ptrs) {
                (func(ptrs), ...);
            }, features);
        }

    private:
        features_t features;
    };

}
