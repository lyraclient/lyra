#include "Help.hpp"
#include "../command_handler.hpp"

namespace selaura::commands {
    void help(std::istringstream&) {
        std::println("Available commands:");
        for (const auto& cmd : selaura::command_list) {
            std::println("  {} - {}", cmd.name, cmd.description);
        }
    }
};