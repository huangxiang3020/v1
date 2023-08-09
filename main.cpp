#include <glm/glm.hpp>
#include "GfxDevice.h"
#include "Camera.h"
#include "Render.h"
#include "Scene.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "Light.h"
#include "ObjectManager.h"
#include "Prefab.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "TimeManger.h"
#include "Spin.h"
#include "EditorCameraController.h"
#include "TextRender.h"

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
	cameraNode->addComponent<EditorCameraController>();

	// light
	const auto lightNode = std::make_shared<Node>();
	const auto light = lightNode->addComponent<Light>();
	light->setLightColor(glm::vec4(1, 1, 1, 1));
	light->setDirection(glm::vec3(0, -1, -1));

	// pet
	const auto petPrefab = ResourceManager::instance().load<Prefab>("res/model/fbx/pet001/pet001.fbx");
	const auto petPrefabNode = petPrefab->getNode();
	petPrefabNode->setLocalEulerAngles(glm::vec3(-90, 0, 0));
	petPrefabNode->setLocalPosition(glm::vec3(0, -1, 0));
	petPrefabNode->addComponent<Spin>();

	// text
	const auto font = ResourceManager::instance().load<Font>("res/fonts/font_ssb_kt.ttf");
	font->setSize(50);

	const auto textPrefab = std::make_shared<Node>();
	const auto textRender = textPrefab->addComponent<TextRender>();
	textRender->setFont(font);
	textRender->setColor(glm::vec4(1, 1, 0, 1));
	textRender->setText("What\na\nWonderful\nPlace!");
	textPrefab->setLocalPosition(glm::vec3(1, 1, 0));
	textPrefab->setLocalScale(glm::vec3(0.01f, 0.01f, 0.01f));

	// scene
	const auto scene = std::make_shared<Scene>();
	scene->getNode()->addChild(cameraNode);
	scene->getNode()->addChild(lightNode);
	scene->getNode()->addChild(petPrefabNode);
	scene->getNode()->addChild(textPrefab);

	while (!device->shouldQuit())
	{
		InputManager::instance().processInput();
		TimeManger::instance().update();
		scene->updatePhase();

		// startDraw
		device->clearColor(glm::vec4(1, 1, 1, 1));
		for (const auto& renderCamera : CameraManager::instance().getCameras())
		{
			for (const auto& render : RenderManager::instance().getRenders())
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
