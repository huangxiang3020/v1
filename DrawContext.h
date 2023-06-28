#pragma once

#include "Mesh.h"
#include "Material.h"

class DrawContext
{
public:
	void setMesh(const std::shared_ptr<Mesh>& mesh);
	void setMaterial(const std::shared_ptr<Material>& material);
	void draw() const;
private:
	std::shared_ptr<Mesh> mMesh;
	std::shared_ptr<Material> mMaterial;
};
