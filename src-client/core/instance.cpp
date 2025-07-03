#include "instance.hpp"
#include <Windows.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "event/event_types.hpp"

void __fastcall render_detour(void* ctx, void* clientinstance, void* owner, int pass, void* renderAABB) {
    spdlog::info("SplashTextRenderer::render intercepted");
}

selaura::instance::instance() {
    auto startTime = std::chrono::high_resolution_clock::now();
#ifdef _DEBUG
    selaura::console::init();
#endif
    selaura::hook_init();

    auto log_file = selaura::get_data_folder() / "logs.txt";

    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_file.string(), true));
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());

    auto logger = std::make_shared<spdlog::logger>("selaura", begin(sinks), end(sinks));
    logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
    logger->set_level(spdlog::level::debug);
    logger->flush_on(spdlog::level::debug);

    spdlog::set_default_logger(logger);

    spdlog::info("Detected Minecraft version: {}", selaura::version::get_formatted_version());

    this->get<patch_manager>().init();

#ifdef _DEBUG
    std::string type = "debug";
#else
    std::string type = "release";
#endif
    selaura::set_title("Selaura Client {} (version/{}/{})", selaura::version::get_formatted_version(), CLIENT_VERSION, type);

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = endTime - startTime;

    spdlog::info("Successfully injected [{:.2f}s]", duration.count());
}

std::shared_ptr<selaura::instance> selaura::get() {
    return selaura::inst;
}
