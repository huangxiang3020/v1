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

	const auto shader = std::make_shared<Shader>("res/shader/vertex.vs", "res/shader/frag.fs");
	const auto texture = std::make_shared<Texture>("res/image/container.jpg");

	auto context = DrawContext();
	context.setMesh(mesh);
	context.setShader(shader);
	context.setTexture(texture);

	while (!device.shouldQuit())
	{
		device.processInput();
		device.clearColor(glm::vec4(1, 1, 1, 1));
		device.draw(context);
		device.swap();
	}

	device.terminate();

	return 0;
}
