#pragma once
#include "DrawContext.h"
#include <glm/vec4.hpp>

class GfxDevice
{
public:
	void clearColor(const glm::vec4& color) const;
	void draw(DrawContext& context) const;
};
