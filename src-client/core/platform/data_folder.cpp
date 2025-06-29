#include "data_folder.hpp"

namespace selaura {
    std::filesystem::path get_data_folder() {
        static std::filesystem::path dir = {};
        if (dir.empty()) {
#ifdef SELAURA_WINDOWS
            char* localAppData = nullptr;
            size_t size = 0;
            _dupenv_s(&localAppData, &size, "APPDATA");

            if (localAppData) {
                dir = std::filesystem::path(localAppData + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\Selaura"));
            }
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