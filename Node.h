#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include <memory>
#include "ObjectDefines.h"
#include "Component.h"
#include "Object.h"

class Component;

class Node : public Object, public std::enable_shared_from_this<Node>
{
	REGISTER_CLASS(Node)
	friend class Component;
	void setParent(const std::shared_ptr<Node>& parent);
	void addChild(const std::shared_ptr<Node>& child);
	void removeChild(const std::shared_ptr<Node>& child);
	void setLocalPosition(const glm::vec3& position);
	glm::vec3 getLocalPosition() const;
	void setLocalScale(const glm::vec3& scale);
	glm::vec3 getLocalScale() const;
	void setLocalEulerAngles(const glm::vec3& eulerAngles);
	glm::vec3 getLocalEulerAngles() const;
	void setLocalRotation(const glm::quat& rotation);
	glm::quat getLocalRotation() const;
	glm::mat4 getLocalToWorldMatrix() const;
	glm::vec3 getPosition() const;

	template <typename T>
	std::shared_ptr<T> addComponent();

	void update() const;
	void destroy();

protected:
	glm::vec3 mLocalPosition{0, 0, 0};
	glm::quat mLocalRotation = {1, 0, 0, 0};
	glm::vec3 mLocalScale{1, 1, 1};
	glm::mat4 mLocalToWorldMatrix{};
	glm::vec3 mPosition = {0, 0, 0};
	std::vector<std::shared_ptr<Node>> mChildren = {};
	std::weak_ptr<Node> mParent;
	std::vector<std::shared_ptr<Component>> mComponents = {};

private:
	void updateTransform();
	void innerDestroy() const;
};

template <typename T>
std::shared_ptr<T> Node::addComponent()
{
	auto component = std::make_shared<T>(this);
	mComponents.push_back(component);

	component->awake();
	return component;
}
