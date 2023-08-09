#include "Font.h"
#include <iostream>
#include <unordered_map>
#include <glm/glm.hpp>

constexpr uint32_t letterTexWidth = 512;
constexpr uint32_t letterTexHeight = 512;
static uint32_t letterTexX = 0;
static uint32_t letterTexY = 0;
static uint32_t letterTexNextY = 0;
static uint32_t letterTexSpace = 1;
static uint8_t letterTex[letterTexWidth * letterTexHeight];
static std::unordered_map<uint32_t, Letter> letterDictionary;

static void addChar(const FT_GlyphSlot glyph, Letter& letter)
{
	const auto bitmap = glyph->bitmap;
	const auto width = glyph->bitmap.width;
	const auto height = glyph->bitmap.rows;

	if (letterTexX + width + letterTexSpace > letterTexWidth)
	{
		letterTexX = letterTexSpace;
		letterTexY = letterTexNextY;
	}

	if (letterTexY + height > letterTexNextY)
	{
		letterTexNextY = letterTexY + height + letterTexSpace;
	}

	if (letterTexY > letterTexHeight)
	{
		std::cout << "letterTex error: " << std::endl;
		return;
	}

	for (uint32_t i = 0; i < bitmap.rows; i++)
	{
		for (uint32_t j = 0; j < bitmap.width; j++)
		{
			const auto letterTexI = i + letterTexY;
			const auto letterTexJ = j + letterTexX;
			if (letterTexJ >= letterTexWidth || letterTexI >= letterTexHeight)
			{
				continue;
			}

			auto const bitMapIndex = (bitmap.rows - 1 - i) * bitmap.width + j;
			auto const letterTexIndex = letterTexI * letterTexWidth + letterTexJ;
			letterTex[letterTexIndex] = bitmap.buffer[bitMapIndex];
		}
	}

	const auto baseLineOffset = static_cast<uint32_t>(0.26 * letter.h);
	letter.u = static_cast<int32_t>(letterTexX);
	letter.v = static_cast<int32_t>(letterTexY);
	letter.w = static_cast<int32_t>(width);
	letter.h = static_cast<int32_t>(height);
	letter.advance = glyph->advance.x >> 6;
	letter.offsetX = glyph->bitmap_left;
	letter.offsetY = static_cast<int32_t>(baseLineOffset + (glyph->bitmap_top - height));
	letter.texWidth = letterTexWidth;
	letter.texHeight = letterTexHeight;

	letterTexX += width + letterTexSpace;
}

bool Font::load(const std::string& filePath)
{
	auto error = FT_Init_FreeType(&mLibrary);
	if (error)
	{
		std::cout << "freetype error: " << error << std::endl;
		return false;
	}

	error = FT_New_Face(mLibrary, filePath.c_str(), 0, &mFace);
	if (error)
	{
		std::cout << "freetype error: " << error << std::endl;
		return false;
	}

	error = FT_Set_Pixel_Sizes(mFace, 0, mSize);
	if (error)
	{
		std::cout << "freetype error: " << error << std::endl;
		return false;
	}

	std::memset(letterTex, 0, sizeof(letterTex));

	return true;
}

void Font::setSize(uint32_t size)
{
	if (mSize == size)
	{
		return;
	}
	mSize = size;
	const auto error = FT_Set_Pixel_Sizes(mFace, 0, mSize);
	if (error)
	{
		std::cout << "freetype error: " << error << std::endl;
	}
}

uint32_t Font::getSize() const
{
	return mSize;
}

void Font::addCharToTexture(uint32_t charCode) const
{
	if (letterDictionary.find(charCode) != letterDictionary.end())
	{
		return;
	}

	const auto error = FT_Load_Char(mFace, charCode, FT_LOAD_RENDER);
	if (error)
	{
		std::cout << "freetype error: " << error << std::endl;
		return;
	}
	auto letter = Letter();
	letter.h = static_cast<int32_t>(mSize);
	addChar(mFace->glyph, letter);
	letterDictionary[charCode] = letter;
}

std::shared_ptr<Texture> Font::getTexture() const
{
	auto texture = std::make_shared<Texture>();
	texture->load(letterTexWidth, letterTexHeight, 1, letterTex);
	return texture;
}

bool Font::getLetter(uint32_t charCode, Letter& letter) const
{
	if (letterDictionary.find(charCode) == letterDictionary.end())
	{
		addCharToTexture(charCode);
	}
	letter = letterDictionary[charCode];
	return true;
}

Font::~Font()
{
	FT_Done_Face(mFace);
	FT_Done_FreeType(mLibrary);
}
