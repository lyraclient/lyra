#pragma once
#include <string>

namespace seluara {
    template <typename T>
    struct feature_setting;

    template <>
    struct feature_setting<float> {
        feature_setting() = default;
        std::string name;

        float value;
        float minimum_value;
        float maximum_value;

        feature_setting(std::string name, float default_value, float min = 0.0f, float max = 1.0f)
            : name(std::move(name)), value(default_value), minimum_value(min), maximum_value(max) {}

    };
};