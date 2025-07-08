#include <../src-client/plugins/plugin.hpp>

class ExamplePlugin : public selaura::plugin {
public:
    ExamplePlugin() {
        _name = "Example Plugin";
        _desc = "This plugin doesn't have any functionality by itself!";
        _author = "notchyves";
        _version = {1, 2, 3};
    }

    void on_load(std::shared_ptr<selaura::runtime> runtime) override {
        runtime->debug("hello");
        runtime->debug("splashtextrenderer::render value: {}", runtime->sig("48 89 5C 24 18 55 56 57 48 8D AC 24 50 FC FF FF 48 81 EC B0 04 00 00 48 8B FA").value());
    }
};

extern "C" SELAURA_API selaura::plugin* SelauraRuntime_RegisterPlugin() {
    static ExamplePlugin instance;
    return &instance;
}