#pragma once
#include <string>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

class GfxDevice
{
public:
	void clearColor(const glm::vec4& color) const;

	void setVertices(const std::vector<glm::vec3>& vertices);

	void setIndices(const std::vector<uint32_t>& indices);

	void setUVs1(const std::vector<glm::vec2>& uvs1);

	void setShader(const std::string& vertexSource, const std::string& fragmentSource);

	void draw();

	void clean();

	~GfxDevice();

private:
	std::vector<glm::vec3> mVertices;
	std::vector<uint32_t> mIndices;
	std::vector<glm::vec2> mUVs1;

	uint32_t mVao = 0;
	uint32_t mVbo = 0;
	uint32_t mEbo = 0;
	uint32_t mShaderProgram = 0;
};
