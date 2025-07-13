#pragma once
#include <string>
#include <unordered_map>

struct ActivationUri {
    std::string verb;
    std::unordered_map<std::string, std::string> arguments;
};

struct GameArguments {
    void _onUri_hk(ActivationUri* uri);
};