#pragma once
#include "Node.h"

class Node;

class Component
{
public:
	virtual ~Component() = default;
	Component(Node* node);
	virtual void awake();
	virtual void onEnable();
	virtual void start();
	virtual void update();
	virtual void lateUpdater();
	virtual void onDisable();
	virtual void onDestroy();

	void setEnabled(bool value);
	bool getEnabled() const;
	Node* getNode() const;

private:
	Node* mNode;
	bool mEnabled = false;
};
