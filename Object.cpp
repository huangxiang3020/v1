#include "Object.h"

#include "ObjectManager.h"
int32_t Object::sNextId = 0;

Object::Object()
{
	mId = ++sNextId;
	ObjectManager::instance().add(this);
}

Object::~Object()
{
	ObjectManager::instance().remove(this);
}

int32_t Object::getNextId()
{
	return sNextId;
}
