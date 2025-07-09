#include "version.hpp"

selaura::version selaura::version::get_minecraft_version() {
#ifdef SELAURA_WINDOWS
    const winrt::Windows::ApplicationModel::Package package = winrt::Windows::ApplicationModel::Package::Current();
    auto [major, minor, build, revision] = package.Id().Version();

    return {major, minor, build, revision};
#else
#endif
    return {0, 0, 0, 0};
}

std::string selaura::version::get_formatted_version() {
    auto version = get_minecraft_version();
    return std::to_string(version.major) + "." + std::to_string(version.minor) + "." + std::to_string(version.build / 100);
}
