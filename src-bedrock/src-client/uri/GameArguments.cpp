#include "GameArguments.hpp"
#include "../../../../../src-client/core/instance.hpp"

void GameArguments::_onUri_hk(ActivationUri* uri) {
    auto ofunc = selaura::trampolines::GameArguments_onUri;

    // if (uri->verb == "selaura") std::terminate();
    (this->*ofunc)(uri);
};