#pragma once
#include "Node.h"

class Scene : public Object
{
public:
	Scene();
	~Scene() override;

	ClassIDType getClassIDType() const override
	{
		return ClassID(Scene);
	}

	void updatePhase() const;
	std::shared_ptr<Node> getNode();

private:
	std::shared_ptr<Node> mRoot;
};
