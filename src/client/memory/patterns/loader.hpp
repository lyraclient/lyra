#pragma once

#include <future>
#include <vector>
#include <string_view>
#include <spdlog/spdlog.h>

namespace selaura::patterns {
    using sig_resolver = std::function<uintptr_t()>;

    struct sig_task {
        std::string_view name;
        sig_resolver resolver;
    };

    inline void resolve_all_signatures_parallel(const std::vector<sig_task>& tasks) {
        std::vector<std::future<uintptr_t>> futures;
        futures.reserve(tasks.size());

        for (const auto& task : tasks) {
            futures.push_back(std::async(std::launch::async, [task]() {
                uintptr_t result = task.resolver();
                if (!result) spdlog::error("Failed to resolve: {}", task.name);
                return result;
            }));
        }

        for (auto& f : futures) {
            f.wait();
        }
    }
}

namespace selaura {
    void resolve_signatures();
};
