#pragma once
#include "Component.h"

class Spin : public Component
{
	using Component::Component;
public:
	void update() override;
};
