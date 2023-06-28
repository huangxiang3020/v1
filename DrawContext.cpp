#include "DrawContext.h"

#include <glad/gl.h>

void DrawContext::setMesh(const std::shared_ptr<Mesh>& mesh)
{
	mMesh = mesh;
}

void DrawContext::setMaterial(const std::shared_ptr<Material>& material)
{
	mMaterial = material;
}

void DrawContext::draw() const
{
	mMesh->use();
	mMaterial->use();
	glDrawElements(GL_TRIANGLES, static_cast<int32_t>(mMesh->iCount()), GL_UNSIGNED_INT, nullptr);
}



