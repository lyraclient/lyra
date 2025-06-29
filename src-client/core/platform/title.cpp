#include "title.hpp"

void selaura::title::set(const std::string& title) {
#ifdef SELAURA_WINDOWS
    winrt::Windows::ApplicationModel::Core::CoreApplication::MainView().CoreWindow().Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, [title]() {
        winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Title(winrt::to_hstring(title));
    });
#endif
}