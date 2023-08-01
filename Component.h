#pragma once
#include "ObjectDefines.h"
#include "Node.h"
#include "Object.h"
class Node;

class Component : public Object
{
	REGISTER_CLASS(Component)
	friend class Node;
	Component(Node* node);
	Node* getNode() const;
	void destroy();

protected:
	virtual void awake();
	virtual void update();
	virtual void onDestroy();

private:
	void innerDestroy();
	Node* mNode;
};
