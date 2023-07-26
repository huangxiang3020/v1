#pragma once
#include <string>
#include "Node.h"

class Prefab
{
public:
	Prefab() = default;
	void load(const std::string& path);
	std::shared_ptr<Node> getNode();

private:
	std::shared_ptr<Node> mRootNode;
};