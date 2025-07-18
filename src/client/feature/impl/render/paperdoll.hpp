#pragma once
#include "../../feature.hpp"
#include "../../../event/event_types.hpp"
#include "spdlog/spdlog.h"

namespace selaura {

    struct paperdoll;

    template <>
    struct feature_traits<paperdoll> {
        static constexpr auto name = hat::fixed_string{ "Paperdoll" };
        static constexpr auto description = hat::fixed_string{ "Modifies in-game paperdoll" };

        using settings = std::tuple<
            selaura::feature_setting<bool>,
            selaura::feature_setting<float>,
            selaura::feature_setting<float>
        >;
    };

    struct paperdoll : feature<paperdoll> {
        paperdoll() {
            std::get<0>(this->settings) = selaura::feature_setting<bool>("Always Show", true);
            std::get<1>(this->settings) = selaura::feature_setting<float>("Offset X", 15.0f);
            std::get<2>(this->settings) = selaura::feature_setting<float>("Offset Y", 15.0f);
        }

        void on_enable() override;
        void on_disable() override;
        void on_rendercustom_event(selaura::RenderCustom_event& event);
    };

};
