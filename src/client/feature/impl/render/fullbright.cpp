#include "fullbright.hpp"
#include "../../../client.hpp"

namespace selaura {
    void fullbright::on_enable() {
        selaura::get()->get<selaura::event_manager>().subscribe<selaura::BaseLightTextureImageBuilder_event>(&fullbright::on_baselighttextureimagebuilder_event, this);
    }

    void fullbright::on_disable() {
        selaura::get()->get<selaura::event_manager>().unsubscribe<selaura::BaseLightTextureImageBuilder_event>(&fullbright::on_baselighttextureimagebuilder_event, this);
    }

    void fullbright::on_baselighttextureimagebuilder_event(selaura::BaseLightTextureImageBuilder_event& event) {
        event.mNightvisionActive = true;
        event.mNightvisionScale = 1.f;
    }
};