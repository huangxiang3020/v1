#pragma once
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

class DrawContext
{
public:
	void setVertices(const std::vector<glm::vec3>& vertices);
	void setIndices(const std::vector<uint32_t>& indices);
	void setUVs1(const std::vector<glm::vec2>& uvs1);
	void use();
	uint32_t iCount() const;
	~DrawContext();

private:
	void clean();
	void genvram();

	std::vector<glm::vec3> mVertices;
	std::vector<uint32_t> mIndices;
	std::vector<glm::vec2> mUVs1;

	uint32_t mVao = 0;
	uint32_t mVbo = 0;
	uint32_t mEbo = 0;

	bool mDirty = false;
};
