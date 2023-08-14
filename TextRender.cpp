#include "TextRender.h"

#include "ResourceManager.h"

void TextRender::draw(const std::shared_ptr<Camera>& camera) const
{
	const auto modelLocalToWorld = getNode()->getLocalToWorldMatrix();
	const auto cameraNode = camera->getNode();
	const auto cameraLocalToWorld = cameraNode->getLocalToWorldMatrix();

	const glm::vec3 cameraForward = glm::normalize(glm::vec3(cameraLocalToWorld[2]));
	const glm::vec3 cameraTarget = cameraNode->getPosition() - cameraForward;
	const auto view = glm::lookAt(cameraNode->getPosition(), cameraTarget,
	                              glm::normalize(glm::vec3(cameraLocalToWorld[1])));
	const auto proj = glm::perspective(camera->getFov(), camera->getAspect(), camera->getNear(), camera->getFar());
	const auto projView = proj * view;

	mShader->use();
	mShader->setMat4("_Model", modelLocalToWorld);
	mShader->setMat4("_ProjView", projView);
	mShader->setInt("_MainTex", 0);
	mShader->setVec4("_Color", mColor);
	mTexture->active(0);
	mMesh->use();
}

void TextRender::awake()
{
	Render::awake();
	mShader = ResourceManager::instance().load<Shader>(
		"res/shader/textVertex.vs", "res/shader/textFrag.fs");
}

void TextRender::onDestroy()
{
	Render::onDestroy();
}

void TextRender::setFont(const std::shared_ptr<Font>& font)
{
	mFont = font;
}

void TextRender::setText(const std::string& text)
{
	mText = text;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<uint32_t> indices;
	int32_t alignY = 0;
	int32_t alignX = 0;
	for (uint32_t i = 0; i < text.size(); ++i)
	{
		const uint8_t charCode = text[i];
		if (charCode <= 0x7f)
		{
			if (charCode == '\n')
			{
				alignY -= static_cast<int32_t>(mFont->getSize());
				alignX = 0;
				continue;
			}

			if (!addCharToMesh(charCode, alignX, alignY, vertices, uvs, indices))
			{
				break;
			}
		}
		else if (charCode >= 0xc0 && charCode <= 0xdf)
		{
			const uint32_t a = text[i] & 0x1f;
			const uint32_t b = text[i + 1] & 0x3f;
			if (!addCharToMesh((a << 6) + b, alignX, alignY, vertices, uvs, indices))
			{
				break;
			}
			i++;
		}
		else if (charCode >= 0xe0 && charCode <= 0xef)
		{
			const uint32_t a = text[i] & 0xf;
			const uint32_t b = text[i + 1] & 0x3f;
			const uint32_t c = text[i + 2] & 0x3f;
			if (!addCharToMesh((a << 12) + (b << 6) + c, alignX, alignY, vertices, uvs, indices))
			{
				break;
			}
			i += 2;
		}
		else if (charCode >= 0xf0 && charCode <= 0xf7)
		{
			const uint32_t a = text[i] & 0x7;
			const uint32_t b = text[i + 1] & 0x3f;
			const uint32_t c = text[i + 2] & 0x3f;
			const uint32_t d = text[i + 3] & 0x3f;
			if (!addCharToMesh((a << 18) + (b << 6) + (c << 6) + d, alignX, alignY, vertices, uvs, indices))
			{
				break;
			}
			i += 3;
		}
	}

	mMesh = std::make_shared<Mesh>();
	mMesh->setVertices(vertices);
	mMesh->setUVs(uvs);
	const std::vector<glm::vec3> normals;
	mMesh->setNormals(normals);
	mMesh->setIndices(indices);
	mTexture = mFont->getTexture();
}

void TextRender::setColor(const glm::vec4& color)
{
	mColor = color;
}

void TextRender::setMaxTextWidth(int32_t maxTextWidth)
{
	mMaxTextWidth = maxTextWidth;
}

bool TextRender::addCharToMesh(uint32_t charCode, int32_t& alignX, int32_t& alignY, std::vector<glm::vec3>& vertices,
                               std::vector<glm::vec2>& uvs, std::vector<uint32_t>& indices) const
{
	auto letter = Letter();
	mFont->getLetter(charCode, letter);

	if (mMaxTextWidth > 0 && alignX + letter.offsetX + letter.w >= mMaxTextWidth)
	{
		alignY -= static_cast<int32_t>(mFont->getSize());
		alignX = 0;
	}

	vertices.emplace_back(alignX + letter.offsetX, alignY + letter.offsetY, 0);
	vertices.emplace_back(alignX + letter.offsetX + letter.w, alignY + letter.offsetY, 0);
	vertices.emplace_back(alignX + letter.offsetX + letter.w, alignY + letter.offsetY + letter.h, 0);
	vertices.emplace_back(alignX + letter.offsetX, alignY + letter.offsetY + letter.h, 0);

	const auto scaleU = 1.0f / static_cast<float>(letter.texWidth);
	const auto scaleV = 1.0f / static_cast<float>(letter.texHeight);
	const auto u1 = static_cast<float>(letter.u) * scaleU;
	const auto u2 = u1 + static_cast<float>(letter.w) * scaleU;
	const auto v1 = static_cast<float>(letter.v) * scaleV;
	const auto v2 = v1 + static_cast<float>(letter.h) * scaleV;

	uvs.emplace_back(u1, v1);
	uvs.emplace_back(u2, v1);
	uvs.emplace_back(u2, v2);
	uvs.emplace_back(u1, v2);

	const auto index = static_cast<uint32_t>(indices.size()) / 6 * 4;
	indices.push_back(index + 0);
	indices.push_back(index + 1);
	indices.push_back(index + 3);
	indices.push_back(index + 1);
	indices.push_back(index + 2);
	indices.push_back(index + 3);

	alignX += letter.advance;
	return true;
}
