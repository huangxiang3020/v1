#include "Node.h"

void Node::setParent(const std::shared_ptr<Node>& parent)
{
	mParent = parent;
}

void Node::addChild(const std::shared_ptr<Node>& child)
{
	mChildren.push_back(child);
}

void Node::setLocalPosition(const glm::vec3& position)
{
	mLocalPosition = position;
}

glm::vec3 Node::getLocalPosition() const
{
	return mLocalPosition;
}

void Node::setLocalScale(const glm::vec3& scale)
{
	mLocalScale = scale;
}

glm::vec3 Node::getLocalScale() const
{
	return mLocalScale;
}

void Node::setLocalEulerAngles(const glm::vec3& eulerAngles)
{
	mLocalRotation = glm::quat(glm::radians(eulerAngles));
}

glm::vec3 Node::getLocalEulerAngles() const
{
	return glm::degrees(eulerAngles(mLocalRotation));
}

glm::mat4 Node::getLocalToWorldMatrix()
{
	if (mDirty)
	{
		updateTransform();
	}
	return mLocalToWorldMatrix;
}

glm::vec3 Node::getPosition()
{
	if (mDirty)
	{
		updateTransform();
	}
	return mPosition;
}

void Node::updateTransform()
{
	const auto translation = glm::translate(glm::mat4(1.0f), mLocalPosition);
	const auto rotation = glm::mat4_cast(mLocalRotation);
	const auto scale = glm::scale(glm::mat4(1.0f), mLocalScale);
	const auto model = translation * scale * rotation;

	if (mParent == nullptr)
	{
		mLocalToWorldMatrix = model;
	}
	else
	{
		mLocalToWorldMatrix = mParent->mLocalToWorldMatrix * model;
	}

	mPosition = mLocalToWorldMatrix * glm::vec4(0, 0, 0, 1);
	mDirty = false;

	for (const auto& child : mChildren)
	{
		child->updateTransform();
	}
}