#include "GameArguments.hpp"
#include "../../../patcher.hpp"

void GameArguments::_onUri_hk(ActivationUri* uri) {
    //if (uri->verb == "selaura") std::terminate();
    selaura::call_fn<&GameArguments::_onUri_hk>(this, uri);
}