#pragma once
#include "Node.h"

class Node;

class Component
{
public:
	virtual ~Component() = default;
	Component(const std::shared_ptr<Node>& node);
	virtual void awake();
	virtual void onEnable();
	virtual void start();
	virtual void update();
	virtual void lateUpdater();
	virtual void onDisable();
	virtual void onDestroy();

	void setEnabled(bool value);
	bool getEnabled() const;
	std::shared_ptr<Node> getNode() const;

private:
	std::shared_ptr<Node> mNode;
	bool mEnabled = false;
};
