#pragma once
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <vector>

class GfxDevice
{
public:
	void clearColor(const glm::vec4& color) const;

	void setVertices(const std::vector<glm::vec3>& vertices);

	void setIndices(const std::vector<uint32_t>& indices);

	void draw() const;

private:
	std::vector<glm::vec3> mVertices;
	std::vector<uint32_t> mIndices;
};
