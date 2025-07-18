#include "paperdoll.hpp"
#include "../../../client.hpp"

namespace selaura {
    void paperdoll::on_enable() {
        auto& evm = selaura::get()->get<selaura::event_manager>();
        evm.subscribe(&paperdoll::on_rendercustom_event, this);
    }

    void paperdoll::on_disable() {
        auto& evm = selaura::get()->get<selaura::event_manager>();
        evm.unsubscribe(&paperdoll::on_rendercustom_event, this);
    }

    void paperdoll::on_rendercustom_event(selaura::RenderCustom_event &event) {
        auto& always_show = std::get<0>(this->settings).value;
        auto& x = std::get<1>(this->settings).value;
        auto& y = std::get<2>(this->settings).value;

        if (always_show && event.component->mOwner->name == "hud_player") {
            HudPlayerRenderer* renderer = reinterpret_cast<HudPlayerRenderer*>(event.component->renderer);
            renderer->mRenderTime = 1.0f;

            event.component->mOwner->position.x = x;
            event.component->mOwner->position.y = y;
        }
    }

};