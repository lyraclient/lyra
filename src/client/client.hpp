#pragma once
#include <exception>
#include <memory>
#include <tuple>
#include <print>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "memory/signatures.hpp"

namespace selaura {
    template <typename T, typename... Ts>
    concept one_of = (std::same_as<T, Ts> || ...);

    template <typename... subsystems_t>
    struct client_base : std::enable_shared_from_this<client_base<subsystems_t...>> {
        using subsystems_tuple_t = std::tuple<std::shared_ptr<subsystems_t>...>;
        client_base() : subsystems{std::make_tuple(std::make_shared<subsystems_t>()...)} {};

        template <typename T>
        requires one_of<T, subsystems_t...>
        constexpr std::shared_ptr<T> get() {
            return std::get<std::shared_ptr<T>>(subsystems);
        }
    private:
        subsystems_tuple_t subsystems{};
    };

    struct client : public client_base<> {
        void init();
        void unload();
    };

    inline std::shared_ptr<client> client_instance;
    inline std::shared_ptr<client> get() {
        return client_instance;
    }
};