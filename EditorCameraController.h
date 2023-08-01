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
	void goForward(float value) const;
	void goBack(float value) const;
	void strafeLeft(float value) const;
	void strafeRight(float value) const;
	void yaw(float value) const;
	void pitch(float value) const;
};
