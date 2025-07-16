#include "feature.hpp"

namespace selaura {
    void feature::set_enabled(bool state) {
        this->enabled = state;

        if (this->enabled) on_enable();
        if (!this->enabled) on_disable();
    }

    bool feature::get_enabled() {
        return this->enabled;
    }

    void feature::toggle() {
        set_enabled(!this->enabled);
    }

    void feature::set_hotkey(int key) {
        this->hotkey = key;
    }

    int feature::get_hotkey() {
        return this->hotkey;
    }

    const glm::vec2& visual_feature::get_feature_pos() {
        return this->pos;
    }

    const glm::vec2& visual_feature::get_feature_size() {
        return this->size;
    }

    void visual_feature::set_element_size(const glm::vec2& size) {
        this->size = size;
    }

    void visual_feature::set_element_pos(const glm::vec2 &pos) {
        this->pos = pos;
    }

};