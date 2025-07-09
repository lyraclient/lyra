#include "hook.hpp"

namespace selaura {
    void hook_init() {
#ifdef SELAURA_WINDOWS
        MH_Initialize();
#endif
    }
    void hook_install(void* target, void* detour, void** original) {
#ifdef SELAURA_WINDOWS
        MH_CreateHook(target, detour, original);
        MH_EnableHook(target);
#else
        DobbyHook(target, detour, original);
#endif
    }
};