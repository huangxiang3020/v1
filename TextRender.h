#pragma once
#include "Render.h"
#include "Font.h"

class TextRender : public Render
{
	REGISTER_CLASS(TextRender)
	using Render::Render;
	void draw(const std::shared_ptr<Camera>& camera) const override;
	void awake() override;
	void onDestroy() override;
	void setFont(const std::shared_ptr<Font>& font);
	void setText(const std::string& text);
	void setColor(const glm::vec4& color);

protected:
	std::shared_ptr<Font> mFont;
	std::string mText;
	glm::vec4 mColor{1, 1, 1, 1};
	bool addCharToMesh(uint32_t charCode, int32_t& alignX, int32_t& alignY, std::vector<glm::vec3>& vertices,
	                   std::vector<glm::vec2>& uvs, std::vector<uint32_t>& indices) const;
};
