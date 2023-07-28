#pragma once
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include "Object.h"
#include "ObjectDefines.h"

class Mesh :public Object
{
	REGISTER_CLASS(Mesh)
	void setVertices(const std::vector<glm::vec3>& vertices);
	void setIndices(const std::vector<uint32_t>& indices);
	void setUVs(const std::vector<glm::vec2>& uvs1);
	void setNormals(const std::vector<glm::vec3>& normals);
	void use();
	uint32_t iCount() const;
	~Mesh() override;

private:
	void clean();
	void genvram();

	std::vector<glm::vec3> mVertices;
	std::vector<uint32_t> mIndices;
	std::vector<glm::vec2> mUVs;
	std::vector<glm::vec3> mNormals;

	uint32_t mVao = 0;
	uint32_t mVbo = 0;
	uint32_t mEbo = 0;

	bool mDirty = false;
};
