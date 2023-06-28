#include "Material.h"

Material::Material()
{
	const char* vertexCode = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"out vec2 uv1;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"	uv1 = vec2(aPos.x, aPos.y);\n"
		"}";
	const char* fragmentCode = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 uv1;\n"
		"uniform vec4 _Color;\n"
		"uniform sampler2D _MainTex;\n"
		"void main()\n"
		"{\n"
		"   FragColor = texture(_MainTex, uv1);\n"
		"}\n";
	mShader = std::make_shared<Shader>(vertexCode, fragmentCode);
	mTexture = std::make_shared<Texture>("C:/Users/hx/Documents/Project/v1/container.jpg");
}

void Material::use() const
{
	mShader->use();
	mShader->setVec4("_Color", glm::vec4(1, 1, 0, 0));
	mShader->setInt("_MainTex", 0);
	mTexture->active(0);
}
