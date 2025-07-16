#pragma once
#include "../../feature.hpp"
#include "../../../event/event_types.hpp"

namespace selaura {
    struct fullbright : public feature {
        void on_enable() override;
        void on_disable() override;

        static void on_baselighttextureimagebuilder_event(selaura::BaseLightTextureImageBuilder_event& event);
    };

    template <>
    struct selaura::feature_traits<fullbright> {
        static constexpr auto name = hat::fixed_string{ "Fullbright" };
        static constexpr auto description = hat::fixed_string{ "Brightens the world around you." };
    };
};