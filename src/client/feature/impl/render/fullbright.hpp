#pragma once
#include "../../feature.hpp"
#include "../../../event/event_types.hpp"
#include "spdlog/spdlog.h"

namespace selaura {

    struct fullbright;

    template <>
    struct feature_traits<fullbright> {
        static constexpr auto name = hat::fixed_string{ "Fullbright" };
        static constexpr auto description = hat::fixed_string{ "Maximizes world brightness" };

        using settings = std::tuple<
            seluara::feature_setting<float>
        >;
    };

    struct fullbright : feature<fullbright> {
        fullbright() {
            auto& brightness = std::get<0>(this->settings);
            brightness = seluara::feature_setting<float>("Brightness", 1.0f, 0.0f, 1.0f);
        }

        void on_enable() override;
        void on_disable() override;
        void on_baselighttextureimagebuilder_event(selaura::BaseLightTextureImageBuilder_event& event);
    };

};
