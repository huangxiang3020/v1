#include "Material.h"

Material::Material()
{

}

void Material::use() const
{
	mShader->use();
	mShader->setVec4("_Color", glm::vec4(1, 1, 0, 0));
	mShader->setInt("_MainTex", 0);
	mTexture->active(0);
}
