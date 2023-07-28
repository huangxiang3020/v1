#pragma once
#include "Node.h"

class Scene : public Object
{
	REGISTER_CLASS(Scene)
	Scene();
	~Scene() override;
	void updatePhase() const;
	std::shared_ptr<Node> getNode();

private:
	std::shared_ptr<Node> mRoot;
};
