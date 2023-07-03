#include "DrawContext.h"

void DrawContext::setMesh(const std::shared_ptr<Mesh>& mesh)
{
	mMesh = mesh;
}

void DrawContext::setShader(const std::shared_ptr<Shader>& shader)
{
	mShader = shader;
}

void DrawContext::setTexture(const std::shared_ptr<Texture>& texture)
{
	mTexture = texture;
}

void DrawContext::draw() const
{
	mShader->use();
	mShader->setVec4("_Color", glm::vec4(1, 1, 0, 0));
	mShader->setInt("_MainTex", 0);
	mTexture->active(0);
	mMesh->use();
}
