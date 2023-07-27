#pragma once
#include "Component.h"

class Light : public Component
{
	using Component::Component;

public:
	void awake() override;
	void onDestroy() override;
	void setDirection(const glm::vec3& direction);
	glm::vec3 getDirection() const;
	void setLightColor(const glm::vec4& lightColor);
	glm::vec4 getLightColor() const;
	void setAmbientColor(const glm::vec4& ambientColor);
	glm::vec4 getAmbientColor() const;

protected:
	glm::vec3 mDirection{0, -1, 0};
	glm::vec4 mLightColor{1, 1, 1, 1};
	glm::vec4 mAmbientColor{0.1f, 0.1f, 0.1f, 1};
};
