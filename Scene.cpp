#include "Scene.h"

Scene::Scene()
{
	mRoot = std::make_shared<Node>();
}

Scene::~Scene()
{
	mRoot->destroy();
}

void Scene::updatePhase() const
{
	mRoot->update();
}

std::shared_ptr<Node> Scene::getNode()
{
	return mRoot;
}


