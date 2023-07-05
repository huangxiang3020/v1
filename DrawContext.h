#pragma once
#include <memory>
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

class DrawContext
{
public:
	void setMesh(const std::shared_ptr<Mesh>& mesh);
	void setShader(const std::shared_ptr<Shader>& shader);
	void setTexture(const std::shared_ptr<Texture>& texture);
	void draw(const Camera& camera) const;
private:
	std::shared_ptr<Mesh> mMesh;
	std::shared_ptr<Shader> mShader;
	std::shared_ptr<Texture> mTexture;
};
