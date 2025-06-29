#include "data_folder.hpp"

namespace selaura {
    std::filesystem::path get_data_folder() {
        static std::filesystem::path dir = {};
        if (dir.empty()) {
#ifdef SELAURA_WINDOWS
            auto roamingFolder = winrt::Windows::Storage::ApplicationData::Current().RoamingFolder();
            std::wstring path = roamingFolder.Path().c_str();
            dir = std::filesystem::path(path) / "Selaura";
#elif defined(SELAURA_LINUX)
            dir = "/data/data/com.mojang.minecraftpe/Selaura";
#elif defined(SELAURA_ANDROID)
            dir = "/data/data/com.selauraclient.launcher/Selaura";
#endif
            std::filesystem::create_directories(dir);
        }

        return dir;
    }
};