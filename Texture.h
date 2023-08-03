#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include "Object.h"
#include "ObjectDefines.h"

class Texture : public Object
{
	REGISTER_CLASS(Texture)
	bool load(const std::string& filePath);
	bool load(int32_t width, int32_t height, int32_t channels, const void* data);
	void active(uint32_t location) const;
	~Texture() override;

private:
	uint32_t mId = 0;
	int32_t mWidth = 0;
	int32_t mHeight = 0;
	int32_t mChannels = 0;
};
