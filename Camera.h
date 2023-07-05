#pragma once
#include <glm/vec3.hpp>

class Camera
{
public:
	Camera() = default;

	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;

	float near;
	float far;
	float fov;
	float aspect;
};
