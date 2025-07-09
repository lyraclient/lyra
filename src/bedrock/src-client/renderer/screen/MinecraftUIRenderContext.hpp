#pragma once
#include <gsl/gsl>
#include <glm/glm.hpp>

#include "memory/patterns.hpp"

struct RectangleArea {
    float _x0;
    float _x1;
    float _y0;
    float _y1;
};

class UIComponent {
public:
    class UIControl* mOwner;
    virtual void Function0();
};
class UIControl {
    std::byte pad[0x10];
public:
    glm::vec2 position;
    uint64_t flags;
    std::string name;
private:
    std::byte pad2[0x8];
public:
    glm::vec2 bounds;
};

class MinecraftCustomUIRenderer {};

class CustomRenderComponent : public UIComponent {
    std::byte pad[8];
public:
    MinecraftCustomUIRenderer* renderer;
};

struct MinecraftUIRenderContext {
    void renderCustom_hk(gsl::not_null<CustomRenderComponent*> customRender, int pass, RectangleArea* renderAABB);
};

