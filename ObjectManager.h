#pragma once
#include <vector>
#include <memory>
#include "Object.h"
class Object;

class ObjectManager
{
	friend class Object;

public:
	static ObjectManager& instance();
	ObjectManager(const ObjectManager&) = delete;
	ObjectManager& operator=(const ObjectManager&) = delete;

	std::vector<std::shared_ptr<Object>>& getObjects();

	template <typename T>
	std::shared_ptr<T> newObject();

private:
	void add(const std::shared_ptr<Object>& object);
	void remove(const std::shared_ptr<Object>& object);
	ObjectManager() = default;
	std::vector<std::shared_ptr<Object>> mObjects;
};

template <typename T>
std::shared_ptr<T> ObjectManager::newObject()
{
	auto newObject = std::make_shared<T>();
	add(newObject);
	return newObject;
}
