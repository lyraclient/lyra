#include "enchant_glint.hpp"
#include "../../../client.hpp"

namespace selaura {
    void enchant_glint::on_enable() {
        auto& evm = selaura::get()->get<selaura::event_manager>();
        evm.subscribe(&enchant_glint::on_renderiteminhanddescription_event, this);
    }

    void enchant_glint::on_disable() {
        auto& evm = selaura::get()->get<selaura::event_manager>();
        evm.unsubscribe(&enchant_glint::on_renderiteminhanddescription_event, this);
    }

    glm::vec4 enchant_glint::get_chroma_color(float speed, float saturation, float value) {
        using namespace std::chrono;
        float time = duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count() / 1000.0f;
        float hue = fmodf(time * speed * 60.0f, 360.0f);

        float c = value * saturation;
        float x = c * (1 - fabsf(fmodf(hue / 60.0f, 2) - 1));
        float m = value - c;

        float r = 0, g = 0, b = 0;
        if (0 <= hue && hue < 60)      r = c, g = x, b = 0;
        else if (60 <= hue && hue < 120)  r = x, g = c, b = 0;
        else if (120 <= hue && hue < 180) r = 0, g = c, b = x;
        else if (180 <= hue && hue < 240) r = 0, g = x, b = c;
        else if (240 <= hue && hue < 300) r = x, g = 0, b = c;
        else if (300 <= hue && hue < 360) r = c, g = 0, b = x;

        return { r + m, g + m, b + m, 1.0f };
    }

    void enchant_glint::on_renderiteminhanddescription_event(selaura::RenderItemInHandDescription_event &event) {
        auto& color = std::get<0>(this->settings).value;
        auto& chroma = std::get<1>(this->settings).value;
        auto& chroma_speed = std::get<2>(this->settings).value;

        if (chroma) {
            auto chroma_col = get_chroma_color(chroma_speed);
            event.color = { chroma_col.r, chroma_col.g, chroma_col.b };
            event.alpha = chroma_col.a;
        } else {
            event.color = {color.r / 255, color.g / 255, color.b / 255};
            event.alpha = color.a;
        }
    }

};