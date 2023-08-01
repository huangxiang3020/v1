#include "Camera.h"
#include "CameraManager.h"

void Camera::setNear(float near)
{
	mNear = near;
}

float Camera::getNear() const
{
	return mNear;
}

void Camera::setFar(float far)
{
	mFar = far;
}

float Camera::getFar() const
{
	return mFar;
}

void Camera::setFov(float fov)
{
	mFov = fov;
}

float Camera::getFov() const
{
	return mFov;
}

void Camera::setAspect(float aspect)
{
	mAspect = aspect;
}

float Camera::getAspect() const
{
	return mAspect;
}

void Camera::awake()
{
	CameraManager::instance().add(this);
}

void Camera::onDestroy()
{
	CameraManager::instance().remove(this);
}
