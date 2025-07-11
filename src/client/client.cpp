#include "client.hpp"

namespace selaura {
    void client::init() {
        try {
            auto start = std::chrono::steady_clock::now();

            auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            auto logger = std::make_shared<spdlog::logger>("client_logger", sink);
            spdlog::set_default_logger(logger);

            spdlog::set_pattern("[%T] [client/%^%l%$] %v");
            spdlog::flush_on(spdlog::level::info);

            spdlog::info("Warming signatures.");
            selaura::prewarm_signatures<>();

            auto end = std::chrono::steady_clock::now();
            auto ms = std::chrono::duration<float>(end - start).count();
            spdlog::info("Completed injection in {:.2f} ms.", ms);
        } catch (const std::exception& e) {
            spdlog::info("std::exception: {}\n", e.what());
            this->unload();
        } catch (...) {
            spdlog::info("Unknown exception occurred.");
            this->unload();
        }
    }

    void client::unload() {
    }
};