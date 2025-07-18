#pragma once
#include "../../feature.hpp"
#include "../../../event/event_types.hpp"
#include "spdlog/spdlog.h"

namespace selaura {

    struct environment;

    template <>
    struct feature_traits<environment> {
        static constexpr auto name = hat::fixed_string{ "Environment" };
        static constexpr auto description = hat::fixed_string{ "Modifies in-game environment" };

        using settings = std::tuple<
            selaura::feature_setting<float>,
            selaura::feature_setting<bool>,
            selaura::feature_setting<float>
        >;
    };

    struct environment : feature<environment> {
        environment() {
            std::get<0>(this->settings) = selaura::feature_setting<float>("Time", 0.5f, 0.0f, 1.0f);
            std::get<1>(this->settings) = selaura::feature_setting<bool>("Change Time Passage Speed", true);
            std::get<2>(this->settings) = selaura::feature_setting<float>("Time Passage Speed", 50.0f, 0.0f, 100.f);
        }

        void on_enable() override;
        void on_disable() override;
        void on_rendercustom_event(selaura::getTimeOfDay_event& event);
    };

};
