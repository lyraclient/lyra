#pragma once
#include <memory>
#include <tuple>
#include <filesystem>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "platform/all.hpp"
#include "builder.hpp"
#include "options.hpp"

#include "../memory/memory.hpp"
#include "../memory/patterns.hpp"
#include "../memory/patches.hpp"

#include "event/event_manager.hpp"

namespace selaura {
    struct instance : public std::enable_shared_from_this<instance> {
        instance();
        using components_t = std::tuple<
            event_manager,
            sbui::builder,
            patch_manager
        >;

        template <typename component>
        constexpr auto& get() {
            return std::get<component>(components);
        }

        std::shared_ptr<instance> get() {
            return std::dynamic_pointer_cast<instance>(shared_from_this());
        };
    private:
        components_t components{};
        std::filesystem::path data_folder;
    };

    inline std::shared_ptr<selaura::instance> inst;
    std::shared_ptr<selaura::instance> get();
};