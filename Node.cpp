#include "Node.h"

void Node::setParent(const std::shared_ptr<Node>& parent)
{
	if (parent == mParent.lock())
	{
		return;
	}
	mParent.lock()->removeChild(shared_from_this());
	parent->addChild(shared_from_this());
}

void Node::addChild(const std::shared_ptr<Node>& child)
{
	mChildren.push_back(child);
	child->mParent = shared_from_this();
	updateTransform();
}

void Node::removeChild(const std::shared_ptr<Node>& child)
{
	for (auto it = mChildren.begin(); it != mChildren.end(); ++it)
	{
		if (*it == child)
		{
			it = mChildren.erase(it);
			if (it == mChildren.end()) break;
		}
	}
	child->mParent.reset();
	updateTransform();
}

void Node::setLocalPosition(const glm::vec3& position)
{
	mLocalPosition = position;
	updateTransform();
}

glm::vec3 Node::getLocalPosition() const
{
	return mLocalPosition;
}

void Node::setLocalScale(const glm::vec3& scale)
{
	mLocalScale = scale;
	updateTransform();
}

glm::vec3 Node::getLocalScale() const
{
	return mLocalScale;
}

void Node::setLocalEulerAngles(const glm::vec3& eulerAngles)
{
	mLocalRotation = glm::quat(glm::radians(eulerAngles));
	updateTransform();
}

glm::vec3 Node::getLocalEulerAngles() const
{
	return glm::degrees(eulerAngles(mLocalRotation));
}

void Node::setLocalRotation(const glm::quat& rotation)
{
	mLocalRotation = rotation;
	updateTransform();
}

glm::quat Node::getLocalRotation() const
{
	return mLocalRotation;
}

glm::mat4 Node::getLocalToWorldMatrix() const
{
	return mLocalToWorldMatrix;
}

glm::vec3 Node::getPosition() const
{
	return mPosition;
}

void Node::update() const
{
	for (const auto& component : mComponents)
	{
		component->update();
	}

	for (const auto& child : mChildren)
	{
		child->update();
	}
}

void Node::destroy()
{
	innerDestroy();

	if (!mParent.expired())
	{
		for (auto it = mParent.lock()->mChildren.begin(); it != mParent.lock()->mChildren.end(); ++it)
		{
			if (*it == shared_from_this())
			{
				it = mParent.lock()->mChildren.erase(it);
				if (it == mParent.lock()->mChildren.end()) break;
			}
		}
	}
}


void Node::updateTransform()
{
	const auto translation = glm::translate(glm::mat4(1.0f), mLocalPosition);
	const auto rotation = glm::mat4_cast(mLocalRotation);
	const auto scale = glm::scale(glm::mat4(1.0f), mLocalScale);
	const auto model = translation * scale * rotation;

	if (mParent.expired())
	{
		mLocalToWorldMatrix = model;
	}
	else
	{
		mLocalToWorldMatrix = mParent.lock()->mLocalToWorldMatrix * model;
	}

	mPosition = mLocalToWorldMatrix * glm::vec4(0, 0, 0, 1);

	for (const auto& child : mChildren)
	{
		child->updateTransform();
	}
}

void Node::innerDestroy() const
{
	for (const auto& child : mChildren)
	{
		child->innerDestroy();
	}

	for (const auto& component : mComponents)
	{
		component->innerDestroy();
	}
}
