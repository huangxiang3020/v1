#include "Node.h"

void Node::setParent(const std::shared_ptr<Node>& parent)
{
	if (parent == mParent)
	{
		return;
	}
	mParent->removeChild(shared_from_this());
	parent->addChild(shared_from_this());
}

void Node::addChild(const std::shared_ptr<Node>& child)
{
	mChildren.push_back(child);
	child->mParent = shared_from_this();
	child->mDirty = true;
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
	child->mParent = nullptr;
	child->mDirty = true;
}

void Node::setLocalPosition(const glm::vec3& position)
{
	mLocalPosition = position;
	mDirty = true;
}

glm::vec3 Node::getLocalPosition() const
{
	return mLocalPosition;
}

void Node::setLocalScale(const glm::vec3& scale)
{
	mLocalScale = scale;
	mDirty = true;
}

glm::vec3 Node::getLocalScale() const
{
	return mLocalScale;
}

void Node::setLocalEulerAngles(const glm::vec3& eulerAngles)
{
	mLocalRotation = glm::quat(glm::radians(eulerAngles));
	mDirty = true;
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

	if (mParent != nullptr)
	{
		for (auto it = mParent->mChildren.begin(); it != mParent->mChildren.end(); ++it)
		{
			if (*it == shared_from_this())
			{
				it = mParent->mChildren.erase(it);
				if (it == mParent->mChildren.end()) break;
			}
		}
	}
}


void Node::updateTransform()
{
	if (mParent != nullptr && mParent->mDirty)
	{
		mParent->updateTransform();
		return;
	}

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
