#pragma once
#include "ObjectDefines.h"
#include "Node.h"
#include "Object.h"
class Node;

class Component : public Object, public std::enable_shared_from_this<Component>
{
	REGISTER_CLASS(Component)
	friend class Node;
	Component(const std::shared_ptr<Node>& node);
	std::shared_ptr<Node> getNode() const;
	void destroy();

protected:
	virtual void awake();
	virtual void update();
	virtual void onDestroy();

private:
	void innerDestroy();
	std::weak_ptr<Node> mNode;
};
