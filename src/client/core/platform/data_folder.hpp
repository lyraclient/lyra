#pragma once
#include <filesystem>

#ifdef SELAURA_WINDOWS
#include <winrt/Windows.Storage.h>
#endif

namespace selaura {
    std::filesystem::path get_data_folder();
};