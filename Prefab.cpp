#include <fstream>
#include <iostream>
#include <sstream>
#include "Prefab.h"
#include "Render.h"
#include "ResourceManager.h"

void Prefab::load(const std::string& path)
{
	mRootNode = std::make_shared<Node>();

	std::ifstream fileStream(path);
	if (!fileStream.is_open())
	{
		std::cout << " Prefab::load failed" << std::endl;
		return;
	}

	std::string line;
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	std::vector<glm::vec3> modelVertices;
	std::vector<glm::vec2> modelUVs;
	std::vector<glm::vec3> modelNormals;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<uint32_t> intices;
	while (!fileStream.eof())
	{
		getline(fileStream, line);

		if (line.compare(0, 2, "v ") == 0)
		{
			std::stringstream ss(line.erase(0, 2));
			float x, y, z;
			ss >> x >> y >> z;
			modelVertices.emplace_back(x, y, z);
			uvs.emplace_back(0, 0);
			normals.emplace_back(0, 0, 0);
			continue;
		}

		if (line.compare(0, 3, "vt ") == 0)
		{
			std::stringstream ss(line.erase(0, 3));
			float u, v;
			ss >> u >> v;
			modelUVs.emplace_back(u, 1 - v);
			continue;
		}

		if (line.compare(0, 3, "vn ") == 0)
		{
			std::stringstream ss(line.erase(0, 3));
			float x, y, z;
			ss >> x >> y >> z;
			modelNormals.emplace_back(x, y, z);
			continue;
		}

		if (line.compare(0, 2, "f ") == 0)
		{
			std::stringstream ss(line.erase(0, 2));
			std::string oneCorner, v, t, n;
			for (int i = 0; i < 3; ++i)
			{
				getline(ss, oneCorner, ' ');
				std::stringstream oneCornerSS(oneCorner);
				getline(oneCornerSS, v, '/');
				getline(oneCornerSS, t, '/');
				getline(oneCornerSS, n, '/');

				int32_t vIndex = (stoi(v) - 1);
				int32_t tIndex = (stoi(t) - 1);
				int32_t nIndex = (stoi(n) - 1);

				intices.push_back(vIndex);
				uvs[vIndex] = modelUVs[tIndex];
				normals[vIndex] = modelNormals[nIndex];
			}
		}
	}

	mesh->setVertices(modelVertices);
	mesh->setUVs(uvs);
	mesh->setNormals(normals);
	mesh->setIndices(intices);

	// Shader
	const auto shader = ResourceManager::instance().load<Shader>(
		"res/shader/vertex.vs", "res/shader/frag.fs");
	// Texture
	const auto texture = ResourceManager::instance().load<Texture>("res/obj/ssylph.jpg");

	const auto render = mRootNode->addComponent<Render>();
	render->setMesh(mesh);
	render->setShader(shader);
	render->setTexture(texture);
}

std::shared_ptr<Node> Prefab::getNode()
{
	return mRootNode;
}
