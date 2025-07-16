#pragma once
#include <memory>
#include <libhat/fixed_string.hpp>
#include <glm/glm.hpp>

#include "setting.hpp"

namespace selaura {
    template <typename T>
    struct feature_traits {
        static constexpr auto name = hat::fixed_string{ "Unknown" };
        static constexpr auto description = hat::fixed_string{ "Unknown" };
    };

    struct feature {
        feature() = default;
        virtual ~feature() = default;

        void set_enabled(bool state = true);
        [[nodiscard]] bool get_enabled();
        void toggle();

        template <typename setting_t = feature_settings, typename... args_t>
        auto* add_setting(args_t... args) {
            return settings.emplace_back(std::make_unique<setting_t>(std::forward<args_t>(args)...)).get();
        }

        [[nodiscard]] const std::vector<std::unique_ptr<feature_settings>>& getSettings() const {
            return settings;
        }

        void set_hotkey(int key = 0);
        [[nodiscard]] int get_hotkey();

        virtual void on_enable() = 0;
        virtual void on_disable() = 0;
    private:
        bool enabled = false;
        int hotkey = 0;

        std::vector<std::unique_ptr<selaura::feature_settings>> settings;
    };

    struct visual_feature : public feature {
        const glm::vec2& get_feature_size();
        const glm::vec2& get_feature_pos();

        void set_element_size(const glm::vec2& size);
        void set_element_pos(const glm::vec2& pos);
    private:
        glm::vec2 pos{};
        glm::vec2 size{};
    };
};