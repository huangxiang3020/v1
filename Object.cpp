#include "Object.h"

#include "ObjectManager.h"
int32_t Object::sNextId = 0;

Object::Object()
{
	mId = sNextId++;
}

Object::~Object()
{
}
