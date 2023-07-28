#include <iostream>
#include <glm/glm.hpp>
#include "GfxDevice.h"
#include "Camera.h"
#include "Render.h"
#include "Scene.h"
#include "CameraManager.h"
#include "Light.h"
#include "ObjectManager.h"
#include "Prefab.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Spin.h"

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
	cameraNode->setLocalPosition(glm::vec3(0, 0, 5));
	const auto camera = cameraNode->addComponent<Camera>();
	camera->setAspect(1280.f / 720);
	camera->setFar(1000);
	camera->setNear(1);
	camera->setFov(45);

	// light
	const auto lightNode = std::make_shared<Node>();
	const auto light = lightNode->addComponent<Light>();
	light->setLightColor(glm::vec4(1, 1, 1, 1));
	light->setDirection(glm::vec3(0, -1, -1));

	// pet
	const auto petPrefab = ResourceManager::instance().load<Prefab>("res/model/fbx/pet004/pet004.fbx");
	const auto petPrefabNode = petPrefab->getNode();
	petPrefabNode->setLocalEulerAngles(glm::vec3(-90, 0, 0));
	petPrefabNode->setLocalPosition(glm::vec3(0, -1, 0));
	petPrefabNode->addComponent<Spin>();

	// scene
	const auto scene = std::make_shared<Scene>();
	scene->getNode()->addChild(cameraNode);
	scene->getNode()->addChild(petPrefabNode);

	// for (const auto object : ObjectManager::instance().getObjects())
	// {
	// 	std::cout << object->getClassIDType() << std::endl;
	// }

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
