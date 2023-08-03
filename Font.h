#pragma once
#include <ft2build.h>
#include <memory>

#include FT_FREETYPE_H
#include "Object.h"
#include "ObjectDefines.h"
#include "Texture.h"

class Font : public Object
{
	REGISTER_CLASS(Font)
	bool load(const std::string& filePath);
	void setSize(uint32_t size);
	void addCharToTexture(uint32_t charCode) const;
	std::shared_ptr<Texture> getTexture() const;
	~Font() override;

private:
	FT_Library mLibrary = nullptr;
	FT_Face mFace = nullptr;
	uint32_t mSize = 24;
};
