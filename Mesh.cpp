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

void Mesh::setUVs1(const std::vector<glm::vec2>& uvs1)
{
	mUVs1 = uvs1;
	mDirty = true;
}

void Mesh::use()
{
	if (mDirty)
		genvram();

	glBindVertexArray(mVao);
}

uint32_t Mesh::iCount() const
{
	return mIndices.size();
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
	mDirty = false;
	clean();
	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);

	glGenBuffers(1, &mVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, static_cast<int32_t>(mVertices.size() * sizeof(glm::vec3)), mVertices.data(),
		GL_STATIC_DRAW);

	glGenBuffers(1, &mEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<int32_t>(mIndices.size() * sizeof(uint32_t)), mIndices.data(),
		GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	clean();
}
