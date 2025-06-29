#include <thread>
#include "core/instance.hpp"

#ifdef SELAURA_WINDOWS
#include <Windows.h>
#include <Psapi.h>
BOOL APIENTRY DllMain(HMODULE hmodule, DWORD dw_reason, LPVOID lp_reserved)
#elif SELAURA_LINUX
#include <dlfcn.h>
#include <link.h>
extern "C" [[gnu::visibility("default")]] void mod_init()
#elif SELAURA_ANDROID
#include <jni.h>
#include <dlfcn.h>
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
#endif
{
#ifdef SELAURA_WINDOWS
    if (dw_reason == DLL_PROCESS_ATTACH) {
        const HMODULE mc_handle = GetModuleHandleW(L"Minecraft.Windows.exe");
        if (mc_handle == nullptr) return false;
        DisableThreadLibraryCalls(mc_handle);
#else
    {
#endif
        std::thread([]() {
            selaura::inst = std::make_shared<selaura::instance>();
        }).detach();
    }

#ifdef SELAURA_ANDROID
    selaura_platform::set_vm(vm);

    return JNI_VERSION_1_6;
#elif SELAURA_WINDOWS
    return true;
#endif
}