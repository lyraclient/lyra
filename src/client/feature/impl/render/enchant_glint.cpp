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

    void enchant_glint::on_renderiteminhanddescription_event(selaura::RenderItemInHandDescription_event &event) {
        auto& color = std::get<0>(this->settings).value;
        event.color = {color.r / 255, color.g / 255, color.b / 255};
        event.alpha = color.a;
    }

};