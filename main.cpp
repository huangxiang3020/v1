#include <glm/glm.hpp>
#include "GfxDevice.h"
#include "Camera.h"
#include "Render.h"
#include "Scene.h"
#include "CameraManager.h"
#include "Prefab.h"
#include "RenderManager.h"
#include "ResourceManager.h"

int main(int argc, char* argv[])
{
	const auto device = std::make_shared<GfxDevice>();
	const auto ret = device->initalize();
	if (ret != 0)
	{
		return ret;
	}

	// camera
	const auto cameraNode = std::make_shared<Node>();
	cameraNode->setLocalPosition(glm::vec3(-2, 2, -10));
	cameraNode->setLocalEulerAngles(glm::vec3(-10, 0, 0));
	const auto camera = cameraNode->addComponent<Camera>();
	camera->setAspect(640.f / 480);
	camera->setFar(1000);
	camera->setNear(1);
	camera->setFov(45);

	// cube
	const auto cubePrefab = ResourceManager::instance().load<Prefab>("111");
	const auto cubeNode = cubePrefab->getNode();
	cubeNode->setLocalPosition(glm::vec3(0, 5, 0));

	// scene
	const auto scene = std::make_shared<Scene>();
	scene->getNode()->addChild(cameraNode);
	scene->getNode()->addChild(cubeNode);

	while (!device->shouldQuit())
	{
		device->processInput();
		scene->updatePhase();

		// startDraw
		device->clearColor(glm::vec4(1, 1, 1, 1));
		for (const std::shared_ptr<Camera>& renderCamera : CameraManager::instance().getCameras())
		{
			for (const std::shared_ptr<Render>& render : RenderManager::instance().getRenders())
			{
				render->draw(renderCamera);
			}
		}
		device->swap();
		// endDraw
	}

	device->terminate();

	return 0;
}
