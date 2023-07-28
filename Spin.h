#pragma once
#include "Component.h"

class Spin : public Component
{
	REGISTER_CLASS(Spin)
	using Component::Component;
	void update() override;
};
