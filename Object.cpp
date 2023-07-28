#include "Object.h"

#include "ObjectManager.h"
int32_t Object::sNextId = 0;

Object::Object()
{
	mID = ++sNextId;
	ObjectManager::instance().add(this);
}

Object::~Object()
{
	ObjectManager::instance().remove(this);
}
