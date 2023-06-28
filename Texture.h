#pragma once
#include <cstdint>
#include <string>
#include <glm/vec4.hpp>

class Texture
{
public:
	Texture(const std::string& filePath);
	void active(uint32_t location) const;

private:
	uint32_t mId = 0;
	int mWidth = 0;
	int mHeight = 0;
	int mChannels = 0;

};

