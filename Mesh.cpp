#include "Mesh.h"
#include <glad/gl.h>

void Mesh::setVertices(const std::vector<glm::vec3>& vertices)
{
	mVertices = vertices;
	mDirty = true;
}

void Mesh::setIndices(const std::vector<uint32_t>& indices)
{
	mIndices = indices;
	mDirty = true;
}

void Mesh::setUVs(const std::vector<glm::vec2>& uvs1)
{
	mUVs = uvs1;
	mDirty = true;
}

void Mesh::setNormals(const std::vector<glm::vec3>& normals)
{
	mNormals = normals;
	mDirty = true;
}

void Mesh::use()
{
	if (mDirty)
	{
		genvram();
		mDirty = true;
	}
	glBindVertexArray(mVao);
	glDrawElements(GL_TRIANGLES, static_cast<int32_t>(iCount()), GL_UNSIGNED_INT, nullptr);
}

uint32_t Mesh::iCount() const
{
	return static_cast<uint32_t>(mIndices.size());
}

void Mesh::clean()
{
	if (mVao)
	{
		glDeleteVertexArrays(1, &mVao);
		mVao = 0;
	}

	if (mVbo)
	{
		glDeleteBuffers(1, &mVbo);
		mVbo = 0;
	}

	if (mEbo)
	{
		glDeleteBuffers(1, &mEbo);
		mEbo = 0;
	}
}

void Mesh::genvram()
{
	clean();
	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);

	const auto sizeVertices = static_cast<int32_t>(mVertices.size() * sizeof(glm::vec3));
	const auto sizeNormals = static_cast<int32_t>(mNormals.size() * sizeof(glm::vec3));
	const auto sizeUVs = static_cast<int32_t>(mUVs.size() * sizeof(glm::vec2));

	glGenBuffers(1, &mVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeVertices + sizeNormals + sizeUVs, nullptr,GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeVertices, mVertices.data());
	glBufferSubData(GL_ARRAY_BUFFER, sizeVertices, sizeNormals, mNormals.data());
	glBufferSubData(GL_ARRAY_BUFFER, sizeVertices + sizeNormals, sizeUVs, mUVs.data());

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
	                      reinterpret_cast<const void*>(static_cast<int64_t>(sizeVertices)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2),
	                      reinterpret_cast<const void*>(static_cast<int64_t>(sizeVertices + sizeNormals)));
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &mEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<int32_t>(mIndices.size() * sizeof(uint32_t)), mIndices.data(),
	             GL_STATIC_DRAW);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	clean();
}
