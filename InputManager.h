#pragma once
#include <glm/glm.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

class InputManager
{
public:
	static InputManager& instance();
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	glm::vec2 getMousePosition() const;
	bool getKeyDown(int32_t keyCode) const;
	void setWindow(GLFWwindow* window);

private:
	InputManager() = default;
	GLFWwindow* mWindow = nullptr;
};
