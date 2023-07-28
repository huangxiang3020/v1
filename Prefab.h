#pragma once
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Node.h"

class Prefab : public Object
{
public:
	ClassIDType getClassIDType() const override
	{
		return ClassID(Node);
	}
	bool load(const std::string& path);
	std::shared_ptr<Node> getNode();

private:
	std::shared_ptr<Node> mRootNode;
	std::shared_ptr<Node> processAINode(const aiNode* aiNode, const aiScene* aiScene,
	                                    const std::string& objDirectory) const;
	std::string getTexturePath(const aiMaterial* aiMaterial, aiTextureType aiTextureType) const;
};
