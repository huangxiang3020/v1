#include "Render.h"

#include "CameraManager.h"
#include "RenderManager.h"

Render::Render(const std::shared_ptr<Node>& node) : Component(node)
{
}

void Render::draw(const std::shared_ptr<Camera>& camera) const
{
	const auto modelLocalToWorld = getNode()->getLocalToWorldMatrix();
	const auto cameraNode = camera->getNode();
	const auto cameraLocalToWorld = cameraNode->getLocalToWorldMatrix();

	const glm::vec3 cameraForward = glm::normalize(glm::vec3(cameraLocalToWorld[2]));
	const glm::vec3 cameraTarget = cameraNode->getPosition() + cameraForward;
	const auto view = glm::lookAt(cameraNode->getPosition(), cameraTarget,
	                              glm::normalize(glm::vec3(cameraLocalToWorld[1])));
	const auto proj = glm::perspective(camera->getFov(), camera->getAspect(), camera->getNear(), camera->getFar());
	const auto projView = proj * view;

	mShader->use();
	mShader->setMat4("_Model", modelLocalToWorld);
	mShader->setMat4("_ProjView", projView);
	mShader->setInt("_MainTex", 0);
	// Light
	mShader->setVec3("_LightDirection", glm::vec3(0, 0, 1));
	mShader->setVec4("_LightColor", glm::vec4(1, 1, 1, 1));
	mShader->setVec4("_AmbientColor", glm::vec4(0.1f, 0.1f, 0.1f, 0.1f));

	mTexture->active(0);
	mMesh->use();
}

void Render::awake()
{
	const auto render = shared_from_this();
	RenderManager::instance().add(render);
}

void Render::onDestroy()
{
	const auto render = shared_from_this();
	RenderManager::instance().remove(render);
}

void Render::setMesh(const std::shared_ptr<Mesh>& mesh)
{
	mMesh = mesh;
}

void Render::setShader(const std::shared_ptr<Shader>& shader)
{
	mShader = shader;
}

void Render::setTexture(const std::shared_ptr<Texture>& texture)
{
	mTexture = texture;
}
