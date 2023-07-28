#pragma once
#include "Component.h"

class Spin : public Component
{
	using Component::Component;
public:
	ClassIDType getClassIDType() const override
	{
		return ClassID(Spin);
	}
	void update() override;
};
