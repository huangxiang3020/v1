#pragma once
#include <vector>
#include "Object.h"
class Object;

class ObjectManager
{
	friend class Object;

public:
	static ObjectManager& instance();
	ObjectManager(const ObjectManager&) = delete;
	ObjectManager& operator=(const ObjectManager&) = delete;

	std::vector<Object*>& getObjects();

private:
	void add(Object* object);
	void remove(const Object* object);
	ObjectManager() = default;
	std::vector<Object*> mObjects;
};
