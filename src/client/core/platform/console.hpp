#pragma once

#ifdef SELAURA_WINDOWS
#include <Windows.h>
#include <cstdio>
#endif

namespace selaura {
    struct console {
        static void init();
    };
};