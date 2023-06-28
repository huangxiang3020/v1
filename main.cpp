#include <cstdint>
#include "GfxDevice.h"
#include <glm/vec4.hpp>

int main(int argc, char* argv[])
{
	auto device = GfxDevice();
	const auto ret = device.initalize();
	if (ret != 0)
	{
		return ret;
	}

	const auto mesh = std::make_shared<Mesh>();
	const std::vector<glm::vec3> vertices{
		glm::vec3(0.5f, 0.5f, 0.0f),
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(-0.5f, 0.5f, 0.0f),
	};

	const std::vector<uint32_t> intices{
		0, 1, 3,
		1, 2, 3
	};
	mesh->setVertices(vertices);
	mesh->setIndices(intices);

	const auto material = std::make_shared<Material>();
	auto context = DrawContext();
	context.setMesh(mesh);
	context.setMaterial(material);

	while (!device.shouldQuit())
	{
		device.clearColor(glm::vec4(1, 1, 1, 1));
		device.draw(context);
		device.swap();
	}

	device.terminate();

	return 0;
}
