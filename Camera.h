#pragma once
#include "Node.h"
class Node;
class Camera : public Component
{
	using Component::Component;
public:
	ClassIDType getClassIDType() const override
	{
		return ClassID(Camera);
	}

	void setNear(float near);
	float getNear() const;
	void setFar(float far);
	float getFar() const;
	void setFov(float fov);
	float getFov() const;
	void setAspect(float aspect);
	float getAspect() const;

	void awake() override;
	void onDestroy() override;

protected:
	float mNear = 0;
	float mFar = 0;
	float mFov = 0;
	float mAspect = 0;
};
