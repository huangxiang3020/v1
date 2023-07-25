#include "Prefab.h"
#include "Render.h"
#include "ResourceManager.h"

void Prefab::load(std::string path)
{
	// Mesh
	const auto mesh = std::make_shared<Mesh>();
	const std::vector<glm::vec3> vertices{
		glm::vec3(-0.5f, -0.5f, -0.5f), // Vertex 0
		glm::vec3(0.5f, -0.5f, -0.5f), // Vertex 1
		glm::vec3(0.5f, 0.5f, -0.5f), // Vertex 2
		glm::vec3(-0.5f, 0.5f, -0.5f), // Vertex 3
		glm::vec3(-0.5f, -0.5f, 0.5f), // Vertex 4
		glm::vec3(0.5f, -0.5f, 0.5f), // Vertex 5
		glm::vec3(0.5f, 0.5f, 0.5f), // Vertex 6
		glm::vec3(-0.5f, 0.5f, 0.5f) // Vertex 7
	};

	const std::vector<glm::vec2> uvs{
		glm::vec2(0.0f, 0.0f), // UV for Vertex 0
		glm::vec2(1.0f, 0.0f), // UV for Vertex 1
		glm::vec2(1.0f, 1.0f), // UV for Vertex 2
		glm::vec2(0.0f, 1.0f), // UV for Vertex 3
		glm::vec2(0.0f, 0.0f), // UV for Vertex 4
		glm::vec2(1.0f, 0.0f), // UV for Vertex 5
		glm::vec2(1.0f, 1.0f), // UV for Vertex 6
		glm::vec2(0.0f, 1.0f) // UV for Vertex 7
	};

	const std::vector<uint32_t> intices{
		0, 1, 2, // Face 1
		2, 3, 0, // Face 2
		1, 5, 6, // Face 3
		6, 2, 1, // Face 4
		7, 6, 5, // Face 5
		5, 4, 7, // Face 6
		4, 0, 3, // Face 7
		3, 7, 4, // Face 8
		4, 5, 1, // Face 9
		1, 0, 4, // Face 10
		3, 2, 6, // Face 11
		6, 7, 3 // Face 12
	};
	mesh->setVertices(vertices);
	mesh->setUVs(uvs);
	mesh->setIndices(intices);

	// Shader
	const auto shader = ResourceManager::instance().load<Shader>("res/shader/vertex.vs", "res/shader/frag.fs");

	// Texture
	const auto texture = ResourceManager::instance().load<Texture>("res/image/container.jpg");

	// cube
	mRootNode = std::make_shared<Node>();
	const auto render = mRootNode->addComponent<Render>();
	render->setMesh(mesh);
	render->setShader(shader);
	render->setTexture(texture);
}

std::shared_ptr<Node> Prefab::getNode()
{
	return mRootNode;
}
