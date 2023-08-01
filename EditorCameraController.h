#pragma once
#include "Component.h"

class EditorCameraController : public Component
{
	REGISTER_CLASS(EditorCameraController)
	using Component::Component;
	void update() override;

private:
	bool mFreeMode = false;
	glm::vec2 mLastMousePosition = {};
};

