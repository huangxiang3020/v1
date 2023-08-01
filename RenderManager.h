#pragma once
#include "Render.h"

class Render;

class RenderManager
{
public:
	static RenderManager& instance();
	RenderManager(const RenderManager&) = delete;
	RenderManager& operator=(const RenderManager&) = delete;

	void add(Render* render);
	void remove(Render* render);
	std::vector<Render*>& getRenders();

private:
	RenderManager() = default;
	std::vector<Render*> mRenders;
};
