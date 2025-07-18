#include "platform.hpp"

selaura::dynamic_module& selaura::get_dynamic_module(std::string_view name) {
    static dynamic_module mod{};
    if (mod.valid()) return mod;

#ifdef SELAURA_WINDOWS
    HMODULE handle = GetModuleHandleA(name.data());
    if (!handle) return mod;

    MODULEINFO moduleinfo;
    if (!GetModuleInformation(GetCurrentProcess(), handle, &moduleinfo, sizeof(moduleinfo))) return mod;

    mod.native_handle = reinterpret_cast<void*>(handle);
    mod.base_address = reinterpret_cast<std::uintptr_t>(moduleinfo.lpBaseOfDll);
    mod.size = moduleinfo.SizeOfImage;

    mod.memory_view = std::span<std::byte>{reinterpret_cast<std::byte*>(mod.base_address), mod.size};
#else
    void* handle = dlopen(name.data(), RTLD_NOLOAD);
    if (!handle) return mod;

    mod.native_handle = reinterpret_cast<void*>(handle);
    dl_iterate_phdr([](dl_phdr_info* info, size_t, void* mod_ptr) -> int {
        auto* out = static_cast<dynamic_module*>(mod_ptr);
        if (!info->dlpi_name) return 0;

        if (std::strstr(info->dlpi_name, out->name_match)) {
            out->base_address = info->dlpi_addr;
            for (int i = 0; i < info->dlpi_phnum; ++i) {
                if (info->dlpi_phdr[i].p_type == PT_LOAD) {
                    out->size = info->dlpi_phdr[i].p_memsz;
                    break;
                }
            }
            out->memory_view = std::span<std::byte>{
                reinterpret_cast<std::byte*>(out->base_address),
                out->size
            };
            return 1;
        }
        return 0;
    }, &mod);
#endif

    return mod;
}

selaura::dynamic_module& selaura::get_dynamic_module() {
#ifdef SELAURA_WINDOWS
    return get_dynamic_module("Minecraft.Windows.exe");
#else
    return get_dynamic_module("libminecraftpe.so");
#endif
}
