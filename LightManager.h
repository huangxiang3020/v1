#pragma once
#include "Light.h"

class LightManager
{
public:
	static LightManager& instance();
	LightManager(const LightManager&) = delete;
	LightManager& operator=(const LightManager&) = delete;

	void add(const std::shared_ptr<Light>& light);
	void remove(const std::shared_ptr<Light>& light);
	std::vector<std::shared_ptr<Light>>& getLights();

private:
	LightManager() = default;
	std::vector<std::shared_ptr<Light>> mLights;
};
