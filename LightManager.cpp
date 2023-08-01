#include "LightManager.h"

LightManager& LightManager::instance()
{
	static LightManager instance;
	return instance;
}

void LightManager::add(Light* light)
{
	mLights.push_back(light);
}

void LightManager::remove(Light* light)
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

std::vector<Light*>& LightManager::getLights()
{
	return mLights;
}
