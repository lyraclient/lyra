#pragma once

namespace mce {
    struct Color {
        float r;
        float g;
        float b;
        float a;

        Color(float r, float g, float b, float a) {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }

        Color(unsigned int color) {
            this->r = static_cast<float>((color & 0xFF000000) >> 24) / 255.0f;
            this->g = static_cast<float>((color & 0x00FF0000) >> 16) / 255.0f;
            this->b = static_cast<float>((color & 0x0000FF00) >> 8) / 255.0f;
            this->a = static_cast<float>((color & 0x000000FF)) / 255.0f;
        }

        Color() {
            this->r = 0.0f;
            this->g = 0.0f;
            this->b = 0.0f;
            this->a = 0.0f;
        }
    };
};
