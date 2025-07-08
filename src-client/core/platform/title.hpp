#pragma once

#include <format>

#ifdef SELAURA_WINDOWS
#include <winrt/base.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.Core.h>
#endif

namespace selaura {
    static void set_title(const std::string& title) {
#ifdef SELAURA_WINDOWS
        auto dispatcher = winrt::Windows::ApplicationModel::Core::CoreApplication::MainView().CoreWindow().Dispatcher();
        auto hTitle = winrt::to_hstring(title);
        dispatcher.RunAsync(
            winrt::Windows::UI::Core::CoreDispatcherPriority::Normal,
            [hTitle]() {
                winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Title(hTitle);
            }
        );
#endif
    }

    template <typename... Args>
    static void set_title(std::format_string<Args...> fmt_str, Args&&... args) {
        set_title(std::format(fmt_str, std::forward<Args>(args)...));
    }
}
