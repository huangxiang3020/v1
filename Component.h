#pragma once
#include "Node.h"
#include "Object.h"

class Node;

class Component : public Object, public std::enable_shared_from_this<Component>
{
	friend class Node;

public:
	virtual ~Component() = default;
	Component(const std::shared_ptr<Node>& node);
	std::shared_ptr<Node> getNode() const;
	void destroy();

protected:
	virtual void awake();
	virtual void update();
	virtual void onDestroy();

private:
	void innerDestroy();
	std::shared_ptr<Node> mNode;
};
