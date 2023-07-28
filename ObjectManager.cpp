#include "ObjectManager.h"

ObjectManager& ObjectManager::instance()
{
	static ObjectManager instance;
	return instance;
}

void ObjectManager::add(Object* object)
{
	mObjects.push_back(object);
}

void ObjectManager::remove(const Object* object)
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

std::vector<Object*>& ObjectManager::getObjects()
{
	return mObjects;
}
