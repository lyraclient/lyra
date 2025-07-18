#pragma once
#include <string>
#include <glm/glm.hpp>

namespace selaura {
    template <typename T>
    struct feature_setting;

    template <>
    struct feature_setting<float> {
        feature_setting() = default;
        std::string name;

        float value;
        float minimum_value;
        float maximum_value;
        float step;

        feature_setting(std::string name, float default_value, float min = 0.0f, float max = 1.0f, float step = 1.0f)
            : name(std::move(name)), value(default_value), minimum_value(min), maximum_value(max) {}

    };

    template <>
    struct feature_setting<bool> {
        feature_setting() = default;
        std::string name;

        bool value;

        feature_setting(std::string name, bool default_value)
            : name(std::move(name)), value(default_value) {}

    };

    template <>
    struct feature_setting<glm::vec4> {
        feature_setting() = default;
        std::string name;

        glm::vec4 value;

        feature_setting(std::string name, glm::vec4 default_value)
            : name(std::move(name)), value(default_value) {}

    };
};