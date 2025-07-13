#pragma once
#include "../gui/UIControl.hpp"

class UIComponent {
public:
    class UIControl* mOwner;
    virtual void Function0();
};