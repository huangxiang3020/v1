#pragma once
#include "Node.h"

class Camera : public Component
{
public:
	Camera(Node* node);

	void setNear(float near);
	float getNear() const;
	void setFar(float far);
	float getFar() const;
	void setFov(float fov);
	float getFov() const;
	void setAspect(float aspect);
	float getAspect() const;

protected:
	float mNear = 0;
	float mFar = 0;
	float mFov = 0;
	float mAspect = 0;
};
