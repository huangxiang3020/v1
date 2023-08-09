#pragma once
#include <ft2build.h>
#include <memory>

#include FT_FREETYPE_H
#include "Object.h"
#include "ObjectDefines.h"
#include "Texture.h"

struct Letter
{
	int32_t u;
	int32_t v;
	int32_t w;
	int32_t h;
	int32_t advance;
	int32_t offsetX;
	int32_t offsetY;
	int32_t texWidth;
	int32_t texHeight;
};

class Font : public Object
{
	REGISTER_CLASS(Font)
	bool load(const std::string& filePath);
	void setSize(uint32_t size);
	uint32_t getSize() const;
	void addCharToTexture(uint32_t charCode) const;
	std::shared_ptr<Texture> getTexture() const;
	bool getLetter(uint32_t charCode, Letter& letter) const;
	~Font() override;

private:
	FT_Library mLibrary = nullptr;
	FT_Face mFace = nullptr;
	uint32_t mSize = 24;
};
