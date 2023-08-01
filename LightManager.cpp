#include "LightManager.h"

LightManager& LightManager::instance()
{
	static LightManager instance;
	return instance;
}

void LightManager::add(const std::shared_ptr<Light>& light)
{
	mLights.push_back(light);
}

void LightManager::remove(const std::shared_ptr<Light>& light)
{
	for (auto it = mLights.begin(); it != mLights.end(); ++it)
	{
		if (*it == light)
		{
			it = mLights.erase(it);
			if (it == mLights.end()) break;
		}
	}
}

std::vector<std::shared_ptr<Light>>& LightManager::getLights()
{
	return mLights;
}
