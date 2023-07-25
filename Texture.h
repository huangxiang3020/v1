#pragma once
#include <cstdint>
#include <string>

class Texture
{
public:
	Texture() = default;
	auto load(const std::string& filePath) -> void;
	void active(uint32_t location) const;
	~Texture();

private:
	uint32_t mId = 0;
	int mWidth = 0;
	int mHeight = 0;
	int mChannels = 0;

};

