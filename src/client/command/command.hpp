#pragma once
#include <string_view>
#include <sstream>

namespace selaura {
    using command_fn = void(*)(std::istringstream&);

    struct command {
        std::string_view name;
        std::string_view description;
        command_fn handler;
    };
}