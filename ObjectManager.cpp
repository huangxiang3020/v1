#include "ObjectManager.h"

ObjectManager& ObjectManager::instance()
{
	static ObjectManager instance;
	return instance;
}

void ObjectManager::add(const std::shared_ptr<Object>& object)
{
	mObjects.push_back(object);
}

void ObjectManager::remove(const std::shared_ptr<Object>& object)
{
	for (auto it = mObjects.begin(); it != mObjects.end(); ++it)
	{
		if (*it == object)
		{
			it = mObjects.erase(it);
			if (it == mObjects.end()) break;
		}
	}
}

std::vector<std::shared_ptr<Object>>& ObjectManager::getObjects()
{
	return mObjects;
}
