#include "ResourceManager.h"

ResourceManager& ResourceManager::instance()
{
	static ResourceManager instance;
	return instance;
}
