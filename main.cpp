#include <glm/glm.hpp>
#include "GfxDevice.h"
#include "Camera.h"
#include "Cube.h"
#include "Scene.h"

int main(int argc, char* argv[])
{
	const auto device = std::make_shared<GfxDevice>();
	const auto ret = device->initalize();
	if (ret != 0)
	{
		return ret;
	}

	// Camera
	const auto cameraNode = std::make_shared<Node>();
	cameraNode->setLocalPosition(glm::vec3(-2, 2, -10));
	cameraNode->setLocalEulerAngles(glm::vec3(-10, 0, 0));

	const auto camera = cameraNode->addComponent<Camera>();
	camera->setAspect(640.f / 480);
	camera->setFar(1000);
	camera->setNear(1);
	camera->setFov(45);

	auto cube = Cube();

	const auto scene = std::make_shared<Scene>();
	scene->getNode()->addChild(cameraNode);

	while (!device->shouldQuit())
	{
		device->processInput();
		scene->update();

		// startDraw
		device->clearColor(glm::vec4(1, 1, 1, 1));
		cube.draw(camera);
		device->swap();
		// endDraw
	}

	device->terminate();

	return 0;
}
