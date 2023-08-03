#include "Texture.h"
#include <glad/gl.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

bool Texture::load(const std::string& filePath)
{
	int width, height, channels;
	void* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
	if (data)
	{
		load(width, height, channels, data);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return false;
	}

	stbi_image_free(data);
	return true;
}

bool Texture::load(int32_t width, int32_t height, int32_t channels, const void* data)
{
	mWidth = width;
	mHeight = height;
	mChannels = channels;
	int32_t format;
	switch (mChannels)
	{
	case 1:
		format = GL_RED;
		break;
	case 3:
		format = GL_RGB;
		break;
	default:
		format = GL_RGBA;
		break;
	}

	glGenTextures(1, &mId);
	glBindTexture(GL_TEXTURE_2D, mId);
	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return true;
}

void Texture::active(uint32_t location) const
{
	glActiveTexture(GL_TEXTURE0 + location);
	glBindTexture(GL_TEXTURE_2D, mId);
}

Texture::~Texture()
{
	glDeleteTextures(1, &mId);
}
