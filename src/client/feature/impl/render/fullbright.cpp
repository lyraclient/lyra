#include "fullbright.hpp"
#include "../../../client.hpp"

namespace selaura {
    void fullbright::on_enable() {
        auto& evm = selaura::get()->get<selaura::event_manager>();
        evm.subscribe(&fullbright::on_baselighttextureimagebuilder_event, this);
    }

    void fullbright::on_disable() {
        auto& evm = selaura::get()->get<selaura::event_manager>();
        evm.unsubscribe(&fullbright::on_baselighttextureimagebuilder_event, this);
    }

    void fullbright::on_baselighttextureimagebuilder_event(selaura::BaseLightTextureImageBuilder_event &event) {
        auto& brightness = std::get<0>(this->settings).value;

        event.mNightvisionActive = true;
        event.mNightvisionScale = brightness;
    }

};