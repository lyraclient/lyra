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
            selaura::feature_setting<glm::vec4>,
            selaura::feature_setting<bool>,
            selaura::feature_setting<float>
        >;
    };

    struct enchant_glint : feature<enchant_glint> {
        enchant_glint() {
            std::get<0>(this->settings) = selaura::feature_setting<glm::vec4>("Color", {73, 36, 116, 1});
            std::get<1>(this->settings) = selaura::feature_setting<bool>("Chroma", true);
            std::get<2>(this->settings) = selaura::feature_setting<float>("Chroma Speeding", 1.0f, 0.0f, 5.0f, 0.1f);
        }

        void on_enable() override;
        void on_disable() override;
        glm::vec4 get_chroma_color(float speed = 1.0f, float saturation = 1.0f, float value = 1.0f);
        void on_renderiteminhanddescription_event(selaura::RenderItemInHandDescription_event& event);
    };

};