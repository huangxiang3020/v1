#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include <memory>
#include "Component.h"

class Component;

class Node : public std::enable_shared_from_this<Node>
{
	friend class Component;
public:
	Node() = default;
	virtual ~Node() = default;
	void setParent(const std::shared_ptr<Node>& parent);
	void addChild(const std::shared_ptr<Node>& child);
	void setLocalPosition(const glm::vec3& position);
	glm::vec3 getLocalPosition() const;
	void setLocalScale(const glm::vec3& scale);
	glm::vec3 getLocalScale() const;
	void setLocalEulerAngles(const glm::vec3& eulerAngles);
	glm::vec3 getLocalEulerAngles() const;
	glm::mat4 getLocalToWorldMatrix();
	glm::vec3 getPosition();

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
	std::shared_ptr<Node> mParent = nullptr;
	std::vector<std::shared_ptr<Component>> mComponents = {};

private:
	bool mDirty = true;
	void updateTransform();
	void innerDestroy() const;
};

template <typename T>
std::shared_ptr<T> Node::addComponent()
{
	auto component = std::make_shared<T>(shared_from_this());
	mComponents.push_back(component);
	component->awake();
	return component;
}
