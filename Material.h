#pragma once
#include <memory>
#include "Shader.h"
#include "Texture.h"

class Material
{
public:
	Material();
	void use() const;

private:
	std::shared_ptr<Shader> mShader;
	std::shared_ptr<Texture> mTexture;
};
