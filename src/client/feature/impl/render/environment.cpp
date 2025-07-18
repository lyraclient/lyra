#include "environment.hpp"
#include "../../../client.hpp"

namespace selaura {
    void environment::on_enable() {
        auto& evm = selaura::get()->get<selaura::event_manager>();
        evm.subscribe(&environment::on_rendercustom_event, this);
    }

    void environment::on_disable() {
        auto& evm = selaura::get()->get<selaura::event_manager>();
        evm.unsubscribe(&environment::on_rendercustom_event, this);
    }

    void environment::on_rendercustom_event(selaura::getTimeOfDay_event &event) {
        auto& time = std::get<0>(this->settings).value;
        auto& time_passage_speed_bool = std::get<1>(this->settings).value;
        auto& time_passage_speed = std::get<2>(this->settings).value;

        if (time_passage_speed_bool) {
            event.time *= time_passage_speed;
        } else {
            event.overriden_time = time;
        }
    }

};