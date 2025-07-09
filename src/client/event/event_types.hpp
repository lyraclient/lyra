#pragma once

namespace selaura {
    struct cancellable_event {
        void cancel() {
            this->cancelled = true;
        }
    private:
        bool cancelled;
    };

    struct frame_event {
        int fps;
    };
};