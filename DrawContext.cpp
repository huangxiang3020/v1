#include "DrawContext.h"
#include <glm/gtc/matrix_transform.hpp>

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

void DrawContext::draw(const Camera& camera) const
{
	constexpr auto model = glm::mat4(1.0f);
	const auto view = glm::lookAt(camera.position, camera.position - camera.forward, camera.up);
	const auto proj = glm::perspective(camera.fov, camera.aspect, camera.near, camera.far);
	const auto projView = proj * view;

	mShader->use();
	mShader->setMat4("_Model", model);
	mShader->setMat4("_ProjView", projView);
	mShader->setVec4("_Color", glm::vec4(1, 1, 0, 0));
	mShader->setInt("_MainTex", 0);
	mTexture->active(0);
	mMesh->use();
}
