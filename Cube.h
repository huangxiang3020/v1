#pragma once
#include <memory>
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Node.h"

class Node;
class Camera;
class Cube : public Node
{
public:
	Cube();
	~Cube() override = default;
	void draw(Camera& camera) ;

private:
	std::shared_ptr<Mesh> mMesh;
	std::shared_ptr<Shader> mShader;
	std::shared_ptr<Texture> mTexture;
};

