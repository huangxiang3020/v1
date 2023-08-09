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
	for (const char charCode : text)
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

bool TextRender::addCharToMesh(uint32_t charCode, int32_t& alignX, int32_t& alignY, std::vector<glm::vec3>& vertices,
                               std::vector<glm::vec2>& uvs, std::vector<uint32_t>& indices) const
{
	auto letter = Letter();
	mFont->getLetter(charCode, letter);

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
