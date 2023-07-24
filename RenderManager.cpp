#include "RenderManager.h"

RenderManager& RenderManager::instance()
{
	static RenderManager instance;
	return instance;
}

void RenderManager::add(const std::shared_ptr<Render>& render)
{
	mRenders.push_back(render);
}

void RenderManager::remove(const std::shared_ptr<Render>& render)
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

std::vector<std::shared_ptr<Render>>& RenderManager::getRenders()
{
	return mRenders;
}
