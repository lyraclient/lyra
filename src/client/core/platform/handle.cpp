#include "handle.hpp"

namespace selaura {
    std::unique_ptr<handle> handle::resolve(const std::string_view& name) {
        auto result = std::make_unique<handle>();

#ifdef SELAURA_WINDOWS
        HMODULE hModule = GetModuleHandleA(name.data());
        if (!hModule) {
            throw std::runtime_error("Failed to get module handle.");
        }

        MODULEINFO moduleInfo;
        if (!GetModuleInformation(GetCurrentProcess(), hModule, &moduleInfo, sizeof(moduleInfo))) {
            throw std::runtime_error("GetModuleInformation failed.");
        }

        result->native_handle = reinterpret_cast<void*>(hModule);
        result->bytes = reinterpret_cast<std::byte*>(moduleInfo.lpBaseOfDll);
        result->size = moduleInfo.SizeOfImage;

#else
        void* libHandle = dlopen(name.data(), RTLD_NOLOAD);
        if (!libHandle) {
            throw std::runtime_error("dlopen failed.");
        }

        result->native_handle = libHandle;

        struct callback_data {
            std::string_view name;
            handle* out;
        } data{name, result.get()};

        dl_iterate_phdr([](dl_phdr_info* info, size_t, void* user_data) -> int {
            auto* data = reinterpret_cast<callback_data*>(user_data);
            if (info->dlpi_name && std::string_view(info->dlpi_name).find(data->name) != std::string_view::npos) {
                data->out->bytes = reinterpret_cast<std::byte*>(info->dlpi_addr);
                // fallback: use first loadable segment
                for (int i = 0; i < info->dlpi_phnum; ++i) {
                    if (info->dlpi_phdr[i].p_type == PT_LOAD) {
                        data->out->size = info->dlpi_phdr[i].p_memsz;
                        return 1;
                    }
                }
            }
            return 0;
        }, &data);

        if (!result->bytes || result->size == 0) {
            throw std::runtime_error("Failed to find matching library segment.");
        }
#endif

        return result;
    }

    std::unique_ptr<handle> handle::resolve() {
#ifdef SELAURA_WINDOWS
        return resolve("Minecraft.Windows.exe");
#else
        return resolve("libminecraftpe.so");
#endif
    }
};