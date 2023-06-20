#include <glad/gl.h>
#include "GfxDevice.h"

#include <iostream>

void GfxDevice::clearColor(const glm::vec4& color) const
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GfxDevice::setVertices(const std::vector<glm::vec3>& vertices)
{
	mVertices = vertices;
}

void GfxDevice::setIndices(const std::vector<uint32_t>& indices)
{
	mIndices = indices;
}

void GfxDevice::setUVs1(const std::vector<glm::vec2>& uvs1)
{
	mUVs1 = uvs1;
}

void GfxDevice::setShader(const std::string& vertexSource, const std::string& fragmentSource)
{
	if (mShaderProgram)
	{
		glDeleteProgram(mShaderProgram);
		mShaderProgram = 0;
	}

	const char* vertexShaderSource = vertexSource.c_str();
	const char* fragmentShaderSource = fragmentSource.c_str();
	const uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	const uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, vertexShader);
	glAttachShader(mShaderProgram, fragmentShader);
	glLinkProgram(mShaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void GfxDevice::draw()
{
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

	glUseProgram(mShaderProgram);

	glDrawElements(GL_TRIANGLES, static_cast<int32_t>(mIndices.size()), GL_UNSIGNED_INT, nullptr);
	clean();
}

void GfxDevice::clean()
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

	if (mShaderProgram)
	{
		glDeleteProgram(mShaderProgram);
		mShaderProgram = 0;
	}
}

GfxDevice::~GfxDevice()
{
	clean();
}
