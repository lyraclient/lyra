#include "console.hpp"

namespace selaura {
    void console::init() {
#ifdef SELAURA_WINDOWS
        AllocConsole();
        FILE* fp;
        freopen_s(&fp, "CONOUT$", "w", stdout);
        freopen_s(&fp, "CONOUT$", "w", stderr);
        freopen_s(&fp, "CONIN$", "r", stdin);
#endif
    }
};