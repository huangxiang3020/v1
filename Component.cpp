#include "Component.h"


Component::Component(const std::shared_ptr<Node>& node)
{
	mNode = node;
}

void Component::awake()
{
}

void Component::update()
{
}

void Component::onDestroy()
{
}

std::shared_ptr<Node> Component::getNode() const
{
	return mNode.lock();
}

void Component::destroy()
{
	innerDestroy();
	const auto node = getNode();
	for (auto it = node->mComponents.begin(); it != node->mComponents.end(); ++it)
	{
		if ((*it).get() == this)
		{
			it = node->mComponents.erase(it);
			if (it == node->mComponents.end()) break;
		}
	}
}

void Component::innerDestroy()
{
	onDestroy();
}
