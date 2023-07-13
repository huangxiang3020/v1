#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "Cube.h"

#include "Camera.h"

Cube::Cube()
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
	const auto shader = std::make_shared<Shader>("res/shader/vertex.vs", "res/shader/frag.fs");

	// Texture
	const auto texture = std::make_shared<Texture>("res/image/container.jpg");

	mMesh = mesh;
	mShader = shader;
	mTexture = texture;
}

void Cube::draw(Camera& camera)
{
	const auto modelLocalToWorld = getLocalToWorldMatrix();
	const auto cameraLocalToWorld = camera.getLocalToWorldMatrix();

	const glm::vec3 cameraForward = glm::normalize(glm::vec3(cameraLocalToWorld[2]));
	const glm::vec3 cameraTarget = camera.getPosition() + cameraForward;
	const auto view = glm::lookAt(camera.getPosition(), cameraTarget, glm::normalize(glm::vec3(cameraLocalToWorld[1])));
	const auto proj = glm::perspective(camera.getFov(), camera.getAspect(), camera.getNear(), camera.getFar());
	const auto projView = proj * view;

	mShader->use();
	mShader->setMat4("_Model", modelLocalToWorld);
	mShader->setMat4("_ProjView", projView);
	mShader->setVec4("_Color", glm::vec4(1, 1, 0, 0));
	mShader->setInt("_MainTex", 0);
	mTexture->active(0);
	mMesh->use();
}
