#pragma once
#include "../../feature.hpp"
#include "../../../event/event_types.hpp"
#include "spdlog/spdlog.h"

namespace selaura {

    struct enchant_glint;

    template <>
    struct feature_traits<enchant_glint> {
        static constexpr auto name = hat::fixed_string{ "Enchantment Glint" };
        static constexpr auto description = hat::fixed_string{ "Modifies the color of the enchantment glint on items" };

        using settings = std::tuple<
            selaura::feature_setting<glm::vec4>
        >;
    };

    struct enchant_glint : feature<enchant_glint> {
        enchant_glint() {
            std::get<0>(this->settings) = selaura::feature_setting<glm::vec4>("Color", {73, 36, 116, 1});
        }

        void on_enable() override;
        void on_disable() override;
        void on_renderiteminhanddescription_event(selaura::RenderItemInHandDescription_event& event);
    };

};