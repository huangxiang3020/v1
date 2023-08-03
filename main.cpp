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
#include "Font.h"

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

	// image
	const std::vector<glm::vec3> vertices =
	{
		{0, 0, 0},
		{1, 0, 0},
		{1, 1, 0},
		{0, 1, 0},
	};
	const std::vector<glm::vec2> uvs = {
		{0, 0},
		{1, 0},
		{1, 1},
		{0, 1},
	};
	const std::vector<glm::vec3> normals =
	{
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
	};
	const std::vector<uint32_t> indices = {
		0, 1, 3,
		1, 2, 3,
	};
	const auto imageMesh = std::make_shared<Mesh>();
	imageMesh->setVertices(vertices);
	imageMesh->setUVs(uvs);
	imageMesh->setNormals(normals);
	imageMesh->setIndices(indices);
	const auto font = ResourceManager::instance().load<Font>("res/fonts/segoe_slboot.ttf");
	font->setSize(150);
	font->addCharToTexture('A');
	font->addCharToTexture('B');
	font->addCharToTexture('C');
	for (int i = 0; i < 20; i++)
	{
		font->addCharToTexture(i + 0x48);
	}
	const auto fontTexture = font->getTexture();
	// Shader
	const auto shader = ResourceManager::instance().load<Shader>(
		"res/shader/vertex.vs", "res/shader/frag.fs");
	const auto imagePrefab = std::make_shared<Node>();
	imagePrefab->setLocalPosition(glm::vec3(1, 0, 0));
	const auto render = imagePrefab->addComponent<Render>();
	render->setMesh(imageMesh);
	render->setShader(shader);
	render->setTexture(fontTexture);

	// scene
	const auto scene = std::make_shared<Scene>();
	scene->getNode()->addChild(cameraNode);
	scene->getNode()->addChild(lightNode);
	scene->getNode()->addChild(petPrefabNode);
	scene->getNode()->addChild(imagePrefab);

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
