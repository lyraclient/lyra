#pragma once

#include <format>
#ifdef SELAURA_WINDOWS
#include <winrt/base.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.Core.h>
#endif

namespace selaura {
    struct title {
        static void set(const std::string& title);

        template <typename... Args>
        static void set(std::format_string<Args...> fmt_str, Args&&... args) {
            set(std::format(fmt_str, std::forward<Args>(args)...));
        }
    };
};