#pragma once
#include "../memory/sdk/world/BaseLightTextureImageBuilder.hpp"

namespace selaura {
    struct cancellable_event {
        void cancel() {
            this->cancelled = true;
        }
    private:
        bool cancelled;
    };

    struct BaseLightTextureImageBuilder_event {
        bool mNightvisionActive;
        float mNightvisionScale;
    };
};