#include "Component.h"


Component::Component(const std::shared_ptr<Node>& node)
{
	mNode = node;
}

void Component::awake()
{
}

void Component::onEnable()
{
}

void Component::start()
{
}

void Component::update()
{
}

void Component::lateUpdater()
{
}

void Component::onDisable()
{
}

void Component::onDestroy()
{
}

void Component::setEnabled(bool value)
{
	mEnabled = value;
}

bool Component::getEnabled() const
{
	return mEnabled;
}

std::shared_ptr<Node> Component::getNode() const
{
	return mNode;
}
