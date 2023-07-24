#pragma once
#include "Render.h"

class Render;

class RenderManager
{
public:
	static RenderManager& instance();
	RenderManager(const RenderManager&) = delete;
	RenderManager& operator=(const RenderManager&) = delete;

	void add(const std::shared_ptr<Render>& render);
	void remove(const std::shared_ptr<Render>& render);
	std::vector<std::shared_ptr<Render>>& getRenders();

private:
	RenderManager() = default;
	std::vector<std::shared_ptr<Render>> mRenders;
};
