#pragma once
#include <string>

#ifdef SELAURA_WINDOWS
#include <winrt/base.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.Core.h>
#endif

namespace selaura {
    struct version {
        int major;
        int minor;
        int build;
        int revision;

        version(int maj, int min, int bld, int rev)
            : major(maj), minor(min), build(bld), revision(rev) {}

        static version get_minecraft_version();
        static std::string get_formatted_version();
    };
};