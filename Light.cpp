#include "Light.h"
#include "LightManager.h"

void Light::awake()
{
	LightManager::instance().add(this);
}

void Light::onDestroy()
{
	LightManager::instance().remove(this);
}

void Light::setDirection(const glm::vec3& direction)
{
	mDirection = direction;
}

glm::vec3 Light::getDirection() const
{
	return mDirection;
}

void Light::setLightColor(const glm::vec4& lightColor)
{
	mLightColor = lightColor;
}

glm::vec4 Light::getLightColor() const
{
	return mLightColor;
}

void Light::setAmbientColor(const glm::vec4& ambientColor)
{
	mAmbientColor = ambientColor;
}

glm::vec4 Light::getAmbientColor() const
{
	return mAmbientColor;
}
