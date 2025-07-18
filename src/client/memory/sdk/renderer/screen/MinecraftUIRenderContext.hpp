#pragma once
#include <gsl/gsl>
#include <glm/glm.hpp>

#include "../../gui/controls/UIComponent.hpp"
#include "../../gui/controls/renderers/HudPlayerRenderer.hpp"
#include "../../gui/controls/renderers/SplashTextRenderer.hpp"

class MinecraftCustomUIRenderer {};

struct RectangleArea {
    float _x0;
    float _x1;
    float _y0;
    float _y1;
};

class CustomRenderComponent : public UIComponent {
    std::byte pad[8];
public:
    MinecraftCustomUIRenderer* renderer;
};

struct MinecraftUIRenderContext {
    void renderCustom_hk(gsl::not_null<CustomRenderComponent*> customRender, int pass, RectangleArea* renderAABB);
};