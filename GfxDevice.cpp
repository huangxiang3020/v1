#include <glad/gl.h>
#include "GfxDevice.h"

void GfxDevice::clearColor(const glm::vec4& color) const
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GfxDevice::draw(DrawContext& context) const
{
	context.use();
	glDrawElements(GL_TRIANGLES, static_cast<int32_t>(context.iCount()), GL_UNSIGNED_INT, nullptr);
}
