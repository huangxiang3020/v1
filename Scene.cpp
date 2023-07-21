#include "Scene.h"

Scene::Scene()
{
	mRoot = std::make_shared<Node>();
}

void Scene::update() const
{
	mRoot->update();
}

std::shared_ptr<Node> Scene::getNode()
{
	return mRoot;
}


