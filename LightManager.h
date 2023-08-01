#pragma once
#include "Light.h"

class LightManager
{
public:
	static LightManager& instance();
	LightManager(const LightManager&) = delete;
	LightManager& operator=(const LightManager&) = delete;

	void add(Light* light);
	void remove(Light* light);
	std::vector<Light*>& getLights();

private:
	LightManager() = default;
	std::vector<Light*> mLights;
};
