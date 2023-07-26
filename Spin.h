#pragma once
#include "Component.h"

class Spin : public Component
{
public:
	Spin(const std::shared_ptr<Node>& node);
	void update() override;
};
