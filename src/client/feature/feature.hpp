#pragma once
#include <vector>
#include <libhat/fixed_string.hpp>

#include "setting.hpp"

namespace selaura {
    template <typename T>
    struct feature_traits {
        static constexpr auto name = hat::fixed_string { "Unknown" };
        static constexpr auto description = hat::fixed_string { "Unknown" };

        using settings = std::tuple<>;
    };

    template <typename T>
    struct feature {
        virtual ~feature() = default;
        using details = feature_traits<T>;
        using settings_type = typename details::settings;

        void set_enabled(bool state = true) {
            this->enabled = state;

            if (this->enabled) {
                on_enable();
            } else {
                on_disable();
            }
        }
        [[nodiscard]] bool is_enabled() const {
            return this->enabled;
        }

        void toggle() {
            set_enabled(!this->enabled);
        }

        void set_hotkey(int hotkey = 0) {
            this->hotkey = hotkey;
        }

        [[nodiscard]] int get_hotkey() const {
            return this->hotkey;
        }

        virtual void on_enable() = 0;
        virtual void on_disable() = 0;
        settings_type settings{};
    private:
        bool enabled = false;
        int hotkey = 0;
    };
};