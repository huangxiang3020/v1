#pragma once
#include <cstdint>
#include <string>
#include "Object.h"
#include "ObjectDefines.h"

class Texture : public Object
{
	REGISTER_CLASS(Texture)
	bool load(const std::string& filePath);
	void active(uint32_t location) const;
	~Texture() override;

private:
	uint32_t mId = 0;
	int mWidth = 0;
	int mHeight = 0;
	int mChannels = 0;
};
