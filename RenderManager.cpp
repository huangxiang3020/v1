#include "RenderManager.h"

RenderManager& RenderManager::instance()
{
	static RenderManager instance;
	return instance;
}

void RenderManager::add(Render* render)
{
	mRenders.push_back(render);
}

void RenderManager::remove(Render* render)
{
	for (auto it = mRenders.begin(); it != mRenders.end(); ++it)
	{
		if (*it == render)
		{
			it = mRenders.erase(it);
			if (it == mRenders.end()) break;
		}
	}
}

std::vector<Render*>& RenderManager::getRenders()
{
	return mRenders;
}
