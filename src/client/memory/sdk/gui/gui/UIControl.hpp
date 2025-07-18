#pragma once
#include <gsl/gsl>
#include <glm/glm.hpp>

#include <string>

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