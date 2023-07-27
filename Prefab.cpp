#include <iostream>
#include "Prefab.h"
#include "Render.h"
#include "ResourceManager.h"

bool Prefab::load(const std::string& path)
{
	Assimp::Importer importer;
	const auto scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (scene == nullptr)
	{
		mRootNode = std::make_shared<Node>();
		std::cout << "Prefab::load failed:" << path << std::endl;
		return false;
	}

	const std::string objDirectory = path.substr(0, path.find_last_of("/"));
	mRootNode = processAINode(scene->mRootNode, scene, objDirectory);
	return true;
}

std::shared_ptr<Node> Prefab::processAINode(const aiNode* aiNode, const aiScene* aiScene,
                                            const std::string& objDirectory) const
{
	const auto node = std::make_shared<Node>();
	for (uint32_t i = 0; i < aiNode->mNumMeshes; ++i)
	{
		const auto aiMesh = aiScene->mMeshes[aiNode->mMeshes[i]];
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
		std::vector<uint32_t> indices;
		vertices.resize(aiMesh->mNumVertices);
		normals.resize(aiMesh->mNumVertices);
		uvs.resize(aiMesh->mNumVertices);
		for (uint32_t j = 0; j < aiMesh->mNumVertices; ++j)
		{
			glm::vec3 v, n;
			glm::vec2 uv = glm::vec2(0, 0);
			v.x = aiMesh->mVertices[j].x;
			v.y = aiMesh->mVertices[j].y;
			v.z = aiMesh->mVertices[j].z;
			vertices[j] = v;

			n.x = aiMesh->mNormals[j].x;
			n.y = aiMesh->mNormals[j].y;
			n.z = aiMesh->mNormals[j].z;
			normals[j] = n;
			if (aiMesh->mTextureCoords[0])
			{
				uv.x = aiMesh->mTextureCoords[0][j].x;
				uv.y = aiMesh->mTextureCoords[0][j].y;
			}
			uvs[j] = uv;
		}

		const uint32_t faceNum = aiMesh->mNumFaces;
		indices.resize(faceNum * 3);
		for (uint32_t j = 0; j < aiMesh->mNumFaces; ++j)
		{
			const auto face = aiMesh->mFaces[j];
			for (uint32_t k = 0; k < face.mNumIndices; ++k)
			{
				indices[j * 3 + k] = face.mIndices[k];
			}
		}

		const auto mesh = std::make_shared<Mesh>();
		mesh->setVertices(vertices);
		mesh->setUVs(uvs);
		mesh->setNormals(normals);
		mesh->setIndices(indices);

		const auto aiMaterial = aiScene->mMaterials[aiMesh->mMaterialIndex];
		const auto diffuseTexturePath = getTexturePath(aiMaterial, aiTextureType_DIFFUSE);

		// Texture
		const auto texture = ResourceManager::instance().load<Texture>((objDirectory + "/").append(diffuseTexturePath));
		// Shader
		const auto shader = ResourceManager::instance().load<Shader>(
			"res/shader/vertex.vs", "res/shader/frag.fs");
		const auto meshNode = std::make_shared<Node>();
		const auto render = meshNode->addComponent<Render>();
		render->setMesh(mesh);
		render->setShader(shader);
		render->setTexture(texture);
		node->addChild(meshNode);
	}

	for (uint32_t i = 0; i < aiNode->mNumChildren; ++i)
	{
		const auto childNode = processAINode(aiNode->mChildren[i], aiScene, objDirectory);
		node->addChild(childNode);
	}

	return node;
}

std::string Prefab::getTexturePath(const aiMaterial* aiMaterial, aiTextureType aiTextureType) const
{
	for (uint32_t i = 0; i < aiMaterial->GetTextureCount(aiTextureType); ++i)
	{
		aiString str;
		aiMaterial->GetTexture(aiTextureType_DIFFUSE, i, &str);
		return str.C_Str();
	}
	return "";
}

std::shared_ptr<Node> Prefab::getNode()
{
	return mRootNode;
}
