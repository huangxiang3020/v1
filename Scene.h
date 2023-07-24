#pragma once
#include "Node.h"

class Scene
{
public:
	Scene();
	~Scene();
	void update() const;
	std::shared_ptr<Node> getNode();

private:
	std::shared_ptr<Node> mRoot;
};
