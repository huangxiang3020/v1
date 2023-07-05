#include <cstdint>
#include <glm/vec4.hpp>
#include "GfxDevice.h"
#include "Camera.h"

int main(int argc, char* argv[])
{
	auto device = GfxDevice();
	const auto ret = device.initalize();
	if (ret != 0)
	{
		return ret;
	}

	// Mesh
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

	// Shader
	const auto shader = std::make_shared<Shader>("res/shader/vertex.vs", "res/shader/frag.fs");

	// Texture
	const auto texture = std::make_shared<Texture>("res/image/container.jpg");

	// Camera
	auto camera = Camera();
	camera.position = glm::vec3(0, 0, 10);
	camera.forward = glm::vec3(0, 0, 1);
	camera.up = glm::vec3(0, 1, 0);
	camera.aspect = 640.f / 480;
	camera.far = 1000;
	camera.near = 1;
	camera.fov = 45;

	auto context = DrawContext();
	context.setMesh(mesh);
	context.setShader(shader);
	context.setTexture(texture);

	while (!device.shouldQuit())
	{
		device.processInput();
		device.clearColor(glm::vec4(1, 1, 1, 1));
		device.draw(camera, context);
		device.swap();
	}

	device.terminate();

	return 0;
}
