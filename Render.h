#pragma once
#include "Camera.h"
#include "Node.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"

class Render : public Component, public std::enable_shared_from_this<Render>
{
public:
	Render(const std::shared_ptr<Node>& node);
	void draw(const std::shared_ptr<Camera>& camera) const;
	void awake() override;
	void onDestroy() override;
	void setMesh(const std::shared_ptr<Mesh>& mesh);
	void setShader(const std::shared_ptr<Shader>& shader);
	void setTexture(const std::shared_ptr<Texture>& texture);

protected:
	std::shared_ptr<Mesh> mMesh;
	std::shared_ptr<Shader> mShader;
	std::shared_ptr<Texture> mTexture;
};
